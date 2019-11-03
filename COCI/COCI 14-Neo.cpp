/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : COCI 2014 contest 6
   problem name : Neo (COCI 14-Neo)
   problem link : https://dmoj.ca/problem/coci14c6p5

   problem's solution :
    same like editorial solution : 
	 https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/COCI/official/2015/contest6_solutions/solutions.pdf

*/

#include <bits/stdc++.h>

using namespace std ;

const int MAX = 1005 ;

int arr[MAX][MAX] , arr2[MAX][MAX] , r[MAX][MAX] , s[MAX] , e[MAX] ;
int n , m ;

int calc(int i)
{
	stack< pair<int , int> >st ;
	for(int j = 1 ; j <= m ; ++j)
	{
		while(st.size() > 0 && arr2[i][j] <= st.top().first)
			st.pop() ;
		if(st.size() > 0)
			s[j] = st.top().second + 1;
		else
			s[j] = 1 ;
		st.push({arr2[i][j] , j}) ;
	}
	while(st.size() > 0)
		st.pop() ;
	for(int j = m ; j >= 1 ; --j)
	{
		while(st.size() > 0 && arr2[i][j] <= st.top().first)
			st.pop() ;
		if(st.size() > 0)
			e[j] = st.top().second - 1 ;
		else
			e[j] = m ;
		st.push({arr2[i][j] , j}) ;
	}
	int ans = 0 ;
	for(int j = 1 ; j <= m ; ++j)
	{
		if(arr2[i][j] != 0)
			ans = max(ans , (arr2[i][j]+1) * (e[j]-s[j]+2)) ;
	}
	return ans ;
}

int main()
{
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	cin>>n>>m ;
	for(int i = 1 ; i <= n ; ++i)
	{
		for(int j = 1 ; j <= m ; ++j)
			cin>>arr[i][j] ;
	}
	for(int i = 1 ; i < n ; ++i)
	{
		for(int j = 1 ; j < m ; ++j)
		{
			if(arr[i][j] + arr[i+1][j+1] <= arr[i][j+1] + arr[i+1][j])
				arr2[i][j] = 1 ;
		}
	}
	for(int i = 1 ; i <= n ; ++i)
	{
		for(int j = m ; j >= 1 ; --j)
		{
			if(arr2[i][j] == 1)
				r[i][j] = max(r[i][j+1] , j) ;
		}
	}
	int ans = 0 ;
	for(int i = 1 ; i <= n ; ++i)
	{
		for(int j = 1 ; j <= m ; ++j)
		{
			if(arr2[i][j] == 1)
				arr2[i][j] += arr2[i-1][j] ;
		}
		ans = max(ans , calc(i)) ;
	}
	return cout<<ans<<"\n" , 0 ; 
}