/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : JOI 2019 spring camp
   problem name : Mergers (JOISC2019-Mergers)
   problem link : https://oj.uz/problem/view/JOI19_mergers

   problem's solution :
   	same idea : https://github.com/nikolapesic2802/Programming-Practice/blob/master/Mergers/main.cpp

*/ 

#include <bits/stdc++.h>
 
using namespace std ;
 
const int MAX = 5e5 + 5 ;
 
vector< vector<int> >adj(MAX) ;
vector< vector<int> >st(MAX) ;
vector< vector<int> >level(MAX) ;
int n , k;
 
int state[MAX] , P[MAX][22] , depth[MAX] , lca[MAX];
int lowestdepth[MAX] , nodenum[MAX] , deg[MAX] , id[MAX] , nxt[MAX];
int nodes = 0 ;
 
void dfs(int node , int lvl , int par)
{
	depth[node] = lvl ;
	P[node][0] = par ;
	for(auto &child : adj[node])
	{
		if(child == par)
			continue ;
		dfs(child , lvl + 1 , node) ;
	}
	return ;
}
 
void preprocess()
{
	dfs(1 , 0 , 0) ;
	for(int j = 1 ; j < 22 ; ++j)
	{
		for(int i = 1 ; i <= n ; ++i)
			P[i][j] = P[P[i][j-1]][j-1] ;
	}
	return ;
}
 
int LCA(int x , int y)
{
	if(depth[x] < depth[y])
		swap(x , y) ;
	for(int i = 21 ; i >= 0 ; --i)
	{
		if(depth[x] - (1 << i) >= depth[y])
			x = P[x][i] ;
	}
	if(x == y)
		return x ;
	for(int i = 21 ; i >= 0 ; --i)
	{
		if(P[x][i] != P[y][i])
			x = P[x][i] , y = P[y][i] ;
	}
	return P[x][0] ;
}

void init()
{
	for(int i = 1 ; i < MAX ; ++i)
		nxt[i] = i ;
}

int root(int node)
{
	if(nxt[node] == node)
		return node ;
	return (nxt[node] = root(nxt[node])) ;
}

void Union(int x , int y)
{
	int a = root(x) ;
	int b = root(y) ;
	nxt[a] = b ;
}

int main()
{
	//ios_base::sync_with_stdio(0) ;
	//cin.tie(0) ;
	cin>>n>>k ;
	for(int i = 0 ; i < n-1 ; ++i)
	{
		int x , y ;
		cin>>x>>y ;
		adj[x].push_back(y) ;
		adj[y].push_back(x) ;
	}
	for(int i = 1 ; i <= n ; ++i)
	{
		cin>>state[i] ;
		st[state[i]].push_back(i) ;
	}
	preprocess() ;
	for(int i = 1 ; i <= k ; ++i)
	{
		int lca2 = st[i][0] ;
		for(auto &node : st[i])
			lca2 = LCA(lca2 , node) ;
		for(auto &node : st[i])
		{
			lca[node] = lca2 ;
		}
	}
	init() ;
	for(int i = 1 ; i <= n ; ++i)
	{
		int now = root(i) ;
		for(; ;)
		{
			if(depth[now] <= depth[lca[i]])
				break ;
			Union(now , P[now][0]) ;
			now = root(now) ;
		}
	}
	for(int i = 1 ; i <= n ; ++i)
	{
		if(root(i) == i && P[i][0] != 0)
			deg[root(P[i][0])]++ , deg[i]++ ;
	}
	int cnt = 0 ;
	for(int i = 1 ; i <= n ; ++i)
	{
		if(deg[i] == 1)
			cnt++ ;
	}
	return cout<<(cnt+1)/2<<"\n" , 0 ;
}