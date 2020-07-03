/* Author: Mohamed Bakry (handle: MohamedAhmed04)

   contest name: Romanian Master of Informatics (RMI) 2018 day 1
   problem name: Password (RMI 2018-Password)
   problem link: https://oj.uz/problem/view/RMI18_password

   Problem's solution:
    my idea is like this idea: https://github.com/stefdasca/CompetitiveProgramming/blob/master/Infoarena/password2.cpp

*/

#include <bits/stdc++.h>
 
using namespace std ;
 
const int MAX = 1e5 + 10 ;
 
int arr[MAX] , freq[27] , before[27][27] , letters[MAX] ;
int n , c ;
 
string ans = "" ;
 
int query(string s);
 
bool Check_Before(int a , int b)
{
	string s = ans ;
	s.push_back((char)(a+'a')) ;
	for(int i = 0 ; i < freq[b] ; ++i)
		s.push_back((char)(b+'a')) ;
	return (query(s) == s.size()) ;
}
 
bool cmp(int &a , int &b)
{
	return before[a][b] ;
}
 
string guess(int n , int c)
{
	for(int i = 0 ; i < c ; ++i)
		freq[i] = query(string(n , (char)('a'+i))) ;
	for(int i = 0 ; i < c ; ++i)
	{
		for(int j = i+1 ; j < c ; ++j)
		{
			before[i][j] = Check_Before(i , j) ;
			if(!before[i][j])
				before[j][i] = 1 ;
		}
	}
	for(int i = 0 ; i < c ; ++i)
		letters[i] = i ;
	sort(letters , letters + c , cmp) ;
	for(int i = 0 ; i < n ; ++i)
	{
		int x = letters[0] ;
		freq[x]-- ;
		ans.push_back((char)(x+'a')) ;
		int l = 1 , r = c-1 ;
		int idx = 0 ;
		if(freq[x] == 0)
			idx = c-1 ;
		else
		{
			while(l <= r)
			{
				int mid = (l + r) >> 1 ;
				if(!Check_Before(letters[0] , letters[mid]))
					idx = mid , l = mid+1 ;
				else
					r = mid-1 ;
			}
		}
		for(int i = 0 ; i < idx ; ++i)
			letters[i] = letters[i+1] ;
		letters[idx] = x ;
	}
	return ans ;
}	