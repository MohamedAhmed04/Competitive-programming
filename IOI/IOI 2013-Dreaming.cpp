/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest name : IOI 2013 day 1
   problem name : Dreaming (IOI 2013-Dreaming)
   problem link : https://oj.uz/problem/view/IOI13_dreaming

   important blog to read : https://codeforces.com/blog/entry/17974

   an easier version of problem if you want to solve :
    https://codeforces.com/contest/1092/problem/E

   problem solution :
      http://blog.brucemerry.org.za/2013/07/ioi-2013-day-1-analysis.html

   note : see comments for more clarification.

*/

#include "dreaming.h"
#include <bits/stdc++.h>

using namespace std;

const int MAX = 1e5 + 5 ;
vector< vector< pair<int , int> > >adj(MAX) ;
int vis[MAX] , parent[MAX] , Distance[MAX];

// now is the farthest node and dist is distance between node and now
int now , dist = 0 ;

//A bfs function to to find farthest node from node and distance of it
void bfs(int node)
{
    now = node , dist = 0 ;
    queue< pair<int , pair<int , int> > >q ;
    q.push({node , {0 , -2}}) ;
    Distance[node] = 0 ;
    parent[node] = node ;
    while(!q.empty())
    {
        pair<int , pair<int , int> >p = q.front() ;
        q.pop() ;
        int cur = p.first , d = p.second.first , par = p.second.second ;
        vis[cur] = 1 ;
        parent[cur] = par ;
        if(d > dist)
            now = cur , dist = d ;
        for(auto &child : adj[cur])
        {
            if(child.first == par)
                continue;
            Distance[child.first] = child.second ;
            q.push({child.first , {d + child.second , cur}}) ;
        }
    }
    return ;
}

int travelTime(int n , int m , int l , int A[] , int B[] , int T[] )
{
    //make the adjacency list
    memset(parent , -1 , sizeof(parent)) ;
    for(int i = 0 ; i < m ; ++i)
    {
        int x = A[i] , y = B[i] , c = T[i] ;
        adj[x].push_back({y , c}) ;
        adj[y].push_back({x , c}) ;
    }
    vector< pair<int , int> >v ;
    //loop on every Tree
    for(int i = 0 ; i < n ; ++i)
    {
        if(vis[i] == 1)
            continue ;
        //found new Tree
        bfs(i) ;
        int x = now ;
        bfs(now) ;
        //one node only
        if(dist == 0)
        {
            v.push_back({0 , i}) ;
            continue;
        }
        //find the center of the diameter that minimizes distance to the two farthest node.
        int sum = 0 , cur = now , prv = -1 ;
        for(int j = 0 ; j < n ; ++j)
        {
            sum += Distance[cur] ;
            prv = cur ;
            cur = parent[cur] ;
            if(cur == -1)
                while(1) ;
            if(sum*2 >= dist)
                break;
        }
        int a = max(sum , dist - sum) ;
        sum -= Distance[prv] ;
        if(max(sum , dist - sum) < a && prv != -1)
            v.push_back({max(sum , dist - sum) , prv}) ;
        else
            v.push_back({a , cur}) ;
    }
    //connect edges to make one tree
    sort(v.rbegin() , v.rend()) ;
    int idx = v[0].second ;
    for(int i = 1 ; i < v.size() ; ++i)
    {
        int idx2 = v[i].second ;
        adj[idx].push_back({idx2 , l}) ;
        adj[idx2].push_back({idx , l}) ;
    }
    //return diameter of the new tree
    bfs(0) ;
    bfs(now) ;
    return dist ;
}

