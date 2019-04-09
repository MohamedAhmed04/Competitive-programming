/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   problem name : KOMPICI (Spoj KOMPICI - Kompići)
   problem link : https://www.spoj.com/problems/KOMPICI/

   problem solution :
   represent every number as mask and avoid repetitions of digits and now we can
   loop a nested loop and count number of pairs.

*/

#include <bits/stdc++.h>

using namespace std;

int arr[1030] ;

int main()
{
    int n ;
    scanf("%d" , &n) ;
    for(int i = 0 ; i < n ; ++i)
    {
        long long x ;
        scanf("%lld" , &x) ;
        int mask = 0;
        while(x > 0)
        {
            mask |= (1 << (x % 10)) ;
            x /= 10 ;
        }
        arr[mask]++ ;
    }
    long long ans = 0ll ;
    for(int i = 1 ; i <= 1024 ; ++i)
    {
        for(int j = i ; j <= 1024 ; ++j)
        {
            if(i == j)
                ans += (arr[j] * (arr[j]-1ll) / 2ll) * 1ll ;
            else if((i & j))
                ans += (arr[i] * arr[j]) * 1ll ;
        }
    }
    return printf("%lld\n" , ans) , 0 ;
}
