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
    Rectangle nw(x - w / 2, y + h / 2, w, h);
    Rectangle ne(x + w / 2, y + h / 2, w, h);
    Rectangle sw(x - w / 2, y - h / 2, w, h);
    Rectangle se(x + w / 2, y - h / 2, w, h);

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

void quadTree::bulkLoadquadTree(vector<Point> &pts)
{
    // If there are no points or the number of points is less than or equal to the capacity, insert them into the current node.
    vector<Point> NW, NE, SE, SW;
    int i=points.size();
    for (auto it : pts)
    {
        if(i++ < capacity) this->points.push_back(it);
        if(i==capacity+1){if(!divided)subdivide();}
        if(i>capacity){
            if(northeast->boundary.contains(it)) NE.push_back(it);
            else if(northwest->boundary.contains(it)) NW.push_back(it);
            else if(southeast->boundary.contains(it)) SE.push_back(it);
            else if(southwest->boundary.contains(it)) SW.push_back(it);
        }

    }
    if(i>capacity){
        northeast->bulkLoadquadTree(NE);
        northwest->bulkLoadquadTree(NW);
        southeast->bulkLoadquadTree(SE);
        southwest->bulkLoadquadTree(SW);
    }
}


// Recursively perform k-Nearest Neighbor (kNN) search.
void quadTree::knnSearchRecursive(const Point &query, int k, vector<Point> &nearestPoints)
{   
    for(auto point : points){
        double dist = distance(point, query);
        // add point to neighbours if it is closer to query or the we do not get k points
        if(nearestPoints.size() < k || dist < distance(nearestPoints.back(), query)){
            nearestPoints.push_back(point);

            std::sort(nearestPoints.begin(), nearestPoints.end(), [query](Point p1, Point p2){
                return distance(p1, query) < distance(p2, query);
            } );

            if(nearestPoints.size() > k)
                nearestPoints.pop_back(); // keep k closet neighbours
        }
    }

    if(divided){
        //northeast
        double x1 = northeast->boundary.x - northeast->boundary.w/2;
        double x2 = northeast->boundary.x + northeast->boundary.w/2;
        double y1 = northeast->boundary.y - northeast->boundary.h/2;
        double y2 = northeast->boundary.y + northeast->boundary.h/2;
        double dist = min(abs(query.x - x1), abs(query.x - x2));
        dist = min(dist, min(abs(query.y - y1), abs(query.y - y2)));
        if(nearestPoints.size() < k || distance(nearestPoints.back(), query) > dist){
            northeast->knnSearchRecursive(query, k, nearestPoints);
        }

        //northwest
        x1 = northwest->boundary.x - northwest->boundary.w/2;
        x2 = northwest->boundary.x + northwest->boundary.w/2;
        y1 = northwest->boundary.y - northwest->boundary.h/2;
        y2 = northwest->boundary.y + northwest->boundary.h/2;
        dist = min(abs(query.x - x1), abs(query.x - x2));
        dist = min(dist, min(abs(query.y - y1), abs(query.y - y2)));
        if(nearestPoints.size() < k || distance(nearestPoints.back(), query) > dist){
            northwest->knnSearchRecursive(query, k, nearestPoints);
        }

        //southeast
        x1 = southeast->boundary.x - southeast->boundary.w/2;
        x2 = southeast->boundary.x + southeast->boundary.w/2;
        y1 = southeast->boundary.y - southeast->boundary.h/2;
        y2 = southeast->boundary.y + southeast->boundary.h/2;
        dist = min(abs(query.x - x1), abs(query.x - x2));
        dist = min(dist, min(abs(query.y - y1), abs(query.y - y2)));
        if(nearestPoints.size() < k || distance(nearestPoints.back(), query) > dist){
            southeast->knnSearchRecursive(query, k, nearestPoints);
        }

        //southwest
        x1 = southwest->boundary.x - southwest->boundary.w/2;
        x2 = southwest->boundary.x + southwest->boundary.w/2;
        y1 = southwest->boundary.y - southwest->boundary.h/2;
        y2 = southwest->boundary.y + southwest->boundary.h/2;
        dist = min(abs(query.x - x1), abs(query.x - x2));
        dist = min(dist, min(abs(query.y - y1), abs(query.y - y2)));
        if(nearestPoints.size() < k || distance(nearestPoints.back(), query) > dist){
            southwest->knnSearchRecursive(query, k, nearestPoints);
        }
    }
}

// Perform a k-Nearest Neighbor (kNN) search from the root node.
vector<Point> quadTree::knnSearch(const Point &query, int k)
{
    vector<Point> nearestPoints;
    knnSearchRecursive(query, k, nearestPoints);
    return nearestPoints;
}

quadTree::~quadTree()
{
    delete northwest;
    delete northeast;
    delete southwest;
    delete southeast;
}

//method to know whether the point is present
bool quadTree::search(Point p){
    if(!boundary.contains(p))return false; 
    for(int i=0;i<capacity;i++){
        if(this->points[i]==p) return true;
    }
    if(divided){
        if(this->northeast->search(p) | this->northwest->search(p) | this->southeast->search(p) | this->southwest->search(p)){
            return true;
        }
    }
    return false;
}

int quadTree::getHeight(){
        if(capacity==0) return 0;
        if(!divided) return 1;
        return 1 + max(max(max(northeast->getHeight(), northwest->getHeight()),southeast->getHeight()), southwest->getHeight());
    }