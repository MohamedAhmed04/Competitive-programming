/* Author : MohamedAhmed (handle : MohamedAhmed04)

   contest name : Baltic olympiad in informatics 2015
   problem name : Network (BOI 15-Network)
   problem link : https://oj.uz/problem/view/BOI15_net

   problem solution :
      https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/Baltic/Baltic-15-net.txt
*/

#include <bits/stdc++.h>

using namespace std;

const int MAX = 500005 ;
int n ;

vector< vector<int> >adj(MAX) ;
stack<int>s ;
vector<int>v ;

void dfs(int node , int par)
{
    if(adj[node].size() == 1)
        v.push_back(node) ;
    for(auto &child : adj[node])
    {
        if(child == par)
            continue;
        dfs(child , node) ;
    }
}


int main()
{
    scanf("%d" , &n) ;
    for(int i = 0 ; i < n-1 ; ++i)
    {
        int x , y ;
        scanf("%d %d" , &x , &y) ;
        adj[x].push_back(y) ;
        adj[y].push_back(x) ;
    }
    int leaves = 0 ;
    for(int i = 1 ; i <= n ; ++i)
    {
        if(adj[i].size() == 1)
            leaves++;
    }
    int start = -1 ;
    for(int i = 1 ; i <= n ; ++i)
    {
        if(adj[i].size() > 1)
        {
            start = i ;
            dfs(start , -1) ;
            break;
        }
    }
    int edges = (leaves + 1) / 2 ;
    cout<<edges<<"\n";
    if(leaves & 1)
    {
        cout<<v[edges-1]<<" "<<start<<"\n";
    }
    for(int i = 0 ; v.size()/2 ; ++i)
    {
        if(i + edges >= v.size())
            break;
        cout<<v[i]<<" "<<v[i+edges]<<"\n";
    }
    return 0 ;
}
