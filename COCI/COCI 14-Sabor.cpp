/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest name : COCI contest 4
   problem name : Sabor (COCI 14-Sabor)
   problem link : https://dmoj.ca/problem/coci14c4p5

   solution of the problem :
   since it's guaranteed that there's a solution..then we should loop
   on them and see if there's a person that has the same character with more
   than two in their adjlist then we should change their characters and make dfs to
   loop on their children to see if we should change characters of them or no..and at
   end we should print ans of every node.

   note : you should use fast input like scanf and printf because time limit isn't large.
*/

#include <bits/stdc++.h>

using namespace std;

const int MAX = 200010 ;
char ans[MAX] ;
vector< vector<int> >adjlist(MAX) ;
int visited[MAX] ;
int n ;

bool can(int node)
{
    int cnt = 0 ;
    for(auto &child : adjlist[node])
    {
        if(ans[child] == ans[node])
            cnt++;
    }
    return cnt <= 2 ;
}

void dfs(int node)
{
    if(can(node))
        return ;
    visited[node] = 1 ;
    if(ans[node] == 'A')
        ans[node] = 'B' ;
    else
        ans[node] = 'A' ;
    for(auto &child : adjlist[node])
        dfs(child) ;
}

int main()
{
    scanf("%d" , &n) ;
    for(int i = 1 ; i <= 5 ; ++i)
    {
        int m ;
        scanf("%d" , &m) ;
        while(m--)
        {
            int x , y;
            scanf("%d %d" , &x , &y) ;
            adjlist[x].push_back(y) ;
            adjlist[y].push_back(x) ;
        }
    }
    for(int i = 1 ; i <= n ; ++i)
        ans[i] = 'A' ;
    for(int i = 1 ; i <= n ; ++i)
    {
        if(!can(i))
            dfs(i) ;
    }
    for(int i = 1 ; i <= n ; ++i)
        printf("%c" , ans[i]);
    return 0 ;
}
