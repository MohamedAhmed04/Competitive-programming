/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : APIO 2008 
   problem name : roads (APIO 2008 - roads)
   problem link : https://tioj.ck.tp.edu.tw/problems/1740
   You can use google translate to understand the problem statement

   Problem's solution : 
    First add to answer the edges that must be added else then graph will be disconnected.
    we can find concrete roads to be added by adding all cobbled edges then see if we add current concrete road no cycle will happen.
    do the same to cobbled edges.
    Now if count if added cobbled roads is > k then NoSolution(), else then add cobbled roads that won't make cycle
    until making count of cobbled roads be exactly k then add concrete roads to make the graph MST.
    implementation is same like implementing kruskal.
    Now check if it's tree and count of edges is k and number of roads added is n-1.

*/



//#include "1740_roads.h"
#include "lib1740.h"
#include <bits/stdc++.h>

using namespace std ;

const int MAX = 200100 ;

int U[MAX], V[MAX], C[MAX] , par[MAX] ;
int n , m , k ;

void init()
{
	for(int i = 0 ; i < MAX ; ++i)
		par[i] = i ;
}

int root(int node)
{
	if(par[node] == node)
		return node ;
	return (par[node] = root(par[node])) ;
}

void Union(int x , int y)
{
	int a = root(x) ;
	int b = root(y) ;
	if(a == b)
		return ;
	par[a] = b ;
}

vector<int>ans ;
int cnt = 0 ;

void solve(int cur)
{
	init() ;
	for(int i = 0 ; i < m ; ++i)
	{
		if(C[i] == cur)
			Union(U[i] , V[i])  ;
	}
	for(int i = 0 ; i < m ; ++i)
	{
		if(C[i] != cur && root(U[i]) != root(V[i]))
		{
			Union(U[i] , V[i]) ;
			ans.push_back(i) ;
			if(C[i] == 0)
				cnt++ ;
		}
	}
}

int main()
{	
	Init(n, m, k, U, V, C);
	solve(0) ;
	solve(1) ;
	if(cnt > k)
	{
		NoSolution();
		return 0 ;
	}
	init() ;
	for(auto &i : ans)
		Union(U[i] , V[i]) ;
	for(int i = 0 ; i < m ; ++i)
	{
		if(C[i] == 0 && root(U[i]) != root(V[i]) && cnt < k)
		{
			cnt++ ;
			ans.push_back(i) ;
			Union(U[i] , V[i]) ;
		}
	}
	for(int i = 0 ; i < m ; ++i)
	{
		if(C[i] == 1 && root(U[i]) != root(V[i]))
		{
			ans.push_back(i) ;
			Union(U[i] , V[i]) ;
		}
	}
	bool flag = true ;
	for(int i = 1 ; i <= n ; ++i)
	{
		if(root(i) != root(1))
			flag = false ;
	}
	if(flag == false || cnt != k || ans.size() != n-1)
		NoSolution() ;
	else
	{
		for(auto &i : ans)
			Solution(U[i] , V[i] , C[i]) ;
	}
	return 0 ;
}