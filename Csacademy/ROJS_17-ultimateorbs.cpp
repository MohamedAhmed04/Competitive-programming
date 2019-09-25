/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)
   
   contest name : Junior-challenge-2017-day-2
   problem name : Ultimate Orbs
   problem link : https://csacademy.com/contest/junior-challenge-2017-day-2/task/ultimateo

   problem's solution :
    main observation of the problem is :
    let i be index of current number and let a be largest index where
    a < i and arr[a] > arr[i] and let b be smallest index where b > i and arr[b] > arr[i].
    and let x be sum of numbers from index a+1 to index b-1 in array.
    so if arr[a] is orb can remain until the end and x + d >= arr[a] 
    then i can remain until end,
    or if arr[b] is orb can remain until the end and x + d >= arr[b]
    then i can remain until end,.

    using this observation we will compute l[i] and r[i] where all numbers from l[i] to r[i]
    are <= arr[i] and i must be between l[i] and r[i].
    to compute it I used monotonic stack to preprocess the array in O(N).
    then sort the numbers in decreasing order and apply the observation above.

 */

#include <bits/stdc++.h>

using namespace std ;

const int MAX = 1e6 + 10 ;

long long arr[MAX] , l[MAX] , r[MAX] , sum[MAX] , ans[MAX];

int main()
{
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	int n ;
	long long d ;
	cin>>n>>d ;
	for(int i = 1 ; i <= n ; ++i)
		cin>>arr[i] ;
	arr[0] = 2e18 , arr[n+1] = 2e18 ;
	stack<int>s ;
	for(int i = 0 ; i <= n ; ++i)
	{
		while(s.size() > 0 && arr[i] >= arr[s.top()])
			s.pop() ;
		if(s.size())
			l[i] = s.top() + 1;
		s.push(i) ;
	}
	while(s.size() > 0)
		s.pop() ;
	for(int i = n+1 ; i >= 1 ; --i)
	{
		while(s.size() > 0 && arr[i] >= arr[s.top()])
			s.pop() ;
		if(s.size())
			r[i] = s.top() - 1;
		s.push(i) ;
	}
	sum[0] = 0 , sum[n+1] = 0;
	for(int i = 1 ; i <= n ; ++i)
		sum[i] = sum[i-1] + arr[i] ;
	vector< pair<long long , int> >vp ;
	for(int i = 1 ; i <= n ; ++i)
		vp.push_back({arr[i] , i}) ;
	sort(vp.rbegin() , vp.rend()) ;
	for(int i = 0 ; i < vp.size() ; ++i)
	{
		int idx = vp[i].second ;
		long long x = sum[r[idx]] - sum[l[idx]-1] ;
		if(l[idx] == 1 && r[idx] == n)
			ans[idx] = 1 ;
		else
		{
			if(l[idx] > 1 && x+d >= arr[l[idx]-1] && ans[l[idx]-1] == 1)
				ans[idx] = 1 ;
			else if(r[idx] <= n-1 && x + d >= arr[r[idx]+1] && ans[r[idx]+1] == 1)
				ans[idx] = 1 ;
		}
	}
	for(int i = 1 ; i <= n ; ++i)
	{
		if(ans[i] == 1)
			cout<<i<<" ";
	}
	return 0 ;
}