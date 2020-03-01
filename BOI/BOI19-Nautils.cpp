/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : Baltic Olympiad in informatics day 1
   problem name : Nautils (BalticOI 19-Nautils)
   problem link : https://oj.uz/problem/view/BOI19_nautilus

   problem's solution : 
    - make bitset for every row and value of cell is 1 if it can be in answer
      in ith step.
    - we need another bitset that any forbidden cell ("#") is setted by 1 for every row.
    - keep two bitsets, current bitset for ith step and previous bitset
      which stores the answer of every row in last step.
    - in every stop, loop on every now and let current row is i then
      if current step is N or ? then : now[i] |= prv[i+1]
      if current step is S or ? then : now[i] |= prv[i-1]
      if current step is W or ? then : now[i] |= (prv[i] >> 1)
      if current step is E or ? then : now[i] |= (prv[i] << 1)
    - some forbidden cells may have value 1 so we need to set them to 0
      let mask[i] is the name of bitset carrying forbidden cells for row i
      then to set them to 0 we can first
      now[i] |= mask[i]
      then
      now[i] ^= mask[i]
    - after last step, answer is summation of setted cells in every row.

*/

#include <bits/stdc++.h>

using namespace std ;

const int MAX = 510 ;

char arr[MAX][MAX] ;
int n , m , k ;

bitset<MAX>prv[MAX] , now[MAX] , mask[MAX] ;

string s ;

int main()
{
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	cin>>n>>m>>k ;
	for(int i = 0 ; i < n ; ++i)
	{
		for(int j = 0 ; j < m ; ++j)
		{
			cin>>arr[i][j] ;
			if(arr[i][j] == '.')
				now[i][j] = 1 ;
			else
				mask[i][j] = 1 ;
		}
		mask[i][m] = 1 ;
	}
	cin>>s ;
	for(int j = 0 ; j < k ; ++j)
	{
		for(int i = 0 ; i < n ; ++i)
			prv[i] = now[i] , now[i].reset() ;
		if(s[j] == 'N' || s[j] == '?')
		{
			for(int i = 0 ; i < n-1 ; ++i)
				now[i] |= prv[i+1] ;
		}
		if(s[j] == 'S' || s[j] == '?')
		{
			for(int i = 1 ; i < n ; ++i)
				now[i] |= prv[i-1] ;
		}
		if(s[j] == 'W' || s[j] == '?')
		{
			for(int i = 0 ; i < n ; ++i)
				now[i] |= (prv[i] >> 1) ;
		}
		if(s[j] == 'E' || s[j] == '?')
		{
			for(int i = 0 ; i < n ; ++i)
				now[i] |= (prv[i] << 1) ;
		}
		for(int i = 0 ; i < n ; ++i)
		{
			now[i] |= mask[i] ;
			now[i] ^= mask[i] ;
		}
	}
	int ans = 0 ;
	for(int i = 0 ; i < n ; ++i)
		ans += now[i].count() ;
	return cout<<ans<<"\n" , 0 ;
}		