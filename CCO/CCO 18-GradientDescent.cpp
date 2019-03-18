/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest name : CCO 2018
   problem name : Gradient Descent (CCO 18-Gradient Descent)
   problem link : https://dmoj.ca/problem/cco18p4

   problem solution :
     we notice that the values are increasing until a point then it's decreasing
   or it's decreasing at a point then increasing , so we can solve it using ternary search.
   but if we make two ternary searches : one for rows and another for columns we won't get the
   full score as we will ask many queries in last subtask.
   so to fix that we will make one ternary search which inside it there's two starting and ending points :
   one for row and another for column.
   and now maximum number of queries is 3 queries per each iteration and in query function we need also to make
   map of pairs so that we won't ask multiple queries on the same cell.

   note : see the comments below for more clarifications.

*/

#include <bits/stdc++.h>

using namespace std;

map< pair<int , int> , int>mp , mp2;
int n , m , k;

//query function.
int query(int row , int column)
{
    int r = row , c = column ;
    int ret = 0 ;
    //handle if query isn't in range ([1 , n][1 , m])
    if(row < 1 || row > n)
    {
        if(row < 1)
            row++ , ret += 1e8;
        else
            row-- , ret += 1e8;
    }
    if(column < 1 || column > m)
    {
        if(column < 1)
            column++ , ret += 1e8 ;
        else
            column-- , ret += 1e8 ;
    }
    //handle multiple queries
    if(mp2[{row , column}] == 1)
        return (ret + mp[{row , column}]) ;
    if(mp2[{r , c}] == 1)
        return (mp[{r , c}]) ;
    //make query and store it.
    mp2[{r , c}] = 1 ;
    mp2[{row , column}] = 1 ;
    cout<<"? "<<row<<" "<<column<<endl ;
    int x ;
    cin>>x ;
    mp[{row , column}] = x ;
    mp[{r , c}] = ret + x ;
    return (mp[{r , c}]) ;
}

int main()
{
    cin>>n>>m>>k ;
    //make ternary search
    int l1 = -1 , r1 = n+1 ;
    int l2 = -1 , r2 = m+1 ;
    while(r1 - l1 > 1 || r2 - l2 > 1)
    {
        int mid1 = (l1 + r1) / 2 ;
        int mid2 = (l2 + r2) / 2 ;
        int a = query(mid1 , mid2) ;
        int b = query(mid1+1 , mid2) ;
        int c = query(mid1 , mid2+1) ;
        if(a < b)
            r1 = mid1 ;
        else
            l1 = mid1 ;
        if(a < c)
            r2 = mid2 ;
        else
            l2 = mid2 ;
    }
    int row = l1+1 , column = l2+1 ;
    cout<<"! "<<query(row , column)<<endl ;
    return 0 ;
}
