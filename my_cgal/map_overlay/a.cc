#include "cgal_basic.cc"


struct edge_record{
	line<double> l;
	int e_no,l_,l_prev,l_next; //index pointer to twin, prev and next..
	int cycle,color;
};


int main(){
	FILE *fp = fopen("input","r");
	vector<edge_record> edge_list;
	double x1,y1,x2,y2;
	int twin_idx,prev_idx,next_idx,edge_no;
	fscanf(fp,"%*[^\n]%*c"); //ignores the first line.....
	while(!feof(fp)){
		fscanf(fp,"e%d: (%lf,%lf) (%lf,%lf) %d %d %d\n", &edge_no,&x1,&y1,&x2,&y2,  &twin_idx,&prev_idx,&next_idx);
		struct edge_record er;
		er.e_no = edge_no;
		er.l = mp(mp(x1,y1),mp(x2,y2));
		er.l_ = twin_idx;
		er.l_prev = prev_idx;
		er.l_next = next_idx;
		edge_list.pb(er);
		//printf("%lf\n",er.l.F.F);
	}
	for(int i=0;i<edge_list.size();i++){
		printf("e%d 	(%lf,%lf)->(%lf,%lf)   %d %d %d\n",edge_list[i].e_no,edge_list[i].l.F.F,edge_list[i].l.F.S,edge_list[i].l.S.F,edge_list[i].l.S.S,
													edge_list[i].l_,edge_list[i].l_prev,edge_list[i].l_next);
	}
	sort(edge_list.begin(),edge_list.end());
	int n = edge_list.size();
	for(int i=0;i<n;i++) edge_list[i].color = 0;
	for(int i=0;i<n;i++){
		
	}
}