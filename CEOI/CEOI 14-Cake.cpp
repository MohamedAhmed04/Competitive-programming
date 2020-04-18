/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : Central European Olympiad In Informatics (CEOI) 2014 day 2
   problem name : Cake (CEOI 2014-Cake)
   problem link : https://oj.uz/problem/view/CEOI14_cake

   Problem's solution:
    same idea: https://github.com/stefdasca/CompetitiveProgramming/blob/master/CEOI/CEOI%2014-cake.cpp

*/

#include <bits/stdc++.h>
 
using namespace std ;
 
const int MAX = 3e5 + 10 ;
 
int arr[MAX] ;
int n , a ;
 
int tree[4 * MAX] ;
 
void build(int node , int l , int r)
{
	if(l == r)
	{
		tree[node] = arr[l] ;
		return ;
	}
	int mid = (l + r) >> 1 ;
	build(node << 1 , l , mid) ;
	build(node << 1 | 1 , mid+1 , r) ;
	tree[node] = max(tree[node << 1] , tree[node << 1 | 1]) ;
}
 
void update(int node , int l , int r , int idx , int val)
{
	if(idx > r || idx < l)
		return ;
	if(l == r)
	{
		tree[node] = val ;
		return ;
	}
	int mid = (l + r) >> 1 ;
	update(node << 1 , l , mid , idx , val) ;
	update(node << 1 | 1 , mid+1 , r , idx , val) ;
	tree[node] = max(tree[node << 1] , tree[node << 1 | 1]) ;
}
 
int query(int node , int l , int r , int from , int to)
{
	if(from > r || to < l)
		return 0ll ;
	if(l >= from && r <= to)
		return tree[node] ;
	int mid = (l + r) >> 1 ;
	int a = query(node << 1 , l , mid , from , to) ;
	int b = query(node << 1 | 1, mid+1 , r , from , to) ;
	return max(a , b) ;
}
 
int FirstLeft(int node , int l , int r , int from , int to , int val)
{
	if(from > r || to < l)
		return -1 ;
	if(val > tree[node])
		return -1 ;
	if(l == r)
		return l ;
	int mid = (l + r) >> 1 ;
	int x = FirstLeft(node << 1 , l , mid , from , to , val) ;
	if(x == -1)
		x = FirstLeft(node << 1 | 1 , mid+1 , r , from , to , val) ;
	return x ;
}

int FirstRight(int node , int l , int r , int from , int to , int val)
{
	if(from > r || to < l)
		return -1 ;
	if(val > tree[node])
		return -1 ;
	if(l == r)
		return l ;
	int mid = (l + r) >> 1 ;
	int x = FirstRight(node << 1 | 1 , mid+1 , r , from , to , val) ;
	if(x == -1)
		x = FirstRight(node << 1 , l , mid , from , to , val) ;
	return x ;
}

int main()
{
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	cin>>n>>a ;
	vector< pair<int , int> >vp ;
	for(int i = 1 ; i <= n ; ++i)
	{
		cin>>arr[i] ;
		vp.emplace_back(arr[i] , i) ;
	}
	sort(vp.begin() , vp.end()) ;
	for(int i = 0 ; i < n ; ++i)
		arr[vp[i].second] = i+1ll ;
	build(1 , 1 , n) ;
	set< pair<int , int> >s ;
	for(int i = 1 ; i <= n ; ++i)
		s.insert({arr[i] , i}) ;
	while(s.size() > 10)
		s.erase(s.begin()) ;
	int q ;
	cin>>q ;
	while(q--)
	{
		char c ;
		cin>>c ;
		if(c == 'E')
		{
			int x , y ;
			cin>>x>>y ;
			s.insert({arr[x] , x}) ;
			if(s.size() > 10)
			{
				s.erase({arr[x] , x}) ;
				s.erase(s.begin()) ;
			}
			else
				s.erase({arr[x] , x}) ;
			pair<int , int>p = *s.rbegin() ;
			int val = p.first ;
			for(int i = min(n , 10) ; i >= 1 ; --i)
			{
				val++ ;
				if(i == y)
				{
					arr[x] = val ;
					s.insert({arr[x] , x}) ;
					update(1 , 1 , n , x , arr[x]) ;
					continue ;
				}
				p = *s.begin() ;
				s.erase(p) ;
				arr[p.second] = val ;
				update(1 , 1 , n , p.second , arr[p.second]) ;
				s.insert({arr[p.second] , p.second}) ;
			}
		}
		else
		{
			int x ;
			cin>>x ;
			if(x == a)
			{
				cout<<0<<"\n" ;
				continue ;
			}
			int Max ;
			int l , r , ans = a ;
			if(x < a)
			{
				Max = query(1 , 1 , n , x , a-1) , l = a+1 , r = n ;
				ans = FirstLeft(1 , 1 , n , l , r , Max) ;
				if(ans == -1)
					ans = n ;
				else
					ans-- ;
			}
			else
			{
				Max = query(1 , 1 , n , a+1 , x) , l = 1 , r = a-1 ;
				ans = FirstRight(1 , 1 , n , l , r , Max) ;
				if(ans == -1)
					ans = 1 ;
				else
					ans++ ;
			}
			cout<<abs(x-a)+abs(ans-a)<<"\n" ;
		}
	}
	return 0 ;
}	