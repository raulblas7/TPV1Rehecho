#pragma once
#include <iostream>



class Vector2D
{
private:
    double x, y;

public:
    Vector2D();
    Vector2D(double x, double y);
    double getX() const {
        return x;
    };
    double getY() const {
        return y;
    };
    void normalize();
    Vector2D operator+(const Vector2D& v) const;
    Vector2D operator-(const Vector2D& v) const;
    Vector2D operator*(double d) const;
    double operator*(const Vector2D& d) const;
    friend std::ostream& operator<<(std::ostream& os, const Vector2D& v);

};

using Point2D = Vector2D;
