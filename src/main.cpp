// Written by Aaron Barge
// Copyright 2022

#include <Magick++.h>
#include <chrono>
#include <iostream>
#include <string>

#include "draw.hpp"

int main(int argc, char** argv) {
    // argv[0] = main
    // argv[1] = string background_color
    // argv[2] = string image_dimensions
    // argv[3] = string color
    // argv[4] = int    stroke_width
    // argv[5] = int    radius_1
    // argv[6] = int    radius_2
    // argv[7] = int    radius_3
    // argv[8] = bool   outside
    // argv[9] = string output_file
    if (argc != 10) {
        std::cerr << "ERROR: must be run as:" << std::endl;
        std::cerr << "./main `background_color` `width`x`height` `color` `stroke_width` `radius_1` `radius_2` `radius_3` `outside` `output_file`" << std::endl;
        return -1;
    }

    // Start timing draw function
    auto start = std::chrono::high_resolution_clock::now();

    // Process command line inputs
    std::string background_color = argv[1];
    std::string dimensions = argv[2];
    std::string color = argv[3];
    uint16_t stroke_width = std::stoi(argv[4]);
    uint16_t static_radius = std::stoi(argv[5]);
    uint16_t rolling_radius = std::stoi(argv[6]);
    uint16_t drawing_radius = std::stoi(argv[7]);
    bool outside = std::stoi(argv[8]) != 0;
    std::string output_file = argv[9];

    // Instantiate Drawing Area
    Magick::InitializeMagick(*argv);
    Magick::Image image = atn::image_context(dimensions, background_color, color, stroke_width);

    // Draw Spirograph
    if (outside) {
        atn::draw_outside(image, static_radius, rolling_radius, drawing_radius);
    } else {
        atn::draw_inside(image, static_radius, rolling_radius, drawing_radius);
    }

    // End timing draw function
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // Print timing result
    std::cout << "Time elapsed: " << duration.count() << "ms" << std::endl;

    // Save image to file
    image.write(output_file);
    return 0;
}
