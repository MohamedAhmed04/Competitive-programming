/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest : AtCoder dp Educational contest (Atcoder dp)
   problem name : dp_p - Independent Set
   problem link : https://atcoder.jp/contests/dp/tasks/dp_p

*/

#include <bits/stdc++.h>

using namespace std;

const int MAX = 1e5 + 10 ;
const long long mod = 1e9 + 7ll ;
vector< vector<int> >adjlist ;
long long dp[MAX][2] ;
int n ;

long long solve(int parent , int node , int color)
{
    if(adjlist.size() == 1 && parent != -1)
        return 1ll ;
    long long &ret = dp[node][color] ;
    if(ret != -1)
        return ret ;
    ret = 1ll ;
    for(auto &child : adjlist[node])
    {
        if(child == parent)
            continue;
        if(color == 1)
            ret = (ret * solve(node , child , 0)) % mod ;
        else
        {
            long long ways = (solve(node , child , 0) + solve(node , child , 1)) % mod ;
            ret = (ret * ways) % mod ;
        }
    }
    return ret ;
}

int main()
{
    memset(dp , -1 , sizeof(dp));
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n ;
    adjlist = vector< vector<int> >(n+2) ;
    for(int i = 0 ; i < n-1 ; ++i)
    {
        int x , y ;
        cin>>x>>y ;
        --x ;
        --y ;
        adjlist[x].push_back(y);
        adjlist[y].push_back(x);
    }
    return cout<<((solve(-1 , 0 , 0) + solve(-1 , 0 , 1)) % mod) % mod<<"\n" , 0 ;
}
