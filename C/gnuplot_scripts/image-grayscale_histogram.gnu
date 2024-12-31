# Histogram Settings
set terminal png size 800,600
set output 'output/image_grayscale_hist.png'

set style data histograms
set style fill solid border -1
set boxwidth 0.9
set xlabel "Pixel Intensity (0-255)"
set ylabel "Frequency"
set title "Red Channel Histogram"

set xrange [0:255]
set yrange [0:*]

plot 'output/image_gray_hist.txt' using 1:2 with boxes lc rgb "red" title "Red Channel"
