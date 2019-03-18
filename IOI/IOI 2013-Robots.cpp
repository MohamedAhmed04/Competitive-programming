/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest name : IOI 2013 day 2
   problem name : Robots (IOI 2013-Robots)
   problem link : https://oj.uz/problem/view/IOI13_robots

   problem solution :
   http://blog.brucemerry.org.za/2013/07/

   note : see the comments below .
*/

#include "robots.h"
#include <bits/stdc++.h>

using namespace std ;

const int MAX = 50005 ;

int n , m ;

int Weight[MAX] , Size[MAX] ;

vector< vector<int> >appear ;

//the check function that return true if robots can put away toys in mid second and otherwise it will return false
bool check(int mid)
{
    priority_queue<int>q ;
    //put away toys using weak robots.
    for(int i = 0 ; i < n ; ++i)
    {
        for(int j = 0 ; j < appear[i].size() ; ++j)
            q.push(appear[i][j]) ;
        int sz = q.size() ;
        for(int j = 0 ; j < min(sz , mid) ; ++j)
            q.pop() ;
    }
    //handle case for toys that their weight is more than all weak robots weight.
    for(int j = 0 ; j < appear[n].size() ; ++j)
        q.push(appear[n][j]) ;
    //put away remaining toys using small robots.
    for(int i = 0 ; i < m ; ++i)
    {
        int sz = q.size() ;
        for(int j = 0 ; j < min(sz , mid) ; ++j)
        {
            int a = q.top() ;
            if(a >= Size[i])
                break;
            q.pop() ;
        }
    }
    if(q.empty())
        return 1 ;
    return 0 ;
}

int putaway(int A , int B , int T , int X[] , int Y[] , int W[] , int S[])
{
    for(int i = 0 ; i < A ; ++i)
        Weight[i] = X[i] ;
    for(int i = 0 ; i < B ; ++i)
        Size[i] = Y[i] ;
    sort(Weight , Weight + A) ;
    sort(Size , Size + B) ;
    n = A , m = B ;
    appear.resize(A+1) ;
    for(int i = 0 ; i < T ; ++i)
    {
        int idx1 = upper_bound(Weight , Weight + A , W[i]) - Weight ;
        int idx2 = upper_bound(Size , Size + B , S[i]) - Size ;
        //if current toy weight is bigger than weight of all weak robots and its size is more than size of all small robots
        if(idx1 == A && idx2 == B)
            return -1 ;
        appear[idx1].push_back(S[i]) ;
    }
    reverse(Size , Size + B) ;
    //sort sizes that's inside every vector in appear in decreasing order
    for(int i = 0 ; i <= n ; ++i)
    {
        if(appear[i].size() == 0)
            continue ;
        sort(appear[i].begin() , appear[i].end() , greater<int>());
    }
    //make binary search
    int l = 1 , r = T , ans;
    while(l <= r)
    {
        int mid = (l + r) / 2 ;
        if(check(mid))
            r = mid-1 , ans = mid;
        else
            l = mid+1 ;
    }
    return ans ;
}
