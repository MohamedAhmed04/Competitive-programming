/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : COCI 2017-2018 contest 4
   problem name : Ceste (COCI 17 Ceste)
   problem link : https://oj.uz/problem/view/COCI17_ceste

   problem solution :
    make Dijkstra from node 1 to all nodes and every time we try to minimize some of costs
   until current node but the problem that will lead to TLE.
   so to fix that we will make array to store minimum sum of time to this node until now.
   since we make dijkstra in priority queue so we know every time that sum of C is >= all prev times
   and if also we went to state before that with sum of time less than current sum of time so no need to
   continue in this state.

*/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2010 , MAXT = MAXN * MAXN;

struct edge
{
    int to , time , cost ;
    edge(int ve , int ti , int co)
    {
        to = ve ;
        time = ti ;
        cost = co ;
    }
};

vector< vector<edge> >adj(MAXN) ;
long long ans[MAXN] , tillnow[MAXN] ;
int n , m ;

int main()
{
    scanf("%d %d" , &n,  &m) ;
    int a , b , c , d ;
    for(int i = 0 ; i < m ; ++i)
    {
        scanf("%d %d %d %d" , &a , &b , &c , &d) ;
        adj[a].push_back(edge(b , c , d)) ;
        adj[b].push_back(edge(a , c , d)) ;
    }
    long long cons = 1e17 ;
    for(int i = 1 ; i <= n ; ++i)
        ans[i] = cons , tillnow[i] = 1e17;
    priority_queue< pair<int , pair<int , int> > , vector< pair<int , pair<int , int>  > > , greater< pair<int , pair<int , int> > > >q ;
    q.push({0 , {0 , 1}}) ;
    while(!q.empty())
    {
        pair<int , pair<int , int> >p = q.top() ;
        q.pop() ;
        int node = p.second.second , sumc = p.first , sumt = p.second.first ;
        ans[node] = min(ans[node] , (sumt * 1ll) * (sumc * 1ll)) ;
        if(sumt > tillnow[node])
            continue;
        tillnow[node] = sumt ;
        for(auto &child : adj[node])
        {
            int nto = child.to ;
            int ntime = child.time + sumt;
            int ncost = child.cost + sumc;
            if(ntime >= MAXT)
                continue ;
            q.push({ncost , {ntime , nto}}) ;
        }
    }
    for(int i = 2 ; i <= n ; ++i)
    {
        if(ans[i] == cons)
            ans[i] = -1 ;
        printf("%lld\n" , ans[i]);
    }
    return 0 ;
}
