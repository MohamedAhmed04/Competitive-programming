/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   problem name : Puncte
   problem link : https://www.infoarena.ro/problema/puncte

   problem solution :
     let's simplify it : (x1-x2)^2 + (y1 - y2)^2
                         (x1-x2)^2 + (y1 - 0)^2 (y2 is 0 since it's on x axis)
                         (x1-x2)^2 + y1^2
                         (x1-x2)*(x1-x2) + y1^2
     so now we have function that's ab + y , so we will make Li Chao tree to find minimum distance.

*/

#include <bits/stdc++.h>

using namespace std;

const long long inf = 2e18 ;

struct LiChao_min
{
    struct line
    {
        int64_t a, b;
        line() { a = 0; b = 0; }
        line(int64_t _a, int64_t _b) { a = _a; b = _b; }
        int64_t eval(int x) { return (x-a) * (x-a) + (int64_t)b*b; }
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

LiChao_min tree ;

int main()
{
    freopen("puncte.in" , "r" , stdin) ;
    freopen("puncte.out" , "w" , stdout) ;
    tree.init(1e9+5) ;
    int n , m ;
    scanf("%d %d" , &n , &m) ;
    for(int i = 0 ; i < n ; ++i)
    {
        long long a , b ;
        scanf("%lld %lld" , &a , &b) ;
        tree.add_line(a , b) ;
    }
    while(m--)
    {
        long long x ;
        scanf("%lld" , &x) ;
        printf("%lld\n" , tree.query(x));
    }
    return 0 ;
}
