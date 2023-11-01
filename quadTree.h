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
public:
    // w = width
    // h = height
    double x, y, w, h;
    Rectangle(double x, double y, double w, double h) : x(x), y(y), w(w), h(h) {}
    bool contains(const Point &);
    bool intersects(const Rectangle &);
};

class quadTree
{
private:
    void knnSearchRecursive(const Point& target, int k, std::vector<Point>& nearestPoints);
public:
    int capacity;
    bool divided;
    Rectangle boundary;
    vector<Point> points;
    quadTree *northwest;
    quadTree *northeast;
    quadTree *southwest;
    quadTree *southeast;

public:
    quadTree(const Rectangle &boundary, int capacity) : boundary(boundary), capacity(capacity), divided(false), northwest(nullptr), northeast(nullptr), southwest(nullptr), southeast(nullptr) {}
    void subdivide();
    bool insert(const Point &);
    vector<Point> rangeQuery(Rectangle &);
    void display();
    quadTree bulkLoadquadTree(vector<Point> &, Rectangle &, int capacity);
    vector<Point> knnSearch(const Point& target, int k);
    ~quadTree();

    //try
        
    //try
};
