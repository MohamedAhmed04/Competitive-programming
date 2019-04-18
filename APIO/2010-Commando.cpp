/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest name : APIO 2010
   problem name : Commando (APIO 2010-Commando)
   problem link : https://dmoj.ca/problem/apio10p1

   problem solution :
   explanation of solution : https://web.archive.org/web/20180327234823/http://wcipeg.com/wiki/Convex_hull_trick
   but I coded it using LiChao Tree.

   note : low memory limit in problem.
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll ;

const ll inf = (ll)1e16;

const int MAX = 1e6+5 ;

int arr[MAX] , sum[MAX];
long long dp[MAX] ;

int a , b , c ;
int n;

struct LiChao_max
{
	struct line
	{
		ll a, b;
		line() { a = 0; b = 0; }
		line(ll _a, ll _b) { a = _a; b = _b; }
		ll eval(int x) { return a * 1ll * x + (ll)b; }
	};

	struct node
	{
		node *l, *r; line f;

		node() { f = line(); l = nullptr; r = nullptr; }
		node(ll a, ll b) { f = line(a, b); l = nullptr; r = nullptr; }
		node(line v) { f = v; l = nullptr; r = nullptr; }
	};

	typedef node* pnode;

	pnode root; int sz;
	void init(int _sz) { sz = _sz + 1; root = nullptr; }

	void add_line(ll a, ll b) { line v = line(a, b); insert(v, -sz, sz, root); }
	ll query(int x) { return query(x, -sz, sz, root); }

	void insert(line &v, int l, int r, pnode &nd)
	{
		if(!nd) { nd = new node(v); return; }

		ll trl = nd->f.eval(l), trr = nd->f.eval(r);
		ll vl = v.eval(l), vr = v.eval(r);

		if(trl >= vl && trr >= vr) return;
		if(trl < vl && trr < vr) { nd->f = v; return; }

		int mid = (l + r) >> 1;
		if(trl < vl) swap(nd->f, v);
		if(nd->f.eval(mid) > v.eval(mid)) insert(v, mid + 1, r, nd->r);
		else swap(nd->f, v), insert(v, l, mid, nd->l);
	}

	ll query(int x, int l, int r, pnode &nd)
	{
		if(!nd) return -inf;
		if(l == r) return nd->f.eval(x);

		int mid = (l + r) >> 1;
		if(mid >= x) return max(nd->f.eval(x), query(x, l, mid, nd->l));
		return max(nd->f.eval(x), query(x, mid + 1, r, nd->r));
	}
};

int main()
{
    scanf("%d" , &n) ;
    scanf("%d %d %d" , &a , &b , &c) ;
    sum[0] = 0 ;
    for(int i = 1 ; i <= n ; ++i)
    {
        scanf("%d" , &arr[i]) ;
        sum[i] = sum[i-1] + arr[i] ;
    }
    LiChao_max tree ;
    tree.init(1e8+5) ;
    tree.add_line(0 , 0) ;
    for(int i = 1 ; i <= n ; ++i)
    {
        dp[i] = (a*1ll)*(sum[i]*1ll)*(sum[i]*1ll)+(b*1ll)*(sum[i]*1ll)+(c*1ll) ;
        dp[i] += tree.query(sum[i]) ;
        tree.add_line((-2ll*1ll)*(a*1ll)*(sum[i]*1ll) , (dp[i]*1ll) + a * 1ll*sum[i]*1ll * (sum[i]*1ll) - (b*1ll) * (sum[i]*1ll)) ;
    }
    return printf("%lld" , dp[n]) , 0 ;
}
