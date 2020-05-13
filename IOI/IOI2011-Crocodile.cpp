/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : International Olympiad In Informatics (IOI) 2011 day 2
   problem name : Crocodile (IOI 2011 - Crocodile)
   problem link : https://oj.uz/problem/view/IOI11_crocodile

   Problem's solution:
     Multi-source dijkstra from every exit node and find second shortest path to any node,
     answer is the second shortest path to node 0.

*/

//#include "grader.cpp"
#include "crocodile.h"
#include <bits/stdc++.h>

using namespace std ;

const int MAX = 1e5 + 10 ;

pair<int , int> dist[MAX] ;
vector< vector< pair<int , int> > >adj(MAX) ;

int travel_plan(int N, int M, int R[][2], int L[], int K, int P[])
{
	memset(dist , -1 , sizeof(dist)) ;
	for(int i = 0 ; i < M ; ++i)
	{
		int x = R[i][0] , y = R[i][1] ;
		adj[x].push_back({y , L[i]*1ll}) ;
		adj[y].push_back({x, L[i] * 1ll}) ;
	}
	priority_queue< pair<int , int> , vector< pair<int , int> > , greater< pair<int , int> > >q ;
	for(int i = 0 ; i < K ; ++i)
	{
		dist[P[i]] = {0 , 0} ;
		q.push({0ll, P[i]}) ;
	}
	while(!q.empty())
	{
		pair<int, int>p = q.top() ;
		q.pop() ;
		int node = p.second ;
		int cost = p.first ;
		if(cost > dist[node].second)
			continue ;
		for(auto &child : adj[node])
		{
			int to = child.first ;
			int ncost = cost + child.second ;
			int prv = dist[to].second ;
			if(ncost < dist[to].first || dist[to].first == -1)
				dist[to].second = dist[to].first , dist[to].first = ncost ;
			else if(ncost < dist[to].second || dist[to].second == -1)
				dist[to].second = ncost ;
			if(dist[to].second < prv || (prv == -1 && dist[to].second != -1))
				q.push({dist[to].second, to}) ;
		}
	}
	return dist[0].second ;
}


