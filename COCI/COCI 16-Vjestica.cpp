/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : COCI 2016 contest 1
   problem name : Vjestica (COCI 2016-Vjestica)
   problem link : https://oj.uz/problem/view/COCI16_vjestica

   Problem's solution:
 	dp[mask] is minimum number of nodes in tree contains strings with index set by 1 in mask.
 	then dp[mask] equals min(dp[a] + dp[b] - common part) where a is submask of mask and b is submask of mask
 	and a xor b = mask.
 	we can use submask enumeration to iterate on submasks of the current mask.
 	time complexity: O(3^n).

*/

#include <bits/stdc++.h>

using namespace std ;

const int MAX = 17 ;

string arr[MAX] ;
int freq[MAX][27] , dp[(1 << MAX)] ;

int  n ;

int commonpref(int mask)
{
	int sum = 0 ;
	for(int i = 0 ; i < 26 ; ++i)
	{
		int cnt = -1 ;
		for(int j = 0 ; j < n ; ++j)
		{
			if(!(mask & (1 << j))) 
				continue ;
			if(cnt == -1)
				cnt = freq[j][i] ;
			else
				cnt = min(cnt , freq[j][i]) ;
		}
		sum += max(cnt , 0) ;
	}
	return sum ;
}

int main()
{
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	cin>>n ;
	for(int i = 0 ; i < n ; ++i)
	{
		cin>>arr[i] ;
		for(auto &c : arr[i])
			freq[i][c-'a']++ ;
	}
	for(int mask = 1 ; mask < (1 << n) ; ++mask)
	{
		dp[mask] = 1e9 ;
		int x = commonpref(mask) ;
		int Max = -1 ;
		for(int i = 0 ; i < n ; ++i)
		{
			if((mask & (1 << i)))
				Max = max(Max , (int)arr[i].size()) ;
		}
		if(Max == x)
		{
			dp[mask] = x ;
			continue ;
		}
		for(int sub = mask ; sub ; sub = (sub-1) & mask)
			dp[mask] = min(dp[mask] , dp[sub] + dp[mask ^ sub] - x) ;
	}
	return cout<<dp[(1 << n) - 1]+1<<"\n" , 0 ;
}		