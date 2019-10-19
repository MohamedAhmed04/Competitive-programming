/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : central europian olympiad in informatics 2017 (CEOI 2017)
   problem name : building bridges
   problem link : https://csacademy.com/contest/ceoi-2017-day-2/task/building-bridges/

   problem's solution :
   	we can do it using dp where dp[i] = min(dp[j] + (h[i]-h[j])*(h[i]-h[j])+sum[i-1]-sum[j]) where j < i
   	sum[i] = sum w[i] from 1 to i.
   	we can do it using LiChao tree (convex hull trick optimization).

*/

#include <bits/stdc++.h>
 
using namespace std ;
 
struct point
{
	long long x , y ;
};
 
long long f(point a , long long x)
{
	return (a.x - x) * (a.x - x) + a.y ;
}
 
const int MAX = 8e6 + 100 ;
 
int L[MAX] , R[MAX] ;
point line[MAX] ;
int id = 1 ;
 
void init()
{
	for(int i = 0 ; i < MAX ; ++i)
		line[i].x = 0 , line[i].y = 1e18 ;
}
 
int lft(int node)
{
	if(!L[node])
		L[node] = ++id ;
	return L[node] ;
}
 
int rig(int node)
{
	if(!R[node])
		R[node] = ++id ;
	return R[node] ;
}
 
void add_line(point nw , int v = 1 , long long l = -1e12-5 , long long r = 1e12+5)
{
	long long m = l + (r-l) / 2ll ;
	bool lef = f(nw , l) < f(line[v] , l) ;
	bool mid = f(nw , m) < f(line[v] , m) ;
	if(mid)
		swap(line[v] , nw) ;
	if(r-l == 1)
		return ;
	else if(lef != mid)
		add_line(nw , lft(v) , l , m) ;
	else
		add_line(nw , rig(v) , m , r) ;
}
 
long long get(long long x , int v = 1 , long long l = -1e12-5 , long long r = 1e12+5)
{
	long long m = l + (r-l) / 2 ;
	if(r-l == 1)
		return f(line[v] , x) ;
	else if(x < m)
		return min(f(line[v] , x) , get(x , lft(v) , l , m)) ;
	else
		return min(f(line[v] , x) , get(x , rig(v) , m , r)) ;
}


int main()
{
	init() ;
    int n ;
    scanf("%d" , &n) ;
    long long arr[n+1] , sum[n+1] , dp[n+1];
    for(int i = 1 ; i <= n ; ++i)
        scanf("%lld" , &arr[i]) ;
    sum[0] = 0 ;
    for(int i = 1 ; i <= n ; ++i)
    {
        long long x ;
        scanf("%lld" , &x) ;
        sum[i] = sum[i-1] + x ;
    }
    point p ;
    dp[1] = 0 ;
    p.x = arr[1] , p.y = -sum[1] + dp[1] ;
    add_line(p) ;
    for(int i = 2 ; i <= n ; ++i)
    {
        dp[i] = get(arr[i]) + sum[i-1] ;
        p.x = arr[i] , p.y = -sum[i] + dp[i] ;
        add_line(p) ;
    }
    return printf("%lld" , dp[n]) , 0 ;
}