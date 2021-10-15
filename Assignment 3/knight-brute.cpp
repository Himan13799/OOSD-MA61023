#include<iostream>

using namespace std;

/*to ensure all the starting positions are tried 
before declaring non-existence of knight's tour
*/
int nonempty=1;

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
			cout<<*((board+i*N)+j)<<" ";
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
function to search for a tour with:
current: as starting position
move[]: the 8 possible moves of a knight from a position
*/
bool search_tour(int *sol, knight move[], knight current, knight begin, int step, int N)
{
	knight next;
	if(step==N*N)
		return true;
	for(int i=0;i<8;i++)
	{
		next.x = current.x + move[i].x;
		next.y = current.y + move[i].y;
		if(valid(next,sol,N))
		{
			*((sol+N*next.x) + next.y)=step+1;
			if(search_tour(sol, move, next, begin, step+1, N))
				return true;
			else
				*((sol+N*next.x) + next.y) = -1;
		}
	}
	return false;
}

/*
Function for initiating search process of a knight's tour
*/
bool knight_tour(int N,int *cmp)
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
	int start_x = rand()%N;
	int start_y = rand()%N;
	while(*((cmp+N*start_x)+start_y)==1)
	{
		start_x = rand()%N;
		start_y = rand()%N;
	}
	*((cmp+N*start_x)+start_y) = 1;
	nonempty++;
	knight present = {start_x,start_y}, start = {start_x,start_y};
	knight move[8] = {{2,1},{1,2},{-1,2},{-2,1},{-2,-1},{-1,-2},{1,-2},{2,-1}};
	solution[start_x][start_y] = step;
	if(search_tour(&solution[0][0], move, present, start, step, N)==false)
	{
		return false;
	}
	else
	{
		cout<<"One of the Knight's tour is: \n";
		display(&solution[0][0],N);
		return true;
	}
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