/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest name : COCI 14 contest 3
   problem name : Dom (COCI 14-Dom)
   problem link : https://dmoj.ca/problem/coci14c3p2

   explanation of problem : There are prisoners and there's tv and
   if current channel in tv is hated by anyone so youngest of prisoners
   who hate it turn to his favourite channel..and repeat the process
   until there's channel that isn't hated by anyone or it will repeat until infinity
   so if it will be repeated until infinity print -1 else print number of tv channels
   changes of tv channels until there will be channel that no one hate it.

   problem solution : first we need two arrays fav to store favourite channel
   for everyone and hate to store the first person who hate current channel
   and after that make ans that's number of changes and loop and if we visit this
   channel before then ans is -1 else then if current channel no one hate it so break
   else go to fav channel of youngest person hate current channel

*/

#include <bits/stdc++.h>

using namespace std;

const int MAX = 1e5 + 10 ;
const int inf = 1e9 ;
int hate[MAX] , fav[MAX] ;
int visited[MAX] ;


int main()
{
    for(int i = 0 ; i <= MAX-5 ; ++i)
        hate[i] = inf ;
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n , m , p ;
    cin>>n>>m>>p ;
    for(int i = 1 ; i <= n ; ++i)
    {
        int x , y ;
        cin>>x>>y ;
        fav[i] = x ;
        hate[y] = min(hate[y] , i);
    }
    int ans = -1 ;
    while(true)
    {
        ans++;
        if(visited[p])
        {
            ans = -1 ;
            break;
        }
        visited[p] = 1 ;
        if(hate[p] == inf)
        {
            break ;
        }
        int person = hate[p] ;
        p = fav[person] ;
    }
    return cout<<ans<<"\n" , 0 ;
}
