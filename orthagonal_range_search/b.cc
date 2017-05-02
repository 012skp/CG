#include"cgal_basic.h"
using namespace std;

#define F first
#define S second

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
  while(1){
    printf("ll = %d rr = %d\n",ll,rr);
    Point p = point_list[ll]; // Pivot element is first one...
    printf("pivot point = {%d,%d}\n",(int)p.x,(int)p.y);
    it = partition(point_list.begin()+ll,point_list.begin()+rr,[p](Point check)->bool{return check.x < p.x;});
    int nmid = it - point_list.begin(); // new_mid in partition
    printf("pointer is pointing to {%d,%d}\n",(int)it->x,(int)it->y);
    if(nmid==mid) break;
    else if(nmid > mid) rr = (rr==nmid?rr-1:nmid);
    else if(nmid < mid) ll = (ll==nmid?ll+1:nmid);
    printf("nmid = %d\n",nmid);
    for(int i=ll;i<rr;i++) printf("{%d,%d}  ",(int)point_list[i].x,(int)point_list[i].y);
    cout<<endl;
    getchar();
  }
  for(int i=0;i<10;i++) printf("{%d,%d}  ",(int)point_list[i].x,(int)point_list[i].y);
  return 0;
}
