/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   problem name : Classmates 2 (Timus 1362 Classmates 2)
   problem link : http://acm.timus.ru/problem.aspx?space=1&num=1362

   solution of the problem :
     first let's make it as a tree which root is Tanya..so now we have
   a tree which root is Tanya and we need minimum time to go to all nodes
   and parent can't go to two nodes at the same minute
   so let's consider the test case :
   first minute we will visit  : 1
   second minute we will visit : 3 , 4
   third minute we will visit  : 6 , 5
   fourth minute we will visit : 9 , 8 , 7
   fifth minute we will visit  : 10
   so we took 5 minutes to visit them all.
   so now let's try to simulate the solution of the problem.
   it's clear that every time we will go first to the node that have
   highest time.
   so let's make dp[i] which is min time that we will visit all nodes in its
   subtree (minimum time to visit all subtree equal to maximum time of every node in
            its subtree)
   and make cnt which is number of minutes we took to visit next node.
   and to minimize maximum time we will visit nodes that have highest time first.
   and after ending of dfs...print dp[root] which is time to visit all nodes.
   note : see the comments bellow in the code
*/

#include <bits/stdc++.h>

using namespace std;

const int MAX = 100010 ;
int dp[MAX] ;
vector< vector<int> >adjlist ;

void dfs(int node , int parent)
{
    for(auto &child : adjlist[node])
    {
        if(child != parent)
            dfs(child , node);
    }
    dp[node] = 0 ;
    vector<int>v ;
    //add time that every child took to visit its subtree
    for(auto &child : adjlist[node])
    {
        if(child != parent)
            v.push_back(dp[child]);
    }
    //sort according to highest time of child took to visit its subtree
    sort(v.begin() , v.end() , greater<int>() );
    //assign cnt that increases every minute.
    int cnt = 0 ;
    for(int i = 0 ; i < v.size() ; ++i)
    {
        cnt++;
        /*dp[node] is maximum current dp[node] or time of child subtree + minutes we took to
          to go to child */
        dp[node] = max(dp[node] , v[i] + cnt);
    }
    return ;
}

int main()
{
    int n ;
    cin>>n ;
    adjlist = vector< vector<int> >(n+5);
    for(int i = 1 ; i <= n ; ++i)
    {
        int node ;
        while(cin>>node)
        {
            if(node == 0)
                break;
            adjlist[i].push_back(node) ;
            adjlist[node].push_back(i);
        }
    }
    int root ;
    cin>>root ;
    dfs(root , -1);
    return cout<<dp[root]<<"\n" , 0 ;
}
