/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : Balkan Olympiad In Informatics 2011 day 2
   problem name : Trapezoids (BalkanOI 11-Trapezoids)
   problem link : https://oj.uz/problem/view/balkan11_trapezoid

   Problem's solution:
    we want to find longest subsequence of trapezoids that this condition fulfills:
    if the upper segment of first trapezoid is from a1 to b1 and for the second trapezoid is from a2 to b2
    and if the upper segment of first trapezoid is from l1 to r1 and for the second trapezoid is from l2 to b2
    so we need: b1 < a2 and r1 < l2
    so we will sort the segments according to the upper segment and find the LIS of the second segment.
    similarly we will find the number of ways.

*/

#include <bits/stdc++.h>

using namespace std ;

const int mod = 30013 ;
const int MAX = 1e5 + 10 ;

struct segment_tree
{
	vector<int>v ;
	vector<long long> tree ;
	int sz ;
	bool flag ;
	void init(vector<int>v2 , bool t)
	{
		if(t == 0)
			flag = 0 ;
		else
			flag = 1 ;
		sz = (int)v2.size() ;
		v = v2 ;
		sort(v.begin() , v.end()) ;
		tree.resize(sz*4+10) ;
		for(int i = 0 ; i <= sz*4 ; ++i)
			tree[i] = 0 ;
	}
	int getidx1(long long idx)
	{
		int idx2 = lower_bound(v.begin() , v.end() , idx) - v.begin() ;
		return idx2 ;
	}
	int getidx2(long long idx)
	{
		int idx2 = upper_bound(v.begin() , v.end() , idx) - v.begin() ;
		idx2-- ;
		return idx2 ;
	}
	void update(int node , int l , int r , int idx , long long v)
	{
		if(idx > r || idx < l || idx < 0)
			return ;
		if(l == r)
		{
			if(flag == 0)
				tree[node] = max(tree[node] , v) ;
			else
				tree[node] = (tree[node] + v) % mod ;
			return ;
		}
		int mid = (l + r) >> 1 ;
		update(node << 1 , l , mid , idx , v) ;
		update(node << 1 | 1 , mid+1 , r , idx , v) ;
		if(flag == 0)
			tree[node] = max(tree[node << 1] , tree[node << 1 | 1]) ;
		else
			tree[node] = (tree[node << 1] + tree[node << 1 | 1]) % mod ;
	}
 
	long long query(int node , int l , int r , int from , int to)
	{
		if(from > r || to < l || from > to)
			return 0 ;
		if(l >= from && r <= to)
			return tree[node] ;
		int mid = (l + r) >> 1 ;
		long long a = query(node << 1 , l , mid , from , to) ;
		long long b = query(node << 1 | 1 , mid+1 , r , from , to) ;
		if(flag == 0)
			return max(a , b) ;
		else
			return (a + b) % mod ;
	}
 
	void update(long long idx , long long val)
	{
		idx = getidx1(idx) ;
		update(1 , 0 , sz , idx , val) ;
	}
 
	long long query(long long idx)
	{
		idx = getidx2(idx) ;
		return query(1 , 0 , sz , 0 , idx) ;
	}
};


int arr[MAX] ;
int n ;

vector< array<int , 4> >v ;
vector<int>v2 ;
vector<int>lis[MAX] ;
int LIS[MAX] , ways[MAX] ;

int main()
{
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	cin>>n ;
	for(int i = 0 ; i < n ; ++i)
	{
		int l1 , r1 , l2 , r2 ;
		cin>>l1>>r1>>l2>>r2 ;
		v.push_back({l1 , r1 , l2 , r2}) ;
		v2.push_back(r2) ;
	}
	sort(v.begin() , v.end()) ;
	segment_tree tree ;
	tree.init(v2 , 0) ;
	set< pair<int , int> >s ;
	int ans = 0 ;
	for(int i = 0 ; i < n ; ++i)
	{
		while(s.size() > 0)
		{
			pair<int , int>p = *s.begin() ;
			if(p.first >= v[i][0])
				break ;
			tree.update(v[p.second][3] , LIS[p.second]) ;
			s.erase(p) ;
		}
		LIS[i] = tree.query(v[i][2]-1) + 1 ;
		ans = max(ans , LIS[i]) ;
		s.insert({v[i][1] , i}) ;
		lis[LIS[i]].push_back(v[i][3]) ;
	}
	vector<segment_tree>treecnt(n+1) ;
	treecnt[0].init({-1} , 1) ;
	treecnt[0].update(-1 , 1) ;
	for(int i = 1 ; i <= n ; ++i)
	{
		if(lis[i].size())
			treecnt[i].init(lis[i] , 1) ;
	}
	int cnt = 0 ;
	s.clear() ;
	for(int i = 0 ; i < n ; ++i)
	{
		while(s.size() > 0)
		{
			pair<int , int>p = *s.begin() ;
			if(p.first >= v[i][0])
				break ;
			treecnt[LIS[p.second]].update(v[p.second][3] , ways[p.second]) ;
			s.erase(p) ;
		}
		ways[i] = treecnt[LIS[i]-1].query(v[i][2]-1) ;
		if(LIS[i] == ans)
			cnt = (cnt + ways[i]) % mod ;
		s.insert({v[i][1] , i}) ;
	}
	return cout<<ans<<" "<<cnt<<"\n" , 0 ;
}		