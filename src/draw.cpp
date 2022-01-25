// Written by Aaron Barge
// Copyright 2022

#include "draw.hpp"

#define RESOLUTION (1000u)
#define DELTA_THETA (M_PI * 2.0 / RESOLUTION)

namespace {

uint32_t gcd(uint32_t a, uint32_t b) {
    return b == 0 ? a : gcd(b, a % b);
}

void update_pos(Magick::Coordinate& drawing_pos, const Magick::Coordinate& static_pos,
        const double& theta_rolling, const double& orbit_rolling_ratio,
        const double& orbit_radius, const double& drawing_radius) {
    double theta_drawing = theta_rolling * orbit_rolling_ratio;
    drawing_pos.x(static_pos.x() + atn::x_offset(orbit_radius, theta_rolling));
    drawing_pos.y(static_pos.y() + atn::y_offset(orbit_radius, theta_rolling));
    drawing_pos.x(drawing_pos.x() + atn::x_offset(drawing_radius, theta_drawing));
    drawing_pos.y(drawing_pos.y() + atn::y_offset(drawing_radius, theta_drawing));
}

void draw(
        Magick::Image& image, const double& rolling_radius,
        const double& orbit_radius, const double& drawing_radius,
        const double& orbit_rolling_ratio) {
    double theta_rolling = 0.0;
    const Magick::Coordinate static_pos(
            image.columns() >> 1, image.rows() >> 1);
    Magick::Coordinate drawing_pos;
    uint32_t revolutions = rolling_radius / gcd(orbit_radius, rolling_radius);
    std::cout <<  "Revolutions: " << revolutions << std::endl;
    Magick::CoordinateList points;
    for (size_t i = 0; i < revolutions * RESOLUTION + 1; ++i) {
        theta_rolling = i * DELTA_THETA;
        update_pos(
                drawing_pos, static_pos, theta_rolling,
                orbit_rolling_ratio, orbit_radius, drawing_radius);
        points.push_back(drawing_pos);
    }
    image.draw(Magick::DrawablePolyline(points));
}

} // End Anonymous namespace

Magick::Image atn::image_context(
        std::string dimension, std::string background_color, 
        std::string stroke_color, uint16_t stroke_width) {
    Magick::Image image(dimension, background_color);
    image.strokeColor(stroke_color);
    image.strokeWidth(stroke_width);
    image.fillColor(background_color);
    return image;
}

double atn::x_offset(double r, double theta) {
    return r * std::sin(theta);
}

double atn::y_offset(double r, double theta) {
    return r * std::cos(theta);
}

void atn::draw_outside(
        Magick::Image& image, uint16_t static_radius,
        uint16_t rolling_radius, uint16_t drawing_radius) {
    const double orbit_radius = static_radius + rolling_radius;
    draw(image, rolling_radius, orbit_radius, double(drawing_radius), orbit_radius / rolling_radius);
}

void atn::draw_inside(
        Magick::Image& image, uint16_t static_radius,
        uint16_t rolling_radius, uint16_t drawing_radius) {
    const double orbit_radius = static_radius - rolling_radius;
    draw(image, rolling_radius, orbit_radius, double(drawing_radius), -orbit_radius / rolling_radius);
}
