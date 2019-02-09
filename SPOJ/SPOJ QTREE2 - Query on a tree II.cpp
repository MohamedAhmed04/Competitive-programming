/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   problem name : SPOJ QTREE2 - Query on a tree II
   problem link : https://www.spoj.com/problems/QTREE2/

*/

#include <bits/stdc++.h>

using namespace std;

const int MAX = 10010 ;
const int MAX_LOG = 14 ;
long long P[MAX][MAX_LOG] , dist[MAX] , parent[MAX] , depth[MAX] , arr[MAX];
vector< vector< pair<int , int> > >adj ;
int n ;
//dfs to find depth of evey node and assign parent for them and distance of every node
void dfs(int node , int par , int lvl)
{
    parent[node] = par ;
    depth[node] = lvl ;
    for(auto &child : adj[node])
    {
        if(child.first != par)
            dist[child.first] = (dist[node] + child.second * 1ll) * 1ll , dfs(child.first , node , lvl+1) ;
    }
}
//preprocess the LCA and distance
void preprocess()
{
    memset(parent , -1 , sizeof(parent));
    dfs(1 , -1 , 0) ;
    for(int i = 1 ; i <= n ; ++i)
    {
        for(int j = 1 ; j < MAX_LOG ; ++j)
            P[i][j] = -1 ;
        P[i][0] = parent[i] ;
    }
    for(int j = 1 ; (1 << j) <= n ; ++j)
    {
        for(int i = 1 ; i <= n ; ++i)
        {
            if(P[i][j-1] != -1)
            {
                P[i][j] = P[P[i][j-1]][j-1] ;
            }
        }
    }
    return ;
}
//Find kth ancestor of node
int kth_ancestor(int node , int k)
{
    if(k == 0)
        return node ;
    for(int j = MAX_LOG-1 ; j >= 0 ; --j)
    {
        if(k - (1 << j) >= 0 && P[node][j] != -1)
        {
            node = P[node][j] ;
            k -= (1 << j) ;
        }
    }
    return node ;
}

//Find lowest common ancestor of two nodes
int LCA(int x , int y)
{
    if(depth[x] < depth[y])
        swap(x , y) ;
    int log ;
    for(log = 1 ; (1 << log) <= depth[x] ; ++log);
    log--;
    for(int i = log ; i >= 0 ; --i)
    {
        if(depth[x] - (1 << i) >= depth[y])
            x = P[x][i] ;
    }
    if(x == y)
        return x ;
    for(int i = log ; i >= 0 ; --i)
    {
        if(P[x][i] != -1 && P[x][i] != P[y][i])
            x = P[x][i] , y = P[y][i] ;
    }
    return parent[x] ;
}

//answer or DIST query
void DIST(int a , int b)
{
    int lca = LCA(a , b) ;
    cout<<dist[a] + dist[b] - 2 * dist[lca]<<"\n" ;
}

//answer for KTH query
void KTH(int x , int y , int k)
{
    int lca = LCA(x , y) ;
    if(lca == x)
    {
        int d = depth[y] - depth[x] + 1 ;
        swap(x , y) ;
        k = d - k + 1 ;
    }
    else if(lca != y)
    {
        if(k > depth[x] - depth[lca] + 1)
        {
            int d = depth[x] + depth[y] - 2 * depth[lca] + 1 ;
            k = d - k + 1 ;
            swap(x , y) ;
        }
    }
    --k ;
    for(int i = MAX_LOG-1 ; i >= 0 ; --i)
    {
        if(k & (1 << i))
            x = P[x][i] ;
    }
    cout<<x<<"\n" ;
}
int main()
{
    ios::sync_with_stdio(0) ;
    cin.tie(0) ;
    int t ;
    cin>>t ;
    while(t--)
    {
        cin>>n ;
        adj = vector< vector< pair<int , int> > >(n+5) ;
        for(int i = 1 ; i <= n ; ++i)
            adj[i].clear() ;
        for(int i = 0 ; i < n-1 ; ++i)
        {
            int x , y , z ;
            cin>>x>>y>>z ;
            adj[x].push_back({y , z}) ;
            adj[y].push_back({x , z}) ;
        }
        preprocess();
        while(true)
        {
            string s ;
            cin>>s ;
            if(s == "DONE")
                break;
            int x , y , k;
            cin>>x>>y ;
            if(s == "DIST")
                DIST(x , y) ;
            else if(s == "KTH")
            {
                cin>>k ;
                KTH(x , y , k) ;
            }
        }
    }
    return 0 ;
}
