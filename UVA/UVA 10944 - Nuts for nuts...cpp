/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   problem name : UVA 10944 - Nuts for nuts..

   solution of the problem :
   since number of nuts is 15 only...so we can think it as a travelling
   salesman problem (TSP)...so we will solve it as TSP problem and to get
   distance between any two nuts..since it can move diagonally or vertically or
   horizontally...so minimum distance is :
   max(abs(first.x - second.x) , abs(first.y - second.y)).
*/

#include <bits/stdc++.h>

using namespace std;

vector< pair<int , int> >nuts ;
pair<int , int>s ;

const int inf = 1e5 ;
const int MAX = (1 << 15)+10 ;
int dp[MAX][18] ;

int Distance(pair<int , int>a , pair<int , int>b)
{
    int x = abs(a.first - b.first) ;
    int y = abs(a.second - b.second) ;
    return max(x , y) ;
}

int solve(int mask , int idx)
{
    if(mask == ((1 << nuts.size())-1))
        return Distance(s , nuts[idx]) ;
    int &ret = dp[mask][idx] ;
    if(ret != -1)
        return ret ;
    ret = inf ;
    for(int i = 0 ; i < nuts.size() ; ++i)
    {
        if((mask & (1 << i)) == 0)
        {
            int dist = Distance(nuts[idx] , nuts[i]) ;
            int sum = solve(mask | (1 << i) , i) ;
            ret = min(ret , dist + sum) ;
        }
    }
    return ret ;
}

int main()
{
    int n , m ;
    while(cin>>n>>m)
    {
        memset(dp , -1 , sizeof(dp));
        nuts.clear();
        char arr[n][m] ;
        for(int i = 0 ; i < n ; ++i)
        {
            for(int j = 0 ; j < m ; ++j)
            {
                cin>>arr[i][j] ;
                if(arr[i][j] == '#')
                    nuts.push_back({i , j}) ;
                else if(arr[i][j] == 'L')
                    s = {i , j} ;
            }
        }
        int ans = inf ;
        for(int i = 0 ; i < nuts.size() ; ++i)
        {
            int x = Distance(s , nuts[i]);
            int y = solve(1 << i , i) ;
            ans = min(ans , x+y) ;
        }
        if(ans == inf)
            ans = 0 ;
        cout<<ans<<"\n";
    }
}
