/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   problem name : UVA 11234 - Expressions

   idea of solution of the problem :
   https://github.com/AbdelrahmanRamadan/competitive-programming/blob/master/UVA/11234%20-%20Expressions.cpp
*/

#include <bits/stdc++.h>

using namespace std;

string s ;
vector< vector<int> >adjlist ;

vector< pair<int , int> >order ;

void dfs(int node , int d = 0 , int pos = 1)
{
    order[node] = {-d , pos} ;
    if(adjlist[node].size() > 0)
    {
        dfs(adjlist[node][0] , d+1 , pos * 2) ;
        dfs(adjlist[node][1] , d+1 , pos * 2 + 1) ;
    }
}

bool cmp(int &a , int &b)
{
    return order[a] < order[b] ;
}

int main()
{
    int t ;
    cin>>t ;
    while(t--)
    {
        cin>>s ;
        int n = s.size() ;
        adjlist = vector< vector<int> >(n+2);
        order = vector< pair<int , int> >(n+2) ;
        stack<int>st ;
        for(int i = 0 ; i < n ; ++i)
        {
            if(isupper(s[i]))
            {
                int a = st.top() ;
                st.pop();
                int b = st.top();
                st.pop();
                st.push(i) ;
                adjlist[i].push_back(a) ;
                adjlist[i].push_back(b) ;
            }
            else
                st.push(i);
        }
        dfs(n-1);
        vector<int>v ;
        for(int i = 0 ; i < n ; ++i)
            v.push_back(i) ;
        sort(v.begin() , v.end() , cmp);
        for(int i = 0 ; i < n ; ++i)
            cout<<s[v[i]];
        cout<<"\n";
    }
    return 0 ;
}
