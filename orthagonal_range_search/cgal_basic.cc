#include "cgal_basic.h"
#define pb push_back
#define mp make_pair


Point::Point(double a, double b){
  x = a;
  y = b;
}

Line::Line(Point p1, Point p2){
  v1 = p1;
  v2 = p2;
}

int rotation(Point p1, Point p2, Point p3){
	//printf("Checking rotation of {%d,%d} {%d,%d} {%d,%d}...\n",p1.x,p1.y,p2.x,p2.y,p3.x,p3.y);
	auto x1 = p1.x - p2.x, y1 = p1.y-p2.y;
	auto x2 = p3.x - p2.x, y2 = p3.y-p2.y;
	auto r = (x1*y2 - x2*y1);
	if(r > 0) return 1; // p1,p2,p3 in clockwise direction...
	else if(r < 0) return -1;// p1,p2,p3 in anti-clockwise direction...
	else return 0; //colLinear points....
}


void convex_hull(vector<Point > &v, vector<Point > &cv){
	int n = v.size();
	if(n == 1){cv.pb(v[0]); return; }
	cv.pb(v[0]);
	cv.pb(v[1]);
	int i = 2;
	while(i<n){
		int n1 = cv.size();
		if(n1 == 1) {cv.pb(v[i]);i++; continue;}
		if(rotation(cv[n1-2],cv[n1-1],v[i]) == 1){cv.pb(v[i]);i++; continue;}
		else{
			auto it = cv.end();
			it--;
			cv.erase(it);
		}
	}

	vector<Point > rv;
	rv.pb(v[0]);
	rv.pb(v[1]);
	i = 2;
	while(i<n){
		int n1 = rv.size();
		if(n1==1){rv.pb(v[i]);i++; continue;}
		if(rotation(rv[n1-2],rv[n1-1],v[i]) == -1){rv.pb(v[i]);i++; continue;}
		else{
			auto it = rv.end();
			it--;
			rv.erase(it);
		}
	}
	reverse(rv.begin(),rv.end());
	cv.insert(cv.end(),rv.begin()+1,rv.end());
}



double  area_polygon(vector<Point > v){
	double  area = 0;
	int n = v.size();
	for(int i=0;i<n-1;i++){
		area += v[i].x*v[i+1].y - v[i].x*v[i+1].y;
	}
	return area;

}


bool onsegment(Point p1, Point p2, Point p3){
	if( (p3.x <= max(p1.x,p2.x) && p3.x >= min(p1.x,p2.x)) && (p3.y <= max(p1.y,p2.y) && p3.y >= min(p1.y,p2.y)) ) return true;
	else return false;
}


int is_intersecting(Line l1, Line l2){
	Point p1=l1.v1,p2=l1.v2,p3=l2.v1,p4=l2.v2;
	int r21 = rotation(p1,p2,p3);
	int r22 = rotation(p1,p2,p4);
	int r11 = rotation(p3,p4,p1);
	int r12 = rotation(p3,p4,p2);
	if(r11*r12 == -1 && r21*r22 == -1) return 1; //proper intersection...
	else if(r11*r12*r21*r22 == 0){	//improper intersection may happen.......
		if(r11 == 0) if(onsegment(p3,p4,p1)) return -1;
		if(r12 == 0) if(onsegment(p3,p4,p2)) return -1;
		if(r21 == 0) if(onsegment(p1,p2,p3)) return -1;
		if(r22 == 0) if(onsegment(p1,p2,p4)) return -1;
		return 0; // no intersection...
	}
	else return 0; // no intersection.....
}



Point intersection_point(Line l1, Line l2){
	int A1,B1,C1,A2,B2,C2;
	A1 = l1.v2.y - l1.v1.y; //y2-y1
	B1 = l1.v1.x - l1.v2.x; //x1-x2
	C1 = A1*l1.v1.x + B1*l1.v1.y; // A*x1+B*y1

	A2 = l2.v2.y - l2.v1.y; //y2-y1
	B2 = l2.v1.x - l2.v2.x; //x1-x2
	C2 = A2*l2.v1.x + B2*l2.v1.y; // A*x1+B*y1

	double delta = A1*B2 - B1*A2;
	if(delta == 0) {printf("Error lines donot intersect! if intersect then call this function\n"); exit(1); }
	Point p;
	double x,y;
	x = (B2*C1 - B1*C2)/delta;
  y = (A1*C2 - A2*C1)/delta;
	p.x = x;
	p.y = y;
	return p;
}
