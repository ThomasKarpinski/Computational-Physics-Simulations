#pragma once

#include <cmath>

namespace MD {

struct Vec2 {
    double x, y;

    Vec2() : x(0.0), y(0.0) {}
    Vec2(double x_val, double y_val) : x(x_val), y(y_val) {}

    // Vector addition
    Vec2 operator+(const Vec2& other) const {
        return Vec2(x + other.x, y + other.y);
    }

    // Vector subtraction
    Vec2 operator-(const Vec2& other) const {
        return Vec2(x - other.x, y - other.y);
    }

    // Scalar multiplication
    Vec2 operator*(double scalar) const {
        return Vec2(x * scalar, y * scalar);
    }

    // Scalar division
    Vec2 operator/(double scalar) const {
        return Vec2(x / scalar, y / scalar);
    }

    // Compound assignment operators
    Vec2& operator+=(const Vec2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vec2& operator-=(const Vec2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vec2& operator*=(double scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Vec2& operator/=(double scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    // Dot product
    double dot(const Vec2& other) const {
        return x * other.x + y * other.y;
    }

    // Magnitude squared
    double mag2() const {
        return x * x + y * y;
    }

    double mag() const {
        return std::sqrt(mag2());
    }
};

inline double wrap_coordinate(double coord, double box_size) {
    if (box_size <= 0) return coord;
    return coord - box_size * std::floor(coord / box_size);
}

inline Vec2 wrap_position(const Vec2& pos, double box_size) {
    return Vec2(wrap_coordinate(pos.x, box_size), wrap_coordinate(pos.y, box_size));
}

struct Particle {
    int id;
    Vec2 position;
    Vec2 velocity;
    Vec2 velocity_pred;
    Vec2 force;
    double mass;

    Particle() : id(0), mass(1.0) {}
    Particle(int id_val, Vec2 pos, Vec2 vel, double m = 1.0)
        : id(id_val), position(pos), velocity(vel), velocity_pred(0.0, 0.0), force(0.0, 0.0), mass(m) {}
};

} // namespace MD
