/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest name : Codeforces round 425(Codeforces832)
   problem name : D. Misha, Grisha and Underground
   problem link : https://codeforces.com/contest/832/problem/D

*/

#include <bits/stdc++.h>

using namespace std;

const int MAX = 1e5 + 10 ;
const int MAX_LOG = log2(MAX) + 2 ;
int P[MAX][MAX_LOG] , parent[MAX] , depth[MAX];
vector< vector<int> >adj(MAX) ;
int n , q ;

void dfs(int node , int par , int lvl)
{
    parent[node] = par ;
    depth[node] = lvl ;
    for(auto &child : adj[node])
    {
        if(child != par)
            dfs(child , node , lvl+1) ;
    }
}
//preprocess the LCA
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

int solve(int s , int f , int t)
{
    int a = LCA(s , f) , b = LCA(f , t) ;
    if((a == f) != (b == f))
        return 1 ;
    if(LCA(s , f) == s || LCA(t , f) == t)
    {
        int now = LCA(s , f) ;
        int now2 = LCA(t , f) ;
        int a = depth[now] , b = depth[now2];
        return 1 + (depth[f] - max(a , b)) ;
    }
    if(depth[LCA(s , t)] >= max(depth[LCA(s , f)] , depth[LCA(t , f)]))
       return depth[LCA(s , t)] + depth[f] - 2 * depth[LCA(LCA(s , t) , f)] + 1 ;
    int now = LCA(s , f) ;
    if(depth[LCA(f , t)] >= depth[now])
        now = LCA(f , t) ;
    return depth[now] + depth[f] - 2 * depth[LCA(now , f)] + 1 ;
}

int main()
{
    scanf("%d %d" , &n , &q) ;
    for(int i = 2 ; i <= n ; ++i)
    {
        int x ;
        scanf("%d" , &x) ;
        adj[x].push_back(i) ;
    }
    preprocess();
    vector<int>v(3) ;
    while(q--)
    {
        scanf("%d %d %d" , &v[0] , &v[1] , &v[2]) ;
        sort(v.begin() , v.end()) ;
        int ans = 0;
        do
        {
            ans = max(ans , solve(v[0] , v[1] , v[2]));
        }
        while(next_permutation(v.begin() , v.end()));
        printf("%d\n" , ans) ;
    }
    return 0 ;
}
