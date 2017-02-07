#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define mp make_pair
#define pb push_back
template<typename T> using point = pair<T,T>;
template<typename T> using line = pair<pair<T,T>,pair<T,T> >;
template<typename T>
int Rotation(point<T> p1, point<T> p2, point<T> p3){
	//printf("Checking rotation of {%d,%d} {%d,%d} {%d,%d}...\n",p1.F,p1.S,p2.F,p2.S,p3.F,p3.S);
	auto x1 = p1.F - p2.F, y1 = p1.S-p2.S;
	auto x2 = p3.F - p2.F, y2 = p3.S-p2.S;
	auto r = (x1*y2 - x2*y1);
	if(r > 0) return 1; // p1,p2,p3 in clockwise direction...
	else if(r < 0) return -1;// p1,p2,p3 in anti-clockwise direction...
	else return 0; //collinear points....
}

template<typename T>
void convex_hull(vector<point<T> > &v, vector<point<T> > &cv){
	int n = v.size();
	if(n == 1){cv.pb(v[0]); return; }
	cv.pb(v[0]);
	cv.pb(v[1]);
	int i = 2;
	while(i<n){
		int n1 = cv.size();
		if(n1 == 1) {cv.pb(v[i]);i++; continue;}
		if(Rotation(cv[n1-2],cv[n1-1],v[i]) == 1){cv.pb(v[i]);i++; continue;}
		else{
			auto it = cv.end();
			it--;
			//printf("{%d,%d} deleted...\n",it->F,it->S);
			cv.erase(it);
		}
	}
	
	vector<point<T> > rv;
	rv.pb(v[0]);
	rv.pb(v[1]);
	i = 2;
	while(i<n){
		int n1 = rv.size();
		if(n1==1){rv.pb(v[i]);i++; continue;}
		if(Rotation(rv[n1-2],rv[n1-1],v[i]) == -1){rv.pb(v[i]);i++; continue;}
		else{
			auto it = rv.end();
			it--;
			//printf("{%d,%d} deleted...\n",it->F,it->S);
			rv.erase(it);
		}
	}
	reverse(rv.begin(),rv.end());
	cv.insert(cv.end(),rv.begin()+1,rv.end());
} 


template<typename T>
double  area_polygon(vector<point<T> > v){
	double  area = 0;
	int n = v.size();
	for(int i=0;i<n-1;i++){
		area += v[i].F*v[i+1].S - v[i].S*v[i+1].F;
	}
	return area;

}

template<typename T>
bool onsegment(point<T> p1, point<T> p2, point<T> p3){
	if( (p3.F <= max(p1.F,p2.F) && p3.F >= min(p1.F,p2.F)) && (p3.S <= max(p1.S,p2.S) && p3.S >= min(p1.S,p2.S)) ) return true;
	else return false;
}


template<typename T>
int is_intersecting(line<T> l1, line<T> l2){
	point<T> p1=l1.F,p2=l1.S,p3=l2.F,p4=l2.S;
	int r21 = Rotation(p1,p2,p3);
	int r22 = Rotation(p1,p2,p4);
	int r11 = Rotation(p3,p4,p1);
	int r12 = Rotation(p3,p4,p2);
	if(r11*r12 == -1 && r21*r22 == -1) return 1; //proper intersection...
	else if(r11*r12*r21*r22 == 0){	//improper intersection may happen.......
		if(r11 == 0) if(onsegment(p3,p4,p1)) return -1;
		if(r12 == 0) if(onsegment(p3,p4,p2)) return -1;
		if(r21 == 0) if(onsegment(p1,p2,p3)) return -1;
		if(r22 == 0) if(onsegment(p1,p2,p4)) return -1;
		return false;
	}
	else return 0;
}

template<typename T>
point<double> intersection_point(line<T> l1, line<T> l2){
	int A1,B1,C1,A2,B2,C2;
	A1 = l1.S.S - l1.F.S; //y2-y1
	B1 = l1.F.F - l1.S.F; //x1-x2
	C1 = A1*l1.F.F + B1*l1.F.S; // A*x1+B*y1
	
	A2 = l2.S.S - l2.F.S; //y2-y1
	B2 = l2.F.F - l2.S.F; //x1-x2
	C2 = A2*l2.F.F + B2*l2.F.S; // A*x1+B*y1

	double delta = A1*B2 - B1*A2;
	if(delta == 0) {printf("Error lines donot intersect..\n"); exit(1); }
	point<double> p;
	double x,y;
	x = (B2*C1 - B1*C2)/delta;
        y = (A1*C2 - A2*C1)/delta;
	p = mp(x,y);
	return p;
}


/*
int main(){
	while(1){
		cout<<"enter two line seg"<<endl;
		line<int> l1,l2;
		cin>>l1.F.F>>l1.F.S>>l1.S.F>>l1.S.S;
		cin>>l2.F.F>>l2.F.S>>l2.S.F>>l2.S.S;
		int r = is_intersecting(l1,l2);
		if(r == 1){
			cout<<"Proper intersection.."<<endl;
			point<double> p = intersection_point(l1,l2);
			cout<<"intersection point is "<<p.F<<' '<<p.S<<endl;
		}
		else if(r == -1){
			cout<<"improper intersection..."<<endl;
			point<double> p = intersection_point(l1,l2);
			cout<<"intersection point is "<<p.F<<' '<<p.S<<endl;
		}
		else cout<<"Not intersecting..."<<endl;
	}
return 0;
}
*/