/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : APIO 2008
   problem name : dna (APIO 2008-dna)
   problem link : https://dunjudge.me/analysis/problems/542/

   problem's solution :
    same idea : https://github.com/Yehezkiel01/CompetitiveProgramming/blob/master/APIO/APIO-08-DNA.cpp

*/

#include <bits/stdc++.h>

using namespace std ;

const int MAX = 50010 ;

int n , k ;
long long r ;
long long dp[MAX][12][4] ;
string s ;

map<char , int>id ;

long long solve(int idx , int cnt , int prv)
{
	if(cnt > k)
		return 0ll ;
	if(idx == n)
		return 1ll ;
	long long &ret = dp[idx][cnt][prv] ;
	if(ret != -1)
		return ret ;
	ret = 0ll ;
	if(s[idx] != 'N')
		ret = solve(idx+1 , cnt + (id[s[idx]] < prv), id[s[idx]]) ;
	else
	{
		for(int j = 0 ; j < 4 ; ++j)
			ret += solve(idx+1 , cnt + (j < prv) , j) ;
	}
	return ret ;
}

int main()
{
	memset(dp , -1 , sizeof(dp)) ;
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	id['A'] = 0 ;
	id['C'] = 1 ;
	id['G'] = 2 ;
	id['T'] = 3 ;
	cin>>n>>k>>r ;
	cin>>s ;
	int cnt = 1 ;
	int prv = -1 ;
	for(int i = 0 ; i < n ; ++i)
	{
		if(s[i] != 'N')
		{
			cout<<s[i] ;
			if(id[s[i]] < prv)
				cnt++ ;
			prv = id[s[i]] ;
		}
		else
		{
			for(int j = 0 ; j < 4 ; ++j)
			{
				long long x = solve(i+1 , cnt + (j < prv) , j) ; 
				if(x >= r)
				{
					cnt += (j < prv) ;
					prv = j ;
					if(j == 0)
						cout<<'A' ;
					if(j == 1)
						cout<<'C' ;
					if(j == 2)
						cout<<'G' ;
					if(j == 3)
						cout<<'T' ;
					break ;
				}
				else
					r -= x ;
			}
		}
	}
	return 0 ;
}		