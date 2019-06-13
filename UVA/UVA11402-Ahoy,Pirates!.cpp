/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   problem name : UVA 11402 - Ahoy, Pirates!
   problem link :
    https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2397

   problem's solution :

   it's segment tree problem and we will do lazy propagation inside segment tree to handle updates.
   so let's make tree[node][0] which is number of zeros in range of node
   and           tree[node][1] which is number of ones in range of node.
   at first lazy[node] of all nodes will be -1 (denotes there's no need to update)
   and if lazy[node] = 0 then we will make tree[node][0] = (r-l+1) , and tree[node][1] = 0
   note : r - l + 1 = number of nodes in range.
   and if lazy[node] = 1 then we will make tree[node][0] = 0 , and tree[node][1] = (r - l + 1)
   and in invert query lazy[node] will be equal to 2 and we will swap tree[node][0] and tree[node][1]
   but the problem is there are some cases to handle in invert query :
   if lazy[node] = -1 then we will make lazy[node] = 2
   if lazy[node] = 0 then invert all nodes which will make lazy[node] = 1
   if lazy[node] = 1 then invert all nodes which will make lazy[node] = 0
   if lazy[node] = 2 then no need to update (since we will invert nodes 2 times) leading to no change so we will make lazy[node] = -1.

*/


#include <bits/stdc++.h>

using namespace std;

const int MAX = 1024005 ;

int arr[MAX] ;

int tree[MAX * 4][2] , lazy[MAX * 4] ;

void build(int node , int l , int r)
{
    if(l == r)
    {
        tree[node][arr[l]]++ ;
        return ;
    }
    int mid = (l + r) >> 1 ;
    build(node << 1 , l , mid) ;
    build(node << 1 | 1 , mid + 1 , r) ;
    tree[node][0] = tree[node << 1][0] + tree[node << 1 | 1][0] ;
    tree[node][1] = tree[node << 1][1] + tree[node << 1 | 1][1] ;
}

void prop(int node , int l , int r)
{
    if(lazy[node] == -1)
        return ;
    if(lazy[node] == 0)
    {
        tree[node][0] = (r-l+1) ;
        tree[node][1] = 0 ;
    }
    if(lazy[node] == 1)
    {
        tree[node][1] = (r-l+1) ;
        tree[node][0] = 0 ;
    }
    if(lazy[node] == 2)
    {
        int x = tree[node][0] ;
        int y = tree[node][1] ;
        tree[node][0] = y ;
        tree[node][1] = x ;
    }
    if(l != r)
    {
        if(lazy[node] == 2)
        {
            if(lazy[node << 1] == 2)
                lazy[node << 1] = -1 ;
            else if(lazy[node << 1] == -1)
                lazy[node << 1] = 2 ;
            else
                lazy[node << 1] = !lazy[node << 1] ;
            if(lazy[node << 1 | 1] == 2)
                lazy[node << 1 | 1] = -1 ;
            else if(lazy[node << 1 | 1] == -1)
                lazy[node << 1 | 1] = 2 ;
            else
                lazy[node << 1 | 1] = !lazy[node << 1 | 1] ;
        }
        else
        {
            lazy[node << 1] = lazy[node] ;
            lazy[node << 1 | 1] = lazy[node] ;
        }
    }
    lazy[node] = -1 ;
}

void update(int node , int l , int r , int from , int to , int val)
{
    prop(node , l , r) ;
    if(from > r || to < l)
        return ;
    if(l >= from && r <= to)
    {
        if(val == 2)
        {
            if(lazy[node] == 2)
                lazy[node] = -1 ;
            else if(lazy[node] == -1)
                lazy[node] = 2 ;
            else
                lazy[node] = !lazy[node] ;
        }
        else
            lazy[node] = val ;
        prop(node , l , r) ;
        return ;
    }
    int mid = (l + r) >> 1 ;
    update(node << 1 , l , mid , from , to , val) ;
    update(node << 1 | 1 , mid+1 , r , from , to , val) ;
    tree[node][0] = tree[node << 1][0] + tree[node << 1 | 1][0] ;
    tree[node][1] = tree[node << 1][1] + tree[node << 1 | 1][1] ;
    return ;
}

int query(int node , int l , int r , int from , int to)
{
    prop(node , l , r) ;
    if(from > r || to < l)
        return 0 ;
    if(l >= from && r <= to)
        return tree[node][1] ;
    int mid = (l + r) >> 1 ;
    int a = query(node << 1 , l , mid , from , to) ;
    int b = query(node << 1 | 1 , mid+1 , r , from , to) ;
    return (a + b) ;
}

int main()
{
    ios::sync_with_stdio(0) ;
    cin.tie(0) ;
    int t ;
    cin>>t ;
    int cnt = 0 ;
    while(t--)
    {
        cnt++ ;
        memset(tree , 0 , sizeof(tree)) ;
        memset(lazy , -1 , sizeof(lazy)) ;
        memset(arr , 0 , sizeof(arr)) ;
        int m ;
        cin>>m ;
        string s = "" , a;
        while(m--)
        {
            int x ;
            cin>>x ;
            cin>>a ;
            while(x--)
                s += a ;
        }
        int n = s.size() ;
        for(int i = 1 ; i <= n ; ++i)
            arr[i] = (s[i-1] - '0') ;
        build(1 , 1 , n) ;
        int q ;
        cin>>q ;
        cout<<"Case "<<cnt<<":\n";
        int cnt1 = 0 ;
        while(q--)
        {
            char c ;
            int x , y ;
            cin>>c>>x>>y ;
            ++x ;
            ++y ;
            if(c == 'F')
                update(1 , 1 , n , x , y , 1) ;
            else if(c == 'E')
                update(1 , 1 , n , x , y , 0) ;
            else if(c == 'I')
                update(1 , 1 , n , x , y , 2) ;
            else if(c == 'S')
                cout<<"Q"<<++cnt1<<": "<<query(1 , 1 , n , x , y)<<"\n";
        }
    }
    return 0 ;
}
