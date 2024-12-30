package main

import (
	"bytes"
	"encoding/base64"
	"fmt"
	"image"
	"image/color"
	"image/png"
	"net/http"
	"os"
	"strings"

	"gonum.org/v1/plot"
	"gonum.org/v1/plot/plotter"
	"gonum.org/v1/plot/vg"
)

// LoadImage loads an image from a file path.
func LoadImage(filePath string) (image.Image, error) {
	file, err := os.Open(filePath)
	if err != nil {
		return nil, err
	}
	defer file.Close()
	img, _, err := image.Decode(file)
	if err != nil {
		return nil, err
	}
	return img, nil
}

// SplitChannels splits an image into R, G, B channels.
func SplitChannels(img image.Image) ([][]uint8, [][]uint8, [][]uint8) {
	bounds := img.Bounds()
	width, height := bounds.Max.X, bounds.Max.Y
	R := make([][]uint8, height)
	G := make([][]uint8, height)
	B := make([][]uint8, height)
	for y := 0; y < height; y++ {
		R[y] = make([]uint8, width)
		G[y] = make([]uint8, width)
		B[y] = make([]uint8, width)
		for x := 0; x < width; x++ {
			r, g, b, _ := img.At(x, y).RGBA()
			R[y][x] = uint8(r >> 8)
			G[y][x] = uint8(g >> 8)
			B[y][x] = uint8(b >> 8)
		}
	}
	return R, G, B
}

// Convert RGB image to grayscale
func ConvertToGrayscale(img image.Image) image.Image {
	bounds := img.Bounds()
	width, height := bounds.Max.X, bounds.Max.Y
	grayImg := image.NewGray(bounds)
	for y := 0; y < height; y++ {
		for x := 0; x < width; x++ {
			r, g, b, _ := img.At(x, y).RGBA()
			// Convert to grayscale using the formula: Y = 0.299*R + 0.587*G + 0.114*B
			// This conversion sometimes give values > 255
			// gray := uint8(0.299*float64(r) + 0.587*float64(g) + 0.114*float64(b)) // This conversion is not normalizing the values
			gray := uint8((0.299*float64(r) + 0.587*float64(g) + 0.114*float64(b)) / 256)
			grayImg.SetGray(x, y, color.Gray{Y: gray})
		}
	}
	return grayImg
}

// CalculateHistogram calculates the histogram of a single channel.
func CalculateHistogram(channel [][]uint8) plotter.Values {
	hist := make(plotter.Values, 256)
	for _, row := range channel {
		for _, value := range row {
			hist[value]++
		}
	}
	return hist
}

// EqualizeHistogram applies histogram equalization to a grayscale image.
func EqualizeHistogram(img *image.Gray) *image.Gray {
	bounds := img.Bounds()
	hist := make([]int, 256)
	cdf := make([]int, 256)
	totalPixels := (bounds.Max.X - bounds.Min.X) * (bounds.Max.Y - bounds.Min.Y)

	// Compute histogram
	for y := bounds.Min.Y; y < bounds.Max.Y; y++ {
		for x := bounds.Min.X; x < bounds.Max.X; x++ {
			gray := img.GrayAt(x, y).Y
			hist[gray]++
		}
	}

	// Compute cumulative distribution function (CDF)
	cdf[0] = hist[0]
	for i := 1; i < 256; i++ {
		cdf[i] = cdf[i-1] + hist[i]
	}

	// Normalize CDF to map intensity values
	lut := make([]uint8, 256)
	for i := 0; i < 256; i++ {
		lut[i] = uint8((float64(cdf[i]) / float64(totalPixels)) * 255.0)
	}

	// Apply equalization
	equalizedImg := image.NewGray(bounds)
	for y := bounds.Min.Y; y < bounds.Max.Y; y++ {
		for x := bounds.Min.X; x < bounds.Max.X; x++ {
			gray := img.GrayAt(x, y).Y
			equalizedImg.SetGray(x, y, color.Gray{Y: lut[gray]})
		}
	}
	return equalizedImg
}

// PlotHistogram generates a histogram plot for a channel.
func PlotHistogram(hist plotter.Values, color string, title string) ([]byte, error) {
	p := plot.New()
	p.Title.Text = title
	bar, err := plotter.NewBarChart(hist, vg.Points(5))
	if err != nil {
		return nil, err
	}
	bar.Color = stringToColor(color)
	p.Add(bar)

	// Create a writer for PNG format
	w, err := p.WriterTo(vg.Length(300), vg.Length(200), "png")
	if err != nil {
		return nil, err
	}

	// Write to a buffer
	buf := new(bytes.Buffer)
	_, err = w.WriteTo(buf)
	if err != nil {
		return nil, err
	}

	return buf.Bytes(), nil
}

// imageToSlice converts a grayscale image to a 2D slice of uint8
func imageToSlice(img image.Image) [][]uint8 {
	bounds := img.Bounds()
	width, height := bounds.Max.X, bounds.Max.Y
	slice := make([][]uint8, height)
	for y := 0; y < height; y++ {
		slice[y] = make([]uint8, width)
		for x := 0; x < width; x++ {
			gray, _, _, _ := img.At(x, y).RGBA()
			slice[y][x] = uint8(gray >> 8)
		}
	}
	return slice
}

func main() {
	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		imgPath := "images/cats.jpg" // Replace with your image path
		img, err := LoadImage(imgPath)
		if err != nil {
			http.Error(w, "Error loading image", http.StatusInternalServerError)
			return
		}

		// Convert to grayscale
		grayImg := ConvertToGrayscale(img)

		// Apply histogram equalization
		equalizedImg := EqualizeHistogram(grayImg.(*image.Gray))

		R, G, B := SplitChannels(img)
		// Prepare histogram plots
		redHist := CalculateHistogram(R)
		greenHist := CalculateHistogram(G)
		blueHist := CalculateHistogram(B)
		grayHist := CalculateHistogram(imageToSlice(grayImg))
		equalizedHist := CalculateHistogram(imageToSlice(equalizedImg))

		redPlot, _ := PlotHistogram(redHist, "red", "Red Channel Histogram")
		greenPlot, _ := PlotHistogram(greenHist, "green", "Green Channel Histogram")
		bluePlot, _ := PlotHistogram(blueHist, "blue", "Blue Channel Histogram")
		grayPlot, _ := PlotHistogram(grayHist, "gray", "Grayscale Histogram")
		equalizedPlot, _ := PlotHistogram(equalizedHist, "black", "Equalized Histogram")

		// Render HTML
		w.Write([]byte(`<html><body>
			<h1>Original Image</h1>
			<img src='data:image/png;base64,` + base64.StdEncoding.EncodeToString(imgToBytes(img)) + `'/>
			<h1>Grayscale Image</h1>
			<img src='data:image/png;base64,` + base64.StdEncoding.EncodeToString(imgToBytes(grayImg)) + `'/>
			<h1>Equalized Image</h1>
			<img src='data:image/png;base64,` + base64.StdEncoding.EncodeToString(imgToBytes(equalizedImg)) + `'/>
			<h2>Histograms</h2>
			<img src='data:image/png;base64,` + base64.StdEncoding.EncodeToString(redPlot) + `'/>
			<img src='data:image/png;base64,` + base64.StdEncoding.EncodeToString(greenPlot) + `'/>
			<img src='data:image/png;base64,` + base64.StdEncoding.EncodeToString(bluePlot) + `'/>
			<img src='data:image/png;base64,` + base64.StdEncoding.EncodeToString(grayPlot) + `'/>
			<img src='data:image/png;base64,` + base64.StdEncoding.EncodeToString(equalizedPlot) + `'/>
		</body></html>`))
	})

	fmt.Println("Server is running on http://localhost:8080")
	err := http.ListenAndServe(":8080", nil)
	if err != nil {
		fmt.Printf("Error starting server: %s\n", err)
		os.Exit(1)
	}
}

// Helper function to convert image to bytes
func imgToBytes(img image.Image) []byte {
	buf := new(bytes.Buffer)
	png.Encode(buf, img)
	return buf.Bytes()
}

// Add this function to convert string color names to color.Color
func stringToColor(s string) color.Color {
	s = strings.ToLower(s)
	switch s {
	case "red":
		return color.RGBA{255, 0, 0, 255}
	case "green":
		return color.RGBA{0, 255, 0, 255}
	case "blue":
		return color.RGBA{0, 0, 255, 255}
	default:
		return color.Black
	}
}
