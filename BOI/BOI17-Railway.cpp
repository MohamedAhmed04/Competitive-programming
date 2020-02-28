/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : Baltic olympiad in informatics 2017 day 1
   problem name : Railway (BalticOI 17-Railway)
   problem link : https://oj.uz/problem/view/BOI17_railway

   Problem's solution :
    - for every minister, the lowest depth of a node that will be in a path between two nodes is 
      the LCA of all nodes.
    - based on that we can make dsu on tree, where every node carries a set contains id of ministers that there's a path
      between a node chosen by the minister and another node outside the subtree (so it will pass with the edge between current node and its parent)
   	- and if a node is LCA of nodes of a minister, then erase the id of the minister from the set.
*/

#include <bits/stdc++.h>

using namespace std ;

const int MAX = 1e5 + 10 ;

int arr[MAX] , sz[MAX] , in[MAX] , out[MAX] , Min[MAX] , Max[MAX] , P[MAX][22] , dep[MAX] , lca[MAX] ;
int n , m , k , tim = 1 ;

vector< vector<int> >adj(MAX) ;
vector< vector<int> >v(MAX) ;
vector< vector<int> >Er(MAX) ;
set<int>s[MAX] ;

vector<int>ans ;

map< pair<int , int> , int>idx ;

void dfs(int node , int par)
{
	in[node] = tim++ ;
	sz[node] = 1 ;
	P[node][0] = par ;
	for(int i = 1 ; i < 20 ; ++i)
		P[node][i] = P[P[node][i-1]][i-1] ;
	for(auto &child : adj[node])
	{
		if(child == par)
			continue ;
		dep[child] = dep[node] + 1 ;
		dfs(child , node) ;
		sz[node] += sz[child] ;
	}
	out[node] = tim ;
}

void dfs2(int node , int par)
{
	int mx = -1 , bigchild = -1 ;
	for(auto &child : adj[node])
	{
		if(child != par && sz[child] > mx)
		{
			mx = sz[child] ;
			bigchild = child ;
		}
	}
	for(auto &child : adj[node])
	{
		if(child != par && child != bigchild)
			dfs2(child , node) ;
	}
	if(bigchild != -1)
	{
		dfs2(bigchild , node) ;
		swap(s[bigchild] , s[node]) ;
	}
	for(auto &i : v[node])
		s[node].insert(i) ;
	for(auto &child : adj[node])
	{
		if(child != par && child != bigchild)
		{
			for(auto &i : s[child])
				s[node].insert(i) ;
		}
	}
	for(auto &i : Er[node])
	{
		if(s[node].find(i) != s[node].end())
			s[node].erase(i) ;
	}
	if(s[node].size() >= k)
		ans.push_back(idx[{node , par}]) ;
	return ;
}

int LCA(int x , int y)
{
	if(dep[x] < dep[y])
		swap(x , y) ;
	for(int i = 19 ; i >= 0 ; --i)
	{
		if(dep[x] - (1 << i) >= dep[y])
			x = P[x][i] ;
	}
	if(x == y)
		return x ;
	for(int i = 19 ; i >= 0 ; --i)
	{
		if(P[x][i] != P[y][i])
		{
			x = P[x][i] ;
			y = P[y][i] ;
		}
	}
	return P[x][0] ;
}

int main()
{
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	cin>>n>>m>>k ;
	for(int i = 0 ; i < n-1 ; ++i)
	{
		int x , y ;
		cin>>x>>y ;
		idx[{x , y}] = idx[{y , x}] = i+1 ;
		adj[x].push_back(y) ;
		adj[y].push_back(x) ;
	}
	dfs(1 , 0) ;
	for(int i = 0 ; i < m ; ++i)
	{
		int sz1 ;
		cin>>sz1 ;
		Min[i] = 1e9 , Max[i] = -1 ;
		int x ;
		for(int j = 0 ; j < sz1 ; ++j)
		{
			cin>>x ;
			if(lca[i] == 0)
				lca[i] = x ;
			else
				lca[i] = LCA(lca[i] , x) ;
			v[x].push_back(i) ;
			Min[i] = min(Min[i] , in[x]) ;
			Max[i] = max(Max[i] , in[x]) ;
		}
		Er[lca[i]].push_back(i) ;
	}
	dfs2(1 , 0) ;
	cout<<ans.size()<<"\n" ;
	sort(ans.begin() , ans.end()) ;
	for(auto &i : ans)
		cout<<i<<" " ;
	cout<<"\n" ;
	return 0 ;
}		