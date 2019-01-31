/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   problem name : TopCoder SRM568-D2-1000 WolfInZooDivTwo

   solution of the problem :
   we will make dp to count number of ways and everytime we try to put
   wolf in current point and if there is destination that need one wolf
   to be in it and current point is last point of destination..then we
   shouldn't leave this point without wolf in it so we can't leave it
   without putting wolf and if there isn't so we can leave current point
   without a wolf.
*/

#include <bits/stdc++.h>

using namespace std;

class WolfInZooDivTwo
{
public:
    const long long mod = 1e9 + 7ll ;
    long long dp[310][310] ;
    int n , m;
    vector<int>l , r ;
    long long solve(int idx , int last)
    {
        if(idx == n)
            return 1 ;
        long long &ret = dp[idx][last] ;
        if(ret != -1)
            return ret ;
        bool t = true ;
        if(idx == 0)
            last = -1 ;
        for(int i = 0 ; i < m ; ++i)
        {
            if(l[i] > last && r[i] == idx)
                t = false ;
        }
        ret = (solve(idx+1 , idx) % mod) ;
        if(t)
            ret += (solve(idx+1 , last) % mod) ;
        ret %= mod ;
        return ret ;
    }
    int count(int N, vector <string> L, vector <string> R)
    {
        n = N ;
        memset(dp , -1 , sizeof(dp));
        stringstream a(accumulate(L.begin() , L.end() , string())) ;
        int x ;
        while(a >> x)
        {
            l.push_back(x) ;
        }
        stringstream b(accumulate(R.begin() , R.end() , string()));
        while(b >> x)
        {
            r.push_back(x) ;
        }
        m = l.size() ;
        return solve(0 , 0) ;
    }
};
