/* Author: Mohamed Bakry (handle: MohamedAhmed04)

   contest name: International Olympiad In Informatics (IOI) 2011
   problem name: Tropical Garden (IOI 2011-Garden)
   problem link: https://oj.uz/problem/view/IOI11_garden

   Problem's solution:
     same like: https://github.com/luciocf/Problems/blob/master/IOI/IOI%202011/garden.cpp

*/

#include <bits/stdc++.h>
#include "garden.h"
#include "gardenlib.h"
//#include "grader.cpp" 
 
using namespace std ;
 
const int MAX = 2 * 150010 ; 
 
int mark[MAX] , par[MAX] , vis[MAX] , to[MAX] , best[MAX] , best2[MAX] , dist[MAX][2] , cycleid[MAX] , cycle_sz[MAX] , edge[MAX][2] ;
 
vector< vector<int> >rev_adj(MAX) ;
 
int n , m ;
 
void Addedge(int x , int y , int val)
{
    if(best[x] == val)
    {
        if(best[y] == val)
            to[x] = y+n ;
        else
            to[x] = y ;
    }
    else if(best2[x] == val)
    {
        if(best[y] == val)
            to[x+n] = y+n ;
        else
            to[x+n] = y ;   
    }       
}
 
void ConstructGraph()
{
    for(int i = 0 ; i < m ; ++i)
    {
        int x = edge[i][0] ;
        int y = edge[i][1] ;
        int val = i+1 ;
        ++x , ++y ;
        if(!best[x])
            best[x] = val ;
        else if(!best2[x])
            best2[x] = val ;
        if(!best[y])
            best[y] = val ;
        else if(!best2[y])
            best2[y] = val ;
        Addedge(x , y , val) ;
        Addedge(y , x , val) ;  
    }
}
 
void bfs(int src , bool t)
{
    for(int i = 1 ; i <= n+n ; ++i)
        dist[i][t] = -1 ;
    dist[src][t] = 0 ;
    queue<int>q ;
    q.push(src) ;
    while(!q.empty())
    {
        int node = q.front() ;
        q.pop() ;
        for(auto &child : rev_adj[node])
        {
            if(dist[child][t] == -1)
            {
                dist[child][t] = dist[node][t] + 1 ;
                q.push(child) ;
            }
        }
    }
}
 
int id = 0 ;
 
vector<int>v ;
 
void dfs(int node)
{
    vis[node] = 1 ;
    if(to[node])
    {
        if(mark[to[node]])
        {
            v.clear() ;
            ++id ;
            int a = to[node] ;
            while(node != a)
            {
                v.push_back(node) ;
                node = par[node] ;
            }
            v.push_back(node) ;
            for(auto &i : v)
                cycleid[i] = id ;
            cycle_sz[id] = v.size() ;
            return ;
        }
        mark[node] = 1 ;
        if(!vis[to[node]])
        {
            par[to[node]] = node ;
            dfs(to[node]) ;
        }
    }
    mark[node] = 0 ;
}
 
void find_cycle()
{
    for(int i = 1 ; i <= n+n ; ++i)
    {
        if(vis[i])
            continue ;
        dfs(i) ;
    }
} 
 
void count_routes(int N, int M, int P, int R[][2], int Q, int G[])
{
    for(int i = 0 ; i < M ; ++i)
        edge[i][0] = R[i][0] , edge[i][1] = R[i][1] ;
    P++ ;
    n = N , m = M ;
    ConstructGraph() ;
    for(int i = 1 ; i <= n+n ; ++i)
    {
        if(to[to[i]] == 0 && to[i] > 0)
            to[i] = to[i] - n ;
    }
    for(int i = 1 ; i <= n+n ; ++i)
        rev_adj[to[i]].push_back(i) ;
    bfs(P , 0) ;
    bfs(P+n , 1) ;
    find_cycle() ;
    for(int i = 0 ; i < Q ; ++i)
    {
        int x = G[i] ;
        int ans = 0 ;
        for(int j = 1 ; j <= n ; ++j)
        {
            bool flag = false ;
            if(dist[j][0] != -1)
            {
                if(dist[j][0] == x)
                    flag = true ;
                if(cycleid[P] > 0 && dist[j][0] < x && (x-dist[j][0]) % cycle_sz[cycleid[P]] == 0)
                    flag = true ;
            }
            if(dist[j][1] != -1)
            {
                if(dist[j][1] == x)
                    flag = true ;
                if(cycleid[P+n] > 0 && dist[j][1] < x && (x-dist[j][1]) % cycle_sz[cycleid[P+n]] == 0)
                    flag = true ;
            }
            ans += flag ;
        }
        answer(ans) ;
    }
}