/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest name : Baltic olympiad in informatics 2016 day 1
   problem name : Bosses (BOI16-Bosses)
   problem link : https://oj.uz/problem/view/BOI16_bosses

   problem solution :
   since time limit is strict so one BFS and one DFS won't pass and two BFS won't pass
   so we need to solve it using one BFS so since it's optimal to assign every node to lowest level
   so we will loop every time and make node i as starting node and every time we add to answer number of
   ancestors of node (parents of node) + 1 (node itself) and handle case if node didn't visit
   all nodes so we won't take it as answer else then answer will be minimum answer or cost to make i starting node.
*/

#include <bits/stdc++.h>

using namespace std;

const int MAX = 5005 ;
int vis[MAX] ;
long long cost = 0;

vector< vector<int> >adj(MAX) ;

int n , cnt = 0 ;

void bfs(int src)
{
    queue< pair<int , int> >q ;
    q.push({src , 1}) ;
    vis[src] = 1 ;
    while(!q.empty())
    {
        pair<int , int>p = q.front() ;
        q.pop() ;
        cnt++ ;
        int node = p.first ;
        cost += (p.second * 1ll) ;
        for(auto &child : adj[node])
        {
            if(vis[child] == 1)
                continue ;
            vis[child] = 1 ;
            q.push({child , p.second+1}) ;
        }
    }
    return ;
}

int main()
{
    scanf("%d" , &n) ;
    for(int i = 1 ; i <= n ; ++i)
    {
        int m ;
        scanf("%d" , &m) ;
        while(m--)
        {
            int x ;
            scanf("%d" , &x) ;
            adj[x].push_back(i) ;
        }
    }
    long long ans = 1e18 ;
    for(int i = 1 ; i <= n ; ++i)
    {
        memset(vis , 0 , sizeof(vis)) ;
        cnt = 0 , cost = 0;
        bfs(i) ;
        if(cnt != n)
            continue;
        ans = min(ans , cost) ;
    }
    return printf("%lld" , ans) , 0 ;
}
