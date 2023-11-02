#include<bits/stdc++.h>
#include "quadTree.cpp"
#include<random>
#include<time.h>
using namespace std;

int main(){
    srand(time(0));
    // Just rough work to check the working of search and insertion
    Rectangle Area(100, 100, 100, 100);
    // quadTree  Tree(Area, 4);
    // cout<<" Points inserted into tree:"<<endl;
    vector<Point> input;
    for(int i=0;i<30;i++){
        Point x = Point(100 + rand()%100 - 50, 100 + rand()%100 - 50);
        // cout<<" "<<x.x<<" "<<x.y<<endl;
        input.push_back(x);
    }
    cout<<"Input vector is:"<<endl;
    for(auto it:input)
        cout<<""<<it.x<<" "<<it.y<<endl;
    //Boundary cases working fine
    Point y=Point(115,65);
    input.push_back(y);
    //Bulk loading working fine
    quadTree* Tree = bulkLoadquadTree(input, Area, 4);
    cout<<"Points into range query:"<<endl;
    Rectangle region(125, 75, 20, 20);
    vector<Point> ans = Tree->rangeQuery(region);
    //Range Query working fine
    for(auto it: ans){
        cout<<""<<it.x<<" "<<it.y<<endl;
    }

    //Tree.display();
   
}