/* Author: Mohamed Ahmed Bakry (handle: MohamedAhmed04)

   Problem name: Arb3
   Problem link: https://infoarena.ro/problema/arb3

   Problem's solution:
     same idea: https://github.com/stefdasca/CompetitiveProgramming/blob/master/Infoarena/arb3.cpp

*/

#include <bits/stdc++.h>

using namespace std ;

const int MAX = 1e5 + 10 ;

int arr[MAX] , P[MAX] , order[MAX] ;
long long turn[MAX] , sum[MAX] ;
int n , q ;

vector< vector<int> >adj(MAX) ;

bool cmp(int a , int b)
{
	return arr[a] > arr[b] ;
}

int main()
{
	freopen("arb3.in" , "r" , stdin) ;
	freopen("arb3.out" , "w" , stdout) ;
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	cin>>n>>q ;
	for(int i = 2 ; i <= n ; ++i)
	{
		cin>>P[i] ;
		adj[P[i]].push_back(i) ;
	}
	for(int i = 1 ; i <= n ; ++i)
		cin>>arr[i] ;
	for(int node = 1 ; node <= n ; ++node)
	{
		if(!adj[node].size())
			continue ;
		sort(adj[node].begin() , adj[node].end() , cmp) ;
		turn[adj[node][0]] = 1 , sum[adj[node][0]] = 0 ;
		order[adj[node][0]] = 1 ;
		for(int i = 1 ; i < adj[node].size() ; ++i)
		{
			int child = adj[node][i] , prvchild = adj[node][i-1] ;
			order[child] = i+1 ;
			turn[child] = turn[prvchild] + arr[prvchild] - arr[child] ;
			sum[child] = sum[prvchild] + i * (turn[child] - turn[prvchild]) ;
		}
	}
	while(q--)
	{
		int node ;
		long long y ;
		cin>>node>>y ;
		while(node != 1)
		{
			int par = P[node] ;
			long long a = turn[node] + y-2 ;
			int l = 0 , r = adj[par].size() - 1 ;
			int req = -1 ;
			while(l <= r)
			{
				int mid = (l + r) >> 1 ;
				if(turn[adj[par][mid]] <= a)
					req = adj[par][mid] , l = mid+1 ;
				else
					r = mid-1 ;
			}
			if(req != -1)
			{
				long long rem = a - turn[req] + 1ll ;
				y = sum[req] + rem * order[req] + order[node] ;
			}
			node = par ;
		}
		cout<<y<<"\n" ;
	}
	return 0 ;
}		