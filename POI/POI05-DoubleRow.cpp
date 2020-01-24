/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : Polish olympiad in informatics 2005 (POI 2005)
   problem name : Double row (POI 2005 - Double Row)
   problem link : https://szkopul.edu.pl/problemset/problem/cB5m-M5ddsFOWLds2CwcYKge/site/?key=statement

   problem's solution : 
   	first model it as graph problem, where there's undirected edge between every two indexes
   	that mustn't be in the same row, which is the other index which its value is equal to current index
   	value and the index in the other row.
   	then realize that graph will be consisted of multiple undirected connected components
   	and every undirected connected component is cycle with even number of nodes and every node
   	has degree equal to 2.
   	then solve for every connected component, first try to mark any node as 0 (0 is first row, 1 is second row)
   	then see what's the cost for other nodes, make the same again and mark any node as 1, and see the cost.
   	then choose the minimal cost between these two arrangements.
   	and add to answer minimum cost / 2.

*/

#include <bits/stdc++.h>

using namespace std ;

const int MAX = 50010*2 , MAX2 = 1e5+5 ;

int arr[MAX] , last[MAX2] , vis[MAX] , col[MAX] ;
int n ;
vector< vector<int> >adj(MAX) ;
int cost = 0 ;

void dfs(int node , int cur , int st)
{
	vis[node] = st ;
	if((node <= n && cur != 0) || (node > n && cur != 1))
		cost++ ;
	for(auto &child : adj[node])
	{
		if(vis[child] != st)
			dfs(child , !cur , st) ;
	}
}

int main()
{
	memset(vis , -1 , sizeof(vis)) ;
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	cin>>n ;
	for(int i = 1 ; i <= n+n ; ++i)
	{
		cin>>arr[i] ;
		last[arr[i]] = i ;
	}
	for(int i = 1 ; i <= n+n ; ++i)
	{
		if(last[arr[i]] != i)
		{
			adj[i].push_back(last[arr[i]]) ;
			adj[last[arr[i]]].push_back(i) ;
		}
		if(i <= n)
		{
			adj[i].push_back(i+n) ;
			adj[i+n].push_back(i) ;
		}
	}
	int ans = 0 ;
	for(int i = 1 ; i <= n ; ++i)
	{
		if(vis[i] != -1)
			continue ;
		cost = 0 ;
		dfs(i , 0 , 0) ;
		int x = cost ;
		cost =  0 ;
		dfs(i , 1 , 1) ;
		int y = cost ;
		ans += min(x , y) / 2 ;
	}
	return cout<<ans<<"\n" , 0 ;
}		