/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : Central Europian Olympiad in Informatics (CEOI) 2018 day 1
   problem name : Cloud Computing (CEOI 18-CloudComputing)
   problem link : https://csacademy.com/contest/ceoi-2018-day-1/task/cloud-computing/

   problem's solution : 
   - sort the all computers according to F[i] (including computers that customer needs)
   - now dp[i][j] equal maximum profit if we made orders until idx i and remaining cors is j
   - first clear the dp with very small number and make dp[0][0] = 0
   - transition : dp[i][j] = dp[i-1][j]
                  If this order is buying computer then :
                  dp[i][j] = max(dp[i][j] , dp[i-1][j-arr[i].c]-arr[i].v)
                  else if the order is selling a computer then : 
                  dp[i][j] = max(dp[i][j] , dp[i-1][arr[i].c+j] + arr[i].v)

   - since we need only current state and previous state, then apply memory optimization.
*/

#include <bits/stdc++.h>

using namespace std ;

const int MAX = 2010 ;

struct computer
{
	int c , f , v , id ;
};

int mark[MAX] ;
int n , m ;
computer arr[MAX+MAX] ;

long long dp[2][(MAX+MAX)*52] ;

bool cmp(computer &a , computer &b)
{
	if(a.f != b.f)
		return a.f > b.f ;
	else
		return a.id < b.id ;
}

int main()
{
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	cin>>n ;
	for(int i = 1 ; i <= n ; ++i)
	{
		cin>>arr[i].c>>arr[i].f>>arr[i].v ;
		arr[i].id = i ;
	}
	cin>>m ;
	for(int i = n+1 ; i <= n+m ; ++i)
	{
		cin>>arr[i].c>>arr[i].f>>arr[i].v ;
		arr[i].id = i  ;
	}
	sort(arr+1 , arr+n+m+1 , cmp) ;
	long long ans = 0ll ;
	for(int j = 1 ; j <= (n+m)*50 ; ++j)
		dp[0][j] = -1e14 ;
	for(int i = 1 ; i <= n+m ; ++i)
	{
		for(int j = 0 ; j <= (n+m)*50 ; ++j)
		{
			dp[i&1][j] = dp[(i-1)&1][j] ;
			if(arr[i].id <= n)
			{
				if(j - arr[i].c >= 0)
					dp[i&1][j] = max(dp[i&1][j] , dp[(i-1)&1][j-arr[i].c]-arr[i].v) ;
			}
			else if(arr[i].id > n)
			{
				if(j+arr[i].c <= (n+m)*50)
					dp[i&1][j] = max(dp[i&1][j] , dp[(i-1)&1][arr[i].c+j] + arr[i].v) ;
			}
			ans = max(ans , dp[i&1][j]) ;
		}
	}
	return cout<<ans<<"\n" , 0 ;
}		