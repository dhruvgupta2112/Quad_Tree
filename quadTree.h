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

class quadTree{
private:
    Rectangle boundary;
    int capacity;
    vector<Point> pt;
    bool divided;
public:
    void insert();
};

