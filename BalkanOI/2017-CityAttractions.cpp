/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest name : Balkan Olympiad in Informatics 2017 day 2
   problem name : CityAttractions (BalkanOI2017-CityAttractions)
   problem link : https://csacademy.com/contest/balkan-oi-2017-day-2/task/city-attractions/

   problem solution :
     dp on tree problem
   so our state is dp[node][2] where node is the node we are in now and if dp[node][0] then
   it means max in the subtree and if dp[node][1] then it means max out of subtree so we will try
   to find dp[node][0] for every node in first dfs , and in second dfs we will try to find dp[node][1]
   for all nodes , don't forget about handling cases and after that we will loop and choose the best from
   dp[node][0] and dp[node][1] and after that when print since k is upto 10^18 then there will be cycles so we will
   that happen every period so we will handle it.

   note : see comments in code for more clarification.

*/

#include <bits/stdc++.h>

using namespace std;

const int MAX = 3e5 + 5 ;
int arr[MAX] , vis[MAX] , parent[MAX] , Next[MAX] , visited[MAX] ;
pair<int , int>dp[MAX][2] ;
int n ;
long long k ;
vector< vector<int> >adj(MAX) ;

//first dfs to find dp[node][0] for every node

void dfs0(int node , int par)
{
    parent[node] = par ;
    dp[node][0].first = arr[node] , dp[node][0].second = node ;
    for(auto &child : adj[node])
    {
        if(child == par)
            continue ;
        dfs0(child , node) ;
        if(dp[node][0].second == node)
            dp[node][0].first = dp[child][0].first - 1 , dp[node][0].second = dp[child][0].second ;
        if(dp[child][0].first-1 == dp[node][0].first)
            dp[node][0].second = min(dp[node][0].second , dp[child][0].second) ;
        else if(dp[child][0].first-1 > dp[node][0].first)
            dp[node][0].first = dp[child][0].first - 1,  dp[node][0].second = dp[child][0].second ;
        if(arr[child]-1 == dp[node][0].first)
            dp[node][0].second = min(dp[node][0].second , child) ;
        else if(arr[child]-1 > dp[node][0].first)
            dp[node][0].first = arr[child] - 1 , dp[node][0].second = child ;
    }
    return ;
}

//second dfs to find dp[node][1] for every node

void dfs1(int node)
{
    vis[node] = 1 ;
    dp[node][1].first = arr[node] , dp[node][1].second = node ;
    if(node == 1)
        return ;
    int par = parent[node] ;
    if(vis[par] == 0)
        dfs1(par) ;
    dp[node][1].first = dp[par][1].first - 1 ;
    dp[node][1].second = dp[par][1].second ;
    if(arr[par] - 1 == dp[node][1].first)
        dp[node][1].second = min(dp[node][1].second , par) ;
    else if(arr[par] - 1 > dp[node][1].first)
        dp[node][1].first = arr[par] - 1 , dp[node][1].second = par ;
    for(auto &child : adj[par])
    {
        if(child == node || child == parent[par])
            continue ;
        if(dp[child][0].first-2 == dp[node][1].first)
            dp[node][1].second = min(dp[node][1].second , dp[child][0].second) ;
        else if(dp[child][0].first-2 > dp[node][1].first)
            dp[node][1].first = dp[child][0].first - 2 , dp[node][1].second = dp[child][0].second ;
        if(arr[child] - 2 == dp[node][1].first)
            dp[node][1].second = min(dp[node][1].second  , child) ;
        else if(arr[child] - 2 > dp[node][1].first)
            dp[node][1].first = arr[child] - 2 , dp[node][1].second = child ;
    }
    return ;
}

int main()
{
    scanf("%d %lld" , &n , &k) ;
    for(int i = 1 ; i <= n ; ++i)
        scanf("%d" , &arr[i]) ;
    for(int i = 0 ; i < n-1 ; ++i)
    {
        int x , y ;
        scanf("%d %d" , &x , &y) ;
        adj[x].push_back(y) ;
        adj[y].push_back(x) ;
    }
    //make dfs0 and root tree at 1
    dfs0(1 , 0) ;
    //loop on every unvisited node and make dfs1 from it
    for(int i = 1 ; i <= n ; ++i)
    {
        if(vis[i] == 0)
            dfs1(i) ;
    }
    //choose the best from dp[node][0] and dp[node][1] and handle cases
    for(int node = 1 ; node <= n ; ++node)
    {
        if(dp[node][0].second == node)
        {
            Next[node] = dp[node][1].second ;
            continue ;
        }
        if(dp[node][1].second == node)
        {
            Next[node] = dp[node][0].second ;
            continue ;
        }
        if(dp[node][0].first == dp[node][1].first)
            Next[node] = min(dp[node][0].second , dp[node][1].second) ;
        else if(dp[node][0].first > dp[node][1].first)
            Next[node] = dp[node][0].second ;
        else if(dp[node][1].first > dp[node][0].first)
            Next[node] =  dp[node][1].second ;
    }
    //find period of every cycle happen and handle it
    int now = 1 ;
    vector<int>ans , ans2 ;
    for(int i = 1 ; ; ++i)
    {
        now = Next[now] ;
        if(visited[now] == 2)
            break ;
        if(visited[now] == 1)
            ans2.push_back(now) ;
        else
            ans.push_back(now) ;
        visited[now]++ ;
    }
    --k ;
    if(k < ans.size())
        return printf("%d" , ans[k]) , 0 ;
    k -= ans.size() ;
    return printf("%d" , ans2[(k % ans2.size())]) , 0 ;
}
