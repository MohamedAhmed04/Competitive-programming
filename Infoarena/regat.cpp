/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   problem name : Regat
   problem link : https://www.infoarena.ro/problema/regat

   problem's solution :
    - first make dfs time to store time of entering and exiting every node.
    - make segment tree to store distance from every node to node 1
    - every time when entering a node, decrease distance of nodes in its subtree by cost
      of edge and increase all other nodes by cost of edge, so segtree now stores distance
      of all nodes to current node.
    - when exiting node, increase distance of nodes in its subtree by cost of edge between node and its parent
      and decrease all other nodes.
    - inside each node, loop on queries and find max distance and set it with very small number to find next largest max distance and after
      answering queries of current node, reset distance to its original distance.

*/ 

#include <bits/stdc++.h>

using namespace std ;

#define f first 
#define s second 

const int MAX = 1e5 + 10 ;

vector< pair<int , int> >adj[MAX] ;
pair<int , int> tree[4 * MAX] ;
int lazy[4 * MAX] , st[MAX] , en[MAX] , ans[MAX] ;
int n , q;
vector< vector<int> >qu(MAX) ;

void update(int node , int l , int r , int idx , int val)
{
	if(idx > r || idx < l)
		return ;
	if(l == r)
	{
		tree[node] = {val , idx} ;
		return ;
	}
	int mid = (l + r) >> 1 ;
	update(node << 1 , l , mid , idx , val) ;
	update(node << 1 | 1 , mid + 1 , r , idx , val) ;
	tree[node] = max(tree[node << 1] , tree[node << 1 | 1]) ;
}

void prop(int node , int l , int r)
{
	tree[node].f += lazy[node] ;
	if(l != r)
	{
		lazy[node << 1] += lazy[node] ;
		lazy[node << 1 | 1] += lazy[node] ;
	}
	lazy[node] = 0 ;
}

void updatelazy(int node , int l , int r , int from , int to , int val)
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
	updatelazy(node << 1 , l,  mid , from , to , val) ;
	updatelazy(node << 1 | 1 , mid+1 , r , from , to , val) ;
	tree[node] = max(tree[node << 1] , tree[node << 1 | 1]) ;
}

pair<int , int>query(int node , int l , int r , int from , int to)
{
	prop(node , l , r) ;
	if(from > r || to < l)
		return {-2e9 , -1} ;
	if(l >= from && r <= to)
		return tree[node] ;
	int mid = (l + r) >> 1 ;
	return max(query(node << 1 , l , mid , from , to) , query(node << 1 | 1 , mid + 1 , r , from , to)) ;
}

int tim = 0 ;

void dfs(int node , int par , int dist)
{
	st[node] = ++tim ;
	update(1 , 1 , n , st[node] , dist) ;
	for(auto &child : adj[node])
	{
		if(child.f == par)
			continue ;
		dfs(child.f , node , dist+child.s) ;
	}
	en[node] = tim ;
}

vector< pair<int , int> >vp ;

void dfs2(int node , int par)
{
	for(auto &i : qu[node])
	{
		pair<int , int>p = query(1 , 1 , n , 1 , n) ;
		ans[i] = p.f ;
		updatelazy(1 , 1 , n , p.s , p.s , -2e9) ;
		vp.push_back(p) ; 
	}
	for(auto &i : vp)
		updatelazy(1 , 1 , n , i.s , i.s , 2e9) ;
	vp.clear() ;
	for(auto &child : adj[node])
	{
		if(child.f == par)
			continue ;
		updatelazy(1 , 1 , n , 1 , n , child.s) ;
		updatelazy(1 , 1 , n , st[child.f] , en[child.f] , -2*child.s) ;
		dfs2(child.f , node) ;
		updatelazy(1 , 1 , n , 1 , n , -child.s) ;
		updatelazy(1 , 1 , n , st[child.f] , en[child.f] , 2*child.s) ;
	}
	return ;
}

int main()
{
	freopen("regat.in" , "r" , stdin) ;
	freopen("regat.out" , "w" , stdout) ; 
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	cin>>n>>q ;
	for(int i = 0 ; i < n-1 ; ++i)
	{
		int x , y , z ;
		cin>>x>>y>>z ;
		adj[x].push_back({y , z}) ;
		adj[y].push_back({x , z}) ;
	}
	dfs(1 , -1 , 0) ;
	for(int i = 0 ; i < q ; ++i)
	{
		int x ;
		cin>>x ;
		qu[x].push_back(i) ;
	}
	dfs2(1 , -1) ;
	for(int i = 0 ; i < q ; ++i)
		cout<<ans[i]<<"\n" ;
	return 0 ;
}