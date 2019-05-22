/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : USACO 2017 February Platinum
   problem name : Why Did The Cow Cross The Road II(USACO17-Feb-plat-nocross)
   problem link : http://usaco.org/index.php?page=viewproblem2&cpid=721

   problem solution :
    http://usaco.org/current/data/sol_nocross_platinum_feb17.html

*/

#include <bits/stdc++.h>

using namespace std;

const int MAX = 1e5 + 5 ;
int arr[MAX] , idx[MAX] , tree[MAX * 4];
int n ;

void update(int node , int l , int r , int idx , int val)
{
    if(idx > r || idx < l)
        return ;
    if(l == r)
    {
        tree[node] = max(tree[node] , val) ;
        return ;
    }
    int mid = (l + r) >> 1 ;
    update(node << 1 , l , mid , idx , val) ;
    update(node << 1 | 1 , mid + 1 , r , idx , val) ;
    tree[node] = max(tree[node << 1] , tree[node << 1 | 1]) ;
}

int query(int node , int l , int r , int from , int to)
{
    if(to < l || from > r)
        return 0 ;
    if(l >= from && r <= to)
        return tree[node] ;
    int mid = (l + r) >> 1 ;
    int a = query(node << 1 , l , mid , from , to) ;
    int b = query(node << 1 | 1 , mid + 1 , r , from , to) ;
    return (max(a , b)) ;
}

int main()
{
    freopen("nocross.in" , "r" , stdin) ;
    freopen("nocross.out" , "w" , stdout) ;
    scanf("%d" , &n) ;
    for(int i = 1 ; i <= n ; ++i)
        scanf("%d" , &arr[i]) ;
    for(int i = 1 ; i <= n ; ++i)
    {
        int x ;
        scanf("%d" , &x) ;
        idx[x] = i ;
    }
    for(int i = 1 ; i <= n ; ++i)
    {
        vector<int>v ;
        for(int j = max(1 , arr[i] - 4) ; j <= min(n , arr[i] + 4) ; ++j)
            v.push_back(idx[j]) ;
        sort(v.rbegin() , v.rend());
        for(int j = 0 ; j < v.size() ; ++j)
        {
            int x = query(1 , 1 , n , 1 , v[j]-1) + 1;
            update(1 , 1 , n , v[j] , x) ;
        }
    }
    return cout<<query(1 , 1 , n , 1 , n)<<"\n" , 0 ;
}
