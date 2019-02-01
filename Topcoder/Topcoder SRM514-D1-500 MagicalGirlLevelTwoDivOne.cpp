/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   problem name : TopCoder SRM514-D1-500 MagicalGirlLevelTwoDivOne
   idea(explanation) of the solution :
   https://apps.topcoder.com/wiki/display/tc/SRM+514
*/

#include <bits/stdc++.h>

using namespace std;

class MagicalGirlLevelTwoDivOne
{
public:
    const int mod = 1e9 + 7 ;
    long long fact[10][10][2] ;
    long long maskfact[10][1024] ;
    long long dp[11][1024] ;
    int theCount(vector<string>palette , int n , int m)
    {
        int h = palette.size() ;
        int w = palette[0].size() ;
        for(int i = 0 ; i < n ; ++i)
        {
            for(int j = 0 ; j < m ; ++j)
            {
                for(int k = 0 ; k < 2 ; ++k)
                {
                    long long &p = fact[i][j][k] ;
                    p = 1 ;
                    for(int ii = i ; ii < h ; ii += n)
                    {
                        for(int jj = j ; jj < w ; jj += m)
                        {
                            if(palette[ii][jj] == '.')
                                p = (p * (k+4)) % mod ;
                            else if(palette[ii][jj] % 2 != k)
                                p = 0 ;
                        }
                    }
                }
            }
        }
        for(int y = 0 ; y < n ; ++y)
        {
            for(int mask = 0 ; mask < (1 << m) ; ++mask)
            {
                long long &p = maskfact[y][mask] ;
                p = 1 ;
                int c = 0 ;
                for(int x = 0 ; x < m ; ++x)
                {
                    int k = ((mask >> x) & 1) ;
                    p = (p * fact[y][x][k]) % mod ;
                    c += k ;
                }
                if(c % 2 != 1)
                    p = 0 ;
            }
        }
        memset(dp , 0 , sizeof(dp));
        dp[0][(1 << m)-1] = 1 ;
        for(int y = 1 ; y <= n ; ++y)
        {
            for(int mask = 0 ; mask < (1 << m) ; ++mask)
            {
                long long &ret = dp[y][mask] ;
                ret = 0 ;
                for(int omask = 0 ; omask < (1 << m) ; ++omask)
                {
                    ret += ((maskfact[y-1][omask] * dp[y-1][mask ^ omask]) % mod);
                    ret %= mod ;
                }
            }
        }
        return dp[n][0] ;
    }
};
