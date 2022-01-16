// Written by Aaron Barge
// Copyright 2022

#ifndef _SPIROGRAPH_SRC_DRAW_HPP_
#define _SPIROGRAPH_SRC_DRAW_HPP_

#include <Magick++.h>
#include <cmath>
#include <list>
#include <iostream>
#include <vector>

namespace atn {

// Sets parameters of image for drawing
Magick::Image image_context(
        std::string dimension, std::string background_color, 
        std::string stroke_color, uint16_t stroke_width);

// Finds x-offset from polar coordinate
double x_offset(double r, double theta);

// Finds y-offset from polar coordinate
double y_offset(double r, double theta);

// Draws Spirograph as a gear rotating on the outside of a gear
void draw_outside(
        Magick::Image& image, uint16_t radius_static,
        uint16_t radius_rolling, uint16_t radius_drawing);

// Draws Spirograph as a gear rotating on the inside of a gear
void draw_inside(
        Magick::Image& image, uint16_t radius_static,
        uint16_t radius_rolling, uint16_t radius_drawing);

} // End namespace atn

#endif // _SPIROGRAPH_SRC_DRAW_HPP_
