#pragma once
#include <Arduino.h>

class Color {
public:
    uint8_t r, g, b;

    constexpr Color(uint8_t red, uint8_t green, uint8_t blue)
        : r(red), g(green), b(blue) {}

    // Predefined colors
    static constexpr Color RED()     { return Color(255, 0, 0); }
    static constexpr Color GREEN()   { return Color(0, 255, 0); }
    static constexpr Color BLUE()    { return Color(0, 0, 255); }
    static constexpr Color YELLOW()  { return Color(255, 255, 0); }
    static constexpr Color CYAN()    { return Color(0, 255, 255); }
    static constexpr Color MAGENTA() { return Color(255, 0, 255); }
    static constexpr Color WHITE()   { return Color(255, 255, 255); }
    static constexpr Color OFF()     { return Color(0, 0, 0); }
};