/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : International Olympiad in informatics (IOI) 2016 day 2
   problem name : Paint By Numbers (IOI 2016-Paint)
   problem link : https://oj.uz/problem/view/IOI16_paint

   problem's solution : 
    I think it's same like editorial idea : 
    https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/IOI/official/2016/ioi2016solutions.pdf

*/

//#include "grader.cpp"
#include "paint.h"

#include <bits/stdc++.h>

using namespace std ;

std::string solve_puzzle(std::string s, std::vector<int> c) 
{
	int n = s.size() , m = c.size() ;
	int arr[n+5] , pref[n+5] ;
	pref[0] = 0 ;
	for(int i = 1 ; i <= n ; ++i)
	{
		if(s[i-1] == 'X')
			arr[i] = 1 ;
		else if(s[i-1] == '_')
			arr[i] = 0 ;
		else if(s[i-1] == '.')
			arr[i] = -1 ;
		pref[i] = pref[i-1] ;
		if(arr[i] == 0)
			pref[i]++ ;
	}
	int dp1[n+2][m+2][3] ;
	memset(dp1 , 0 , sizeof(dp1)) ;
	dp1[0][0][0] = 1 ;
	for(int i = 1 ; i <= n ; ++i)
	{
		for(int j = 0 ; j <= m ; ++j)
		{
			for(int k = 0 ; k <= 1 ; ++k)
			{
				if(arr[i] != -1 && arr[i] != k)
					continue ;
				if(k == 0)
				{
					dp1[i][j][k] = dp1[i-1][j][k] ;
					if(j > 0)
					{
						if(i-c[j-1] >= 1)
							dp1[i][j][k] |= dp1[i-c[j-1]][j-1][1] ;
					}
				}
				else if(k == 1 && j != m)
				{
					if(i+c[j]-1 <= n && pref[i+c[j]-1] - pref[i-1] == 0)
						dp1[i][j][k] = dp1[i-1][j][0] ;
				}
			}
		}
	}
	int dp2[n+2][m+2][3] ;
	memset(dp2 , 0 , sizeof(dp2)) ;
	dp2[n+1][m][0] = 1 ;
	for(int i = n ; i >= 1 ; --i)
	{
		for(int j = 0 ; j <= m ; ++j)
		{
			for(int k = 0 ; k <= 1 ; ++k)
			{
				if(arr[i] != -1 && arr[i] != k)
					continue ;
				if(k == 0)
				{
					dp2[i][j][k] = dp2[i+1][j][k] ;
					dp2[i][j][k] |= dp2[i+1][j][1] ;
				}
				else if(k == 1 && j != m)
				{
					if(i+c[j]-1 <= n && pref[i+c[j]-1] - pref[i-1] == 0)
					{
						dp2[i][j][k] = dp2[i+c[j]][j+1][0] ;
					}
				}
			}
		}
	}
	string ans = "" ;
	int Max = -1 ;
	for(int i = 1 ; i <= n ; ++i)
	{
		for(int j = 0 ; j < m ; ++j)
		{
			if(dp1[i][j][1] == 1 && dp2[i][j][1] == 1)
				Max = max(Max , i+c[j]-1) ;
		}
		if(arr[i] == 1)
			ans.push_back('X') ;
		else if(arr[i] == 0)
			ans.push_back('_') ;
		else if(arr[i] == -1)
		{
			bool flag1 = false , flag2 = false ;
			for(int j = 0 ; j <= m ; ++j)
			{
				if(dp1[i][j][0] == 1 && dp2[i][j][0] == 1)
					flag1 = true ;
			}
			if(Max >= i)
				flag2 = true ;
			if(flag1 == 1 && flag2 == 1)
				ans.push_back('?');
			else if(flag1 == 1)
				ans.push_back('_') ;
			else if(flag2 == 1)
				ans.push_back('X') ;
		}
	}
    return ans ;
}
