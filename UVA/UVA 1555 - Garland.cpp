/* Author : MohamedAhmed (handle : MohamedAhmed04)

   problem name : Garland (UVA 1555 - Garland)
   problem link :
     https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=4330

   problem solution :
   let's first simplify the equation if H[i] :
   H[i] = (H[i-1] + H[i+1]) / 2 - 1
   H[i]+1 = (H[i-1] + H[i+1]) / 2
   (H[i] + 1) * 2 = H[i-1] + H[i+1]
   (H[i] + 1) * 2 - H[i-1] = H[i+1].
   so now we will binary search on value of second element and print minimum value that's >= 0.0000000.

*/

#include <bits/stdc++.h>

using namespace std;

int n ;
double a ;

double check(double mid)
{
    double prv = mid , prv2 = a ;
    for(int i = 3 ; i <= n ; ++i)
    {
        double x = (prv + 1.000) * 2.00 - prv2 ;
        if(x < 0.000000000)
            return (-1.0000) ;
        prv2 = prv ;
        prv = x ;
    }
    return prv ;
}

int main()
{
    cout<<fixed<<setprecision(2);
    while(cin>>n>>a)
    {
        double l = 0.00 , r = 1e9*1.00 ;
        double ans = 1e9 * 1.00 ;
        for(int i = 0 ; i < 500 ; ++i)
        {
            double mid = (l + r) / 2.00 ;
            double now = check(mid) ;
            if(now >= 0.00000000000)
                r = mid , ans = min(ans , now) ;
            else
                l = mid ;
        }
        cout<<ans<<"\n";
    }
    return 0 ;
}
