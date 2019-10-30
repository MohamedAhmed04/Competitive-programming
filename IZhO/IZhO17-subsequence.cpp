/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : IZhO 2017 day 1
   problem name : subsequence (IZhO 2017-Subsequence)
   problem link : https://oj.uz/problem/view/IZhO17_subsequence

   problem solution : 
    https://github.com/quangloc99/CompetitiveProgramming/blob/master/olympiad/IZhO/2017/subsequence.cpp
   I preprocessed number of ones in every number from 0 to 2^20 - 1, so it passes faster.

*/

#include <bits/stdc++.h>
 
using namespace std ;
 
const int MAX = 1e5 + 1 ;
const int Middle = 1 << 10 ;
int arr[MAX] , arr2[MAX] , f[Middle][Middle][21] , prv[MAX] , dp[MAX] , ones[(1 << 20)];
void print(int now)
{
	if(now == 0)
		return ;
	print(prv[now]) ;
	cout<<now<<" " ;
}

void preprocess(int now , int cnt , int bit)
{
	if(bit == 20)
	{
		ones[now] = cnt ;
		return ;
	}
	preprocess(now , cnt , bit+1) ;
	preprocess(now + (1 << bit) , cnt+1 , bit+1) ;
	return ;
}

int main()
{
	preprocess(0 , 0 , 0) ;
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	int n ;
	cin>>n ;
	for(int i = 1 ; i <= n ; ++i)
		cin>>arr[i] ;
	for(int i = 1 ; i <= n ; ++i)
		cin>>arr2[i] ;
	int Max = 0 , en , vall , valr , x;
	for(int i = 1 ; i <= n ; ++i)
	{
		dp[i] = 1 ;
		vall = arr[i] & (Middle - 1);
        valr = arr[i] >> 10;
		for(int j = 0 ; j < Middle ; ++j)
		{
			x = arr2[i] - ones[vall & j] ;
			if(x < 0)
				continue ;
			if(dp[f[j][valr][x]] + 1 > dp[i])
			{
				dp[i] = dp[f[j][valr][x]] + 1 ;
				prv[i] = f[j][valr][x] ;
			}
		}
		for(int j = 0 ; j < Middle ; ++j)
		{
			x = ones[valr & j] ;
			if(dp[i] > dp[f[vall][j][x]])
				f[vall][j][x] = i ;
		}
		if(dp[i] > Max)
			Max = dp[i] , en = i ;
	}
	cout<<Max<<"\n" ;
	print(en) ;
	return 0 ;
}