/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest name : APIO 2015
   problem name : Jakarta Skyscrapers (APIO 15-Skyscrapers)
   problem link : https://oj.uz/problem/view/APIO15_skyscraper

   problem solution :
     https://codeforces.com/blog/entry/17717?#comment-226989
*/

#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n , m ;
    scanf("%d %d" , &n , &m) ;
    vector< set<int> >v(n+1) ;
    vector< vector< pair<int , int> > >adj(n+1) ;
    int s , e ;
    for(int i = 0 ; i < m ; ++i)
    {
        int a , b ;
        scanf("%d %d" , &a , &b) ;
        if(i == 0)
            s = a ;
        else if(i == 1)
            e = a ;
        v[a].insert(b) ;
    }
    for(int i = 0 ; i < n ; ++i)
    {
        for(auto &power : v[i])
        {
            for(int j = 1 ; ; ++j)
            {
                int here = i+power*j ;
                if(here >= n)
                    break;
                adj[i].push_back({here , j}) ;
                if(v[here].count(power))
                    break;
            }
            for(int j = 1; ; ++j)
            {
                int here = i-power * j ;
                if(here < 0)
                    break;
                adj[i].push_back({here , j}) ;
                if(v[here].count(power))
                    break;
            }
        }
    }
    priority_queue< pair<int , int> , vector< pair<int , int> > , greater< pair<int , int> > >q ;
    q.push({0 , s}) ;
    int dist[n+2] ;
    for(int i = 0 ; i <= n ; ++i)
        dist[i] = 1e9 ;
    dist[s] = 0 ;
    while(!q.empty())
    {
        pair<int , int> p = q.top();
        q.pop();
        int now = p.second , d = p.first ;
        if(now == e)
            return cout<<d<<"\n" , 0 ;
        if(d > dist[now])
            continue;
        for(auto &i : adj[now])
        {
            int to = i.first ;
            int dist2 = d + i.second ;
            if(dist2 < dist[to])
            {
                dist[to] = dist2 ;
                q.push({dist2 , to}) ;
            }
        }
    }
    return cout<<-1<<"\n" , 0 ;
}
