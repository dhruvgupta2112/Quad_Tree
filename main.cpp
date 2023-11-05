#include <bits/stdc++.h>
#include "quadTree.cpp"
#include <random>
#include <time.h>
using namespace std;

void help(){
    cout<<left<<setw(32)<<"Functions"<<"command"<<endl;
    cout<<left<<setw(32)<<"insertion"<<"i"<<endl;
    cout<<left<<setw(32)<<"multiple insertion(bulkload)"<<"mi"<<endl;
    cout<<left<<setw(32)<<"enter 10 random points: "<<"rand"<<endl;
    cout<<left<<setw(32)<<"range Query"<<"rquery"<<endl;
    cout<<left<<setw(32)<<"k nearest element"<<"knn"<<endl;
    cout<<left<<setw(32)<<"help"<<"help"<<endl;
    cout<<left<<setw(32)<<"exit"<<"exit"<<endl;
}
int main()
{
    Rectangle region(100, 100, 200, 200); // x-cordinate, y-cordinate, width, height
    quadTree qt(region, 4);
    string choice;
    cout<<"\nQuad Tree is created of size 200 * 200\n\n";
    help();
    cout<<endl;
    while(1){
        cout<<"enter your choice: ";
        cin>>choice;
        if(choice == "i"){
            double x, y;
            cout<<"enter x: ";cin>>x;
            cout<<"enter y: ";cin>>y;
            qt.insert(Point(x, y));
            cout<<"Point ("<<x<<", "<<y<<") inserted successfully\n\n";
        }
        else if(choice == "mi"){
            vector<Point> bulk;
            int n;
            double x, y;
            cout<<"enter number of points to enter: ";cin>>n;
            while(n--){
                cout<<"enter x: ";cin>>x;
                cout<<"enter y: ";cin>>y;
                bulk.push_back(Point(x, y));
            }
            qt.bulkLoadquadTree(bulk);
            cout<<"Bulkloading done successfully\n\n";
        }
        else if(choice == "rquery"){
            double x, y, w, h;
            cout<<"define the region for query: \n";
            cout<<"enter x: ";cin>>x;
            cout<<"enter y: ";cin>>y;
            cout<<"enter w: ";cin>>w;
            cout<<"enter h: ";cin>>h;

            Rectangle rquery = Rectangle(x, y, w, h);
            vector<Point> ans = qt.rangeQuery(rquery);
            cout<<"Points lie in the region are: \n";
            if(ans.empty()) cout<<"No points found\n";
            else
            for(auto point: ans){
                cout<<"x: "<<point.x<<"\t"<<"y: "<<point.y<<endl;
            }
        }
        else if(choice == "rand"){
            srand(time(0));
            vector<Point> input;
            for (int i = 0; i < 10; i++){
                Point x = Point(rand()%200, rand()%200);
                input.push_back(x);
            }
            qt.bulkLoadquadTree(input);
            cout<<"10 random points are inserted\n\n";
        }
        else if(choice == "knn"){
            Point p;int n;
            cout<<"enter x: ";cin>>p.x;
            cout<<"enter y: ";cin>>p.y;
            cout<<"enter number of points: ";cin>>n;

            vector<Point> ans = qt.knnSearch(p, n);
            if(ans.empty()) cout<<"there are no points\n\n";
            else{
                cout<<n<<" points nearest to point ("<< p.x<<", "<<p.y<<") are: \n";
                for(auto point: ans){
                    cout<<"x: "<<point.x<<"\ty: "<<point.y<<endl;
                }
                cout<<endl;
            }

        }
        else if(choice == "help"){
            help();
            cout<<endl;
        }
        else if(choice == "exit") break;
        else {
            cout<<"\'"<<choice<<"\'"<<" command not found\n";
            help();
            cout<<endl;
        }
    }

    return 0;
}