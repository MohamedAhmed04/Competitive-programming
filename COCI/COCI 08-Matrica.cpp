/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : COCI 2008 contest 4
   problem name : Matrica (COI 2008-Matrica)
   problem link : https://dmoj.ca/problem/coci08c3p4

   Problem's solution :
   same idea : https://github.com/thackerhelik/DMOJ/blob/master/COCI%2008-Matrica.cpp

*/

#include <bits/stdc++.h>

using namespace std ;

const int MAX = 30010 ;

int arr[55] , freq[27] , sum[MAX] ;
char ans[MAX] , ans2[55][MAX] ;
int n , m , k ;

char Find(int x , int y)
{
	if(x > y)
		return Find(y , x) ;
	int now = sum[x] + max(0 , y-x-1) ;
	for(int j = 0 ; j < 26 ; ++j)
	{
		if(freq[j] == 0)
			continue ;
		now -= (freq[j] / 2) ;
		if(now < 0)
			return (char)(j + 'A') ;
	}
}

void solve(int i)
{
	for(int j = 1 ; j <= n ; ++j)
	{
		if(arr[i] == j)
			continue ;
		ans2[i][j] = Find(arr[i] , j) ;
	}
	return ;
}

int main()
{
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	cin>>n>>k ;
	for(int i = 0 ; i < k ; ++i)
	{
		char c ;
		cin>>c ;
		cin>>freq[(c-'A')] ;
	}
	cin>>m ;
	for(int i = 1 ; i <= m ; ++i)
		cin>>arr[i] ;
	int cnt = 0 ;
	for(int i = 0 ; i < 26 ; ++i)
		cnt += (freq[i] & 1) ;
	if(cnt > n)
		return cout<<"IMPOSSIBLE\n" , 0 ;
	for(int i = 1 ; i <= n ; ++i)
	{
		if(i > 1)
			sum[i] = sum[i-1] + (n-(i-1)) ;
		cnt = 0 ;
		for(int j = 0 ; j < 26 ; ++j)
			cnt += (freq[j] & 1) ;
		if(n-i-1 >= cnt)
		{
			int cnt2 = 0 ;
			for(int j = 0 ; j < 26 ; ++j)
			{
				if(freq[j] == 0)
					continue ;
				if((freq[j] & 1))
				{
					ans[i] = (char)(j + 'A') ;
					freq[j]-- ;
					break ;
				}
				cnt2 += (freq[j] / 2) ;
				if(cnt2 > sum[i])
				{
					ans[i] = (char)(j + 'A') ;
					freq[j]-- ;
					break ;
				}
			}
		}
		else
		{
			for(int j = 0 ; j < 26 ; ++j)
			{
				if((freq[j] & 1))
				{
					ans[i] = (char)(j + 'A') ;
					freq[j]-- ;
					break ;
				}
			}
		}
	}
	for(int i = 1 ; i <= m ; ++i)
		solve(i) ;
	for(int j = 1 ; j <= n ; ++j)
	{
		for(int i = 1 ; i <= m ; ++i)
		{
			if(j == arr[i])
			{
				cout<<ans[j] ;
			}
			else
				cout<<ans2[i][j] ;
		}
		cout<<"\n" ;
	}
	return 0 ;
}		