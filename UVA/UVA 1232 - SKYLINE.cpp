/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   problem name : UVA 1232 - SKYLINE

   solution of the problem :
   since we need to know everytime what current building overlap with other
   so we can use segment tree to see which range does current range overlap
   and count them..so we need MAX to know max of every range and MIN to know minimum
   of every range as if MIN > current height so we can exit this range else
   then continue until finding the ranges and add them..so we need also
   lazy propagation to update the ranges.
*/

#include <bits/stdc++.h>

using namespace std;

int cnt = 0 ;

const int MAX = 100010 ;
struct segment_tree
{
    int MIN = -1 , MAX = -1 ;
};
segment_tree tree[8 * MAX] , lazy[8 * MAX] ;

void shift(int node)
{
    if(lazy[node].MAX == -1)
        return ;
    tree[node].MIN = lazy[node].MIN ;
    tree[node].MAX = lazy[node].MAX ;
    lazy[node << 1].MIN = lazy[node].MIN ;
    lazy[node << 1].MAX = lazy[node].MAX ;
    lazy[node << 1 | 1].MIN = lazy[node].MIN ;
    lazy[node << 1 | 1].MAX = lazy[node].MAX ;
    lazy[node].MIN = lazy[node].MAX = -1 ;
}

void update(int node , int l , int r , int x , int y , int value)
{
    shift(node) ;
    if(x > r || y < l)
        return ;
    if(l == r)
    {
        if(tree[node].MAX <= value)
            tree[node].MIN = tree[node].MAX = value ;
        return ;
    }
    if(l >= x && r <= y)
    {
        if(tree[node].MAX <= value)
        {
            lazy[node].MAX = value ;
            lazy[node].MIN = value ;
            shift(node) ;
            return ;
        }
        if(tree[node].MIN > value)
            return ;
    }
    shift(node) ;
    int mid = (l + r) >> 1 ;
    update(node << 1 , l , mid , x , y , value) ;
    update(node << 1 | 1 , mid+1 , r , x , y , value) ;
    tree[node].MIN = min(tree[node << 1].MIN , tree[node << 1 | 1].MIN);
    tree[node].MAX = max(tree[node << 1].MAX , tree[node << 1 | 1].MAX) ;
}

int query(int node , int l , int r , int x , int y , int value)
{
    shift(node) ;
    if(x > r || y < l)
        return 0 ;
    if(l == r)
    {
        if(tree[node].MAX <= value)
            return 1 ;
        return 0 ;
    }
    if(l >= x && r <= y)
    {
        if(tree[node].MAX <= value)
            return (r-l+1) ;
        else if(tree[node].MIN > value)
            return 0 ;
    }
    int mid = (l + r) >> 1 ;
    int a = query(node << 1 , l , mid , x , y , value) ;
    int b = query(node << 1 | 1 , mid+1 , r , x , y , value) ;
    return (a + b) ;
}

int main()
{
    int t ;
    cin>>t ;
    while(t--)
    {
        for(int i = 0 ; i < MAX*8 ; ++i)
            tree[i].MAX = tree[i].MIN = lazy[i].MAX = lazy[i].MIN = -1 ;
        int n ;
        cin>>n ;
        long long ans = 0ll ;
        for(int i = 0 ; i < n ; ++i)
        {
            int x , y , z ;
            cin>>x>>y>>z ;
            ans = (ans + query(1 , 1 , 100000 , x+1 , y , z) * 1ll) * 1ll ;
            update(1 , 1 , 100000 , x+1 , y , z) ;
        }
        cout<<ans<<"\n";
    }
    return 0 ;
}
