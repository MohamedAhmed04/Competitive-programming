/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : IOI 2014 practice session
   problem name : Skwishinese (IOI2014Practice - Skwishinese)
   problem link : https://www.hackerrank.com/contests/ioi-2014-practice-contest-1/challenges/skwishinese-ioi14

   problem's solution : 
    dp, where state is dp[idx][l][r] where
    idx : current idx in s, l : character that we need to match in s where we matched [0 , l-1]
    r : character we need to match in s where we matched [r+1 , n-1]
    so we have two choices, either leave current character (s[idx]), or pick it
    when we pick a character, we see if it matches s[l] and s[r].
    if(l > r), then s is subsequence of UU(R).

*/ 

#include <bits/stdc++.h>

using namespace std ;

const int MAX = 400 + 10 ;

int dp[MAX][MAX][MAX] ;
int n ;
string s ;

int match1(int l , int idx)
{
	if(s[l] == s[idx])
		return l+1 ;
	else
		return l ;
}

int match2(int r , int idx)
{
	if(s[r] == s[idx])
		return r-1 ;
	else
		return r ;
}

int solve(int idx , int l , int r)
{
	if(l > r)
		return 0 ;
	if(idx == n)
		return MAX ;
	int &ret = dp[idx][l][r] ;
	if(ret != -1)
		return ret ;
	ret = solve(idx+1 , l , r) ;
	ret = min(ret , solve(idx+1 , match1(l , idx) , match2(r , idx))+1) ;
	return ret ;
}

int main()
{
	memset(dp , -1 , sizeof(dp)) ;
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	cin>>n ;
	cin>>s ;
	return cout<<solve(0 , 0 , n-1)<<"\n" , 0 ;
}		