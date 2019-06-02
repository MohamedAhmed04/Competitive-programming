/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : IOI 2017 practice session
   problem name : Mountains (IOI2017-Mountains)
   problem link : https://oj.uz/problem/view/IOI17_mountains

   problem solution :
    - we can solve this problem using dp and state is dp[l][r] where it stores
      maximum number of deevs that can be imprisoned in mountains from index l to index r
    - we want to be sure of one thing : no element between l and r can see element between r+1 and n-1
      and no element between l and r can see element from 0 to l-1 (0-indexed)
    - so every time we will have two choices :
        first choice : choose maximum element and partition it so first choice equal to
                       dp[l][idx of maximum - 1] + dp[idx of maximum + 1][r]
        second choice : we will pick maximum element and after that we will loop to partition them so no partition can see maximum element.

        note : see comments in code for more clarification.

*/

#include "mountains.h"
#include <bits/stdc++.h>

using namespace std ;

const int MAX = 2005 ;
int dp[MAX][MAX] ;
int n ;
vector<int>v ;

//function return true if element at b is strictly higher than line between element at a and element at b
bool check(int a,int b,int c)
{
    return 1ll * (v[a]*1ll - v[b] * 1ll) * (a*1ll - c*1ll) > 1ll * (v[a] * 1ll - v[c] * 1ll) * (a * 1ll - b * 1ll);
}

int solve(int l , int r)
{
    //if l > r then return 0 , if l == r then return 1
    if(l >= r)
        return (l == r) ;
    int &ret = dp[l][r] ;
    if(ret != -1)
        return ret ;
    int MAX = 0 , idx = l ;
    for(int i = l ; i <= r ; ++i)
    {
        if(v[i] > MAX)
            MAX = v[i] , idx = i ;
    }
    //first choice
    int choice1 = solve(l , idx-1) + solve(idx+1 , r) ;
    int choice2 = 1;
    //second choice
    int last = idx+1 ;
    //loop from idx of maximum to r and partition them
    for(int i = last ; i <= r ; ++i)
    {
        i = last;
        for(int j = i+1 ; j <= r ; ++j)
        {
            last = j ;
            //v[j] and v[idx] can see each other so we will make partition to [i+1 , j-1]
            if(!check(idx , i , j))
            {
                choice2 += solve(i+1 , j-1) ;
                break;
            }
        }
        //if no element can see idx then make partition from [i+1 , r]
        if(last == r && check(idx , i , r))
            choice2 += solve(i+1 , r) ;
    }
    last = idx-1 ;
    //loop from idx of maximum to l to partition them
    for(int i = last ; i >= l ; --i)
    {
        i = last ;
        for(int j = i-1 ; j >= l ; --j)
        {
            last = j ;
            //v[j] and v[idx] can see each other so we will make partition to [j+1 , i-1]
            if(!check(j , i , idx))
            {
                choice2 += solve(j+1 , i-1) ;
                break;
            }
        }
        //if no element can see idx then make partition from [l , i-1]
        if(last == l && check(l , i , idx))
            choice2 += solve(l , i-1) ;
    }
    //return maximum of choice1 and choice2
    ret = max(choice1 , choice2) ;
    return ret ;
}
int maximum_deevs(vector<int>x)
{
    memset(dp , -1 , sizeof(dp)) ;
    v = x ;
    n = v.size() ;
    return solve(0 , n-1) ;
}
