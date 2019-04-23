/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest name : SingaporeNOI 2019
   problem name : Pilot (SingaporeNOI2019-Pilot)
   problem link : https://dunjudge.me/analysis/problems/1824/

   problems solution :
   first let us sort array in increasing order and queries in increasing order (since queries are offline)
   so now for every query we need to loop on array from last element we didn't loop so if current number in query
   is >= arr[i] then we mark it as taken idx and we took idx-1 or idx+1 so we union it using a dsu.
*/

#include <bits/stdc++.h>

using namespace std;

const int MAX = 1e6+5 ;
int par[MAX] , sz[MAX] , taken[MAX] ;
long long anss[MAX];
long long ans = 0ll ;
int n , q;
void init()
{
    for(int i = 0 ; i <= n ; ++i)
        par[i] = i , sz[i] = 1 ;
}

int root(int node)
{
    if(par[node] == node)
        return node ;
    return (par[node] = root(par[node])) ;
}

void Union(int x , int y)
{
    int a = root(x) ;
    int b = root(y) ;
    if(a == b)
        return ;
    ans -= (sz[a] * 1ll * (sz[a]+1ll)) / 2ll ;
    ans -= (sz[b] * 1ll * (sz[b]+1ll)) / 2ll ;
    if(sz[a] >= sz[b])
    {
        par[b] = a ;
        sz[a] += sz[b] ;
        ans += (sz[a] * 1ll * (sz[a]+1ll)) / 2ll ;
    }
    else
    {
        par[a] = b ;
        sz[b] += sz[a] ;
        ans += (sz[b] * 1ll * (sz[b] + 1ll)) / 2ll ;
    }
    return ;
}

int main()
{
    scanf("%d %d" , &n , &q) ;
    vector< pair<int , int> >vp , vp2;
    for(int i = 0 ; i < n ; ++i)
    {
        int x ;
        scanf("%d" , &x) ;
        vp.push_back({x , i}) ;
    }
    sort(vp.begin() , vp.end()) ;
    for(int i = 0 ; i < q ; ++i)
    {
        int x ;
        scanf("%d" , &x) ;
        vp2.push_back({x , i}) ;
    }
    sort(vp2.begin() , vp2.end()) ;
    init();
    int last = 0 ;
    for(int i = 0 ; i < q ; ++i)
    {
        int here = vp2[i].first , idx2 = vp2[i].second ;
        for(int j = last ; j < n ; ++j)
        {
            int now = vp[j].first , idx = vp[j].second ;
            if(here < now)
                break ;
            last = j+1 ;
            ans++ ;
            taken[idx] = 1 ;
            if(idx != 0 && taken[idx-1] == 1)
                Union(idx , idx-1) ;
            if(idx != n-1 && taken[idx+1] == 1)
                Union(idx , idx+1) ;
        }
        anss[idx2] = ans ;
    }
    for(int i = 0 ; i < q ; ++i)
        printf("%lld\n" , anss[i]);
    return 0 ;
}
