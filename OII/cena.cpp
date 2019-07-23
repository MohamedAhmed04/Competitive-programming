/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : OII 2018 National contest
   problem name : cena (OII2018-cena)
   problem link : https://training.olinfo.it/contests/oii2018/tasks/cena/description

   problem's solution : 
   	- preprocess array match where match[i] = minimum idx such that all participants
   	  will eat dishes if they started from idx >= i
   	- to preprocess that array we will make array found where found[i] = -1 
   	  if until now participants ate more than or less than m-i dishes else it will
   	  equal to idx of last dish that participant ate (from right).
   	- if found[0] isn't equal to -1 then participants can eat dishes if they started
   	  from i to found[0].
   	- now match[i] = min(match[i+1] , match[i]).
   	- loop on number dishes that Mojito will eat from left and add to answer n - match[i]
   	  where n - match[i] equals to number of dishes that Chupito can eat if Mojito ate i dishes.

 */

#include <bits/stdc++.h>
//#include "grader.cpp"

using namespace std ;

long long conta(int S, int s[], int P, int p[]) 
{
	int n = S , m = P ;
	int match[n] ;
	for(int i = 0 ; i < n ; ++i)
		match[i] = n ;
	long long ans = 0ll ;
	vector< vector<int> >idx(101) ;
	for(int i = 0 ; i < m ; ++i)
		idx[p[i]].push_back(i) ;
	int found[m+1] ;
	memset(found , -1 , sizeof(found)) ;
	for(int i = n-1 ; i >= 0 ; --i)
	{
		for(auto &j : idx[s[i]])
		{
			bool t = false ;
			if(j == m-1)
				found[m-1] = i , t = true;
			else
			{
				if(found[j+1] != -1)
					found[j] = found[j+1] , found[j+1] = -1 , t = true;
			}
			if(t && j == 0)
				match[i] = found[j] ;
		}
	}
	for(int i = n-2 ; i >= 0 ; --i)
	{
		match[i] = min(match[i] , match[i+1]) ;
	}
	for(int i = 0 ; i < n ; ++i)
	{
		ans += n * 1ll - match[i] * 1ll ;
	}
    return ans;
}
