/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : Baltic olympiad in informatics 2011
   problem name : Treasures and Vikings
   problem link : https://cses.fi/100/list/

   problem solution :
   	same idea : 
   	https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/Baltic/official/boi2011_solutions/vikings-sol.pdf
*/

#include <bits/stdc++.h>

using namespace std ;

int dx[] = {1 , 0 , 0 , -1} ;
int dy[] = {0 , 1 , -1 , 0} ;

const int MAX = 710 ;

char arr[MAX][MAX] ;
int prefrow[MAX][MAX], prefcol[MAX][MAX] , dist[MAX][MAX] , dist2[MAX][MAX], vis[MAX][MAX];
int n , m ;

int main()
{
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	cin>>n>>m ;
	pair<int , int>Y , V , T ;
	for(int i = 0 ; i < n ; ++i)
	{
		for(int j = 0 ; j < m ; ++j)
		{
			cin>>arr[i][j] ;
			prefrow[i][j] = prefcol[i][j] = 1e8 ;
			if(arr[i][j] == 'Y')
				Y.first = i , Y.second = j ;
			if(arr[i][j] == 'V')
				V.first = i , V.second = j ;
			if(arr[i][j] == 'T')
				T.first = i , T.second = j ;
		}
	}
	queue< pair<int , int> >q ;
	q.push({V.first , V.second}) ;
	prefrow[V.first][V.second] = prefcol[V.first][V.second] = 0 ;
	while(!q.empty())
	{
		pair<int , int>p = q.front() ;
		q.pop() ;
		for(int i = 0 ; i < 4 ; ++i)
		{
			int x = p.first+dx[i] ;
			int y = p.second + dy[i] ;
			if(x < 0 || x >= n || y < 0 || y >= m)
				continue ;
			if(arr[x][y] == 'I')
				continue ;
			if(prefrow[x][y] > prefrow[p.first][p.second] + 1)
			{
				prefrow[x][y] = prefcol[x][y] = prefrow[p.first][p.second] + 1 ;
				q.push({x , y}) ;		
			}
		}
	}
	for(int i = 0 ; i < n ; ++i)
	{
		for(int j = 1 ; j < m ; ++j)
		{
			if(arr[i][j] == 'I')
				continue ;
			prefrow[i][j] = min(prefrow[i][j], prefrow[i][j-1]) ;
		}
		for(int j = m-2 ; j >= 0 ; --j)
		{
			if(arr[i][j] == 'I')
				continue ;
			prefrow[i][j] = min(prefrow[i][j] , prefrow[i][j+1]) ;
		}
	}
	for(int j = 0 ; j < m ; ++j)
	{
		for(int i = 1 ; i < n ; ++i)
		{
			if(arr[i][j] == 'I')
				continue ;
			prefcol[i][j] = min(prefcol[i][j],  prefcol[i-1][j]) ;
		}
		for(int i = n-2 ; i >= 0 ; --i)
		{
			if(arr[i][j] == 'I')
				continue ;
			prefcol[i][j] = min(prefcol[i][j], prefcol[i+1][j]) ;
		}
	}
	for(int i = 0 ; i < n ; ++i)
	{
		for(int j = 0 ; j < m ; ++j)
			dist[i][j] = min(prefrow[i][j] , prefcol[i][j]) ;
	}
	q.push({Y.first,  Y.second}) ;
	dist2[Y.first][Y.second] = 0 ;
	vis[Y.first][Y.second] = 1 ;
	while(!q.empty())
	{
		pair<int , int>p = q.front() ;
		q.pop() ;
		if(p == T)
			return cout<<"YES\n" , 0 ;
		for(int i = 0 ; i < 4 ; ++i)
		{
			int x = p.first+dx[i] ;
			int y = p.second + dy[i] ;
			if(x < 0 || x >= n || y < 0 || y >= m)
				continue ;
			if(arr[x][y] == 'I' || vis[x][y] == 1)
				continue ;
			if(dist[x][y] > dist2[p.first][p.second] + 1)
			{
				dist2[x][y] = dist2[p.first][p.second] + 1 ;
				vis[x][y] = 1 ;
				q.push({x , y}) ;		
			}
		}
	}
	return cout<<"NO\n" , 0 ;
}