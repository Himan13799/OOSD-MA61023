/*
Himanshu Surgade
17MA20056
Description: This program prints points in a given range(rectangle) in 2d plane by building a kd tree and then performing search on it.
It can take "any" point as input(from the user or randomly generated) and prints the output to output.txt
*/


#include<bits/stdc++.h>
#include<vector>
#include<utility>
#include<algorithm>

using namespace std;

int crtree=0,qpoint=0; //counter variables for functions build_tree and search_tree
/*
Represents a node in the k-d tree
(x,y) represent the coordinates of the point or the median (x,INT_MIN) for vertical line and (INT_MIN,y) for horizontal line
axis represents whether the line dividing 2d plane is vertical(0) or horizontal(1)
*/
struct point
{
	double x,y;
	int axis;
	struct point *left, *right;
};

/*
range - represents range of the rectangle and 
tmp - represents range of the current node of k-d tree 
xl-lower limit of x,
xh-upper limit of x,
similarly yl and yh
*/
struct t
{
	int xl,xh,yl,yh;
}tmp,range;

//function to create new node in kd tree
struct point *newPoint(double a, double b, int dir)
{
	struct point *p = new point;
	p->x=a;
	p->y=b;
	p->axis = dir;
	p->left = NULL;
	p->right =NULL;
	return p;
}

//comparator function for sorting with respect to 'x' 
bool compare_x(const pair<int,int> &A,const pair<int,int> &B)
{
	if(A.first<=B.first)
		return 1;
	else
		return 0;
}

//comparator function for sorting with respect to 'y'
bool compare_y(const pair<int,int> &A,const pair<int,int> &B)
{
	if(A.second<=B.second)
		return 1;
	else
		return 0;
}

/*
function which returns root of the built k-d tree
Input: list of points{(x1,y1),(x2,y2),...,(xn,yn)} and current depth of kd tree
Output: Root of the current sub-tree
*/
struct point* build_tree(vector<pair<int,int>> &V, int depth)
{
	crtree++;
	if(V.size()==1)
	{	
		return(newPoint(V[0].first,V[0].second,2));
	}
	else
	{
		double median=0.0; //to store the median of sub sequence
		int n = V.size();
		vector<pair<int,int>> p1,p2;//to store the sub sequences
		int axis=depth%2;
		if(axis==0)
		{	
			sort(V.begin(),V.end(),&compare_x);
			if ((n % 2)!= 0) 
			{
				median = (double)V[n/2].first;
				//loops to create subsequence
				for (int i=0; i<(n/2+1); i++) 
        			p1.push_back( make_pair(V[i].first,V[i].second));
        		for (int i=(n/2+1); i<n; i++) 
        			p2.push_back( make_pair(V[i].first,V[i].second));
			}
			else
			{
				median = (double)(V[(n-1)/2].first + V[n/2].first)/2.0;
				//loops to create subsequence
				for (int i=0; i<((n-1)/2 + 1); i++) 
        			p1.push_back( make_pair(V[i].first,V[i].second));
        		for (int i=((n-1)/2 + 1); i<n; i++) 
        			p2.push_back( make_pair(V[i].first,V[i].second));
			}
		}
		else
		{
			sort(V.begin(), V.end(),&compare_y);
			if((n%2)!=0)
			{	
				median = (double)V[n/2].second;
				//loops to create subsequence
				for (int i=0; i<(n/2+1); i++) 
        			p1.push_back( make_pair(V[i].first,V[i].second));
        		for (int i=(n/2+1); i<n; i++) 
        			p2.push_back( make_pair(V[i].first,V[i].second));
			}
			else
			{
				median = (double)(V[(n-1)/2].second + V[n/2].second)/2.0;
				//loops to create subsequence
				for (int i=0; i<((n-1)/2 + 1); i++) 
        			p1.push_back( make_pair(V[i].first,V[i].second));
        		for (int i=((n-1)/2 + 1); i<n; i++) 
        			p2.push_back( make_pair(V[i].first,V[i].second));
			}
		}
		struct point *p_left=NULL,*p_right=NULL;
		p_left = build_tree(p1,depth+1);
		p_right = build_tree(p2,depth+1);
		struct point *v=NULL;
		if(axis==0) 
			v = newPoint(median,INT_MIN,0);
		else
			v = newPoint(INT_MIN,median,1);
		v->left = p_left;
		v->right = p_right;
		return v;
	}

}

//function to determine whether leaf nodes are in the range of given rectangle 'rect'
bool inRange(int a,int b, struct t rect)
{
	if(a>=rect.xl && a<=rect.xh)
		if(b>=rect.yl && b<=rect.yh)
			return 1;
	return 0;
}

//function to determine whether the rectangle 'r' contains the current sub-tree 'sub'
bool contains(struct t sub, struct t r)
{
	if(sub.xl>=r.xl && sub.xh<=r.xh)
		if(sub.yl>=r.yl && sub.yh<=r.yh)
			return 1;
	return 0;
}

//function to determine whether the rectangle 'r' intersects the current sub-tree 'sub'
bool intersects(struct t sub, struct t r)
{
	if(sub.xl<=r.xh && sub.xh>=r.xl)
		if(sub.yl<=r.yh && sub.yh>=r.yl)
			return 1;
	return 0;
}

//function to print whole sub-tree which is contained in the range of the rectangle
void reportSubTree(struct point *r)
{
	ofstream fi;
	fi.open("output.txt",ios::app);
	if(r->left==NULL && r->right==NULL)
	{
		fi<<"("<<r->x<<","<<r->y<<")\n";
		fi.close();
		return;
	}
	else
	{
		reportSubTree(r->left);
		reportSubTree(r->right);
	}
}

/*
Function for the search query
Input: root of the k-d tree and the range of rectangle given
Prints all the points present within the range of the rectangle
*/
void search_tree(struct point *r, struct t range)
{
	ofstream file;
	file.open("output.txt",ios::out|ios::app);
	qpoint++;
	if(r->left==NULL && r->right==NULL)  // for the leaf nodes
	{
		if(inRange(r->x,r->y,range))
			file<<"("<<r->x<<","<<r->y<<")\n";
		file.close();
		return;
	}
	else
	{
		//first searching the left subtree

		int p=tmp.xh,q=tmp.yh; // temporary variables p and q to remember range values
		if(r->axis==0)
			tmp.xh = r->x;
		else
			tmp.yh = r->y;
		if(contains(tmp,range))
			reportSubTree(r->left);
		else
		{
			if(intersects(tmp,range))
				search_tree(r->left,range);
			
			tmp.xh=p;
			tmp.yh=q;
			
		}
		p = tmp.xl;
		q = tmp.yl;

		//then searching the right subtree
		
		if(r->axis==0)
			tmp.xl = r->x;
		else
			tmp.yl = r->y;
		if(contains(tmp,range))
			reportSubTree(r->right);
		else
		{
			if(intersects(tmp,range))
				search_tree(r->right,range);
			
			tmp.xl=p;
			tmp.yl=q;
		}
	}
}

int main()
{
	vector<pair <int, int> > vect; //to store the list of points in 2d plane
	int choice,N,m,s; // choice of input by user, N number of points, m = x-coordinate of point, n= y-coordinate of point
	cout<<"Enter the choice(1 or 2): \n";
	cout<<"1 - Let the program generate points: \n";
	cout<<"2 - Enter the points yourself: \n";
	cin>>choice;
	cout<<"Enter the number of points: \n";
	cin>>N;
	int arr[2*N];
	if(choice==1)
	{
		ofstream outf;
		outf.open("input.txt",ios::out);
		srand(time(NULL));
		// loop for storing points in input.txt
		for(int i=0;i<N;i++)
		{
			m = rand()%(N/2);
			s = rand()%(N/2);
			outf<<m<<" "<<s<<" ";
		}
		outf.close();
		ifstream in;
		in.open("input.txt",ios::in);
		//loop for copying points into array
		for(int i=0;i<2*N;i++)
			in>>arr[i];
		in.close();
	}
	else
	{
		//loop to get points from user
		for(int i=0;i<2*N-1;i+=2)
		{
			cout<<"Enter the x coordinate of point "<<i/2+1<<": ";
			cin>>arr[i];
			cout<<"Enter the y coordinate of point "<<i/2+1<<": ";
			cin>>arr[i+1];
		}
	}
    int n = sizeof(arr)/sizeof(arr[0]); 
    //loop to create list of points
    for (int i=0; i<n-1; i+=2) 
        vect.push_back( make_pair(arr[i],arr[i+1]));

    struct point *root=NULL;
    root = build_tree(vect, 0);// build kd tree
    
    cout<<"Enter the range of coordinates of rectangle: \n\n";
    cout<<"Enter the x coordinate of lower left corner: ";
    cin>>range.xl;
    cout<<"Enter the y coordinate of lower left corner: ";
    cin>>range.yl;
    cout<<"Enter the x coordinate of upper right corner: ";
    cin>>range.xh;
    cout<<"Enter the y coordinate of upper right corner: ";
    cin>>range.yh;
    cout<<"\n\n****Tree built****\n\ncrtree: "<<crtree<<"\n";
    ofstream f;
    f.open("output.txt",ios::out);
    f<<"Range: x in ["<<range.xl<<","<<range.xh<<"] and y in ["<<range.yl<<","<<range.yh<<"]\n";
    f<<"Points in above range are: \n";
    f.close();
    tmp.xl=INT_MIN;
    tmp.xh=INT_MAX;
    tmp.yl=INT_MIN;
    tmp.yh=INT_MAX;
    search_tree(root, range); // search points in given range
    cout<<"qpoint: "<<qpoint<<"\n";
    return 0; 
}