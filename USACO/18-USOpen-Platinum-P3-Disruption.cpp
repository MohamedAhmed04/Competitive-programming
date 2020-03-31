/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : USACO US Open Platinum 2018
   problem name : Disruption (18-USACO US Open Platinum Disruption)
   problem link : http://usaco.org/index.php?page=viewproblem2&cpid=842

   Problem's solution:
    This problem can be solved with dsu on trees and dfs time, let in[node]
    equals the time of entering node, and out[node] is time of exiting the subtree of the 
    node, so we can have a set store the edges cost that starts from a node inside the subtree and 
    ends at node outside the subtree and answer is maximum cost in this set or -1 if the set is empty.
    To store this edges, we will do dsu on trees, where every node have a set of pair where first number is
    the time of other end of the edge and second number is its value, so we need to erase from the set every pair
    its first value is between in[node] and out[node], as the edge is inside the subtree and erase this values from 
    second set that stores the values.

*/

#include <bits/stdc++.h>

using namespace std ;

const int MAX = 5e4 + 10 ;

int sz[MAX] , in[MAX] , out[MAX] , ans[MAX] ;
int n , m ;
int tim = 0 ;

vector< vector< pair<int , int> > >adj(MAX) , adj2(MAX) ;

set< pair<int , int> >s1[MAX] ;
set< pair<int , int> >::iterator it ;
multiset<int> s2 ;

void dfs(int node , int par)
{
	in[node] = ++tim ;
	sz[node] = 1 ;
	for(auto &child : adj[node])
	{
		if(child.first == par)
			continue ;
		dfs(child.first, node) ;
		sz[node] += sz[child.first] ;
	}
	out[node] = tim ;
	return ;
}

void dfs2(int node , int par , bool keep , int idx)
{
	int Max = -1 , bigchild = -1 , idx2 ;
	for(auto &child : adj[node])
	{
		if(child.first != par && sz[child.first] > Max)
			Max = sz[child.first] , bigchild = child.first , idx2 = child.second ;
	}
	for(auto &child : adj[node])
	{
		if(child.first == par || child.first == bigchild)
			continue ;
		dfs2(child.first , node , 0 , child.second) ;
	}
	if(bigchild != -1)
	{
		dfs2(bigchild , node , 1 , idx2) ;
		swap(s1[bigchild] , s1[node]) ;
	}
	for(auto &child : adj2[node])
	{
		s1[node].insert({in[child.first] , child.second}) ;
		s2.insert(child.second) ;
	}
	for(auto &child : adj[node])
	{
		if(child.first != par && child.first != bigchild)
		{
			for(auto &j : s1[child.first])
			{
				s1[node].insert(j) ;
				s2.insert(j.second) ;
			}
		}
	}
	it = s1[node].lower_bound({in[node] , -1}) ;
	vector< pair<int , int> >vp ;
	for(it ; it != s1[node].end() ; it++)
	{
		pair<int , int>p = *it ;
		if(p.first >= in[node] && p.first <= out[node])
			vp.push_back(p) ;
		else
			break ;
	}
	for(auto &j : vp)
		s1[node].erase(j) , s2.erase(j.second) ;
	if(s2.size())
		ans[idx] = *s2.begin() ;
	else
		ans[idx] = -1 ;
	if(keep == 0)
	{
		for(auto &j : s1[node])
			s2.erase(j.second) ;
	}
}

int main()
{
	freopen("disrupt.in" , "r" , stdin) ;
	freopen("disrupt.out" , "w" , stdout) ;
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	cin>>n>>m ;
	for(int i = 0 ; i < n-1 ; ++i)
	{
		int x , y ;
		cin>>x>>y ;
		adj[x].push_back({y , i}) ;
		adj[y].push_back({x , i}) ;
	}
	for(int i = 0 ; i < m ; ++i)
	{
		int x , y , z ;
		cin>>x>>y>>z ;
		adj2[x].emplace_back(y , z) ;
		adj2[y].emplace_back(x , z) ;
	}
	dfs(1 , -1) ;
	dfs2(1 , -1 , 1 , n) ;
	for(int i = 0 ; i < n-1 ; ++i)
		cout<<ans[i]<<"\n" ;
	return 0 ;
}		