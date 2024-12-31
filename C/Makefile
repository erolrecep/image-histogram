CC = gcc
CFLAGS = -Wall -Wextra -I./src
LDFLAGS = -lm

SRC_DIR = src
OBJ_DIR = obj

SRCS = $(wildcard $(SRC_DIR)/*.c) main.c
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

TARGET = main

.PHONY: all clean run plot

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

run: $(TARGET)
	./$(TARGET) images/cats.jpg

plot: gnuplot gnuplot_scripts/image-red_channel_histogram.gnu gnuplot_scripts/image-green_channel_histogram.gnu gnuplot_scripts/image-blue_channel_histogram.gnu gnuplot_scripts/image-grayscale_histogram.gnu
	gnuplot gnuplot_scripts/image-red_channel_histogram.gnu
	gnuplot gnuplot_scripts/image-green_channel_histogram.gnu
	gnuplot gnuplot_scripts/image-blue_channel_histogram.gnu
	gnuplot gnuplot_scripts/image-grayscale_histogram.gnu

clean:
	rm -rf $(OBJ_DIR) $(TARGET)
	rm -rf output/*

gnuplot: 
	which gnuplot || (echo "gnuplot not found"; exit 1)
