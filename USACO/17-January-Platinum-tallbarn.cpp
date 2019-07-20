/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : USACO 2017 January Platinum
   problem name : tallbarn (USACO 17jan-tallbarn-plat)
   problem link : http://usaco.org/index.php?page=viewproblem2&cpid=697

   problem's solution : 
   	http://usaco.org/current/data/sol_tallbarn_platinum_jan17.html

*/

#include <bits/stdc++.h>

using namespace std; 

const int MAX = 1e5 + 5 ;

long long n , k ;

long long arr[MAX] ;

bool check(long double mid)
{
	long long now = 0ll ;
	for(int i = 0 ; i < n ; ++i)
		now += (long long)((sqrt(1 + 4ll*arr[i]/mid)-1)/2);
	return now <= k ;
}

int main()
{
	freopen("tallbarn.in" , "r" , stdin) ;
	freopen("tallbarn.out" , "w" , stdout) ;
	scanf("%lld %lld" , &n,  &k) ;
	k -= n ;
	for(int i = 0 ; i < n ; ++i)
		scanf("%lld" , &arr[i]) ;
	long double l = 0.0 , r = 1e18 ;
	long double ans = r ;
	for(int i = 0 ; i < 200 ; ++i)
	{
		long double mid = (l + r) / 2.00 ;
		if(check(mid))
			ans = min(ans , mid) , r = mid ;
		else
			l = mid ;
	}
	long double ans2 = 0.00 ; 
	long long now = 0 ;
	for(int i = 0 ; i < n ; ++i)
	{
		long double x = (long long)((sqrt(1 + 4ll*arr[i]/ans)-1)/2);
		ans2 += 1.00 * arr[i] / (x+1) ;
		now += x ;
	}
	return cout<<(long long)round(ans2 - (k - now) * ans)<<"\n" , 0;
}
