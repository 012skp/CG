#include "cgal_basic.h"
#include <unistd.h>

#define pb push_back
#define mp make_pair
#define KCYN  "\x1B[31m"
#define KWHT  "\x1B[37m"
double x_min=INT_MAX,x_max=-1,y_min=INT_MAX,y_max=-1;
class edge_record{
public:
	Line l;
	int e_no,cycle_no,face_no;
	int l_,l_prev,l_next; //edge_no and  index pointer to twin, prev and next..

	bool operator==(const edge_record &e2){
		return e_no == e2.e_no;
	}

	bool operator<(const edge_record &e2){
		return e_no < e2.e_no;
	}
};

bool comp(edge_record e1, edge_record e2){
	return e1.e_no<e2.e_no;
}

struct cycle{
	int conf,left_most_eptr,rgb,parent_cycle;
	vector<int> child_cycle;
};


void print_gui(vector<edge_record> &edge_list, vector<cycle> &cycle_list){
	vector<int> color(edge_list.size(),0);
	color[0] = 1;
	double ff =(x_max-x_min)/300; // distance between twin half_edges...
	double xff,yff;
	x_min -= 1; y_min -=1; x_max += 1; y_max += 1;
	FILE *fp = fopen("output","w");
	fprintf(fp,"set xrange[%lf:%lf]\n",x_min-1,x_max+1);
	fprintf(fp,"set yrange[%lf:%lf]\n",y_min-1,y_max+1);
	int i = 1;
	while(1){
		if(color[i]) i = find(color.begin(),color.end(),0)-color.begin(); // finds index whose color is 0;
		if(i==color.size()) break;

		double y,y_,y1,y2,x,x_,x1,x2;
		x = edge_list[i].l.v1.x;
		x_ = edge_list[i].l.v2.x;
		x2 = edge_list[edge_list[i].l_next].l.v2.x;
		x1 = edge_list[edge_list[i].l_prev].l.v1.x;
		y = edge_list[i].l.v1.y;
		y_ = edge_list[i].l.v2.y;
		y2 = edge_list[edge_list[i].l_next].l.v2.y;
		y1 = edge_list[edge_list[i].l_prev].l.v1.y;
		xff = yff = 0.0;
		if(cycle_list[edge_list[i].cycle_no].conf){
			if(x < x1 && x_ < x2) xff = ff;
			if(x > x1 && x_ > x2) xff = -ff;
			if(y < y1 && y_ < y2) yff = ff;
			if(y > y1 && y_ > y2) yff = -ff;
		}
		else{
			if(x < x1 && x_ < x2) xff = -ff;
			if(x > x1 && x_ > x2) xff = ff;
			if(y < y1 && y_ < y2) yff = -ff;
			if(y > y1 && y_ > y2) yff = ff;
		}
		fprintf(fp,"set arrow from %lf,%lf to %lf,%lf linecolor rgb %d\n",edge_list[i].l.v1.x+xff,edge_list[i].l.v1.y+yff,
																edge_list[i].l.v2.x+xff,edge_list[i].l.v2.y+yff,cycle_list[edge_list[i].cycle_no].rgb);
		fprintf(fp, "set label \"e%d\" at %lf,%lf rotate by %lf right front\n",i,((x+x_)/2+6*xff),((y+y_)/2+6*yff),57.3248*atan((y_-y)/(x_-x)));
		color[i] = 1;
		i = edge_list[i].l_next;
	}


	//setting label for cycles...
	for(int ii=1;ii<cycle_list.size();ii++){
		int i = cycle_list[ii].left_most_eptr;
		//printf("for cycle %d left_most_eptr = %d\n",ii,i);
		double y,y_,y1,y2,x,x_,x1,x2;
		x = edge_list[i].l.v1.x;
		x_ = edge_list[i].l.v2.x;
		x2 = edge_list[edge_list[i].l_next].l.v2.x;
		x1 = edge_list[edge_list[i].l_prev].l.v1.x;
		y = edge_list[i].l.v1.y;
		y_ = edge_list[i].l.v2.y;
		y2 = edge_list[edge_list[i].l_next].l.v2.y;
		y1 = edge_list[edge_list[i].l_prev].l.v1.y;
		xff = yff = 0.0;
		if(cycle_list[edge_list[i].cycle_no].conf){
			if(x < x1 && x_ < x2) xff = ff;
			if(x > x1 && x_ > x2) xff = -ff;
			if(y < y1 && y_ < y2) yff = ff;
			if(y > y1 && y_ > y2) yff = -ff;
		}
		else{
			if(x < x1 && x_ < x2) xff = -ff;
			if(x > x1 && x_ > x2) xff = ff;
			if(y < y1 && y_ < y2) yff = -ff;
			if(y > y1 && y_ > y2) yff = ff;
		}
		fprintf(fp, "set label \"C%d\" at %lf,%lf tc rgb %d rotate by %lf left front \n",
					ii,((x+x_)/2+6*xff),((y+y_)/2+6*yff),cycle_list[ii].rgb,57.3248*atan((y_-y)/(x_-x)));
	}
	fprintf(fp, "set label \"C(INF)\" at %lf,%lf center front\n",(x_max-x_min)/2,y_min);
	fprintf(fp, "plot NaN t ''	\n");
	fclose(fp);
	system("./run");
}

void precalculate(vector<edge_record> &edge_list, vector<cycle> &cycle_list){
	cycle_list.resize(edge_list.size());
	vector<int> color(edge_list.size(),0);
	color[0] = 1;
	int idx = 1;
	int x_min;
	int i = 1;
	x_min = i;
	while(1){				// assigns unique cycle_no to each half_edge cycle... and finds left_most_eptr in each cycle..
		if(color[i]){ // if already colored....
			cycle_list[idx].left_most_eptr = x_min;
			idx++;
			i = find(color.begin(),color.end(),0)-color.begin(); // finds index whose color is 0;
			if(i==color.size()) break;
			x_min = i;
		}
		edge_list[i].cycle_no = idx;
		color[i] = 1;
		if(edge_list[i].l.v2.x < edge_list[x_min].l.v2.x) x_min = i;
		i = edge_list[i].l_next;
	}
	cycle_list.resize(idx);

	for(int i=1;i<cycle_list.size();i++) printf("cycle %d has left most eptr = %d\n",i,cycle_list[i].left_most_eptr);
	for(int i=1;i<cycle_list.size();i++){ // setting cycles as innercycle(1) or outercycle(0)
		Point p1,p2,p3;
		p1.x = edge_list[cycle_list[i].left_most_eptr].l.v1.x;
		p1.y = edge_list[cycle_list[i].left_most_eptr].l.v1.y;
		p2.x = edge_list[cycle_list[i].left_most_eptr].l.v2.x;
		p2.y = edge_list[cycle_list[i].left_most_eptr].l.v2.y;
		p3.x = edge_list[edge_list[cycle_list[i].left_most_eptr].l_next].l.v2.x;
		p3.y = edge_list[edge_list[cycle_list[i].left_most_eptr].l_next].l.v2.y;
		if(rotation(p1,p2,p3) == -1) cycle_list[i].conf =1; //anti-clockwise rotation set it to innercycle..
		else cycle_list[i].conf = 0;
	}

}

// finds to which cycle left_most_point of each outer cycle connects to.....
void find_face_graph(vector<edge_record> &edge_list, vector<cycle> &cycle_list){

	for(int i=1;i<cycle_list.size();i++){
		if(!cycle_list[i].conf){ // graph from outer cycles only...
				int eptr = cycle_list[i].left_most_eptr;
				set<int> twin_cycles; //contains all adjacent interior cycles.
				int t_eptr = edge_list[eptr].l_next;
				twin_cycles.insert(edge_list[edge_list[eptr].l_].cycle_no);
				while(t_eptr != eptr){ //pickup all twin cycles....
					twin_cycles.insert(edge_list[edge_list[t_eptr].l_].cycle_no);
					t_eptr = edge_list[t_eptr].l_next;
				}
				Point p1,p2,p3,p4;
				p1.x = edge_list[eptr].l.v2.x;
				p1.y = edge_list[eptr].l.v2.y;
				p2.x = x_min;
				p2.y = p1.y;
				Line l1 = {p1,p2};
				double dist = INT_MAX;
				set<pair<double,int> > lines_intersecting;
				vector<int> count_of_cycles(cycle_list.size(),0);
				//find half edges intersecting to this horizontal line....
				for(int j=1;j<edge_list.size();j++){
					// No need to check half edges form current cycle or twin cycle...
					if(edge_list[j].cycle_no == i || twin_cycles.find(edge_list[j].cycle_no)!=twin_cycles.end()) continue;
					p3.x = edge_list[j].l.v1.x;
					p3.y = edge_list[j].l.v1.y;
					p4.x = edge_list[j].l.v2.x;
					p4.y = edge_list[j].l.v2.y;
					Line l2 = {p3,p4};

					if(is_intersecting(l1,l2)){
						//printf("current cno = %d\n",i );
						//printf("(%lf,%lf),(%lf,%lf) 	and 	(%lf,%lf),(%lf,%lf) are intersecting....\n",
						//l1.v1.x,l1.v1.y,l1.v2.x,l1.v2.y,l2.v1.x,l2.v1.y,l2.v2.x,l2.v2.y);
						//printf("intersecting cno = %d\n",edge_list[j].cycle_no);
						Point p = intersection_point(l1,l2);
						//printf("distance = %lf\n",distance(p,p1));
						dist = distance(p,p1);
						lines_intersecting.insert(mp(dist,j));
						if(lines_intersecting.size()>2){
							auto it = lines_intersecting.end();
							it--;
							lines_intersecting.erase(it);
						}
						count_of_cycles[edge_list[j].cycle_no]++;
					}
				}

				if(lines_intersecting.size()>=2){ //if there were some edges intersecting the horizontal line..
					int cno = edge_list[lines_intersecting.begin()->second].cycle_no; // checkout first one...
					if(count_of_cycles[cno] == 1){ // if only 1 intersection to that cycle connect its innercycle...
						if(cycle_list[cno].conf == 1){
							cycle_list[i].parent_cycle = cno;
							cycle_list[cno].child_cycle.pb(i);
						}
						else{ // pickup the second edge that will be innercycle.....
							auto it = lines_intersecting.begin();
							it++;
							cno = edge_list[it->second].cycle_no;
							cycle_list[i].parent_cycle = cno;
							cycle_list[cno].child_cycle.pb(i);
						}
					}
					else{ // if the cycle is intersected more than 1 time then select outercycle...
						if(cycle_list[cno].conf == 0){ // still checking first half_edge for begin outercycle...
							cycle_list[i].parent_cycle = cno;
							cycle_list[cno].child_cycle.pb(i);
						}
						else{ // pickup the second edge that will be outercycle...
							auto it = lines_intersecting.begin();
							it++;
							cno = edge_list[it->second].cycle_no;
							cycle_list[i].parent_cycle = cno;
							cycle_list[cno].child_cycle.pb(i);
						}
					}
				}
				else {//if there is no intersection half_edge its parnet_cycle is INFINITY..
					cycle_list[i].parent_cycle = 0;	 // Cycle 0 is infinity cycle...
					cycle_list[0].child_cycle.pb(i);
					//printf("no edges intersecting for %d cycle_no\n",i);
				}
		}
	}
}

void dfs(vector<cycle> &cycle_list, int n, vector<int> &color, int space){
	//if(color[n]) return;
	//printf("dfs(%d[%d %ld])",n,cycle_list[n].parent_cycle,cycle_list[n].child_cycle.size());
	color[n] = 1;
	int p;
	if(n == 0){
		p  = printf("%sC(INF)%s-->",KCYN,KWHT);
		p -= 10;
		for(int i=0;i<cycle_list[n].child_cycle.size();i++){
			if(i) printf("\b|\v\b|----->");
			dfs(cycle_list,cycle_list[n].child_cycle[i],color,space+p);
		}
	}
	else if(cycle_list[n].child_cycle.size()){
		if(cycle_list[n].conf == 0) p = printf("C(%d)--->",n);
		else{
			p = printf("%sC(%d)%s-->",KCYN,n,KWHT);
			p-=10;
		}
		for(int i=0;i<cycle_list[n].child_cycle.size();i++){
			if(i) printf("\b|\v\b|----->");
			dfs(cycle_list,cycle_list[n].child_cycle[i],color,space+p);
		}
	}
	else{
		if(cycle_list[n].conf == 1) printf("%sC(%d)%s\n",KCYN,n,KWHT);
		else	printf("C(%d)\n",n);
	}
}

void print_half_edge_list(vector<edge_record> &edge_list){
	for(int i=1;i<edge_list.size();i++){ //prints input data on terminal....
		printf("e%d 	(%lf,%lf)->(%lf,%lf)   %d %d %d\n",edge_list[i].e_no,edge_list[i].l.v1.x,edge_list[i].l.v1.y,
					edge_list[i].l.v2.x,edge_list[i].l.v2.y,edge_list[i].l_,edge_list[i].l_prev,edge_list[i].l_next);
	}
}

int main(int argc, char* argv[]){
	if(argc < 2){printf("usage %s <input_file> \n",argv[0]); exit(1);}
	//srand(time(NULL)); //seed random numbers...
	printf("%d\n",getpid());
	FILE *fp = fopen(argv[1],"r");
	vector<edge_record> edge_list(1);
	double x1,y1,x2,y2;
	int twin_idx,prev_idx,next_idx,edge_no;
	fscanf(fp,"%*[^\n]%*c"); //ignores the first line.....
	while(!feof(fp)){ //take input form 'input' file......
		fscanf(fp,"e%d: (%lf,%lf) (%lf,%lf) %d %d %d\n", &edge_no,&x1,&y1,&x2,&y2,  &twin_idx,&prev_idx,&next_idx);
		x_min = min(x_min,min(x1,x2));
		x_max = max(x_max,max(x1,x2));
		y_min = min(y_min,min(y1,y2));
		y_max = max(y_max,max(y1,y2));
		edge_record er;
		er.e_no = edge_no;
		er.l = {{x1,y1},{x2,y2}};
		er.l_ = twin_idx;
		er.l_prev = prev_idx;
		er.l_next = next_idx;
		edge_list.pb(er);
		//printf("%lf\n",er.l.F.F);
	}
	print_half_edge_list(edge_list);
	for(int i=0;i<edge_list.size();i++){ //checks whether pointers given in input are correct or not....
		int twin = edge_list[i].l_;
		int prev = edge_list[i].l_prev;
		int next = edge_list[i].l_next;
		int n =  edge_list.size();
		if(twin >= n || prev >= n || next >= n){
			printf("edge no %d in 'input' file is wrong...!\n",i);
			printf("edge no should start from '1' and they should be continuous.\n" );
			exit(1);
		}
	}
	vector<cycle> cycle_list;
	precalculate(edge_list,cycle_list);
	for(int i=1;i<cycle_list.size();i++) cycle_list[i].rgb = rand()%(1<<24);
	print_gui(edge_list,cycle_list);
	find_face_graph(edge_list,cycle_list);
	vector<int> color(cycle_list.size(),0);
	//prints face-graphs...
	cout<<"\n\n\nFACE GRAPH  is:\n\n"<<endl;
	for(int i=0;i<cycle_list.size();i++) if(color[i] == 0 && cycle_list[i].child_cycle.size()) dfs(cycle_list,i,color,0);
	for(int i=0;i<cycle_list.size();i++) if(color[i] == 0) dfs(cycle_list,i,color,0);
	int f=0;
	for(int i=0;i<cycle_list.size();i++) if(cycle_list[i].conf) f++;
	printf("So total no of faces are %d\n",f+1);
	printf("Every connected component represents 1 face\n");
	printf("Colored cycles(RED) in each connected component is Inner Cycle represents a FACE that may contains holes\n");
	return 0;
}
