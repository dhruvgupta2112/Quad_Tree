#include<bits/stdc++.h>
#include "quadTree.cpp"
#include<random>
#include<time.h>
using namespace std;

int main(){
    srand(time(0));
    // Just rough work to check the working of search and insertion
    Rectangle Area(100, 100, 100, 100);
    quadTree  Tree(Area, 4);
    
    for(int i=0;i<30;i++){
        Point x = Point(100 + rand()%100 - 50, 100 + rand()%100 - 50);
        Tree.insert(x);
    }

    Rectangle region(125, 75, 30, 30);
    vector<Point> ans = Tree.rangeQuery(region);
    for(auto it: ans){
        cout<<""<<it.x<<" "<<it.y<<endl;
    }
    //Tree.display();
   
}