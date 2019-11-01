/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : IZhO 2014 day 1
   problem name : Divide and conquer (IzhO14-Divide)
   problem link : https://oj.uz/problem/view/IZhO14_divide

   problems's solution :
   - for every index we want to find best answer and answer will be max answer of all indexes.
   - best answer for every index is farthest index we can go and left energy will be >= 0
   - make prefix array where pref[i] = remaining left energy after going from 1 to pref[i]
     so if pref[i] is < 0 then we can't go from 1 to i
   - let prefv[i] is sum of gold in mines from mine 1 to mine i.
   - so answer of first index is largest j where pref[j] >= 0
   - if we started from index 2 then we need to have sum where sum
     is sum added after starting from 2 not 1, same thing for every index > 1
   - every time we visit idx we will add to sum (distance of current mine to previous mine - energy of previous mine)
   - now answer of every index we want to know farthest pref[j] such that pref[j] + sum >= 0 
   - to find largest j, it's classical problem where segment tree can handle it.
   - answer for every ndex will be prefv[j] - prefv[i-1] (which is amount of gold)
   - answer is max answer for every index.

*/

#include <bits/stdc++.h>

using namespace std ;

const int MAX = 1e5 + 10 ;

long long a[MAX] , e[MAX] , v[MAX] , pref[MAX] , prefv[MAX] ;
long long tree[4 * MAX] ;
long long sum = 0ll ;

void build(int node , int l , int r)
{
	if(l == r)
	{
		tree[node] = pref[l] ;
		return ;
	}
	int mid = (l + r) >> 1 ;
	build(node << 1 , l , mid) ;
	build(node << 1 | 1 , mid + 1 , r) ;
	tree[node] = max(tree[node << 1] , tree[node << 1 | 1]) ;
}

void update(int node , int l , int r , int idx)
{
	if(idx > r || idx < l)
		return ;
	if(l == r)
	{
		tree[node] = -1e12 ;
		return ;
	}
	int mid = (l + r) >> 1 ;
	update(node << 1 , l , mid , idx) ;
	update(node << 1 | 1 , mid + 1 , r , idx) ;
	tree[node] = max(tree[node << 1] , tree[node << 1 | 1]) ;
}

int query(int node , int l , int r)
{
	if(l == r)
		return l ;
	int mid = (l + r) >> 1 ;
	if(tree[node << 1 | 1]+sum >= 0)
		return query(node << 1 | 1 , mid+1 , r) ;
	else
		return query(node << 1 , l , mid) ;
}

int main()
{
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	int n ;
	cin>>n ;
	long long a[n] , e[n] , v[n] ;
	for(int i = 1 ; i <= n ; ++i)
		cin>>a[i]>>v[i]>>e[i] ;
	e[0] = 0 , v[0] = 0 , a[0] = a[1] ;
	for(int i = 1 ; i <= n ; ++i)
	{
		pref[i] = pref[i-1] - (a[i] - a[i-1]) + e[i] ;
		prefv[i] = prefv[i-1] + v[i] ;
	}
	build(1 , 1 , n) ;
	long long ans = 0ll ;
	for(int i = 1 ; i <= n ; ++i)
	{
		sum += a[i] - a[i-1] - e[i-1] ;
		int idx = query(1 , 1 , n) ;
		ans = max(ans , prefv[idx] - prefv[i-1]) ;
		update(1 , 1 , n , i) ;
	}
	return cout<<ans<<"\n" ,  0;
}