/* Author: Mohamed Bakry (handle: MohamedAhmed04)

   contest name : Central European Olympiad In Informatics (CEOI) 2010
   problem name : A Huge Tower (CEOI 2010-Tower)
   problem link : English statement: http://ceoi.inf.elte.hu/probarch/10/tow-eng.pdf
                  submit from here : https://szkopul.edu.pl/problemset/problem/5TfG0f1dOXc2sUTq9NMM9zSD/site/?key=statement

   Problem's solution:
      same idea: https://github.com/luciocf/Problems/blob/master/CEOI/CEOI%202010/tower.cpp

*/

#include <bits/stdc++.h>

using namespace std ;

const long long mod = 1e9 + 9ll ;
const int MAX = 1e6 + 10 ;

int n , d ;
vector<int>v ;

int main()
{
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	cin>>n>>d ;
	v.resize(n) ;
	for(int i = 0 ; i < n ; ++i)
		cin>>v[i] ;
	sort(v.begin() , v.end()) ;
	reverse(v.begin() , v.end()) ;
	int idx = 0 ;
	long long ans = 1ll ;
	for(int i = 0 ; i < n ; ++i)
	{
		while(v[idx] > v[i]+d)
			idx++ ;
		long long x = (i-idx+1ll) ;
		ans = (ans * x) % mod ;
	}
	return cout<<ans<<"\n" , 0 ;
}		