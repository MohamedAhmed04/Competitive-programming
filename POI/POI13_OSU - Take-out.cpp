/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest name : POI 13
   problem name : Take-out (POI13_OSU - Take-out)
   problem link : https://oj.uz/problem/view/POI13_usu

   solution idea :
     we can greedily see if number of b's before current c and after current
   c (using prefix array) is more than or equal to k then we can erase them , else
   then continue until find it and at the end reverse the array to avoid the gaps.

   problem type : Greedy / Ad hoc (constructive algorithms)

*/

#include <bits/stdc++.h>

using namespace std ;

const int MAX = 1000000 ;
int arr[MAX] ;

int main()
{
	int n , k ;
	cin>>n>>k ;
	string s ;
	cin>>s ;
	int cnt = 0 ;
	vector<int>v ;
	vector< vector<int> >ans ;
	for(int i = 0 ; i < n ; ++i)
	{
		v.push_back(i) ;
		if(s[i] == 'b')
			arr[cnt]++ ;
		else if(s[i] == 'c')
			cnt++ ;
		if(cnt == 0)
			continue ;
		if(arr[cnt] + arr[cnt-1] >= k)
		{
			int s = v.size()-k-1 ;
			vector<int>tmp ;
			for(int j = s ; j <= s+k ; ++j)
				tmp.push_back(v[j]) ;
			for(int j = 0 ; j < k+1 ; ++j)
				v.pop_back() ;
			int need = min(k , arr[cnt]) ;
			ans.push_back(tmp) ;
			arr[cnt] -= need ;
			--cnt ;
			arr[cnt] -= (k-need) ;
		}
	}
	reverse(ans.begin() , ans.end()) ;
	for(int i = 0 ; i < ans.size() ; ++i)
	{
		for(int j = 0 ; j < ans[i].size() ; ++j)
			cout<<ans[i][j]+1<<" ";
		cout<<"\n";
	}
	return 0 ;
}
