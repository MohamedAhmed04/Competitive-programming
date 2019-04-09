/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   problem name : Vmin
   problem link : https://www.infoarena.ro/problema/vmin

   problem solution :
   classical convex hull problem (I solved it using Li Chao tree) , so in every time
   we try to find idx of minimum x in function and print it.

*/

#include <bits/stdc++.h>

using namespace std;

const long long inf = 2e18 ;

struct LiChao_min
{
    struct line
    {
        int64_t a, b , idx;
        line() { a = 0; b = 0; idx = 0;}
        line(int64_t _a, int64_t _b , int64_t _idx) { a = _a; b = _b; idx = _idx;}
        int64_t eval(int x) { return a * 1ll * x + (int64_t)b; }
    };

    struct node
    {
        node *l, *r; line f;

        node() { f = line(); l = nullptr; r = nullptr; }
        node(int64_t a, int64_t b , int64_t idx) { f = line(a, b , idx); l = nullptr; r = nullptr; }
        node(line v) { f = v; l = nullptr; r = nullptr; }
    };

    typedef node* pnode;

    pnode root; int sz;
    void init(int _sz) { sz = _sz + 1; root = nullptr; }

    void add_line(int64_t a, int64_t b , int64_t idx) { line v = line(a, b , idx); insert(v, -sz, sz, root); }
    pair<int64_t , int64_t> query(int x) { return query(x, -sz, sz, root); }

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

    pair<int64_t , int64_t> query(int x, int l, int r, pnode &nd)
    {
        if(!nd) return {inf , inf};
        if(l == r) return {nd->f.eval(x) , nd->f.idx};

        int mid = (l + r) >> 1;
        if(mid >= x)
        {
            pair<int64_t , int64_t> tmp ;
            tmp.first =  nd->f.eval(x) , tmp.second = nd->f.idx ;
            pair<int64_t , int64_t> tmp2 = query(x , l , mid , nd->l) ;
            if(tmp.first < tmp2.first)
                return {tmp.first , tmp.second} ;
            else
                return {tmp2.first , tmp2.second} ;
        }
        else
        {
            pair<int64_t , int64_t> tmp ;
            tmp.first = nd->f.eval(x) , tmp.second = nd->f.idx;
            pair<int64_t , int64_t> tmp2 = query(x , mid + 1 , r , nd->r) ;
            if(tmp.first < tmp2.first)
                return {tmp.first,  tmp.second} ;
            else
                return {tmp2.first , tmp2.second} ;
        }
    }
};


int64_t readlong () {
	bool minus = false;
	int64_t result = 0;
	char ch;
	ch = getchar();
	while (true) {
		if (ch == '-') break;
		if (ch >= '0' && ch <= '9') break;
		ch = getchar();
	}
	if (ch == '-') minus = true; else result = ch-'0';
	while (true) {
		ch = getchar();
		if (ch < '0' || ch > '9') break;
		result = result*10ll + (ch - '0') * 1ll;
		result = result * 1ll ;
	}
	if (minus)
		return -result;
	else
		return result;
}

LiChao_min tree ;

int main()
{
    freopen("vmin.in" , "r" , stdin) ;
    freopen("vmin.out" , "w" , stdout) ;
    tree.init(1e9 + 5) ;
    int n , q ;
    n = readlong() ;
    q = readlong() ;
    for(int i = 1 ; i <= n ; ++i)
    {
        int64_t a , b ;
        a = readlong() ;
        b = readlong() ;
        tree.add_line(a , b , i) ;
    }
    while(q--)
    {
        int64_t x ;
        x = readlong() ;
        pair<int64_t , int64_t>p = tree.query(x) ;
        printf("%lld " , p.second) ;
    }
    return 0 ;
}
