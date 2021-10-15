/*
Guidance from the following implementation has been taken while building this code:
https://iq.opengenus.org/chans-algorithm-convex-hull/
*/

#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>
#include <time.h>
using namespace std;

// structure for storing x and y coordinates of a point in 2D plane
struct Point
{
	int x;
	int y;
	Point(int x1=0, int y1=0)
	{
		x = x1;
		y = y1;
	}
}p0;

int length(struct Point a, struct Point b)
{
	// function for computing length of the line segment between two points a and b
	return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}

int direction(struct Point a, struct Point b, struct  Point c)
{
	/*
	Important function to find the alignment of the line segments between (a and b) and (b and c)
	through difference of their slopes
	*/
	int slopeDiff = (b.y-a.y)*(c.x-b.x) - (c.y-b.y)*(b.x-a.x);
	if(slopeDiff == 0) return 0;// represents collinear
	if(slopeDiff>0)
		return -1;//represents Clock wise
	else
		return 1;//represents Anti Clockwise
}

int diff(const void *q, const void *r)
{
	// helper function for the function qsort used for sorting
	Point *a = (Point *)q;
	Point *b = (Point *)r;
	int d = direction(p0,*a,*b);
	if (d == 0)
	{	
		if(length(p0,*b)>=length(p0,*a))
			return -1;
		else
			return 1;
	}
	if (d == 1)
		return -1;
	else
		return 1;
}

int tangent(vector<Point> v,struct Point p)
{
	// finds the indices of the point lying on tangent from point p
	// v : vector of objects of structure Point representing vector of hull points
	int l=0;
	int r= v.size();
	int l_before = direction(p, v[0], v[v.size()-1]);
	int l_after = direction(p, v[0], v[(l + 1) % v.size()]);
	while (l < r)
	{
		int c = ((l + r)/2);
		int c_before = direction(p, v[c], v[(c - 1) % v.size()]);
		int c_after = direction(p, v[c], v[(c + 1) % v.size()]);
		int c_side = direction(p, v[l], v[c]);
		if (c_before != -1 and c_after != -1)
			return c;
		else if ((c_side == 1) and (l_after == -1 or l_before == l_after) or (c_side == -1 and c_before == -1))
			r = c;
		else
			l = c + 1 ;
		l_before = -c_after; 
		l_after = direction(p, v[l], v[(l + 1) % v.size()]);
	}
	return l;
}

pair<int,int> extreme_point(vector<vector<Point> >& conv_hulls)
{
	int h= 0,p= 0;
	for (int i=0; i<conv_hulls.size(); ++i){
		int min_index=0;
		int min_y = conv_hulls[i][0].y;
		for(int j=1; j< conv_hulls[i].size(); ++j){
			if(conv_hulls[i][j].y < min_y){
				min_y=conv_hulls[i][j].y;
				min_index=j;
			}
		}
		if(conv_hulls[i][min_index].y < conv_hulls[h][p].y){
			h=i;
			p=min_index;
		}   
	}
	return make_pair(h,p);
}

pair<int,int> next_point(vector<vector<Point> >& conv_hulls, pair<int,int> lpoint)
{
	struct Point p = conv_hulls[lpoint.first][lpoint.second];
	pair<int,int> next = make_pair(lpoint.first, (lpoint.second + 1) % conv_hulls[lpoint.first].size());
	for (int h=0; h< conv_hulls.size(); h++){
		if(h != lpoint.first){
			int s= tan(conv_hulls[h],p);
			Point q= conv_hulls[next.first][next.second];
			Point r= conv_hulls[h][s];
			int t= direction(p,q,r);
			if( t== -1 || (t==0) && length(p,r)>length(p,q))
				next = make_pair(h,s);
		}
	}
	return next;
}

vector<Point> keep_left (vector<Point>& v,struct Point p)
{
	while(v.size()>1 && direction(v[v.size()-2],v[v.size()-1],p) != 1)
		v.pop_back();
	if(!v.size() || !(v[v.size()-1].x==p.x && v[v.size()-1].y==p.y))
		v.push_back(p);
	return v;
}

//graham scan for sub-hulls
vector<Point> graham_scan(vector<Point>& points)
{
	if(points.size()<=1)
		return points;
	qsort(&points[0], points.size(), sizeof(Point), diff);
	vector<Point> lower_hull;
	for(int i=0; i<points.size(); ++i)
		lower_hull = keep_left(lower_hull,points[i]);
	reverse(points.begin(),points.end());
	vector<Point> upper_hull;
	for(int i=0; i<points.size(); ++i)
		upper_hull = keep_left(upper_hull,points[i]);
	for(int i=1;i<upper_hull.size();++i)
		lower_hull.push_back(upper_hull[i]);
	return lower_hull;   
}

// chans algorithm
vector<Point> chans(vector<Point> v)
{
	for(int t=0; t< v.size(); ++t)
	{
		for(int m=1; m< (1<<(1<<t)); ++m)
		{
			vector<vector<Point> > conv_hulls;
			for(int i=0;i<v.size();i=i+m)
			{
				vector<Point> part;
				if(v.begin()+i+m <= v.end())
					part.assign(v.begin()+i,v.begin()+i+m);
				else
					part.assign(v.begin()+i,v.end());        	
				conv_hulls.push_back(graham_scan(part));
			}
			vector<pair<int,int> > hull;
			hull.push_back(extreme_point(conv_hulls));
			for(int i=0; i<m; ++i)
			{
				pair<int,int> p= next_point(conv_hulls,hull[hull.size()-1]);
				vector<Point> output;
				if(p==hull[0])
				{
					for(int j=0; j<hull.size();++j)
					{
						output.push_back(conv_hulls[hull[j].first][hull[j].second]);
					}
					return output;
				}
				hull.push_back(p);
			}
		}
	}
}

int main()
{
	int m,n;
	int x=0,y=0;
	srand(time(NULL));
	int T = rand()%51 + 50;
	Point points[T];
	ofstream outfile;
	outfile.open("input.txt",ios::out);
	for(int i=0;i<T;i++)
	{
		m = (rand()%50);
		n = (rand()%50);
		outfile<<m<<" "<<n<<" ";
	}
	outfile.close();
	ifstream infile;
	infile.open("input.txt",ios::in);
	for(int i=0;i<T;i++)
	{
		infile>>m>>n;
		points[i].x=m;
		points[i].y=n;
	}
	infile.close();
	vector<Point> v(points,points+T);
	vector<Point> output = chans(v);
	ofstream file;
	file.open("output.txt",ios::out);
	file<<"\nConvex Hull\n";
	cout<<"\nConvex Hull is:\n"
	for(int i=0; i< output.size(); ++i)
		file<<"("<<output[i].x<<","<<output[i].y<<")"<<" ";
		cout<<"("<<output[i].x<<","<<output[i].y<<")"<<" ";
	file.close();
}