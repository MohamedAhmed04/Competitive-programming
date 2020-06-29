/* Author: Mohamed Bakry (handle: MohamedAhmed04)

   contest name: Croatian Open Competition In Informatics (COCI) 2007 contest 6
   problem name: Cestarine (COCI 2007-Cestarine)
   problem link: https://dmoj.ca/problem/coci07c6p6

   Problem's solution:
    same idea: https://github.com/thecodingwizard/competitive-programming/blob/master/COCI/COCI%2007-Cestarine.cpp

*/

#include <bits/stdc++.h>

using namespace std ;

const int MAX = 1e5 + 10 ;

int arr[MAX] , arr2[MAX] ;
int n ;

long long dp[MAX] ;

long long calc(int l , int r)
{
	vector<int>v ;
	for(int i = l ; i <= r ; ++i)
		v.push_back(arr2[i]) ;
	long long sum = 1e15 ;
	do
	{
		long long sum2 = 0 ;
		for(int i = 0 ; i < v.size() ; ++i)
		{
			if(arr[l+i] == v[i])
			{
				sum2 = 1e15 ;
				break ;
			}
			sum2 += abs(arr[l+i] - v[i]) ;
		}
		sum = min(sum , sum2) ;
	}while(next_permutation(v.begin() , v.end())) ;
	return sum ;
}

long long solve(int idx)
{
	if(idx == n)
		return 0 ;
	long long &ret = dp[idx] ;
	if(ret != -1)
		return ret ;
	ret = 1e15 ;
	for(int i = idx ; i <= min(n-1 , idx+2) ; ++i)
		ret = min(ret , solve(i+1) + calc(idx , i)) ;
	return ret ;
}

int main()
{
	memset(dp , -1 , sizeof(dp)) ;
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	cin>>n ;
	for(int i = 0 ; i < n ; ++i)
		cin>>arr[i]>>arr2[i] ;
	sort(arr , arr + n) ;
	sort(arr2 , arr2 + n) ;
	return cout<<solve(0)<<"\n" , 0 ;
}		