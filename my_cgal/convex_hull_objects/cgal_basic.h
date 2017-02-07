#ifndef __CGAL_MY_BASIC
#define __CGAL_MY_BASIC
#include<bits/stdc++.h>
template<typename T> using point = pair<T,T>;
template<typename T> using line = pair<pair<T,T>,pair<T,T> >;

template<typename T>
int Rotation(point<T> p1, point<T> p2, point<T> p3);

template<typename T>
void convex_hull(vector<point<T> > &v, vector<point<T> > &cv);

template<typename T>
double  area_polygon(vector<point<T> > v);

template<typename T>
bool onsegment(point<T> p1, point<T> p2, point<T> p3);

template<typename T>
int is_intersecting(line<T> l1, line<T> l2);

template<typename T>
point<double> intersection_point(line<T> l1, line<T> l2);

#endif