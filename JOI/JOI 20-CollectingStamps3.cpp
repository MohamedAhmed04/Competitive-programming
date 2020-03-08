/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : JOI 2020 Final round (The 19th Japanese Olympiad in Informatics Final Round)
   problem name : Collecting Stamps 3 (JOI 20-CollectingStamps3)
   problem link : https://oj.uz/problem/view/JOI20_ho_t3

   Problem's solution :
    my idea is same idea described in this comment : 
    https://codeforces.com/blog/entry/73648?#comment-581433

*/

#include <bits/stdc++.h>
 
using namespace std ;
 
const int inf = 2e9 ;
const int MAX = 210 ;
 
long long X[MAX] , T[MAX] ;
int n ;
long long L ;
long long dp[MAX][MAX][MAX][2] ;
 
long long dist(int i , int j , int a , int b)
{
	if(b == 0)
	{
		if(a == 0)
			return (X[i] - X[i-1]) ;
		else
			return (L - X[j] + X[i-1]) ;
	}
	else
	{
		if(a == 1)
			return (X[j+1] - X[j]) ;
		else
			return (X[i] + L - X[j+1]) ;
	}
}
 
int main()
{
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	cin>>n>>L ;
	for(int i = 1 ; i <= n ; ++i)
		cin>>X[i] ;
	for(int i = 1 ; i <= n ; ++i)
		cin>>T[i] ;
	for(int i = 0 ; i <= n+1 ; ++i)
	{
		for(int j = 0 ; j <= n+1 ; ++j)
		{
			for(int taken = 1 ; taken <= n+1 ; ++taken)
			{
				for(int a = 0 ; a <= 1 ; ++a)
					dp[i][j][taken][a] = inf ;
			}
		}
	}
	X[n+1] = L ;
	int ans = 0 ;
	for(int i = 1 ; i <= n ; ++i)
	{
		for(int j = n ; j >= i ; --j)
		{
			for(int taken = 0 ; taken <= n ; ++taken)
			{
				for(int a = 0 ; a <= 1 ; ++a)
				{
					long long x , y ;
					x = dp[i-1][j][taken][0] + dist(i , j , a , 0) ;
					y = dp[i][j+1][taken][1] + dist(i , j , a , 1) ;
					dp[i][j][taken][a] = min(x , y) ;
					if(taken)
					{
						x = dp[i-1][j][taken-1][0] + dist(i , j , a , 0) ;
						y = dp[i][j+1][taken-1][1] + dist(i , j , a , 1) ;
						if((a == 0 && min(x , y) <= T[i]) || (a == 1 && min(x , y) <= T[j]))
						{
							dp[i][j][taken][a] = min(dp[i][j][taken][a] , min(x , y)) ;
							ans = max(ans , taken) ;
						}
					}
				}
			}
		}
	}
	return cout<<ans<<"\n" , 0 ;
}

/*#include <bits/stdc++.h>

using namespace std ;

const int inf = 2e9 ;
const int MAX = 210 ;

long long X[MAX] , T[MAX] ;
int n ;
long long L ;
long long dp[MAX][MAX][MAX][2] ;
array<int , 4> prv[MAX][MAX][MAX][2] ;

long long dist(int i , int j , int a , int b)
{
	if(b == 0)
	{
		if(a == 0)
			return (min(X[i] - X[i-1] , L - X[i] + X[i-1])) ;
		else
			return (min(L - X[j] + X[i-1] , X[j] - X[i-1])) ;
	}
	else
	{
		if(a == 1)
			return (min(X[j+1] - X[j] , L - X[j+1] + X[j])) ;
		else
			return (min(X[i] + L - X[j+1] , X[j+1] - X[i])) ;
	}
}

int main()
{
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	cin>>n>>L ;
	for(int i = 1 ; i <= n ; ++i)
		cin>>X[i] ;
	for(int i = 1 ; i <= n ; ++i)
		cin>>T[i] ;
	for(int i = 0 ; i <= n+1 ; ++i)
	{
		for(int j = 0 ; j <= n+1 ; ++j)
		{
			for(int taken = 1 ; taken <= n+1 ; ++taken)
			{
				for(int a = 0 ; a <= 1 ; ++a)
					dp[i][j][taken][a] = inf ;
			}
		}
	}
	X[n+1] = L ;
	int ans = 0 ;
	for(int i = 1 ; i <= n ; ++i)
	{
		for(int j = n ; j >= i ; --j)
		{
			for(int taken = 0 ; taken <= n ; ++taken)
			{
				for(int a = 0 ; a <= 1 ; ++a)
				{
					long long x , y ;
					x = dp[i-1][j][taken][a] + dist(i , j , a , 0) ;
					y = dp[i][j+1][taken][a] + dist(i , j , a , 1) ;
					dp[i][j][taken][a] = min(x , y) ;
					if(taken)
					{
						x = dp[i-1][j][taken-1][a] + dist(i , j , a , 0) ;
						y = dp[i][j+1][taken-1][a] + dist(i , j , a , 1) ;
						if((a == 0 && min(x , y) <= T[i]) || (a == 1 && min(x , y) <= T[j]))
						{
							dp[i][j][taken][a] = min(dp[i][j][taken][a] , min(x , y)) ;
							if(dp[i][j][taken][a] == x)
								prv[i][j][taken][a] = {i-1 , j , taken-1 , a} ;
							else
								prv[i][j][taken][a] = {} 
							ans = max(ans , taken) ;
						}
					}
				}
			}
		}
	}
	return cout<<ans<<"\n" , 0 ;
}*/		