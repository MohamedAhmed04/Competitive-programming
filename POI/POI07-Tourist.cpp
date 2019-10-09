/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : Polish olympiad in informatics 2007 (POI 2007)
   problem name : Tourist (POI07-Tourist)
   problem link : https://szkopul.edu.pl/problemset/problem/_L_YGzT5VYJO9zHTfVRwPjwh/site/?key=statement

   problem's solution : 
   	same idea : https://github.com/nikolapesic2802/Programming-Practice/blob/master/Tourist/main.cpp

*/

#include <bits/stdc++.h>

using namespace std ;

const int MAXN = 2e5 + 10 , MAXK = 20;
const int MAXDP = (1ll << (MAXK-1)) ;

vector< vector< pair<int , int> > >adj(MAXN) ;
int n , m , k ;

int before[30] , dist[30][30] , d[MAXN] , dp[MAXK][MAXDP];

void dijkstra(int src)
{
	for(int i = 1 ; i <= n ; ++i)
		d[i] = INT_MAX ;
	priority_queue< pair<int , int> , vector< pair<int , int> > , greater< pair<int , int> > >q ;
	q.push({0 , src}) ;
	d[src] = 0 ;
	while(!q.empty())
	{
		pair<int , int>p = q.top() ;
		q.pop() ;
		int node = p.second ;
		int cost = p.first ;
		if(cost > d[node])
			continue ;
		if(node <= k+1)
			dist[src][node] = cost ;
		else if(node == n)
			dist[src][k+2] = cost ;
		for(auto &to : adj[node])
		{
			int cur = to.first ;
			int ncost = to.second + cost ;
			if(ncost < d[cur])
			{
				d[cur] = ncost ;
				q.push({ncost , cur}) ;
			}
		}
	}
	return ;
}

int compress(int mask , int idx)
{
	int maskk = (1 << idx) - 1 ;
	int now = mask & maskk ;
	mask >>= (idx+1) ;
	mask <<= idx ;
	mask += now ;
	return mask ;
}

int solve(int idx , int mask)
{
	if(mask == (1 << k) - 1)
		return dist[idx][k+2] ;
	int now = INT_MAX ;
	int maskk = compress(mask , idx-2) ;
	if(idx != 1)
	{
		if(dp[idx-2][maskk] != -1)
			return dp[idx-2][maskk] ;
	}
	for(int i = 2 ; i <= k+1 ; ++i)
	{
		int cur = i-2 ;
		if((mask & (1 << cur)))
			continue ;
		if(((before[i] & mask) != before[i]))
			continue ;
		int a = solve(i , mask | (1 << cur)) ;
		int b = dist[idx][i] ;
		if((long long)(a) + (long long)(b) < now)
			now = a + b ;
	}
	if(idx == 1)
		return now ;
	else
		return (dp[idx-2][maskk] = now) ;
}

int main()
{
	memset(dp , -1 , sizeof(dp)) ;
	scanf("%d %d %d" , &n , &m , &k) ;
	for(int i = 0 ; i < m ; ++i)
	{
		int x , y , z ;
		scanf("%d %d %d" , &x , &y , &z) ;
		adj[x].push_back({y , z}) ;
		adj[y].push_back({x , z}) ;
	}
	int g ;
	scanf("%d" , &g) ;
	for(int i = 0 ; i < g ; ++i)
	{
		int x , y ;
		cin>>x>>y ;
		x -= 2 ;
		before[y] |= (1 << x) ;
	}
	for(int i = 1 ; i <= k+1 ; ++i)
		dijkstra(i) ;
	return cout<<solve(1 , 0)<<"\n" , 0 ;
}