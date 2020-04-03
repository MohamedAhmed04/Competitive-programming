/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : Baltic Olympiad in informatics 2019 day 2
   problem name : Valley (BalticOI - Valley)
   problem link : https://oj.uz/problem/view/BOI19_valley

   Problem's solution: 
   - we will answer the queries offline
   - First root the tree at 1, and let in[node] equals time of intering node and 
     out[node] equals time of exiting node.
   - in each query, cutting the edge splits the tree into two components:
     If the edge from a to b where a is parent of b, Then:
      1 - first component contains nodes whose dfs time is from 1 to in[b]-1 and from out[b]+1 to n
      2 - second component contains nodes whose dfs time is from in[b] to out[b].
   - so the answer of query is escaped if E and R are in the same component.
   - If they aren't then we need to find nearest shop to node R.
   - so we can dfs to answer the queries offline and make segment tree with lazy propagation
     to store the distance between all nodes to current node and if the node doesn't contain a shop then
     make the distance with a large value, and answer of queries that city R is current node, so first we'll check
     if current node and E are in the same component after cutting edge I and if they aren't then we need to find the
     shortest distance to a shop inside current node component so we will query to find min in range of componenet in
     the segment tree, and if the answer is > 10^14 (largest possible distance) then the answer is oo (no shop in the component).

*/

#include <bits/stdc++.h>

using namespace std ;

const long long inf = 1e15 , inf2 = 1e14 ;
const int MAX = 1e5 + 10 ;

long long tree[4 * MAX] , lazy[4 * MAX] ;

void prop(int node , int l , int r)
{
	tree[node] += lazy[node] ;
	if(l != r)
	{
		lazy[node << 1] += lazy[node] ;
		lazy[node << 1 | 1] += lazy[node] ;
	}
	lazy[node] = 0 ;
	return ;
}

void update(int node , int l , int r , int from , int to , long long val)
{
	prop(node , l , r) ;
	if(from > r || to < l)
		return ;
	if(l >= from && r <= to)
	{
		lazy[node] += val ;
		prop(node , l , r) ;
		return ;
	}
	int mid = (l + r) >> 1 ;
	update(node << 1 , l , mid , from , to , val) ;
	update(node << 1 | 1 , mid+1 , r , from , to , val) ;
	tree[node] = min(tree[node << 1] , tree[node << 1 | 1]) ;
}

long long query(int node , int l , int r , int from , int to)
{
	prop(node , l , r) ;
	if(from > r || to < l || from > to)
		return inf ;
	if(l >= from && r <= to)
		return tree[node] ;
	int mid = (l + r) >> 1 ;
	long long a = query(node << 1 , l , mid , from , to) ;
	long long b = query(node << 1 | 1 , mid+1 , r , from , to) ;
	return min(a , b) ;
}

int u[MAX] , v[MAX] , c[MAX] , mark[MAX] , in[MAX] , out[MAX] ;
int n , s , q , e ;

long long ans[MAX] ;

vector< vector< pair<int , int> > >adj(MAX) , Query(MAX) ;

int tim = 0 ;

void dfs1(int node , int par , long long dist)
{
	in[node] = ++tim ;
	if(mark[node])
		update(1 , 1 , n , in[node] , in[node] , dist) ;
	else
		update(1 , 1 , n , in[node] , in[node] , inf) ;
	for(auto &child : adj[node])
	{
		if(child.first == par)
			continue ;
		dfs1(child.first , node , dist+child.second) ;
	}
	out[node] = tim ;
	return ;
}

void dfs2(int node , int par)
{
	for(auto &i : Query[node])
	{
		int x = i.first ;
		bool flag1 = (in[node] >= in[v[x]] && in[node] <= out[v[x]]) ;
		bool flag2 = (in[e] >= in[v[x]] && in[e] <= out[v[x]]) ;
		if(flag1 == flag2)
		{
			ans[i.second] = -2 ;
			continue ;
		}
		if(flag1)
		{
			ans[i.second] = query(1 , 1 , n , in[v[x]] , out[v[x]]) ;
			if(ans[i.second] > inf2)
				ans[i.second] = -1 ;
		}
		else
		{
			long long a = query(1 , 1 , n , 1 , in[v[x]]-1) ;
			long long b = query(1 , 1 , n  , out[v[x]]+1 , n) ;
			ans[i.second] = min(a , b) ;
			if(ans[i.second] > inf2)
				ans[i.second] = -1 ;
		}
	}
	for(auto &child : adj[node])
	{
		if(child.first == par)
			continue ;
		update(1 , 1 , n , 1 , n , child.second) ;
		update(1 , 1 , n , in[child.first] , out[child.first] , -2ll * child.second) ;
		dfs2(child.first , node) ;
		update(1 , 1 , n , 1 , n , -1ll * child.second) ;
		update(1 , 1 , n , in[child.first] , out[child.first] , 2ll * child.second) ;
	}
	return ;
}

int main()
{
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	cin>>n>>s>>q>>e ;
	for(int i = 1 ; i <= n-1 ; ++i)
	{
		cin>>u[i]>>v[i]>>c[i] ;
		adj[u[i]].emplace_back(v[i] , c[i]) ;
		adj[v[i]].emplace_back(u[i] , c[i]) ;
	}
	for(int i = 0 ; i < s ; ++i)
	{
		int x ;
		cin>>x ;
		mark[x] = 1 ;
	}
	for(int i = 0 ; i < q ; ++i)
	{
		int x , y ;
		cin>>x>>y ;
		Query[y].emplace_back(x , i) ;
	}
	dfs1(1 , -1 , 0) ;
	for(int i = 1 ; i <= n-1 ; ++i)
	{
		if(in[v[i]] < in[u[i]])
			swap(u[i] , v[i]) ;
	}
	dfs2(1 , -1) ;
	for(int i = 0 ; i < q ; ++i)
	{
		if(ans[i] >= 0)
			cout<<ans[i]<<"\n" ;
		else if(ans[i] == -1)
			cout<<"oo\n" ;
		else
			cout<<"escaped\n" ;
	}
	return 0 ;
}		