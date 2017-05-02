
#include"cgal_basic.h"

using namespace std;
#define pb push_back
#define F first
#define S second

struct ort{ //Orthagonal range tree...
  int lvl; // 0 for x 1 for y
  Point p;
  struct ort *left;
  struct ort *right;
  int count; // No of nodes in this subtree
};

void do_it(struct ort *node, struct ort *parent, vector<Point> &point_list, int l, int r){
  //if(parent!=NULL)  printf("do_it called with parent{%lf,%lf} l = %d and r = %d\n",parent->p.x,parent->p.y,l,r);
  //If l>r Node created by parent free it
  if(l>=r) {
    free(node);
    if(parent->left == node) parent->left = NULL;
    if(parent->right == node) parent->right = NULL;
    return ;
  }
  if(r-l == 1){
    node->p = point_list[l];
    node->count = 1;
    return;
  }

  //Find the median based in range 'l' to 'r' based on root->lvl
  //Partition with respect to x coordinate
  int mid = (l+r)/2; //Searching for median by recursive partition...
  int ll = l; //current right in partition
  int rr = r; //current left in partition
  vector<Point>::iterator it;
  while(1){
    //printf("ll = %d rr = %d\n",ll,rr);
    Point p = point_list[ll]; // Pivot element is first one...
    //printf("pivot point = {%d,%d}\n",(int)p.x,(int)p.y);
    it = partition(point_list.begin()+ll,point_list.begin()+rr,[p,node](Point check)->bool{
      return (node->lvl == 0)?(check.x < p.x):(check.y < p.y);});
    int nmid = it - point_list.begin(); // new_mid in partition
    //printf("pointer is pointing to {%d,%d}\n",(int)it->x,(int)it->y);
    if(nmid==mid) break;
    else if(nmid > mid) rr = (rr==nmid?rr-1:nmid);
    else if(nmid < mid) ll = (ll==nmid?ll+1:nmid);
    //printf("nmid = %d\n",nmid);
    //for(int i=ll;i<rr;i++) printf("{%d,%d}  ",(int)point_list[i].x,(int)point_list[i].y); cout<<endl;
  }
  int idx  = it - point_list.begin();
  //printf("Median found is {%lf,%lf}\n",point_list[idx].x,point_list[idx].y);
  for(int i=l;i<r;i++) printf("{%d,%d} ",(int)point_list[i].x,(int)point_list[i].y);
  node->p = point_list[idx];
  //Create two children with lvl opposite of current node...
  node->left = (struct ort*)malloc(sizeof(struct ort));
  node->right = (struct ort*)malloc(sizeof(struct ort));
  node->left->lvl = node->right->lvl = (node->lvl+1)%2;
  node->left->left = node->left->right = node->right->left = node->right->right = NULL;

  //Call two children with partitioned array as input...
  do_it(node->left,node,point_list,l,idx);
  do_it(node->right,node,point_list,idx+1,r);
  node->count = ((node->left!=NULL)?(node->left->count):0) + 1 + ((node->right!=NULL)?(node->right->count):0);
  //printf("at node {%d,%d} count = %d\n",(int)node->p.x,(int)node->p.y,node->count);
}

int query(struct ort *node, double x1, double x2, double y1, double y2){
  if(node == NULL) return 0;
  double x = node->p.x;
  double y = node->p.y;
  if(node->lvl == 0){
    if(x < x1) return query(node->left,x1,x2,y1,y2);
    if(x > x2) return query(node->right,x1,x2,y1,y2);
    if(x <=x2 && x>= x1 ){
      if(y <= y2 && y>= y1) return 1+ query(node->right,x1,x2,y1,y2)+query(node->left,x1,x2,y1,y2);
      else return query(node->right,x1,x2,y1,y2)+query(node->left,x1,x2,y1,y2);
    }
  }
  else{
    if(y < y1) return query(node->left,x1,x2,y1,y2);
    if(y > y2) return query(node->right,x1,x2,y1,y2);
    if(y <= y2 && y>= y1){
      if(x<=x2 && x>= x1) return 1+ query(node->right,x1,x2,y1,y2)+query(node->left,x1,x2,y1,y2);
      else return query(node->right,x1,x2,y1,y2)+query(node->left,x1,x2,y1,y2);
    }
  }
}

int main(){
  int n;
  cin>>n;
  vector<Point> point_list;
  double x,y;
  for(int i=0;i<n;i++) scanf("%lf %lf",&x,&y),point_list.pb({x,y});

  struct ort *root = (struct ort*)malloc(sizeof(struct ort));
  root->lvl = 0; // Root node will partition based on x coordinate...
  root->left = root->right = NULL;
  do_it(root,NULL,point_list,0,n);

  double x1,x2,y1,y2;
  scanf("%lf %lf %lf %lf",&x1,&x2,&y1,&y2);
  {
    printf("count = %d\n",query(root,x1,x2,y1,y2));
  }


  cout<<endl;
  return 0;
}
