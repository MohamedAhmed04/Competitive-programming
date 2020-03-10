/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   problem name : Pitici3
   problem link : https://www.infoarena.ro/problema/pitici3

   Problem's solution : 
    same idea : https://github.com/stefdasca/CompetitiveProgramming/blob/master/Infoarena/pitici3.cpp

*/

#include <bits/stdc++.h>

using namespace std ;

const int MAX = 1e5 + 10 , MAXN = 2010 ;

int n , d ;
vector< pair<int , int> >vp ;
int suff[MAXN] , dp[MAXN][MAXN] ;

bool cmp(pair<int , int> &a , pair<int , int> &b)
{
	return a.first + a.second < b.first + b.second ;
}

int main()
{
	freopen("pitici3.in" , "r" , stdin) ;
	freopen("pitici3.out" , "w" , stdout) ;
	memset(dp , -1 , sizeof(dp)) ;
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	cin>>n ;
	for(int i = 0 ; i < n ; ++i)
	{
		int x , y; 
		cin>>x>>y ;
		vp.emplace_back(x , y) ;
	}
	cin>>d ;
	vp.emplace_back(0 , 0) ;
	sort(vp.begin() , vp.end() , cmp) ;
	for(int i = n ; i >= 1 ; --i)
		suff[i] = suff[i+1] + vp[i].first ;
	for(int i = 0 ; i <= n ; ++i)
	{
		dp[i][0] = suff[1] ;
		for(int j = 1 ; j <= n ; ++j)
			dp[i][j] = -1e9 ;
	}
	int ans = 0 ;
	for(int i = 1 ; i <= n ; ++i)
	{
		for(int j = 1 ; j <= n ; ++j)
		{
			dp[i][j] = dp[i-1][j] ;
			int x = dp[i-1][j-1] - vp[i].first ;
			if(x > dp[i][j] && x + vp[i].second + vp[i].first >= d)
			{
				dp[i][j] = x ;
				ans = j ;
			}
		}
	}
	return cout<<ans<<"\n" , 0 ;
}		