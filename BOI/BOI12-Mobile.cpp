/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : Baltic olympiad in informatics 2012 day 1
   problem name : Mobile (BOI12-Mobile)
   problem link : https://oj.uz/problem/view/BOI12_mobile

   problem's solution : 
    same idea : https://github.com/ivokaragyozov/CompetitiveProgramming/blob/master/BalticOI/Baltic-12-mobile.cpp

*/

#include <bits/stdc++.h>
 
using namespace std ;
 
const int MAX = 1e6 + 10 ;
int x[MAX] , y[MAX] ;
int n , l;
double a , b , now;
 
bool check(double radius)
{
	now = 0.00 ;
	for(int i = 0 ; i < n ; ++i)
	{
		a = sqrt(radius * radius - ((-y[i] * 1ll) * (-y[i] * 1ll))) + x[i] * 1ll ;
		b = -sqrt(radius * radius - ((-y[i] * 1ll) * (-y[i] * 1ll))) + x[i] * 1ll ;
		if(a > b)
			swap(a , b) ;
		if(a <= now)
			now = max(now , b) ; 
	}
	return (now >= l) ;
}
 
int main()
{
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	cin>>n>>l ;
	for(int i = 0 ; i < n ; ++i)
		cin>>x[i]>>y[i] ;
	double low = 0.000 , high = 1e9 ;
	double ans = high ;
	for(int i = 0 ; i < 40 ; ++i)
	{
		double mid = (low + high) / 2.00 ;
		if(check(mid))
			ans = mid , high = mid ;
		else
			low = mid ;
	}
	return cout<<fixed<<setprecision(6)<<ans<<"\n" , 0 ;
}
