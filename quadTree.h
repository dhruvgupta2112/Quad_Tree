#pragma once
#include <bits/stdc++.h>
using namespace std;

class Point
{
public:
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

class Rectangle
{
    // ******************************************************************************
    // w = width
    // h = height
    // double x, y, w, h;
    // Rectangle(double x, double y, double w, double h): x(x), y(y), w(w), h(h){}
    // bool contains(const Point &);
    // bool intersects(const Rectangle&);
    // ************************************************************************************
public:
    Point centre;   // Centre point of the rectangle
    double HalfDim; // Distance of centre from boundary of rectangle
    Rectangle(Point centre, double HalfDim) : centre(centre), HalfDim(HalfDim) {}
};
// To check if the point is inside the boundary of rectangle or not
bool checkPoint(Rectangle &boundary, Point &point)
{
    if (point.x < boundary.centre.x - boundary.HalfDim || point.x > boundary.centre.x + boundary.HalfDim)
        return false;
    if (point.y < boundary.centre.y - boundary.HalfDim || point.y > boundary.centre.y + boundary.HalfDim)
        return false;
    return true;
}

class quadTree
{
private:
    Rectangle boundary;
    int capacity;
    vector<Point> points;
    bool divided;

public:
    void insert();
};
