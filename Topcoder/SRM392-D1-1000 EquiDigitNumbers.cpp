/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   problem name : TopCoder srm392 Div1 1000 EquiDigitNumbers

*/

#include <bits/stdc++.h>

using namespace std ;

class EquiDigitNumbers
{
public:
	string calc(string s , int occ , int idx , int c)
	{
		int n = s.size() ;
		int freq[10] ;
		for(int i = 0 ; i <= 9 ; ++i)
			freq[i] = occ ;
		string s2 = "" ;
		for(int i = 0 ; i < idx ; ++i)
		{
			s2.push_back(s[i]) ;
			freq[s[i] - '0']-- ;
		}
		s2.push_back((char)(c + '0')) ;
		freq[c]-- ;
		for(int i = idx+1 ; i < n ; ++i)
		{
			int sum = 0 ;
			for(int j = 0 ; j <= 9 ; ++j)
			{
				if(freq[j] < occ && freq[j] >= 0)
					sum += freq[j] ;
			}
			if(sum < n-i)
			{
				for(int j = 0 ; j <= 9 ; ++j)
				{
					if(freq[j] > 0)
					{
						freq[j]-- ;
						s2.push_back((char)(j + '0')) ;
						break ;
					}
				}
			}
			else
			{
				for(int j = 0 ; j <= 9 ; ++j)
				{
					if(freq[j] < occ && freq[j] > 0)
					{
						freq[j]-- ;
						s2.push_back((char)(j + '0')) ;
						break ;
					}
				}
			}
		}
		if(s2.size() != n)
			return string(30 , '9') ;
		for(int i = 0 ; i <= 9 ; ++i)
		{
			if(freq[i] != 0 && freq[i] != occ)
				return string(30 , '9') ;
		}
		return s2 ;
	}
	string build(string s , int occ)
	{
		int n = s.size() ;
		string ans = string(30 , '9') ;
		for(int i = 0 ; i < n ; ++i)
		{
			int now = s[i] - '0' ;
			for(int j = now+1 ; j <= 9 ; ++j)
			{
				string cur = calc(s , occ , i , j) ;
				if(cur < ans)
					ans = cur ;
			}
		}
		return ans ;
	}
	long long solve(string s)
	{
		int n = s.size() ;
		string ans = string(30 , '9') ;
		//handle if s is equidigitnumber
		int freq[10] ;
		memset(freq , 0 , sizeof(freq)) ;
		for(int i = 0 ; i < n ; ++i)
			freq[s[i] - '0']++ ;
		int now = 0 ;
		for(int i = 0 ; i <= 9 ; ++i)
		{
			if(freq[i] > 0)
			{
				now = freq[i] ;
				break ;
			}
		}
		bool flag = true ;
		for(int i = 0 ; i <= 9 ; ++i)
			flag &= (freq[i] == 0 || freq[i] == now) ;
		if(flag)
			ans = s ;
		//loop to find smallest equidigt number > s
		for(int i = 1 ; i <= n ; ++i)
		{
			if(n % i != 0)
				continue ;
			string cur = build(s , i) ;
			if(cur < ans)
				ans = cur ;
		}
		long long ans2 = 0ll ;
		for(int i = 0 ; i < n ; ++i)
			ans2 = ans2 * 10ll + (ans[i] - '0') ;
		return ans2 ;
	}
	long long findNext(string n)
	{
		return solve(n) ;
	}
};

/*int main()
{
	string s ;
	cin>>s ;
	EquiDigitNumbers a ;
	return cout<<a.findNext(s)<<"\n" , 0 ;
}*/