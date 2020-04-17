/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : Croatian Olympiad In Informatics (COI) 2016
   problem name : Torrent (COI 2016-Torrent)
   problem link : https://oj.uz/problem/view/COI16_torrent

   Problem's solution:
   - First root the tree at A, and it's optimal for B to send the file to the nodes in its subtree,
     But it's not optimal for A to send the file to all other nodes.
   - so we want to make B send the file to some other subtrees, and A send it to the remaining nodes,
     but it's not optimally for B to send the file to any node not in the path from A to B.
   - so we want B to send the file to a node in the path between A to B (one of its ancestors), and A send
     the file to remaining nodes, It means that we will partition the tree into 2 trees, such that cost of 
     max(tree1 , tree2) is minimized.
   - to find this node, we will realize that as depth of this node increases, then cost of tree 1 increases and
     cost of tree2 decreases, so we want to find the optimal node such that cost of tree1 <= cost of tree2, so we want
     to find the node that has maximum depth in path from A -> B and above condition is valid.
   - We can binary search to find this node, and answer will be equal to minimum(ans of this node, ans of previous of this node in the path,
                                                                                 ans of previous node of this node in the path)
*/                                                                             

#include <bits/stdc++.h>

using namespace std ;

const int MAX = 3e5 + 10 ;

int dep[MAX] , P[MAX] , sz[MAX] ;
int n , a , b ;

vector< vector<int> >adj(MAX) ;

void dfs1(int node , int par)
{
	P[node] = par ;
	for(auto &child : adj[node])
	{
		if(child == par)
			continue ;
		dep[child] = dep[node] + 1 ;
		dfs1(child , node) ;
	}
	return ;
}

int x , y ;

int dfs2(int node , int par)
{
	vector<int>v ;
	for(auto &child : adj[node])
	{
		if(child == par)
			continue ;
		if((child == x && y == node) || (child == y && node == x))
			continue ;
		v.push_back(dfs2(child , node)) ;
	}
	sort(v.rbegin() , v.rend()) ;
	int cnt = 0 ;
	for(int i = 0 ; i < v.size() ; ++i)
		cnt = max(cnt , v[i]+1+i) ;
	return cnt ;
}

int check(int mid , bool flag)
{
	int now = b ;
	while(dep[now] != mid)
		now = P[now] ;
	x = P[now] , y = now ;
	if(!flag)
		return (dfs2(a,-1) <= dfs2(b,-1)) ;
	else
		return max(dfs2(a , -1) , dfs2(b , -1)) ;
}

int main()
{
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	cin>>n>>a>>b ;
	for(int i = 0 ; i < n-1 ; ++i)
	{
		int x , y ;
		cin>>x>>y ;
		adj[x].push_back(y) ;
		adj[y].push_back(x) ;
	}
	dfs1(a , -1) ;
	int l = 1 , r = dep[b] ;
	int ans = 0 ;
	while(l <= r)
	{
		int mid = (l + r) >> 1 ;
		if(check(mid , 0))
			ans = mid , l = mid+1 ;
		else
			r = mid-1 ;
	}
	//cout<<ans<<" : "<<check(ans , 1)<<"\n" ;
	int ans2 = check(ans , 1) ;
	if(ans-1 > 0)
		ans2 = min(ans2 , check(ans-1 , 1)) ;
	if(ans+1 <= dep[b])
		ans2 = min(ans2 , check(ans+1 , 1)) ;
	return cout<<ans2<<"\n" , 0 ;
}		