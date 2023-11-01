#include "quadTree.h"

// Check if the given Point is inside Rectangle.
bool Rectangle::contains(const Point &point)
{
    return (point.x >= x - w / 2 && point.x <= x + w / 2 &&
            point.y >= y - h / 2 && point.y <= y + h / 2);
}

// Check if Rectangle intersects with another Rectangle R2.
bool Rectangle::intersects(const Rectangle &R2)
{
    return !(R2.x - R2.w / 2 > x + w / 2 ||
             R2.x + R2.w / 2 < x - w / 2 ||
             R2.y - R2.h / 2 > y + h / 2 ||
             R2.y + R2.h / 2 < y - h / 2);
}

// Calculate distance between two points
double distance(Point a, Point b)
{
    double dist = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
    dist = sqrt(dist);
    return dist;
}

void quadTree::subdivide()
{
    // Subdivide the current quadTree node into four sub-quadrants.
    double x = this->boundary.x;
    double y = this->boundary.y;
    double w = this->boundary.w / 2;
    double h = this->boundary.h / 2;

    // Create four new sub-Rectangles for the sub-quadrants.
    Rectangle nw(x - w / 2, y - h / 2, w, h);
    Rectangle ne(x + w / 2, y - h / 2, w, h);
    Rectangle sw(x - w / 2, y + h / 2, w, h);
    Rectangle se(x + w / 2, y + h / 2, w, h);

    // Create new quadTree nodes for the sub-quadrants.
    northwest = new quadTree(nw, capacity);
    northeast = new quadTree(ne, capacity);
    southwest = new quadTree(sw, capacity);
    southeast = new quadTree(se, capacity);

    divided = true; // Mark the current node as divided.
}

// Insert a Point into the quadTree.
bool quadTree::insert(const Point &point)
{

    if (this->boundary.contains(point) == 0)
    {
        return false; // Point is outside the boundary
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
            // Subdivide the quadTree if not already divided.
            subdivide();
        }
        // Recursively try to insert the Point into the sub-quadrants.
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

vector<Point> quadTree::rangeQuery(Rectangle &region)
{
    vector<Point> found;
    if (this->boundary.intersects(region) == 0)
    {
        return found; // No intersection
    }
    for (auto &pt : points)
    {
        if (region.contains(pt))
        {
            found.push_back(pt); // Add points that are within the region.
        }
    }
    if (divided)
    {
        // Recursively perform range queries in sub-quadrants and merge results.
        vector<Point> nw = northwest->rangeQuery(region);
        vector<Point> ne = northeast->rangeQuery(region);
        vector<Point> sw = southwest->rangeQuery(region);
        vector<Point> se = southeast->rangeQuery(region);
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

// quadTree *bulkLoadquadTree(vector<Point> &points, Rectangle &region, int capacity)
// {
//     quadTree *QTree = new quadTree(region, capacity);
//     if (points.empty())
//         return QTree;
//     QTree->subdivide();
//     vector<Point> NEpoints, NWpoints, SEpoints, SWpoints;
//     for (auto it : points)
//     {
//         if (QTree->northeast->boundary.contains(it))
//             NEpoints.push_back(it);
//         else if (QTree->northwest->boundary.contains(it))
//             NWpoints.push_back(it);
//         else if (QTree->southeast->boundary.contains(it))
//             SEpoints.push_back(it);
//         else
//             SWpoints.push_back(it);
//     }
//     QTree->northeast = bulkLoadquadTree(NEpoints, QTree->northeast->boundary, capacity);
//     QTree->northwest = bulkLoadquadTree(NWpoints, QTree->northwest->boundary, capacity);
//     QTree->southeast = bulkLoadquadTree(SEpoints, QTree->southeast->boundary, capacity);
//     QTree->southwest = bulkLoadquadTree(SWpoints, QTree->southwest->boundary, capacity);
//     return QTree;
// }

// Recursively perform k-Nearest Neighbor (kNN) search.
void quadTree::knnSearchRecursive(const Point &target, int k, vector<Point> &nearestPoints)
{
    if (!boundary.intersects(Rectangle(target.x, target.y, 0, 0)))
    {
        return;
    }

    for (const Point &point : points)
    {
        if (nearestPoints.size() < k)
        {
            nearestPoints.push_back(point);
        }
        else
        {
            for (Point &nearest : nearestPoints)
            {
                // Update nearest if a closer point is found
                if (distance(point, target) < distance(nearest, target))
                {
                    nearest = point;
                    break;
                }
            }
        }
    }
    // Recursively search in sub-quadrants.
    if (divided)
    {
        northwest->knnSearchRecursive(target, k, nearestPoints);
        northeast->knnSearchRecursive(target, k, nearestPoints);
        southwest->knnSearchRecursive(target, k, nearestPoints);
        southeast->knnSearchRecursive(target, k, nearestPoints);
    }
}

 // Perform a k-Nearest Neighbor (kNN) search from the root node.
vector<Point> quadTree::knnSearch(const Point &target, int k)
{

    vector<Point> nearestPoints;
    knnSearchRecursive(target, k, nearestPoints);
    return nearestPoints;
}

quadTree::~quadTree()
{
    delete northwest;
    delete northeast;
    delete southwest;
    delete southeast;
}