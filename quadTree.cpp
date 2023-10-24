#include "quadTree.h"

bool Rectangle::contains(const Point &point)
{
    return (point.x >= x - w / 2 && point.x <= x + w / 2 &&
            point.y >= y - h / 2 && point.y <= y + h / 2);
}

bool Rectangle::intersects(const Rectangle &R2)
{
    return !(R2.x - R2.w / 2 > x + w / 2 ||
             R2.x + R2.w / 2 < x - w / 2 ||
             R2.y - R2.h / 2 > y + h / 2 ||
             R2.y + R2.h / 2 < y - h / 2);
}

void quadTree::subdivide()
{
    double x = this->boundary.x;
    double y = this->boundary.y;
    double w = this->boundary.w / 2;
    double h = this->boundary.h / 2;

    Rectangle nw(x - w / 2, y - h / 2, w, h);
    Rectangle ne(x + w / 2, y - h / 2, w, h);
    Rectangle sw(x - w / 2, y + h / 2, w, h);
    Rectangle se(x + w / 2, y + h / 2, w, h);

    northwest = new quadTree(nw, capacity);
    northeast = new quadTree(ne, capacity);
    southwest = new quadTree(sw, capacity);
    southeast = new quadTree(se, capacity);

    divided = true;
}

bool quadTree::insert(const Point &point)
{

    if (this->boundary.contains(point) == 0)
    {
        return false;
    }
    if (points.size() < capacity)
    {
        points.push_back(point);
        return true;
    }
    else
    {
        if (!divided)
        {
            subdivide();
        }

        if (northwest->insert(point))
            return true;
        if (northeast->insert(point))
            return true;
        if (southwest->insert(point))
            return true;
        if (southeast->insert(point))
            return true;
    }

    return false;
}

vector<Point> quadTree::search(Rectangle &region)
{
    vector<Point> found;
    if (this->boundary.intersects(region) == 0)
    {
        return found;
    }
    for (auto &pt : points)
    {
        if (region.contains(pt))
        {
            found.push_back(pt);
        }
    }
    if (divided)
    {
        vector<Point> nw = northwest->search(region);
        vector<Point> ne = northeast->search(region);
        vector<Point> sw = southwest->search(region);
        vector<Point> se = southeast->search(region);

        found.insert(found.end(), nw.begin(), nw.end());
        found.insert(found.end(), ne.begin(), ne.end());
        found.insert(found.end(), sw.begin(), sw.end());
        found.insert(found.end(), se.begin(), se.end());
    }

    return found;
}

void quadTree::display()
{
    for (auto it : points)
    {
        cout << it.x << " " << it.y << endl;
    }
    if (divided)
    {
        northeast->display();
        northwest->display();
        southeast->display();
        southwest->display();
    }
}

vector<Point> quadTree::RangeQuery(Rectangle &region)
{
    vector<Point> points;
    if(this->boundary.intersects(region)==0){
        return points;
    }
    if(divided)
    {
        vector<Point> allPoints=search(region); 
        points.insert(points.end(), allPoints.begin(), allPoints.end());
    }
    vector<Point> northwestPoints = RangeQuery(region);
    points.insert(points.end(), northwestPoints.begin(), northwestPoints.end());
    vector<Point> northeastPoints = RangeQuery(region);
    points.insert(points.end(), northeastPoints.begin(), northeastPoints.end());
    vector<Point> southeastPoints = RangeQuery(region);
    points.insert(points.end(), southeastPoints.begin(), southeastPoints.end());
    vector<Point> southwestPoints = RangeQuery(region);
    points.insert(points.end(), southwestPoints.begin(), southwestPoints.end());
}
