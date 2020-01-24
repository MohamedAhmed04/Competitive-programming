/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : Baltic Olympiad in informatics 2008 day
   problem name : Grid (BOI 2008 - Grid)
   problem link : https://cses.fi/114/list/

   problem's solution : 
   	- binary search on the answer
   	- in check function, check all masks with number of bits equals r
   	  and check that 0th bit isn't setted because we can't divide the grid in 0th row.
   	- let solve(mask , mid) return true, if we can partition the grid into less than c columns
   	  and sum of the partitioned grids is <= mid .
    - if solve(mask , mid) is true for one or more masks have r bits and 0th bit isn't setted then
      check(mid) will return true else return false.

*/

#include <bits/stdc++.h>

using namespace std ;

const int MAX = 20 ;

int arr[MAX][MAX] , sum[MAX] ;
int n , m , r , c ;

bool solve(int mask , int mid)
{
	vector<int>v ;
	v.push_back(0) ;
	for(int i = 0 ; i < n ; ++i)
	{
		if((mask & (1 << i)))
			v.push_back(i) ;
	}
	v.push_back(n) ;
	int cnt = 0 ;
	for(int i = 0 ; i < n ; ++i)
		sum[i] = 0 ;
	int idx = 0 ;
	for(int i = 0 ; i < m ; ++i)
	{
		int Max = 0 ;
		idx = 0 ;
		for(int j = 0 ; j < n ; ++j)
		{
			if(j >= v[idx+1])
				idx++ ;
			sum[idx] += arr[j][i] ;
			Max = max(Max , sum[idx]) ;
		}
		if(Max > mid)
		{
			cnt++ ;
			for(int j = 0 ; j < n ; ++j)
				sum[j] = 0 ;
			idx = 0 ;
			for(int j = 0 ; j < n ; ++j)
			{
				if(j >= v[idx+1])
					idx++ ;
				sum[idx] += arr[j][i] ;
				if(sum[idx] > mid)
					return 0 ;
			}
		}
	}
	return (cnt <= c) ;
}

bool check(int mid)
{
	for(int i = 0 ; i < (1 << n) ; ++i)
	{
		if((i & 1))
			continue ;
		if(__builtin_popcount(i) != r)
			continue ;
		if(solve(i , mid))
			return 1 ;
	}
	return 0 ;
}

int main()
{
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	cin>>n>>m>>r>>c ;
	for(int i = 0 ; i < n ; ++i)
	{
		for(int j = 0 ; j < m ; ++j)
			cin>>arr[i][j] ;
	}
	int l = 0 , r = 1e9 ;
	int ans = 0 ;
	while(l <= r)
	{
		int mid = (l + r) >> 1 ;
		if(check(mid))
			ans = mid , r = mid-1 ;
		else
			l = mid+1 ;
	}
	return cout<<ans<<"\n" , 0 ;
}		