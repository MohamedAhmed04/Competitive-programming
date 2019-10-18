/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : Baltic olympiad in informatics 2012 day 2
   problem name : Melody (BOI12-Melody)
   problem link : https://cses.fi/99/list/

   solution idea :
   	same idea like second solution : https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/Baltic/official/boi2012_solutions/melody-sol.pdf

*/

#include <bits/stdc++.h>

using namespace std ;

const int MAXL = 1e5 + 10 , MAXN = 105;

int dist[MAXN][MAXN] , nxt[MAXN][MAXN] ;
int arr[MAXN][MAXN] ;
int dp[MAXL] , seq[MAXL] , prv[MAXL] ;

vector< vector<int> >adj(MAXN) , last(MAXN) ;

void dijkstra(int src)
{
	priority_queue< pair<int , int> , vector< pair<int , int> > , greater< pair<int , int> > >q ;
	q.push({0 , src}) ;
	dist[src][src] = 1 ;
	nxt[src][src] = src ;
	while(!q.empty())
	{
		pair<int , int>p = q.top() ;
		q.pop() ;
		int node = p.second , cost = p.first ;
		if(cost > dist[src][node])
			continue ;
		for(auto &child : adj[node])
		{
			int ncost = cost + 1 ;
			if(dist[src][child] > ncost)
			{
				dist[src][child] = ncost ;
				nxt[child][src] = node ;
				q.push({ncost , child}) ;
			}
		}
	}
	return ;
}

int main()
{
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	memset(prv , -1 , sizeof(prv)) ;
	for(int i = 0 ; i < MAXN ; ++i)
	{
		for(int j = 0 ; j < MAXN ; ++j)
			dist[i][j] = 1e7 ;
	}
	int n , m , g , l;
	cin>>n>>m>>g ;
	for(int i = 0 ; i < n ; ++i)
	{
		for(int j = 0 ; j < m ; ++j)
		{
			char c ;
			cin>>c ;
			arr[i][j] = (c - '0') ;
		}
	}
	cin>>l ;
	for(int i = 0 ; i < l ; ++i)
	{
		cin>>seq[i] ;
		seq[i]-- ;
	}
	for(int i = 0 ; i < n ; ++i)
	{
		for(int j = 0 ; j < n ; ++j)
		{
			int cnt = 0 ;
			for(int k = 0 ; k < m ; ++k)
				cnt += (arr[i][k] != arr[j][k]) ;
			if(cnt <= g)
				adj[i].push_back(j) ;
		}
	}
	for(int i = 0 ; i < n ; ++i)
		dijkstra(i) ;
	for(int i = 0 ; i < l ; ++i)
	{
		for(int j = 0 ; j < n ; ++j)
		{
			int idx = upper_bound(last[j].begin() , last[j].end() , i-dist[j][seq[i]]) - last[j].begin() ;
			idx-- ;
			if(idx == -1)
				continue ;
			if(dp[last[j][idx]] + 1 > dp[i])
				dp[i] = dp[last[j][idx]] + 1 , prv[i] = last[j][idx] ;
		}
		if(dp[i] == 0)
			dp[i] = 1 , prv[i] = -1 ;
		last[seq[i]].push_back(i) ;
	}
	int Max = 0 , idx = -1 ;
	for(int i = 0 ; i < l ; ++i)
	{
		if(dp[i] >= Max)
			Max = dp[i] , idx = i ;
	}
	vector<int>ans ;
	ans.push_back(seq[idx]) ;
	while(prv[idx] != -1)
	{
		int x = seq[idx] , y = seq[prv[idx]] ;
		x = nxt[x][y] ;
		int cnt = 0 ;
		while(x != y)
		{
			cnt++ ;
			ans.push_back(x) ;
			x = nxt[x][y] ;
		}
		while(cnt < idx - prv[idx])
		{
			cnt++ ;
			ans.push_back(y) ;
		}
		idx = prv[idx] ;
	}
	int cur = ans.back() ;
	for(int i = 0 ; i < idx ; ++i)
		ans.push_back(cur) ;
	reverse(ans.begin() , ans.end()) ;
	cur = ans.back() ;
	while(ans.size() < l)
		ans.push_back(cur) ;
	cout<<l - Max<<"\n" ;
	for(auto &i : ans)
		cout<<i+1<<" " ;
	cout<<"\n" ;
	return 0 ;
}