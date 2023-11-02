#include <bits/stdc++.h>
#include "quadTree.cpp"
#include <random>
#include <time.h>
using namespace std;

int main()
{
    // srand(time(0));
    // Just rough work to check the working of search and insertion
    Rectangle Area(100, 100, 100, 100);
    quadTree Tree(Area, 4);
    cout << " Points inserted into tree:" << endl;
    for (int i = 0; i < 30; i++)
    {
        Point x = Point(100 + rand() % 100 - 50, 100 + rand() % 100 - 50);
        cout << " " << x.x << " " << x.y << endl;
        Tree.insert(x);
    }
    Point y = Point(115, 65);
    Tree.insert(y);
    vector<Point> input;
    for (int i = 0; i < 30; i++)
    {
        Point x = Point(100 + rand() % 100 - 50, 100 + rand() % 100 - 50);
        // cout<<" "<<x.x<<" "<<x.y<<endl;
        input.push_back(x);
    }
    cout << "Input vector is:" << endl;
    for (auto it : input)
        cout << "" << it.x << " " << it.y << endl;
    // Boundary cases working fine
    // if we want to use bulk loading on existing quad tree then recursion bulking loading should not be used and if we want to use bulk loading on new quad tree we can use bulk loading using recursion.
    // Bulk loading working fine
    Tree.bulkLoadquadTree(input);
    cout << "Points into range query:" << endl;
    Rectangle region(125, 75, 40, 40);
    vector<Point> ans = Tree.rangeQuery(region);
    // Range Query working fine
    for (auto it : ans)
    {
        cout << "" << it.x << " " << it.y << endl;
    }

    // Tree.display();
}