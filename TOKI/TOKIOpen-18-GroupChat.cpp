/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest name : TOKI open 2018
   problem name : GroupChat
   problem link :
        https://training.ia-toki.org/problemsets/113/problems/629/
   problem solution :
        https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/TOKI/TOKIOpen-18-GroupChat.txt

*/

#include "group.h"
#include <bits/stdc++.h>

using namespace std ;

int getMinimumDelay(int n , vector<int> x, vector<int> y)
{
    long long minx = 2e9+2 , maxx = -2e9 ;
    long long miny = 2e9+2 , maxy = -2e9 ;
    for(int i = 0 ; i < n ; ++i)
    {
        long long a = x[i] + y[i] , b = x[i] - y[i] ;
        x[i] = a , y[i] = b ;
        x[i] = x[i] * 1ll ;
        y[i] = y[i] * 1ll ;
        minx = min(minx , x[i]*1ll) ;
        maxx = max(maxx , x[i]*1ll) ;
        miny = min(miny , y[i]*1ll) ;
        maxy = max(maxy , y[i]*1ll) ;
    }
    long long l = 0 , r = 2e9 ;
    long long ans = 2e9 ;
    while(l <= r)
    {
        long long mid = (l + r) / 2 ;
        bool t1 = 1 , t2 = 1 ;
        for(int i = 0 ; i < n ; ++i)
        {
            t1 &= ((x[i] <= minx+mid && y[i] <= miny+mid) || (x[i] >= maxx-mid && y[i] >= maxy-mid));
            t2 &= ((x[i] <= minx+mid && y[i] >= maxy-mid) || (x[i] >= maxx-mid && y[i] <= miny+mid));
        }
        if(t1 || t2)
            r = mid-1 , ans = min(ans , mid);
        else
            l = mid+1 ;
    }
    return ans ;
}
