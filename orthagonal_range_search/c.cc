#include<bits/stdc++.h>
#include"cgal_basic.h"
using namespace std;

int main(){
  //srand(time(NULL));
  vector<Point> point_list;
  for(int i=0;i<10;i++) point_list.push_back({double(rand()%20),double(rand()%20)});
  cout<<"Initial points..."<<endl;
  for(int i=0;i<10;i++) printf("{%d,%d} ",(int)point_list[i].x,(int)point_list[i].y);
  cout<<endl;

  int l = 0,r=10;
  int mid = (l+r)/2;
  int ll = l; //current right in partition
  int rr = r; //current left in partition
  int cc = 0; //current position
  vector<Point>::iterator it;
  int pp = 2;

    printf("ll = %d rr = %d\n",ll,rr);
    Point p = point_list[4]; // Pivot element is first one...
    printf("pivot point = {%d,%d}\n",(int)p.x,(int)p.y);
    it = partition(point_list.begin()+4,point_list.begin()+rr,[p](Point check)->bool{return check.x <= p.y;});
    int nmid = it - point_list.begin(); // new_mid in partition
    printf("pointer is pointing to {%d,%d}\n",(int)it->x,(int)it->y);
    printf("nmid = %d\n",nmid);
    for(int i=0;i<10;i++) printf("{%d,%d} ",(int)point_list[i].x,(int)point_list[i].y);
    getchar();

    /*
    p = {9,1};
    it = partition(point_list.begin()+nmid,point_list.begin()+rr,[p](Point &check)->bool{return check.x < p.y;});
    nmid = it - point_list.begin(); // new_mid in partition
    printf("pointer is pointing to {%d,%d}\n",(int)it->x,(int)it->y);
    printf("nmid = %d\n",nmid);
    for(int i=0;i<10;i++) printf("{%d,%d}  ",(int)point_list[i].x,(int)point_list[i].y);
    */



  //for(int i=0;i<10;i++) printf("{%d,%d}  ",(int)point_list[i].x,(int)point_list[i].y);
  return 0;
}
