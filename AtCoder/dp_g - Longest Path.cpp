/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest : AtCoder dp Educational contest (Atcoder dp)
   problem name : dp_g - Longest Path
   problem link : https://atcoder.jp/contests/dp/tasks/dp_g

*/

#include <bits/stdc++.h>

using namespace std;

const int MAX = 1e5 + 10 ;
long long dp[MAX] ;
vector< vector<int> >adjlist ;
vector<bool>visited ;

void dfs(int node)
{
    visited[node] = true ;
    for(int i = 0 ; i < adjlist[node].size() ; ++i)
    {
        int child = adjlist[node][i] ;
        if(!visited[child])
            dfs(child);
        dp[node] = max(dp[node] , dp[child]+1);
    }
    return ;
}

int main()
{
    int n , m ;
    cin>>n>>m ;
    adjlist = vector< vector<int> >(n+1) ;
    visited = vector<bool>(n+1) ;
    for(int i = 0 ; i < m ; ++i)
    {
        int x , y ;
        cin>>x>>y ;
        adjlist[x].push_back(y) ;
    }
    for(int i = 1 ; i <= n ; ++i)
    {
        if(!visited[i])
            dfs(i) ;
    }
    long long ans = 0 ;
    for(int i = 1 ; i <= n ; ++i)
        ans = max(ans , dp[i]);
    return cout<<ans<<"\n" , 0 ;
}
