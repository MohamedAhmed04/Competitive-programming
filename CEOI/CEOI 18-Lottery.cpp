/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : Central Europian olympiad in informatics 2018 day 1 (CEOI 2018)
   problem name : Lottery (CEOI 18-Lottery)
   problem link : https://csacademy.com/contest/ceoi-2018-day-1/task/lottery/

   Problem's Solution : 
   - first store the queries to answer them offline and sort them.
   - let ans[i][j] is number of intervals that's Q[j] similar to interval i
   - to find distance between two intervals and update the answer O(N^2logQ)
     first let's iterate on every absolute distance between 1 and n and let's 
     denote it as j.
     at each iteration we want to find the distance between every interval
     i and i+j.
   - so we can make prefix sum where pref[i] = pref[i-1] + 1 (if arr[i] != arr[i+j])
   - now iterate on every i (starting of intervals), so
     the distance between interval i and i+j = pref[i+l-1] - pref[i-1].
     after finding the distance we will update the answer so
     ans[i][lower_bound(Q , Q+q , dist)-Q] will be increased by 1 and
     ans[i+j][lower_bound(Q , Q+q , dist)-Q]++ will be increased by 1.
   - at the end, we will add for every ans[i][j] the ans[i][j-1] + ans[i][j-2] + ..... + ans[i][0].
   - after that print the answer of queries.

*/

#include <bits/stdc++.h>

using namespace std ;

const int MAX = 1e4 + 10 ;

int arr[MAX] , ans[MAX][110] , Cnt[MAX] , pref[MAX] ;
int Q[MAX] , Q2[MAX] ;
int n , l , q ;

int main()
{
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	cin>>n>>l ;
	for(int i = 0 ; i < n ; ++i)
		cin>>arr[i] ;
	cin>>q ;
	for(int i = 0 ; i < q ; ++i)
	{
		cin>>Q[i] ;
		Q2[i] = Q[i] ;
	}
	sort(Q , Q + q) ;
	for(int j = 1 ; j < n ; ++j) // distance
	{
		pref[0] = 0 ;
		for(int i = 0 ; i+j < n ; ++i)
		{
			if(i)
				pref[i] = pref[i-1] ;
			if(arr[i] != arr[i+j])
				pref[i]++ ;
		}
		for(int i = 0 ; i+j+l-1 < n ; ++i)
		{
			int x = pref[i+l-1] ;
			if(i)
				x -= pref[i-1] ;
			int idx = lower_bound(Q , Q + q , x) - Q ;
			ans[i][idx]++ ;
			ans[i+j][idx]++ ;
		}
	}
	for(int i = 0 ; i < n ; ++i)
	{
		for(int j = 1 ; j < q ; ++j)
			ans[i][j] += ans[i][j-1] ;
	}
	for(int i = 0 ; i < q ; ++i)
	{
		for(int j = 0 ; j <= n-l ; ++j)
		{
			int idx = lower_bound(Q , Q + q , Q2[i]) - Q ;
			cout<<ans[j][idx]<<" " ;
		}
		cout<<"\n" ;
	}
	return 0 ;
}		