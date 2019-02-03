/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest name : COCI 13 contest 5
   problem name : Ladice (COCI 13-Ladice)
   problem link : https://dunjudge.me/analysis/problems/777/

   solution of the problem :
   We see that the way of rule 3 and 4 that Mirko use as DSU..that
   every drawer go to another drawer until go to the root which if it
   visited before then output will be "SMECE"..else if that didn't visit
   then the output is "LADICA" and Union the drawer we use to the another drawer
   every time.
*/

#include <bits/stdc++.h>

using namespace std;

const int MAX = 300010 ;
int par[MAX] , vis[MAX] , sz[MAX];

void init()
{
    for(int i = 1 ; i <= 300000 ; ++i)
        par[i] = i , sz[i] = 1;
}

int root(int node)
{
    if(par[node] == node)
        return node ;
    return (par[node] = root(par[node]));
}

void Union(int x , int y)
{
    int a = root(x) ;
    int b = root(y) ;
    par[a] = b ;
    return ;
}

int main()
{
    init();
    int n , l ;
    cin>>n>>l ;
    while(n--)
    {
        int x , y ;
        cin>>x>>y ;
        int a = root(x) ;
        int b = root(y) ;
        if(!vis[x])
        {
            cout<<"LADICA\n";
            vis[x] = 1 ;
            Union(x , y) ;
        }
        else if(!vis[y])
        {
            cout<<"LADICA\n";
            vis[y] = 1 ;
            Union(y , x) ;
        }
        else if(!vis[a])
        {
            cout<<"LADICA\n";
            vis[a] = 1 ;
            Union(x , y) ;
        }
        else if(!vis[b])
        {
            cout<<"LADICA\n";
            vis[b] = 1 ;
            Union(y , x) ;
        }
        else
        {
            cout<<"SMECE\n";
            continue;
        }
    }
    return 0 ;
}
