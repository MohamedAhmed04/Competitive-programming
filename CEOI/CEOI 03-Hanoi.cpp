/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : Central European olympiad in informatics 2003 (CEOI 2003)
   problem name : Hanoi (CEOI 2003-Hanoi)
   problem link : English statement : http://ceoi.inf.elte.hu/probarch/03/hanoi-en.pdf
                  To submit         : https://www.acmicpc.net/problem/2270

           Problem's solution : 
            http://ceoi.inf.elte.hu/probarch/03/hanoi-solution.pdf

*/

#include <bits/stdc++.h>

using namespace std ;

const long long mod = 1e6 ;
const int MAX = 1e5 + 10 ;

int arr[3][MAX] , sz[3] , place[MAX] , P[MAX] ;
int n ;

int main()
{
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	cin>>n ;
	for(int i = 0 ; i < 3 ; ++i)
		cin>>sz[i] ;
	for(int i = 0 ; i < 3 ; ++i)
	{
		for(int j = 0 ; j < sz[i] ; ++j)
		{
			cin>>arr[i][j] ;
			place[arr[i][j]] = i ;
		}
	}
	P[0] = 1ll ;
	for(int i = 1 ; i < MAX ; ++i)
		P[i] = (P[i-1] * (2ll)) % mod ;
	long long ans = 0ll ;
	int cur = place[n] ;
	for(int i = n ; i >= 1 ; --i)
	{
		if(place[i] == cur)
			continue ;
		else
		{
			ans = (ans + P[i-1]) % mod ;
			if(0 != place[i] && 0 != cur)
				cur = 0 ;
			else if(1 != place[i] && 1 != cur)
				cur = 1 ;
			else
				cur = 2 ;
		}
	}
	return cout<<place[n]+1<<"\n"<<ans<<"\n" , 0 ;
}		