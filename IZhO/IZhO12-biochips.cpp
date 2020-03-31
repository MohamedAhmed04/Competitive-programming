/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : IZhO 2012 day 1
   Problem name : Biochips (IZhO12-Biochips)
   problem link : https://oj.uz/problem/view/IZhO12_biochips

   Problem's solution: 
    since if we choose a biochip we can't choose any other biochip inside its subtree,
    so we can make dfs time and flatten the tree and let in[node] is time of entering node subtree 
    and out[node] is time to exit node subtree, so we can do dp like knapsack, 
    but if we choose a node we can't choose any other node to out[node], so if we choose a node we will move to out[node]+1.

*/

#include <bits/stdc++.h>

using namespace std ;

const int MAX = 2e5 + 10 , MAXM = 502 ;

int arr[MAX] , in[MAX] , out[MAX] , id[MAX] ;
int n , m ;

vector< vector<int> >adj(MAX) ;

int tim = 0 ;

int dp[MAX][MAXM] ;

void dfs(int node)
{
	in[node] = ++tim ;
	id[tim] = node ;
	for(auto &child : adj[node])
		dfs(child) ;
	out[node] = tim ;
}

int solve(int idx , int cnt)
{
	if(cnt == m)
		return 0 ;
	if(idx == n+1)
		return -1e7 ;
	int &ret = dp[idx][cnt] ;
	if(ret != -1)
		return ret ;
	ret = solve(idx+1 , cnt) ;
	ret = max(ret , solve(out[id[idx]]+1 , cnt+1) + arr[id[idx]]) ;
	return ret ;
}

int main()
{
	memset(dp , -1 , sizeof(dp)) ;
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	cin>>n>>m ;
	int root ;
	for(int i = 1 ; i <= n ; ++i)
	{
		int par ;
		cin>>par>>arr[i] ;
		if(!par)
			root = i ;
		else
			adj[par].push_back(i) ;
	}
	dfs(root) ;
	return cout<<solve(1 , 0)<<"\n" , 0 ;
}		