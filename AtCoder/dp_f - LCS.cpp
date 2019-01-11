/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest : AtCoder dp Educational contest (Atcoder dp)
   problem name : dp_f - LCS
   problem link : https://atcoder.jp/contests/dp/tasks/dp_f

*/

#include <bits/stdc++.h>

using namespace std;

const int MAX = 3010 ;
int dp[MAX][MAX] ;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    string s , s1 ;
    cin>>s>>s1 ;
    int n = s.size() , m = s1.size() ;
    for(int i = 0 ; i <= n ; ++i)
    {
        for(int j = 0 ; j <= m ; ++j)
        {
            if(i == 0 || j == 0)
                dp[i][j] = 0 ;
            else if(s[i-1] == s1[j-1])
                dp[i][j] = dp[i-1][j-1] + 1 ;
            else
                dp[i][j] = max(dp[i-1][j] , dp[i][j-1]);
        }
    }
    int idx = dp[n][m];
    string lcs = "";
    for(int i = 0 ; i < idx ; ++i)
        lcs += 'z' ;
    int i = n , j = m ;
    while(i > 0 && j > 0)
    {
        if(s[i-1] == s1[j-1])
        {
            lcs[idx-1] = s[i-1] ;
            i--;
            j--;
            idx--;
        }
        else if(dp[i-1][j] > dp[i][j-1])
            i--;
        else
            j--;
    }
    return cout<<lcs , 0 ;
}
