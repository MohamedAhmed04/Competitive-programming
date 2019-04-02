/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest name : COCI 2014 contest 2
   problem name : Bob (COCI 14-Bob)
   problem link : https://oj.uz/problem/view/COCI14_bob

   problem solution :
   let's loop on each column and current element mark it at ending row of current column
   so we will go above to see how many rectangles we can make , and now[i][j] is maximum
   width of rectangle we can form in row i if we start from column j so we will make monotonic stack
   and every time we will add to current element count of above elements which now[k][j] k < i is more than
   or equal now[i][j] and at last answer will be count * now[i][j] + answer of last element in stack.

   note : see comments in code for more clarification.

*/

#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n , m ;
    scanf("%d %d" , &n , &m) ;
    int arr[n+2][m+2] , now[n+2][m+2];
    for(int i = 1 ; i <= n ; ++i)
    {
        for(int j = 1 ; j <= m ; ++j)
            scanf("%d" , &arr[i][j]) ;
    }
    //prepare now for every element
    for(int i = 1 ; i <= n ; ++i)
    {
        now[i][m] = 1ll ;
        for(int j = m-1 ; j >= 1 ; --j)
        {
            if(arr[i][j] == arr[i][j+1])
                now[i][j] = now[i][j+1] + 1ll;
            else
                now[i][j] = 1ll ;
        }
    }
    long long ans = 0ll ;
    long long sol[n+2][m+2] ;
    //loop on every column
    for(int j = 1 ; j <= m ; ++j)
    {
        arr[0][j] = -1 ;
        stack< pair<int , int> >s ;
        for(int i = 1 ; i <= n ; ++i)
        {
            pair<int , int>cur ;
            cur.first = i , cur.second = 1ll ;
            sol[i][j] = 0ll ;
            //new value
            if(arr[i][j] != arr[i-1][j])
            {
                while(!s.empty())
                    s.pop() ;
                sol[i][j] = now[i][j] * 1ll;
                ans += sol[i][j] ;
                s.push(cur) ;
                continue ;
            }
            //loop in stack
            while(!s.empty() && now[s.top().first][j] >= now[i][j])
            {
                pair<int , int>p = s.top() ;
                s.pop() ;
                cur.second += p.second ;
            }
            sol[i][j] = (cur.second * 1ll * now[i][j]) ;
            if(s.size() > 0)
            {
                pair<int , int>p = s.top() ;
                sol[i][j] += sol[p.first][j] ;
            }
            ans += sol[i][j] ;
            s.push(cur) ;
        }
    }
    return printf("%lld" , ans) , 0 ;
}
