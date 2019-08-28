/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : COCI 2008 contest 4
   problem name : Slikar (COCI 2008-Slikar)
   problem link : https://dmoj.ca/problem/coci08c4p4

   problem's solution :
    - let dp[x][y][x2][y2] solution for square (x , y) -> (x2 , y2)
      but since it will get memory limit exceeded and (x2 , y2) are unique
      for every (x , y) and level where level is number if processes we did before
      current process so state will be dp[x][y][level].
    - let's divide current square into 4 equal squares.
    - now we need to make one square black and one square white and two squares we will
      recurse on them.
    - so let's loop on every mask of size 2 of 4 elements and let's denote x , y as two setted bits, and answer for mask will be
      ans for square that we recursed on it + ans for 2nd square that we recursed on it 
      + min(cost of making x black + cost of making y white, cost of making y black + cost of making x white).
    - cost of making square black is number of white cells inside it and cost of making square white is black cells
      inside it.
    - to know number of black cells inside square we will make 2D prefix sums where sum[i][j] is number of ones
      in rectangle (1 , 1) to (x , y).
    - to calculate number of black cells inside square (x , y) to (x2 , y2) equals :
      sum[x2][y2] - sum[x-1][y2] - sum[x2][y-1] + sum[x-1][y-1] 
    - number of white cells in square equals to area of square - number of black cells.
    - answer for dp[x][y][level] will be minimum answer of all masks.
    - we will build the output using same idea above.

*/

#include <bits/stdc++.h>

using namespace std ;

const int MAX = 520 ;

int dp[MAX][MAX][12] ;

int arr[MAX][MAX] , sum[MAX][MAX] ;
int ans[MAX][MAX] ;
int n ;

vector<int>masks ;

int solve(int x , int y , int x2 , int y2 , int level)
{
	if(x == x2 && y == y2)
		return 0 ;
	int &ret = dp[x][y][level] ;
	if(ret != -1)
		return ret ;
	ret = 1e9 ;
	int length = x2-x+1 ;
	int ax[4], ay[4] , ax2[4] , ay2[4] ;
	ax[0] = x , ax2[0] = x + length / 2 - 1, ay[0] = y , ay2[0] = y+length/2-1 ;
	ax[1] = x , ax2[1] = x + length / 2 - 1, ay[1] = y+length/2 , ay2[1] = y2 ;
	ax[2] = x+length/2 , ax2[2] = x2 , ay[2] = y , ay2[2] = y+length/2-1 ;
	ax[3] = x+length/2 , ax2[3] = x2 , ay[3] = y+length/2 , ay2[3] = y2 ;
	for(auto &mask : masks)
	{
		int now = 0 , cnt00 = 0 , cnt01 = 0 , cnt10 = 0 , cnt11 = 0;
		int cnt = 0 ;
		bool flag = 0 ;
		for(int j = 0 ; j < 4 ; ++j)
		{
			if((mask & (1 << j)))
			{
				cnt++ ;
				if(!flag)
				{
					cnt00 = sum[ax2[j]][ay2[j]] - sum[ax[j]-1][ay2[j]] - sum[ax2[j]][ay[j]-1] + sum[ax[j]-1][ay[j]-1] ;
					cnt01 = (length / 2) * (length / 2) - cnt00 ;
				}
				else
				{
					cnt10 = sum[ax2[j]][ay2[j]] - sum[ax[j]-1][ay2[j]] - sum[ax2[j]][ay[j]-1] + sum[ax[j]-1][ay[j]-1] ;
					cnt11 = (length / 2) * (length / 2) - cnt10 ;
				}
				flag = 1 ;
			}
			else
			{
				now += solve(ax[j], ay[j] , ax2[j] , ay2[j] , level+1) ;
			}
		}
		now += min(cnt01 + cnt10 , cnt00 + cnt11) ;
		ret = min(ret , now) ;
	}
	return ret ;
}

void build(int x , int y , int x2 , int y2 , int level)
{
	if(x == x2 && y == y2)
	{
		ans[x][y] = arr[x][y] ;
		return ;
	}
	int length = x2-x+1 ;
	int ax[4], ay[4] , ax2[4] , ay2[4] ;
	ax[0] = x , ax2[0] = x + length / 2 - 1, ay[0] = y , ay2[0] = y+length/2-1 ;
	ax[1] = x , ax2[1] = x + length / 2 - 1, ay[1] = y+length/2 , ay2[1] = y2 ;
	ax[2] = x+length/2 , ax2[2] = x2 , ay[2] = y , ay2[2] = y+length/2-1 ;
	ax[3] = x+length/2 , ax2[3] = x2 , ay[3] = y+length/2 , ay2[3] = y2 ;
	int cur = solve(x , y , x2 , y2 , level) ;
	for(auto &mask : masks)
	{
		int now = 0 , cnt00 = 0 , cnt01 = 0 , cnt10 = 0 , cnt11 = 0;
		int cnt = 0 ;
		bool flag = 0 ;
		for(int j = 0 ; j < 4 ; ++j)
		{
			if((mask & (1 << j)))
			{
				cnt++ ;
				if(!flag)
				{
					cnt00 = sum[ax2[j]][ay2[j]] - sum[ax[j]-1][ay2[j]] - sum[ax2[j]][ay[j]-1] + sum[ax[j]-1][ay[j]-1] ;
					cnt01 = (length / 2) * (length / 2) - cnt00 ;
				}
				else
				{
					cnt10 = sum[ax2[j]][ay2[j]] - sum[ax[j]-1][ay2[j]] - sum[ax2[j]][ay[j]-1] + sum[ax[j]-1][ay[j]-1] ;
					cnt11 = (length / 2) * (length / 2) - cnt10 ;
				}
				flag = 1 ;
			}
			else
			{
				now += solve(ax[j], ay[j] , ax2[j] , ay2[j] , level+1) ;
			}
		}
		now += min(cnt01 + cnt10 , cnt00 + cnt11) ;
		if(now == cur)
		{
			bool flag = 0 ;
			if(cnt00 + cnt11 == min(cnt00+cnt11 , cnt01 + cnt10))
				flag = 0 ;
			else
				flag = 1 ;
			for(int j = 0 ; j < 4 ; ++j)
			{
				if((mask & (1 << j)))
				{
					for(int a = ax[j] ; a <= ax2[j] ; ++a)
					{
						for(int b = ay[j] ; b <= ay2[j] ; ++b)
							ans[a][b] = flag; 
					}
					flag = !flag ;
				}
				else
					build(ax[j], ay[j] , ax2[j] , ay2[j] , level+1) ;
			}
			break ;
		}
	}
	return ;
}

int main()
{
	memset(dp, -1 , sizeof(dp)) ;
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	cin>>n ;
	for(int i = 1 ; i <= n ; ++i)
	{
		for(int j = 1 ; j <= n ; ++j)
		{
			char c ;
			cin>>c ;
			arr[i][j] = (c - '0') ;
		}
	}
	for(int i = 1 ; i <= n ; ++i)
	{
		for(int j = 1 ; j <= n ; ++j)
			sum[i][j] = arr[i][j] + sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] ;
	}
	for(int i = 0 ; i < (1 << 4) ; ++i)
	{
		int cnt = 0 ;
		for(int j = 0 ; j < 4 ; ++j)
		{
			if((i & (1 << j)))
				cnt++ ;
		}
		if(cnt == 2)
			masks.push_back(i) ;
	}
	cout<<solve(1 , 1 , n , n , 0)<<"\n";
	build(1 , 1 , n , n , 0) ;
	for(int i = 1 ; i <= n ; ++i)
	{
		for(int j = 1 ; j <= n ; ++j)
			cout<<ans[i][j];
		cout<<"\n";
	}
	return 0 ;
}