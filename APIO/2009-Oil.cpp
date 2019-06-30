/* Author: Mohamed Ahmed Bakry (handle: MohamedAhmed04)

   contest name : APIO 2009
   problem name : Oil (APIO 2009 Oil)
   problem link : https://tioj.ck.tp.edu.tw/problems/1742 (use google translate to understand statement)

   problem's solution :
    see Editorial, Editorial link : http://apio-olympiad.org/2009/apio2009-solutions.pdf

*/

#include <bits/stdc++.h>

using namespace std ;

const int MAX = 2000 ;
int sum[MAX][MAX] ;
int ta[MAX] , tb[MAX] , tc[MAX], td[MAX] ;
int a[MAX][MAX] , b[MAX][MAX] , c[MAX][MAX] , d[MAX][MAX] , e[MAX][MAX] , f[MAX][MAX] ;

int n , m , k ;

int ans ;

int sumrect(int x , int y , int x2 , int y2)
{
	return (sum[x2][y2] - sum[x - 1][y2] - sum[x2][y - 1] + sum[x-1][y-1]) ;
}

void preprocess()
{
	for(int j = k ; j <= m ; ++j)
	{
		for(int i = k ; i <= n ; ++i)
			ta[j] = max(ta[j-1] , max(ta[j] , sumrect(i - k + 1 , j - k + 1 , i , j))) ;
	}
	for(int j = m - k + 1 ; j >= 1 ; --j)
	{
		for(int i = k ; i <= n ; ++i)
			tb[j] = max(tb[j+1] , max(tb[j] , sumrect(i - k + 1,  j , i , j + k - 1))) ;
	}
	for(int i = k ; i <= n ; ++i)
	{
		for(int j = k ; j <= m ; ++j)
		{
			tc[i] = max(tc[i-1] , max(tc[i] , sumrect(i - k + 1 , j - k + 1 , i , j))) ;
		}
	}
	for(int i = n - k + 1 ; i >= 1 ; --i)
	{
		for(int j = k ; j <= m ; ++j)
		{
			td[i] = max(td[i+1] , max(td[i] , sumrect(i , j - k + 1 , i + k - 1, j))) ;
		}
	}
	for(int i = k ; i <= n ; ++i)
	{
		for(int j = k ; j <= m ; ++j)
		{
			a[i][j] = max(a[i-1][j] , a[i][j-1]) ;
			a[i][j] = max(a[i][j] , sumrect(i - k + 1 , j - k + 1,  i , j)) ;
		}
	}
	for(int i = n-k+1 ; i >= 1 ; --i)
	{
		for(int j = k ; j <= m ; ++j)
		{
			b[i][j] = max(b[i+1][j] , b[i][j-1]) ;
			b[i][j] = max(b[i][j] , sumrect(i , j - k + 1 , i + k - 1 , j)) ;
		}
	}
	for(int i = k ; i <= n ; ++i)
	{
		for(int j = m-k+1 ; j >= 1 ; --j)
		{
			c[i][j] = max(c[i-1][j] , c[i][j+1]) ;
			c[i][j] = max(c[i][j] , sumrect(i-k+1 , j , i , j + k - 1)) ;
		}
	}
	for(int i = n - k + 1 ; i >= 1 ; --i)
	{
		for(int j = m - k + 1 ; j >= 1 ; --j)
		{
			d[i][j] = max(d[i+1][j] , d[i][j+1]) ;
			d[i][j] = max(d[i][j] , sumrect(i , j , i + k - 1 , j + k - 1)) ;
		}
	}
	for(int i = k ; i <= n ; ++i)
	{
		for(int j = 1 ; j <= m - k + 1 ; ++j)
		{
			e[i - k + 1][i] = max(e[i-k+1][i] , sumrect(i - k + 1, j, i, j + k - 1)) ;
		}
		if(i != k)
		{
			for(int j = 1 ; j <= i - k ; ++j)
			{
				e[j][i] = max(e[j][i-1] , e[i-k+1][i]) ;
			}
		}
	}
	for(int j = k ; j <= m ; ++j)
	{
		for(int i = 1 ; i <= n - k + 1 ; ++i)
		{
			f[j - k + 1][j] = max(f[j-k+1][j] , sumrect(i , j - k + 1 , i + k - 1 , j)) ;
		}
		if(j != k)
		{
			for(int i = 1 ; i <= j - k;  ++i)
			{
				f[i][j] = max(f[i][j-1] , f[j - k + 1][j]) ;
			}
		}
	}
}

void calculate()
{
	for(int i = 1 ; i <= n - k + 1 ; ++i)
	{
		for(int j = 1 ; j <= m - k + 1 ; ++j)
		{
			ans = max(ans , ta[j] + c[i][j+1] + d[i+1][j+1]) ;
			ans = max(ans , tb[j+1] + a[i][j] + b[i+1][j]) ;
			ans = max(ans , td[i+1] + a[i][j] + c[i][j+1]) ;
			ans = max(ans , tc[i] + b[i+1][j] + d[i+1][j+1]) ;
		}
	}
	for(int i = k ; i <= n - 2 * k ; ++i)
	{
		for(int j = i+k+1 ; j <= n - k + 1 ; ++j)
		{
			ans = max(ans , tc[i] + e[i+1][j-1] + td[j]) ;
		}
	}
	for(int i = k ; i <= m - 2 * k ; ++i)
	{
		for(int j = i+k+1 ; j <= m - k + 1 ; ++j)
		{
			ans = max(ans , ta[i] + f[i+1][j-1] + tb[j]) ;
		}
	}
	return ;
}

int main()
{
	scanf("%d %d %d" , &n , &m , &k) ;
	for(int i = 1 ; i <= n ; ++i)
	{
		for(int j = 1 ; j <= m ; ++j)
		{
			scanf("%d" , &sum[i][j]) ;
			sum[i][j] = sum[i][j] + sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] ;
		}
	}
	preprocess() ;
	calculate() ;
	return printf("%d\n", ans) , 0;
}
