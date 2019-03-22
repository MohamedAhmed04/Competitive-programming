/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest name : IZhO 2014
   problem name : K blocks (IZhO 14-Blocks)
   problem link : https://oj.uz/problem/view/IZhO14_blocks

   problem solution :
     we can solve this problem using dp , which the state is dp[i][j] which
   i denote the idx and j denote number of groups formed , so now for each element
   we have two choices , be from one group from previous elements or make a new group ,
   so after making many examples we will make observation that the optimal for each element to make
   group with elements that are less than it or last element greater than it , so we will make a monotonic
   queue to try every element.
   note : chosen[i][j] denote the maximum element in group j which idx i is in.
   another note : see comments below for more clarification.

*/

#include <bits/stdc++.h>

using namespace std ;

int main()
{
	int n , k ;
	scanf("%d %d" , &n , &k) ;
	int arr[n+1] ;
	for(int i = 1 ; i <= n ; ++i)
		scanf("%d" , &arr[i]) ;
	int dp[n+1][k+1] ;
	int chosen[n+1][k+1] ;

	//if we make one group so dp[i][1] equal to maximum from index 1 to i.
	dp[0][1] = 0 ;
	for(int i = 1 ; i <= n ; ++i)
		dp[i][1] = max(arr[i] , dp[i-1][1]) , chosen[i][1] = dp[i][1];
    //loop on all possible groups
	for(int j = 2 ; j <= k ; ++j)
	{
		stack<int>s ;
		for(int i = j ; i <= n ; ++i)
		{
			dp[i][j] = dp[i-1][j-1] + arr[i] ;
			chosen[i][j] = arr[i] ;
			//move in stack
			while(s.size() > 0)
			{
				int idx = s.top() ;
				if(arr[idx] <= arr[i])
				{
					if(dp[idx][j] - chosen[idx][j] + max(chosen[idx][j] , arr[i]) < dp[i][j])
					{
						dp[i][j] = dp[idx][j] - chosen[idx][j] + max(chosen[idx][j] , arr[i]) ;
					}
					s.pop() ;
				}
				else
					break ;
			}
			//try last element greater than arr[i].
			if(s.size() > 0)
			{
				int idx = s.top() ;
				if(dp[idx][j] < dp[i][j])
				{
					dp[i][j] = dp[idx][j] ;
                    chosen[i][j] = chosen[idx][j] ;
				}
			}
			s.push(i) ;
		}
	}
	printf("%d" , dp[n][k]) ;
	return 0 ;
}
