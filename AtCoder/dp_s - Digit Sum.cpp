/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest : AtCoder dp Educational contest (Atcoder dp)
   problem name : dp_s - Digit Sum
   problem link : https://atcoder.jp/contests/dp/tasks/dp_s

*/

#include <bits/stdc++.h>

using namespace std;

const long long MAX = 1e5 ;
const long long mod = 1e9 + 7ll ;
long long dp[MAX][105][2][2] ;
vector<long long>num ;
long long d ;

long long solve(long long idx , long long rem , bool t , bool t2)
{
    if(idx == num.size())
    {
        if(rem == 0 && t2 == 1)
            return 1ll ;
        return 0ll ;
    }
    long long &ret = dp[idx][rem][t][t2] ;
    if(ret != -1)
        return ret ;
    ret = 0 ;
    long long LMT ;
    if(t == 0)
        LMT = num[idx] ;
    else
        LMT = 9 ;
    for(long long i = 0 ; i <= LMT ; ++i)
    {
        long long nt = t ;
        long long nt2 = t2 ;
        if(t == 0 && i < LMT)
            nt = 1 ;
        if(t2 == 0 && i != 0)
            nt2 = 1ll ;
        ret = (ret + solve(idx+1 , (rem + i) % d , nt , nt2)) % mod;
        ret = (ret % mod) ;
    }
    return (ret % mod) ;
}

long long run(string s)
{
    for(long long i = 0 ; i < s.size() ; ++i)
        num.push_back(s[i] - '0') ;
    memset(dp , -1 , sizeof(dp));
    long long ans = solve(0 , 0 , 0 , 0);
    return ans ;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    string s ;
    cin>>s ;
    cin>>d ;
    return cout<<run(s)<<"\n" , 0 ;
}
