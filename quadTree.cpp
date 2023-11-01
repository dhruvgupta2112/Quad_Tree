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

double distance(Point a, Point b){
    double dist = (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
    dist = sqrt(dist);

    return dist;
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

vector<Point> quadTree::rangeQuery(Rectangle &region)
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


void quadTree::knnSearchRecursive(const Point& target, int k, std::vector<Point>& nearestPoints) {
        if (!boundary.intersects(Rectangle(target.x, target.y, 0, 0))) {
            return;
        }

        for (const Point& point : points) {
            if (nearestPoints.size() < k) {
                nearestPoints.push_back(point);
            } else {
                for (Point& nearest : nearestPoints) {
                    if (distance(point,target) < distance(nearest, target)) {
                        nearest = point;
                        break;
                    }
                }
            }
        }

        if (divided) {
            northwest->knnSearchRecursive(target, k, nearestPoints);
            northeast->knnSearchRecursive(target, k, nearestPoints);
            southwest->knnSearchRecursive(target, k, nearestPoints);
            southeast->knnSearchRecursive(target, k, nearestPoints);
        }
    }

vector<Point> quadTree::knnSearch(const Point& target, int k) {
    
    vector<Point> nearestPoints;
    knnSearchRecursive(target, k, nearestPoints);
    return nearestPoints;
}

quadTree::~quadTree() {
    delete northwest;
    delete northeast;
    delete southwest;
    delete southeast;
}