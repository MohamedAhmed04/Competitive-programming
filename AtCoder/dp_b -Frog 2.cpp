/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest : AtCoder dp Educational contest (Atcoder dp)
   problem name : dp_b - Frog2
   problem link : https://atcoder.jp/contests/dp/tasks/dp_b

*/

#include <iostream>

using namespace std;

int main()
{
    int n , k;
    cin>>n>>k ;
    int arr[n] , dp[n];
    for(int i = 0 ; i < n ; ++i)
        cin>>arr[i];
    for(int i = 0 ; i < n ; ++i)
        dp[i] = 1e9+5 ;
    dp[n-1] = 0 ;
    for(int j = n-2 ; j >= 0 ; --j)
    {
        for(int i = 1 ; i <= k ; ++i)
        {
            if(j+i >= n)
                break;
            dp[j] = min(dp[j] , dp[j+i] + abs(arr[j] - arr[j+i]));
        }
    }
    return cout<<dp[0]<<"\n" , 0 ;
}
