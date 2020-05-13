/* Author: Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : Japanese Olympiad In Informatics (JOI) 2018 Final Round
   problem name : Commuter Pass (JOI 18-Commuter Pass)
   problem link : https://oj.uz/problem/view/JOI18_commuter_pass

   Problem's solution:
    same idea like: https://github.com/thecodingwizard/competitive-programming/blob/master/JOI/JOI%2018-commuterpass.cpp

*/

#include <bits/stdc++.h>

using namespace std ;

const long long inf = 1e18 ;
const int MAX = 1e5 + 10 ;

bool vis[MAX] , mark[MAX] ;
long long dist[3][MAX] , dp1[MAX] , dp2[MAX] ;
int n , m , s , t , u , v ;

vector< vector< pair<int , long long> > >adj(MAX) ;
vector< vector<int> >adj2(MAX) ;

void dijkstra(int src , int a)
{
	for(int i = 0 ; i < MAX ; ++i)
		dist[a][i] = inf ;
	priority_queue< pair<long long , int> , vector< pair<long long , int> > , greater< pair<long long , int> > >q; 
	dist[a][src] = 0 ;
	q.push({0 , src}) ;
	while(!q.empty())
	{
		pair<long long , int>p = q.top() ;
		q.pop() ;
		int node = p.second ;
		long long cost = p.first ;
		if(cost > dist[a][node])
			continue ;
		for(auto &child : adj[node])
		{
			int nnode = child.first ;
			long long ncost = child.second + cost ;
			if(ncost < dist[a][nnode])
			{
				dist[a][nnode] = ncost ;
				q.push({ncost , nnode}) ;
			}
		}
	}
	return ;
}

long long ans ;

void dfs(int node)
{
	vis[node] = 1 ;
	mark[node] = 1 ;
	for(auto &child : adj[node])
	{
		if(dist[0][node] + child.second == dist[0][child.first])
		{
			if(!vis[child.first])
				dfs(child.first) ;
			adj2[node].push_back(child.first) ;
		}
	}
	mark[node] = 0 ;
	return ;
}

void dfs2(int node)
{
	vis[node] = 1 ;
	dp1[node] = dp2[node] = inf ;
	for(auto &child : adj2[node])
	{
		if(!vis[child])
			dfs2(child) ;
		dp1[node] = min(dp1[node] , dp1[child]) ;
		dp2[node] = min(dp2[node] , dp2[child]) ; ;
		if((dp1[child] == inf || dp2[child] == inf) && child != t)
			continue ;
		dp1[node] = min(dp1[node], dist[1][child]) ;
		dp2[node] = min(dp2[node], dist[2][child]) ;
	}
	ans = min(ans, dist[2][node] + dp1[node]) ;
	ans = min(ans, dist[1][node] + dp2[node]) ;
}

int main()
{
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	cin>>n>>m ;
	cin>>s>>t ;
	cin>>u>>v ;
	for(int i = 0 ; i < m ; ++i)
	{
		int x , y ;
		long long z ;
		cin>>x>>y>>z ;
		adj[x].emplace_back(y , z) ;
		adj[y].emplace_back(x , z) ;
	}
	dijkstra(s , 0) ;
	dijkstra(u , 1) ;
	dijkstra(v , 2) ;
	ans = dist[1][v] ;
	dfs(s) ;
	memset(vis , 0 , sizeof(vis)) ;
	dfs2(s) ;
	return cout<<ans<<"\n" , 0 ;
}		