/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   problem name : Greatest K-Palindrome Substring (UVA 1239 - Greatest K-Palindrome Substring)
   problem link :
     https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3680

   problem solution :
     let dp[i][j] is minimum number of changes to make substring from l to r palindrome , so
     we will loop on all possible substrings and see if number of changes needed is <= k then
     ans is maximum ans or size of substring , and print answer after end of loop.

*/

#include <bits/stdc++.h>

using namespace std;

const int MAX = 1005 ;
int dp[MAX][MAX] ;
string s ;
int n , k;

int solve(int i , int j)
{
    if(i > j)
        return 0 ;
    int &ret = dp[i][j] ;
    if(ret != -1)
        return ret ;
    int cost = 0 ;
    if(s[i] != s[j])
        cost = 1 ;
    return (ret = solve(i+1 , j-1) + cost);
}

int main()
{
    ios::sync_with_stdio(0) ;
    cin.tie(0) ;
    int t ;
    cin>>t ;
    while(t--)
    {
        memset(dp , -1 , sizeof(dp)) ;
        cin>>s>>k ;
        n = s.size() ;
        int ans = 0 ;
        for(int i = 0 ; i < n ; ++i)
        {
            for(int j = i ; j < n ; ++j)
            {
                int now = solve(i , j) ;
                if(now <= k)
                    ans = max(ans , j-i+1) ;
            }
        }
        cout<<ans<<"\n";
    }
    return 0 ;
}
