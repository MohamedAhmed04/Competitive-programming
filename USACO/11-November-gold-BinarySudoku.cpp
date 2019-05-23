/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : USACO 2011 November Gold
   problem name : Binary Sudoku (USACO 2011 November Gold)
   problem link : http://usaco.org/index.php?page=viewproblem2&cpid=92

   problem solution :
    http://usaco.org/current/data/sol_bsudoku.html

*/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10 ;
int arr[MAXN][MAXN] ;
int dp[MAXN][MAXN][(1 << MAXN)][(1 << 4)][2] ;

int solve(int x , int y , int maskcol , int masksub , int now)
{
    if(x == 9)
    {
        if(maskcol == 0 && masksub == 0)
            return 0 ;
        else
            return (1e9) ;
    }
    if(y == 9)
    {
        if(now != 0)
            return 1e9 ;
        if(x%3 == 2 && masksub != 0)
            return (1e9) ;
        if(x % 3 == 2)
            masksub = 0  ;
        return solve(x+1 , 0 , maskcol , masksub , 0) ;
    }
    int &ret = dp[x][y][maskcol][masksub][now] ;
    if(ret != -1)
        return ret ;
    int choice1 = (arr[x][y] == 0) + solve(x , y+1 , maskcol ^ (1 << y) , masksub ^ (1 << (y/3)) , !now);
    int choice2 = (arr[x][y] == 1) + solve(x , y+1 , maskcol  , masksub  , now);
    ret = min(choice1 , choice2) ;
    return ret ;
}

int main()
{
    freopen("bsudoku.in" , "r" , stdin) ;
    freopen("bsudoku.out" , "w" , stdout) ;
    memset(dp , -1 , sizeof(dp));
    for(int i = 0 ; i < 9 ; ++i)
    {
        for(int j = 0 ; j < 9 ; ++j)
        {
            char c ;
            cin>>c ;
            arr[i][j] = (c - '0') ;
        }
    }
    return cout<<solve(0 , 0 , 0 , 0 , 0)<<"\n" , 0 ;
}
