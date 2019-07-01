/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   problem name : DISQUERY - Distance Query (SPOJ DISQUERY)
   problem link : https://www.spoj.com/problems/DISQUERY/

   problem's solution :
    Minimum edge in the path between two nodes (x and y)
    = min(min edge between x and LCA(x , y) , min edge between y and LCA (x , y) )
    and Maximum edge in the path between two nodes (x and y)
    = max(max edge between x and LCA(x , y) , max edge between y and LCA(x , y) )
    so we can make binary lifting which ansmin[x][i] is minimum edge between
    x and 2^i ancestor of x and ansmax[x][i] is maximum edge between y and 2 ^ i ancestor of y
    and with the same way to find LCA we will make it to find minimum in the path and maximum in the path.

*/

#include <bits/stdc++.h>

using namespace std ;

const int MAX = 100005 ;

vector< vector< pair<int , int> > >adj(MAX) ;
int P[MAX][23] , dep[MAX] , ansmin[MAX][23] , ansmax[MAX][23];

void dfs(int node , int par , int level)
{
	P[node][0] = par ;
	dep[node] = level ;
	for(int i = 1 ; i < 22 ; ++i)
	{
		if(P[node][i-1] == -1)
		{
			P[node][i] = -1 ;
			continue ;
		}
		P[node][i] = P[P[node][i-1]][i-1] ;
		ansmin[node][i] = min(ansmin[node][i-1] , ansmin[P[node][i-1]][i-1]) ;
		ansmax[node][i] = max(ansmax[node][i-1] , ansmax[P[node][i-1]][i-1]) ;
	}
	for(auto &child : adj[node])
	{
		if(child.first == par)
			continue ;
		ansmin[child.first][0] = child.second ;
		ansmax[child.first][0] = child.second ;
		dfs(child.first , node , level+1) ;
	}
	return ;
}

pair<int , int>solve(int x , int y)
{
	if(dep[x] < dep[y])
		swap(x , y) ;
	int MIN = INT_MAX , MAX = INT_MIN ;
	for(int i = 21 ; i >= 0 ; --i)
	{
		if(dep[x] - (1 << i) >= dep[y])
		{
			MIN = min(MIN , ansmin[x][i]) ;
			MAX = max(MAX , ansmax[x][i]) ;
			x = P[x][i] ;
		}
	}
	if(x == y)
		return {MIN , MAX} ;
	for(int i = 21 ; i >= 0 ; --i)
	{
		if(P[x][i] != P[y][i])
		{
			MIN = min(MIN , ansmin[x][i]) ;
			MAX = max(MAX , ansmax[x][i]) ;
			MIN = min(MIN , ansmin[y][i]) ;
			MAX = max(MAX , ansmax[y][i]) ;
			x = P[x][i] , y = P[y][i] ;
		}
	}
	MIN = min(MIN , ansmin[x][0]) ;
	MAX = max(MAX , ansmax[x][0]) ;
	MIN = min(MIN , ansmin[y][0]) ;
	MAX = max(MAX , ansmax[y][0]) ;
	return {MIN , MAX} ;
}

int main()
{
	int n ;
	scanf("%d" , &n) ;
	for(int i = 0 ; i < n-1 ; ++i)
	{
		int x , y , z ;
		scanf("%d %d %d" , &x , &y , &z) ;
		adj[x].push_back({y , z}) ;
		adj[y].push_back({x , z}) ;
	}
	for(int i = 0 ; i <= n ; ++i)
	{
		for(int j = 0 ; j < 22 ; ++j)
			P[i][j] = -1 ;
	}
	ansmin[1][0] = INT_MAX ;
	ansmax[1][0] = INT_MIN ;
	dfs(1 , -1 , 0) ;
	int q ;
	scanf("%d" , &q) ;
	while(q--)
	{
		int x , y ;
		scanf("%d %d" , &x , &y) ;
		pair<int , int>ans = solve(x , y) ;
		printf("%d %d\n" , ans.first , ans.second) ;
	}
	return 0 ;
}
