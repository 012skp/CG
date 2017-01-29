#include<bits/stdc++.h>
#include"cgal_basic.cc"
using namespace std;

//Each convex_hull object is list of points (x0,y0),(x1,y1),(x2,y2),...(xn,yn),(x0,y0).
typedef vector<point<double> >  ch_obj;
bool cmp(point<double> p1, point<double> p2){
		return p1.F < p2.F;
}

void my_merge(ch_obj &o1, ch_obj &o2, ch_obj &ans){
	ans.clear();	
	ch_obj::iterator it1,it2;
	it1 = o1.begin();
	it2 = o2.begin();
	while(it1!=o1.end() && it2 != o2.end()){
		point<double> p1 = *it1, p2 = *it2;
		if(p1.F < p2.F){ans.pb(p1); it1++;}
		else{ans.pb(p2); it2++;}
	}
	while(it1!=o1.end()){ ans.pb(*it1); it1++;}
	while(it2!=o2.end()){ ans.pb(*it2); it2++;}
}

void print(ch_obj &v){
for(int i=0;i<v.size();i++)cout<<"{"<<v[i].F<<','<<v[i].S<<"} "; cout<<endl;
}

void merge_objects(vector<ch_obj> &obj_list, int l, int r, ch_obj &ans){
	if(r-l == 1){
		my_merge(obj_list[l],obj_list[r],ans);
		return ;
	}
	if(l == r){ ans = obj_list[l]; return ;}
	ch_obj ans1,ans2;
	int mid = (l+r)/2;
	merge_objects(obj_list,l,mid,ans1);
	merge_objects(obj_list,mid+1,r,ans2);
	my_merge(ans1,ans2,ans);
	return;
}

bool check_convex_hull(ch_obj v){
	int j = 0;
	//find first set of points that are non-collinear points
	//then check its orientation.
	while(Rotation(v[j],v[j+1],v[j+2]) == 0){ j++; if(j+2 == v.size()) return false; }
	if(Rotation(v[j],v[j+1],v[j+2]) == 1){ //if convex hull is in clockwise direction, it should always be in clockwise
		for(int i=j+3;i<v.size();i++) if(Rotation(v[i-2],v[i-1],v[i]) == -1) return false;
		return true;
	}
	else if(Rotation(v[0],v[1],v[2]) == -1){//if convex hull is in anticlockwise direction.
		for(int i=j+3;i<v.size();i++) if(Rotation(v[i-2],v[i-1],v[i]) == 1) return false;
		return true;
	}
}


int main(int argc, char *argv[]){
	if(argc < 2){printf("usage: %s <input_filename>\n",argv[0]); exit(1);}
	//Take input from file....
	FILE *fp = fopen(argv[1],"r");
	int n;
	fscanf(fp,"%d",&n);
	vector<ch_obj> obj_list(n+1); //list of n objects....
	for(int i=1;i<=n;i++){
		int m;
		fscanf(fp,"%d",&m);
		for(int j=1;j<=m;j++){
			double x,y;
			fscanf(fp,"%lf %lf",&x,&y);
			point<double> p = mp(x,y);
			obj_list[i].pb(p);
		}
		if(!check_convex_hull(obj_list[i])){
			printf("Input provided is not convex object, check object no %d\n",i);
			fclose(fp);
			exit(1);
		}		
	}
	fclose(fp);
	
	vector<ch_obj> sorted_obj_list;
	sorted_obj_list.pb(ch_obj(0));
	for(int i=1;i<=n;i++){
		obj_list[i].erase(obj_list[i].end()-1); //erase the last element because first == last.
		int size = obj_list[i].size();
		int idx_max = max_element(obj_list[i].begin(),obj_list[i].end())-obj_list[i].begin();
		int idx_min = min_element(obj_list[i].begin(),obj_list[i].end())-obj_list[i].begin();
		ch_obj o1,o2;
		if(idx_min > idx_max){
			int j = idx_min;
			while(j!=idx_max){
				o1.pb(obj_list[i][j]);
				j = (j+1)%size;
			}
			j = idx_min-1;
			while(j!=idx_max){
				o2.pb(obj_list[i][j]);
				j--;
			}
			o2.pb(obj_list[i][j]);
		}
		if(idx_min<idx_max){
			int j=idx_min;
			while(j!=idx_max){
				o1.pb(obj_list[i][j]);
				j++;
			}
			j = idx_min-1;
			if(j<0) j+=size;
			while(j!=idx_max){
				o2.pb(obj_list[i][j]);			
				j--;
				if(j<0) j+=size;
			}
			o2.pb(obj_list[i][j]);
		}
		// if min == max NOT POSSIBLE must have atleast 3 points...
		ch_obj ans;
		my_merge(o1,o2,ans);
		sorted_obj_list.pb(ans);
	}
	
	ch_obj sorted_points;
	merge_objects(sorted_obj_list,1,n,sorted_points);
	cout<<"convex hull is created.."<<endl;
	ch_obj ans;
	convex_hull(sorted_points,ans);
	print(ans);

return 0;
}

