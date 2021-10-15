#include<iostream>
#include<bits/stdc++.h>

using namespace std;

/*to ensure all the starting positions are tried 
before declaring non-existence of knight's tour
*/
int nonempty=0;
/*
struct knight to represent the position of knight
*/
typedef struct knight
{
	int x,y;
}knight;

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
'knight check' is the position of the next move 
'sol' is the NxN chess board
*/
bool valid(knight check, int *sol, int N)
{
	if(check.x>=0 && check.x<N && check.y>=0 && check.y<N && *((sol+N*check.x) + check.y)==-1)
		return true;
	return false;
}

/*
fuction to find the number of unvisited neighbours from 'pos'
It helps in choosing the position with minimum number of unvisited neighbours
'knight pos': is the position whose degree is to be calculated on NxN board 'sol'
*/
int degree(knight pos, knight move[], int *sol, int N)
{
	int d = 0;
	knight p;
	for(int i=0;i<8;i++)
	{
		p.x = pos.x + move[i].x;
		p.y = pos.y + move[i].y;
		if(valid(p,sol,N))
			d++;
	}
	return d;
}

/*
function to search for a tour with:
current: as starting position
move[]: the 8 possible moves of a knight from a position
*/
bool search_tour(int *sol, knight *current, knight move[], int step, int N)
{
	int min,min_id=-1,min_deg=(N+1);
	knight next;
	int rand_start = rand()%8;
	for(int i=0;i<8;i++)
	{
		int c = (rand_start + i)%8;
		next.x = (*current).x + move[c].x;
		next.y = (*current).y + move[c].y;
		min = degree(next,move,sol,N);
		if(valid(next,sol,N) && (min<min_deg))
		{
			min_id = c;
			min_deg = min;
		}
	}
	if(min_id==-1)
		return false;

	next.x = (*current).x + move[min_id].x;
	next.y = (*current).y + move[min_id].y;
	*((sol+N*next.x) + next.y)=*((sol+((*current).x)*N) + (*current).y)+1;
	(*current).x = next.x;
	(*current).y = next.y;
	return true;
}

/*
Function for initiating search process of a knight's tour
*/
bool knight_tour(int N, int *cmp)
{
	if(nonempty==N*N)
	{
		cout<<"Knight's tour does not exist!\n";
		return true;
	}
	int solution[N][N];
	int step = 1;
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
			solution[i][j]=-1;

	knight move[8] = {{2,1},{1,2},{-1,2},{-2,1},{-2,-1},{-1,-2},{1,-2},{2,-1}};
	int start_x = rand()%N;
	int start_y = rand()%N;
	while(*((cmp+N*start_x)+start_y)==1)
	{
		start_x = rand()%N;
		start_y = rand()%N;
	}
	*((cmp+N*start_x)+start_y) = 1;
	nonempty++;
	knight present = {start_x,start_y};
	solution[start_x][start_y] = step;
	for(int i=0;i<N*N-1;i++)
		if(search_tour(&solution[0][0], &present, move, step, N)==false)
			return false;

	cout<<"One of the knight's tour is: \n";
	display(&solution[0][0],N);
	return true;
}

int main()
{
	int n;
	srand(time(NULL));
	cout<<"Enter the size 'n' of chessboard(nxn) for solution of Knight's tour: \n";
	cin>>n;
	int comp[n][n];
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			comp[i][j]=0;
	while(!knight_tour(n,&comp[0][0]))
		continue;
	return 0;
}