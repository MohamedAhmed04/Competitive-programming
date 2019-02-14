/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest name : BOI 18 (Baltic olympiad in Informatics 2018)
   problem name : Zalmoxis (BOI 18-zalmoxis)
   problem link : https://oj.uz/problem/view/BOI18_zalmoxis

   problem solution :
   we can think of this problem as tree so number denotes the node
   number and level denote level of current node.
   so everytime if we are in node that's level is the level in the
   vector so we found a node from answer.
   else we will propagate to node * 2 until find nodes the are in answer
   or nodes that split..if there's a node that have one of nodes of its children
   didn't split so we will add it to set which is node that will be added to the
   initial sequence and after that split nodes in the set to k nodes and add them
   to the sequence and after that make recursive function to print nodes.
   note : see comments bellow
*/
#include <bits/stdc++.h>

using namespace std ;

const int MAX = 2e6 + 10 ;
int idx ;
vector<int>v ;
int n , k ;
vector<int>ans ;
set<int>s ;

//the dfs function
void solve(int node , int level)
{
    if(level == v[idx])
    {
        idx++;
        ans.push_back(node) ;
        return ;
    }
    solve(node * 2 , level - 1) ;
    if(idx == v.size() || level <= v[idx])
    {
        s.insert(node * 2 + 1) ;
        return ;
    }
    solve(node * 2 + 1 , level - 1) ;
}

//recursive function to print the elements
void print_solution(int node , int level)
{
    if(binary_search(ans.begin() , ans.end() , node))
    {
        cout<<level<<" ";
        return ;
    }
    print_solution(node * 2 , level - 1) ;
    print_solution(node * 2 + 1 , level - 1) ;
}

int main()
{
    scanf("%d %d" , &n , &k) ;
    for(int i = 0 ; i < n ; ++i)
    {
        int x ;
        scanf("%d" , &x) ;
        v.push_back(x) ;
    }
    //make the dfs
    solve(1 , 30) ;
    //split nodes that we will add to k nodes
    while(s.size() < k)
    {
        int now = *s.begin() ;
        s.erase(now) ;
        s.insert(now * 2) ;
        s.insert(now * 2 + 1) ;
    }
    //add k nodes to the initial sequence
    for(auto &i : s)
        ans.push_back(i) ;
    sort(ans.begin() , ans.end()) ;
    //print nodes
    return print_solution(1 , 30) , 0;
}
