/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest name : POI 2010
   problem name : Sums (PO10 - Sums)
   problem link :
   https://szkopul.edu.pl/problemset/problem/4CirgBfxbj9tIAS2C7DWCCd7/site/?key=statement

   problem solution :
     if we can make sum value is x % arr[0] then we can make sum value x ,
   from this observation , our problem will be find shortest cost to make all values
   of x % arr[0] , so we will run dijkstra and we won't go to states that their cost is more than 10^9.

*/

#include <bits/stdc++.h>

using namespace std;

const int MAX = 50005 ;
int vis[MAX] , arr[MAX] , vis2[MAX];
int n ;
void dijkstra()
{
    for(int i = 0 ; i <= 50000 ; ++i)
        vis[i] = 1e9+10 ;
    priority_queue< pair<int , int> , vector< pair<int , int> > , greater< pair<int , int> > >q ;
    q.push({0 , 0}) ;
    vis[0] = 0 ;
    while(!q.empty())
    {
        pair<int , int>p = q.top();
        q.pop();
        int now = p.first , cur = p.second ;
        if(vis[cur] < now)
            continue;
        if(vis2[cur] == 1)
            continue ;
        vis2[cur] = 1 ;
        for(int i = 0 ; i < n ; ++i)
        {
            int now2 = now + arr[i] ;
            int cur2 = (cur + arr[i]) % arr[0] ;
            if(now2 < vis[cur2] && now2 <= 1e9)
            {
                vis[cur2] = now2 ;
                q.push({now2 , cur2}) ;
            }
        }
    }
    return ;
}

int main()
{
    scanf("%d" , &n) ;
    for(int i = 0 ; i < n ; ++i)
        scanf("%d" , &arr[i]) ;
    sort(arr , arr + n) ;
    dijkstra();
    int q ;
    scanf("%d" , &q);
    while(q--)
    {
        int x ;
        scanf("%d" , &x);
        if(vis[x % arr[0]] <= x)
            puts("TAK");
        else
            puts("NIE");
    }
    return 0 ;
}
