#ifndef VEC2_H
#define VEC2_H
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

struct Vec2 {
   double x, y;

    Vec2 operator+=(const Vec2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vec2 operator*(double scalar) const {
        return {x * scalar, y * scalar};
    }

    Vec2 operator-(const Vec2& other) const {
        return {x - other.x, y - other.y};
    }
    

   double length() const {
        return std::sqrt(x * x + y * y);
    }

    Vec2 normalized() const {
        double len = length();
        return (len > 0) ? Vec2{x / len, y / len} : Vec2{0, 0};
    }

    // 构造函数
    Vec2(double x = 0, double y = 0) : x(x), y(y) {}

    // 重载负号运算符
    Vec2 operator-() const {
        return Vec2(-x, -y);
    }
};

#endif