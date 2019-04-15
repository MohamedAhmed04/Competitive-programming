/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest name : Usaco 2008 march
   problem name : ACQUIRE (USACO 2008 march ACQUIRE)
   problem link : https://www.spoj.com/problems/ACQUIRE/

   problem solution :
    https://web.archive.org/web/20180327234823/http://wcipeg.com/wiki/Convex_hull_trick
   the difference between my code and here that I use LiChao tree and I sort increasing of length and decreasing of width.

*/


#include <bits/stdc++.h>

using namespace std;

const int MAX = 50005 ;
typedef long long ll ;
int mark[MAX] ;
ll dp[MAX] ;

bool cmp(pair<ll , ll>&a , pair<ll , ll>&b)
{
    if(a.first != b.first)
        return a.first < b.first ;
    return a.second > b.second ;
}

const long long inf = 1e18 ;

struct LiChao_min
{
    struct line
    {
        int64_t a, b;
        line() { a = 0; b = 0; }
        line(int64_t _a, int64_t _b) { a = _a; b = _b; }
        int64_t eval(int x) { return a * 1ll * x + (int64_t)b; }
    };

    struct node
    {
        node *l, *r; line f;

        node() { f = line(); l = nullptr; r = nullptr; }
        node(int64_t a, int64_t b) { f = line(a, b); l = nullptr; r = nullptr; }
        node(line v) { f = v; l = nullptr; r = nullptr; }
    };

    typedef node* pnode;

    pnode root; int sz;
    void init(int _sz) { sz = _sz + 1; root = nullptr; }

    void add_line(int64_t a, int64_t b) { line v = line(a, b); insert(v, -sz, sz, root); }
    int64_t query(int x) { return query(x, -sz, sz, root); }

    void insert(line &v, int l, int r, pnode &nd)
    {
        if(!nd) { nd = new node(v); return; }

        int64_t trl = nd->f.eval(l), trr = nd->f.eval(r);
        int64_t vl = v.eval(l), vr = v.eval(r);

        if(trl <= vl && trr <= vr) return;
        if(trl > vl && trr > vr) { nd->f = v; return; }

        int mid = (l + r) >> 1;
        if(trl > vl) swap(nd->f, v);
        if(nd->f.eval(mid) < v.eval(mid)) insert(v, mid + 1, r, nd->r);
        else swap(nd->f, v), insert(v, l, mid, nd->l);
    }

    int64_t query(int x, int l, int r, pnode &nd)
    {
        if(!nd) return inf;
        if(l == r) return nd->f.eval(x);

        int mid = (l + r) >> 1;
        if(mid >= x) return min(nd->f.eval(x), query(x, l, mid, nd->l));
        return min(nd->f.eval(x), query(x, mid + 1, r, nd->r));
    }
};


int main()
{
     int n ;
     scanf("%d" , &n) ;
     vector< pair<ll , ll> >vp , arr;
     for(int i = 0 ; i < n ; ++i)
     {
         ll x , y ;
         scanf("%lld %lld" , &x , &y) ;
         vp.push_back({x , y}) ;
     }
     sort(vp.rbegin() , vp.rend()) ;
     long long MAX = 0ll ;
     for(int i = 0 ; i < n ; ++i)
     {
         if(vp[i].second <= MAX)
            mark[i] = 1 ;
         MAX = max(MAX , vp[i].second) ;
     }
     for(int i = 0 ; i < n ; ++i)
     {
         if(mark[i] == 1)
            continue ;
         arr.push_back({vp[i].first , vp[i].second}) ;
     }
     sort(arr.begin() , arr.end() , cmp) ;
     n = arr.size() ;
     LiChao_min tree ;
     tree.init(1e9+5) ;
     tree.add_line(arr[0].second , 0ll) ;
     for(int i = 0 ; i < n ; ++i)
     {
         dp[i] = tree.query(arr[i].first) ;
         if(i != n-1)
            tree.add_line(arr[i+1].second , dp[i]) ;
     }
     return cout<<dp[n-1]<<"\n" , 0 ;
}
