#ifndef __CGAL_BASIC__H
#define __CGAL_BASIC__H

#include <bits/stdc++.h>
using namespace std;


class Point{
public:
	double x,y;
	Point(double a=0, double b=0);
};

class Line{
public:
	Point v1,v2;
	Line(Point p1 = {0,0}, Point p2 = {0,0});
};



int rotation(Point p1, Point p2, Point p3);
void convex_hull(vector<Point > &v, vector<Point > &cv);
double  area_polygon(vector<Point > v);
bool onsegment(Point p1, Point p2, Point p3);
int is_intersecting(Line l1, Line l2);
Point intersection_point(Line l1, Line l2);

#endif
