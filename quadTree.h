#pragma once
#include<bits/stdc++.h>
using namespace std;

class Point{
    int x, y;
};

class Rectangle{
    // w = widht 
    // h = height
    int x, y, w, h;
};

class QuadTree{
    Rectangle boundary;
    int capacity;
    vector<Point> pt;
};

