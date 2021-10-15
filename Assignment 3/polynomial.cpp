#include<bits/stdc++.h>

using namespace std;
/*
Used hard coded values from the implementation of the linear time paper:
http://math.oregonstate.edu/~math_reu/proceedings/REU_Proceedings/Proceedings2004/2004Ganzfried.pdf
*/

int K[8][2]={{-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1}};
int swich[6][2];
int perms[6][8];
int P[][8]={{3,4,2,6,1,5,7,8},{8,7,6,4,2,1,3,5},{5,1,8,6,7,3,4,2},{5,1,3,4,2,6,7,8},{2,1,4,3,5,6,7,8},
{3,4,2,6,1,5,7,8},{8,7,6,4,2,1,3,5},{5,1,3,2,4,6,7,8},{3,2,4,8,1,7,6,5},
{3,4,2,6,1,5,7,8},{8,7,6,4,2,1,3,5},{5,4,1,3,2,6,7,8},{5,2,4,3,1,6,7,8},{8,5,6,4,7,1,2,3},{1,5,7,4,6,8,2,3},
{3,4,6,2,5,7,1,8},{4,2,6,8,1,3,5,7},{8,6,5,1,2,3,4,7},{5,1,8,6,7,3,4,2},{6,1,8,2,5,4,3,7},{7,1,6,4,2,5,3,8},
{3,4,2,6,1,5,7,8},{8,7,6,4,2,1,3,5},{5,1,8,6,7,3,4,2},{5,1,3,4,2,6,7,8},{8,6,7,5,3,4,2,1},{7,8,5,6,3,4,2,1},
{3,4,2,6,1,5,7,8},{8,7,6,4,2,1,3,5},{5,1,3,2,4,6,7,8},{1,5,2,3,4,6,7,8},
{3,4,2,6,1,5,7,8},{8,7,6,4,2,1,3,5},{5,4,1,3,2,6,7,8},{5,2,4,3,1,6,7,8},{8,5,6,4,7,1,2,3},{1,2,4,5,3,6,7,8},
{3,4,6,2,5,7,1,8},{4,2,6,8,1,3,5,7},{8,6,5,1,2,3,4,7},{5,1,8,6,7,3,4,2},{6,1,8,2,5,4,3,7},{6,1,3,5,7,2,8,4}};

/*
Function to initialize the solution matrix A
*/
void intitialize(int *A, int n)
{
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			*((A+i*n)+j) = 0;
}

/*
Function to initialize the hard coded permutation of 8 knight moves and switching values for the permutation
Implemented as described in the above mentioned paper
*/
void intitializeTable(int n)
{
	int r = n%8;
	if(r==0)
	{
		for(int i=0;i<8;i++)perms[0][i] = P[0][i]; swich[0][0] = n-1; swich[0][1] = n-2;
		for(int i=0;i<8;i++)perms[1][i] = P[1][i]; swich[1][0] = 2; swich[1][1] = 2;
		for(int i=0;i<8;i++)perms[2][i] = P[2][i]; swich[2][0] = n-8; swich[2][1] = 1;
		for(int i=0;i<8;i++)perms[3][i] = P[3][i]; swich[3][0] = 7; swich[3][1] = n-3;
		for(int i=0;i<8;i++)perms[4][i] = P[4][i]; swich[4][0] = 0; swich[4][1] = 0;
	}
	if(r==1)
	{
		for(int i=0;i<8;i++)perms[0][i] = P[5][i]; swich[0][0] = n-1; swich[0][1] = n-2;
		for(int i=0;i<8;i++)perms[1][i] = P[6][i]; swich[1][0] = 2; swich[2][1] = 2;
		for(int i=0;i<8;i++)perms[2][i] = P[7][i]; swich[3][0] = n-6; swich[3][1] = (n+9)/2;
		for(int i=0;i<8;i++)perms[3][i] = P[8][i]; swich[4][0] = 0; swich[4][1] = 0;
	}
	if(r==2)
	{
		for(int i=0;i<8;i++)perms[0][i] = P[9][i]; swich[0][0] = 6; swich[0][1]=1;
		for(int i=0;i<8;i++)perms[1][i] = P[10][i]; swich[1][0] = 3; swich[1][1]=1;
		for(int i=0;i<8;i++)perms[2][i] = P[11][i]; swich[2][0] = n-15; swich[2][1]=4;
		for(int i=0;i<8;i++)perms[3][i] = P[12][i]; swich[3][0] = 10; swich[3][1]=n-2;
		for(int i=0;i<8;i++)perms[4][i] = P[13][i]; swich[4][0] = 5; swich[4][1]= (n-6)/2;
		for(int i=0;i<8;i++)perms[5][i] = P[14][i]; swich[5][0] = 0; swich[5][1]= 0;
	}
	if(r==3)
	{
		for(int i=0;i<8;i++)perms[0][i] = P[15][i]; swich[0][0] = n-1; swich[0][1] = n-2;
		for(int i=0;i<8;i++)perms[1][i] = P[16][i]; swich[1][0] = n-6; swich[1][1] = n;
		for(int i=0;i<8;i++)perms[2][i] = P[17][i]; swich[2][0] = 2; swich[2][1] = 5;
		for(int i=0;i<8;i++)perms[3][i] = P[18][i]; swich[3][0] = n-10; swich[3][1] = 3;
		for(int i=0;i<8;i++)perms[4][i] = P[19][i]; swich[4][0] = (n+1)/2; swich[4][1] = n-2;
		for(int i=0;i<8;i++)perms[5][i] = P[20][i]; swich[5][0] = 0; swich[5][1] = 0;
	}
	if(r==4)
	{
		for(int i=0;i<8;i++)perms[0][i] = P[21][i]; swich[0][0] = n-1; swich[0][1]=n-2;
		for(int i=0;i<8;i++)perms[1][i] = P[22][i]; swich[1][0] = 2; swich[1][1]=2;
		for(int i=0;i<8;i++)perms[2][i] = P[23][i]; swich[2][0] = n-8; swich[2][1]=1;
		for(int i=0;i<8;i++)perms[3][i] = P[24][i]; swich[3][0] = 10; swich[3][1]=n-5;
		for(int i=0;i<8;i++)perms[4][i] = P[25][i]; swich[4][0] = 13; swich[4][1]=(n+2)/2;
		for(int i=0;i<8;i++)perms[5][i] = P[26][i]; swich[5][0] = 0;swich[5][1]=0;
	}
	if(r==5)
	{
		for(int i=0;i<8;i++)perms[0][i] = P[27][i]; swich[0][0] = n-1; swich[0][1]=n-2;
		for(int i=0;i<8;i++)perms[1][i] = P[28][i];swich[1][0] = 2; swich[1][1] = 2;
		for(int i=0;i<8;i++)perms[2][i] = P[29][i];
		if(n%16==5)
		{swich[2][0] = n-2; swich[2][1]=(n-5)/2;}
		else
		{swich[2][0] = n-2;swich[2][1]=(n-13)/2;}
		for(int i=0;i<8;i++)perms[3][i] = P[30][i]; swich[3][0] =0; swich[3][1]=0;
	}
	if(r==6)
	{
		for(int i=0;i<8;i++)perms[0][i] = P[31][i]; swich[0][0] = 6; swich[0][1]=1;
		for(int i=0;i<8;i++)perms[1][i] = P[32][i]; swich[1][0] = 3;swich[1][1]=1;
		for(int i=0;i<8;i++)perms[2][i] = P[33][i]; swich[2][0] = n-10; swich[2][1]=1;
		for(int i=0;i<8;i++)perms[3][i] = P[34][i]; swich[3][0] = 10; swich[3][1]=n-2;
		for(int i=0;i<8;i++)perms[4][i] = P[35][i]; swich[4][0] = 3; swich[4][1]=(n+8)/2;
		for(int i=0;i<8;i++)perms[5][i] = P[36][i]; swich[5][0] = 0; swich[5][1] = 0;
	}
	if(r==7)
	{
		for(int i=0;i<8;i++)perms[0][i] = P[37][i]; swich[0][0] = n-1; swich[0][1]=n-2;
		for(int i=0;i<8;i++)perms[1][i] = P[38][i]; swich[1][0] = n-6; swich[1][1]=n;
		for(int i=0;i<8;i++)perms[2][i] = P[39][i]; swich[2][0] = 2; swich[2][1]=5;
		for(int i=0;i<8;i++)perms[3][i] = P[40][i]; swich[3][0] = n-6; swich[3][1]=3;
		for(int i=0;i<8;i++)perms[4][i] = P[41][i]; swich[4][0] = (n+1)/2; swich[4][1]=n-2;
		for(int i=0;i<8;i++)perms[5][i] = P[42][i]; swich[5][0] = 0; swich[5][1]=0;
	}
}

/*
Function to display the knight's tour on NxN 'board'
*/
void display(int *board, int N)
{
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			int num = *((board+i*N)+j);
			if(num/10==0)
				cout<<"  "<<num<<" ";
			else if(num/100==0)
				cout<<" "<<num<<" ";
			else
				cout<<num<<" ";
		}
		cout<<endl;
	}
}

/*
function to check whether a move is valid in the knight's tour
(a,b) is the position of the next move 
'A' is the NxN chess board
*/
bool valid(int *A, int a, int b, int N)
{
	if(a>=0 && a<N && b>=0 && b<N && *((A+N*a)+b)==0)
		return true;
	return false;
}

/*
fuction to find the number of unvisited neighbours from (x,y)
It helps in choosing the position with minimum number of unvisited neighbours
(x,y): is the position whose degree is to be calculated on NxN board 'A'
*/
int degree(int *A, int x, int y, int N)
{
	int deg=0;
	for(int j=0;j<8;j++)
	{
		int u = x + K[j][0];
		int v = y + K[j][1];
		if(valid(A,u,v,N))
			deg++;
	}
	return deg;
}

/*
function to get the next move
*/
int* getNextSquare(int *ar, int *A, int x, int y, int T[], int N)
{
	int min = 9;
	int a=-1,b=-1;
	int key=-1;
	for(int count = 0;count<8;count++)
	{
		int v = x + K[count][0];
		int w = y + K[count][1];
		if(valid(A,v,w,N))
		{
			int deg = degree(A,v,w,N);
			if(deg<min)
			{
				min = deg;
				a=v;
				b=w;
				key = count;
			}
			if(deg==min)
			{
				int k=0;
				while(T[k]!=key && T[k]!=count)
				k++;
				if(T[k]==count)
				{
					a=v;
					b=w;
					key=count;
				}
			}
		}	
	}
	*ar = a;
	*(ar+1)=b;
	return ar;
}

/*
Function for initiating search process of a knight's tour
*/
void Tour(int *A, int N)
{
	int x = 0, y = 0, u, v;
	u = swich[0][0], v = swich[0][1];
	int T[8];
	for(int j=0;j<8;j++)
		T[j] = perms[0][j];
	int t=0,i=1;
	int a[2];
	while(!(x==-1 && y==-1))
	{
		*((A+x*N)+y) = i;
		if(x==u && y==v)
		{
			t++;
			for(int k=0;k<8;k++)
				T[k] = perms[t][k];
			u = swich[t][0];
			v = swich[t][1];
		}
		int *b = getNextSquare(a,A,x,y,T,N);
		x = *b;
		y = *(b+1);
		i++;
	}
}

int main()
{
	int n;
	cout<<"Enter the size of board(nxn) 'n': ";
	cin>>n;
	int board[n][n];
	intitialize(&board[0][0],n);
	intitializeTable(n);
	Tour(&board[0][0],n);
	if(n<5)
		cout<<"Knight's tour does not exist!\n";
	cout<<endl<<"One of the knight's tour is: \n";
	display(&board[0][0],n);
	return 0;
}
