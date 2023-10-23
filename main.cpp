#include<bits/stdc++.h>
#include "quadTree.cpp"
#include<random>
using namespace std;

int main(){
    // Just rough work to check the working of search and insertion
    Rectangle Area(100, 100, 100, 100);
    quadTree  Tree(Area, 4);
    
    Point arr[30];
    for(int i=0;i<30;i++){
        arr[i] = Point(100 + rand()%100 - 50, 100 + rand()%100 - 50);
        Tree.insert(arr[i]);
    }

    Rectangle region(100, 100, 48, 23);
    vector<Point> ans = Tree.search(region);
    for(auto it: ans){
        cout<<it.x<<" "<<it.y<<endl;
    }
    cout<<"runned";
   
}