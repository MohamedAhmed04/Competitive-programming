/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : International Olympiad In Informatics (IOI) 2014 day 1
   problem name : Game (IOI 2014-Game)
   problem link : https://oj.uz/problem/view/IOI14_game

   Problem's solution: 
    make dsu, and if number of edges already asked between the 
    two components is < number of nodes in the first component * number of nodes in the second component
    then the answer is no, else then the answer is yes and combine them.

*/

#include "game.h"
//#include "grader.cpp"
#include <bits/stdc++.h>

using namespace std ;

const int MAX = 1500 + 10 ;

int par[MAX] , sz[MAX] , cnt[MAX][MAX] ;

int N ;

void init()
{
	for(int i = 0 ; i <= N ; ++i)
		par[i] = i , sz[i] = 1 ;
}

int root(int node)
{
	if(par[node] == node)
		return node ;
	return (par[node] = root(par[node])) ;
}

int prv , now ;

void Union(int x , int y)
{
	int a = root(x) ;
	int b = root(y) ;
	if(sz[a] < sz[b])
		swap(a , b) ;
	prv = b ;
	now = a ;
	sz[a] += sz[b] ;
	par[b] = a ;
}

void initialize(int n) 
{
	N = n ;
	init() ;
	return ;
}

int hasEdge(int u, int v) 
{
	int a = root(u) ;
	int b = root(v) ;
	if(a == b)
		return 0 ;
	if(sz[a] * sz[b] != cnt[a][b]+1)
	{
		cnt[a][b]++ ;
		cnt[b][a]++ ;
		return 0 ;
	}
	Union(u , v) ;
	for(int i = 0 ; i < N ; ++i)
	{
		cnt[i][now] += cnt[i][prv] ;
		cnt[now][i] = cnt[i][now] ;
		cnt[i][prv] = cnt[prv][i] = 0 ;
	}
	return 1 ;
}
