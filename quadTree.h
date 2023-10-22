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

// To check if two rectangles intersects or not
bool recIntersect(Rectangle &main, Rectangle &other)
{
    if (main.centre.x + main.HalfDim > other.centre.x - other.HalfDim || main.centre.x - main.HalfDim < other.centre.x + other.HalfDim)
        return true;
    if (main.centre.y + main.HalfDim > other.centre.y - other.HalfDim || main.centre.y - main.HalfDim < other.centre.y + other.HalfDim)
        return true;
    return false;
}

class QuadTree
{
private:
    Rectangle boundary;
    int capacity;
    vector<Point> points;
    bool divided;

public:
    QuadTree *NW;
    QuadTree *SW;
    QuadTree *SE;
    QuadTree *NE;
    QuadTree(const Rectangle &boundary, int capacity) : boundary(boundary), capacity(capacity), divided(false)
    {
        NW = nullptr;
        SW = nullptr;
        SE = nullptr;
        NE = nullptr;
    }
    for (size_t i = 0; i < capacity; i++)
        QuadTree->points[i] = NULL;
    void insert();
};
