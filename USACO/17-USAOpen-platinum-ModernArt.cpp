/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : USACO 2017 USA open contest
   problem name : Modern Art (USACO 2017 USA open contest - platinum - Modern Art)
   problem link : http://usaco.org/index.php?page=viewproblem2&cpid=744

   problem solution :
    http://usaco.org/current/data/sol_art_platinum_open17.html
*/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1005 ;
int arr[MAXN][MAXN] , arr2[MAXN][MAXN] , exist[MAXN*MAXN] ;
int u[MAXN * MAXN] , d[MAXN * MAXN] , r[MAXN * MAXN] , l[MAXN * MAXN];
int painted_first[MAXN*MAXN] ;
int n ;

int main()
{
    freopen("art.in" , "r" , stdin) ;
    freopen("art.out" , "w" , stdout) ;
    scanf("%d" , &n) ;
    for(int i = 1 ; i <= n*n ; ++i)
        painted_first[i] = 1 ;
    for(int i = 1 ; i <= n ; ++i)
    {
        for(int j = 1 ; j <= n ; ++j)
            scanf("%d" , &arr[i][j]) ;
    }
    //prepare coordinates of every rectangle
    int appear = 0 ;
    for(int i = 1 ; i <= n ; ++i)
    {
        for(int j = 1 ; j <= n ; ++j)
        {
            int now = arr[i][j] ;
            if(now == 0)
                continue ;
            if(exist[now] == 0)
                appear++ ;
            exist[now]++ ;
            if(u[now] == 0)
                u[now] = i ;
            if(d[now] == 0)
                d[now] = i ;
            if(l[now] == 0)
                l[now] = j ;
            if(r[now] == 0)
                r[now] = j ;
            u[now] = min(u[now] , i) ;
            d[now] = max(d[now] , i) ;
            l[now] = min(l[now] , j) ;
            r[now] = max(r[now] , j) ;
        }
    }
    if(appear == 1)
    {
        if(n == 1)
            return cout<<1<<"\n" , 0 ;
        else
            return cout<<n*n-1<<"\n" , 0 ;
    }
    //prepare and make prefix sum
    int ans = n*n-appear ;
    for(int i = 1 ; i <= n*n ; ++i)
    {
        if(!exist[i])
            continue ;
        arr2[u[i]][l[i]]++ ;
        arr2[u[i]][r[i]+1]-- ;
        arr2[d[i]+1][l[i]]-- ;
        arr2[d[i]+1][r[i]+1]++ ;
    }
    for(int i = 1 ; i <= n ; ++i)
    {
        for(int j = 1 ; j <= n ; ++j)
            arr2[i][j] = arr2[i][j] + arr2[i-1][j] + arr2[i][j-1] - arr2[i-1][j-1] ;
    }
    for(int i = 1 ; i <= n ; ++i)
    {
        for(int j = 1 ; j <= n ; ++j)
        {
            int now = arr[i][j] ;
            if(arr2[i][j] > 1)
                painted_first[now] = 0 ;
        }
    }
    for(int i = 1 ; i <= n*n ; ++i)
    {
        if(painted_first[i] == 1 && exist[i])
            ans++ ;
    }
    return cout<<ans<<"\n" , 0 ;
}
