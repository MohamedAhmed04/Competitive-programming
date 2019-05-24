/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : COCI 2016 contest 1
   problem name : Cezer (COCI 16-Cezar)
   problem link : https://dmoj.ca/problem/coci16c1p3

   problem solution :
    https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/COCI/official/2017/contest1_solutions/solutions.pdf

*/

#include <bits/stdc++.h>

using namespace std;

vector< vector<int> >adj(28) ;
int vis[28] , st[28] , indegree[28];

bool prefix(string s , string s1)
{
    if(s.size() > s1.size())
        return false ;
    for(int i = 0 ; i < s.size() ; ++i)
    {
        if(s[i] != s1[i])
            return false ;
    }
    return true ;
}

bool cycle(int node)
{
    vis[node] = 1 ;
    st[node] = 1 ;
    for(auto &child : adj[node])
    {
        if(!vis[child])
        {
            if(cycle(child))
                return true ;
        }
        else if(st[child])
            return true ;
    }
    st[node] = 0 ;
    return false ;
}

vector<int>topo ;

void topological_sort(int node)
{
    vis[node] = 1 ;
    for(auto &child : adj[node])
    {
        if(vis[child])
            continue ;
        topological_sort(child) ;
    }
    topo.push_back(node) ;
}

int main()
{
    ios::sync_with_stdio(0) ;
    cin.tie(0) ;
    int n ;
    cin>>n ;
    string words[n] , arr[n];
    for(int i = 0 ; i < n ; ++i)
        cin>>words[i] ;
    for(int i = 0 ; i < n ; ++i)
    {
        int idx ;
        cin>>idx ;
        idx-- ;
        arr[i] = words[idx] ;
    }
    for(int i = 0 ; i < n ; ++i)
    {
        for(int j = 0 ; j < i ; ++j)
        {
            if(prefix(arr[i] , arr[j]))
                return cout<<"NE\n" , 0 ;
        }
    }
    //construct graph
    vector<int>v ;
    for(int i = 0 ; i < n-1 ; ++i)
    {
        int j = i+1 ;
        for(int k = 0 ; k < min(arr[i].size() , arr[j].size()) ; ++k)
        {
            if(arr[i][k] != arr[j][k])
            {
                int c = arr[i][k] - 'a' , c2 = arr[j][k] - 'a' ;
                adj[c2].push_back(c) ;
                indegree[c]++ ;
                break;
            }
        }
    }
    for(int i = 0 ; i < 26 ; ++i)
    {
        if(vis[i] == 0)
        {
            if(cycle(i))
                return cout<<"NE\n" , 0 ;
        }
    }
    cout<<"DA\n";
    memset(vis , 0 , sizeof(vis)) ;
    for(int i = 0 ; i < 26 ; ++i)
    {
        if(indegree[i] == 0 && vis[i] == 0)
            topological_sort(i) ;
    }
    string ans = string("" , 26) ;
    for(int i = 0 ; i < 26 ; ++i)
    {
        ans[topo[i]] = (char)(i+'a') ;
    }
    cout<<ans<<"\n" ;
    return 0 ;
}
