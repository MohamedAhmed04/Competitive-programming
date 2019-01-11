/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest : AtCoder dp Educational contest (Atcoder dp)
   problem name : dp_k - Stones
   problem link : https://atcoder.jp/contests/dp/tasks/dp_k

*/

#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n , k;
    cin>>n>>k ;
    int arr[n] ;
    for(int i = 0 ; i < n ; ++i)
        cin>>arr[i] ;
    int dp[k+1] ;
    dp[0] = 0 ;
    for(int i = 1 ; i <= k ; ++i)
    {
        dp[i] = 0 ;
        for(int j = 0 ; j < n ; ++j)
        {
            if(i - arr[j] < 0)
                continue;
            if(dp[i - arr[j]] == 0)
                dp[i] = 1 ;
        }
    }
    if(dp[k] == 1)
        cout<<"First\n";
    else
        cout<<"Second\n";
    return 0 ;
}
