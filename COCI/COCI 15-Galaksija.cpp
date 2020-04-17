/* Author : Mohamed ahmed Bakry (handle : MohamedAhmed04)

   contest name : COCI 2015 contest 4
   problem name : Galaksija (COCI 2015-Galaksija)
   problem link : https://dmoj.ca/problem/coci15c4p5

   Problem's solution:
    we can reverse the operations so we will need to connect the edges.
    xor of the path of two nodes will be 0 if the xor of the path from the root of the tree
    to the 2 nodes is same.
    so we can union two nodes with dsu using small to larger technique and calculate the answer using dfs (while Unioning).

*/

#include <bits/stdc++.h>

using namespace std ;

const int MAX = 1e5 + 10 ;

int u[MAX] , v[MAX] , c[MAX] , par[MAX] , sz[MAX] , Xor[MAX] , order[MAX] ;
long long Ans[MAX] ;
int n ;

vector< vector< pair<int , int> > >adj(MAX) ;

map< pair<int , long long> , long long>mp ;

long long ans = 0ll ;

void init()
{
	for(int i = 0 ; i < MAX ; ++i)
		par[i] = i , sz[i] = 1 , mp[{i , 0}] = 1 ;
}

int root(int node)
{
	if(par[node] == node)
		return node ;
	return (par[node] = root(par[node])) ;
}


void dfs(int node , int par , int now , int root)
{
	Ans[root] += mp[{root , now}] ;
	ans += mp[{root , now}] ;
	mp[{root , now}]++ ;
	Xor[node] = now ;
	for(auto &child : adj[node])
	{
		if(child.first == par)
			continue ;
		dfs(child.first , node , now ^ child.second , root) ;
	}
	return ;
}

void Union(int x , int y , int cost)
{
	int a = root(x) ;
	int b = root(y) ;
	if(a == b)
		return ;
	if(sz[a] < sz[b])
		swap(a , b) , swap(x , y) ;
	ans -= Ans[b] ;
	dfs(y , -1 , Xor[x] ^ cost , a) ;
	par[b] = a ;
	sz[a] += sz[b] ;
	adj[x].emplace_back(y , cost) ;
	adj[y].emplace_back(x , cost) ;
	return ;
}

int main()
{
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	cin>>n ;
	for(int i = 0 ; i < n-1 ; ++i)
		cin>>u[i]>>v[i]>>c[i] ;
	for(int i = 0 ; i < n-1 ; ++i)
	{
		cin>>order[i] ;
		order[i]-- ;
	}
	init() ;
	vector<long long>anss ;
	anss.push_back(0ll) ;
	for(int i = n-2 ; i >= 0 ; --i)
	{
		int idx = order[i] ;
		Union(u[idx] , v[idx] , c[idx]) ;
		anss.push_back(ans) ;
	}
	reverse(anss.begin() , anss.end()) ;
	for(auto &i : anss)
		cout<<i<<"\n" ;
	return 0 ;
}		