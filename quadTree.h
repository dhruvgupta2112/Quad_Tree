#pragma once
#include <bits/stdc++.h>
using namespace std;

// Define a class to represent 2D points.
class Point
{
public:
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

// Define a class to represent rectangles.
class Rectangle
{
public:
    double x, y, w, h; // w = width, h = height
    Rectangle(double x, double y, double w, double h) : x(x), y(y), w(w), h(h) {}
    bool contains(const Point &);       // Method to check if a given Point is contained within this Rectangle.
    bool intersects(const Rectangle &); // Method to check if this Rectangle intersects with another Rectangle.
};

// Define a class for a quadtree.
class quadTree
{
private:
    void knnSearchRecursive(const Point &target, int k, vector<Point> &nearestPoints);

public:
    int capacity;         // Maximum number of points a node can hold.
    bool divided;         // Indicates if the quadTree has been divided into sub-quadrants.
    Rectangle boundary;   // The boundary of the quadTree.
    vector<Point> points; // Points contained within quadTree node.
    // Pointers to sub-quadrants.
    quadTree *northwest;
    quadTree *northeast;
    quadTree *southwest;
    quadTree *southeast;

public:
    // Constructor for a quadTree node.
    quadTree(const Rectangle &boundary, int capacity) : boundary(boundary), capacity(capacity), divided(false), northwest(nullptr), northeast(nullptr), southwest(nullptr), southeast(nullptr) {}
    // Method to subdivide the current quadTree node into four sub-quadrants.
    void subdivide();
    // Method to insert a Point into the quadTree.
    bool insert(const Point &);
    // Method to perform a range query and retrieve points within a Rectangle.
    vector<Point> rangeQuery(Rectangle &);
    void display();
    // Method to create a quadTree from Bulk Loading Algorithm.
    void bulkLoadquadTree(vector<Point> &);
    // Method to perform a k-Nearest Neighbor search and return the k nearest points to a target Point.
    vector<Point> knnSearch(const Point &target, int k);
    // Destructor
    ~quadTree();

    // try

    // try
};
