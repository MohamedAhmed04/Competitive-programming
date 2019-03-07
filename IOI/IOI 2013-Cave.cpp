/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest name : IOI 2013 day 2
   problem name : Cave (IOI 2013-Cave)
   problem link :https://oj.uz/problem/view/IOI13_cave

   problem solution :
   let's first make array s full of zeros and we will run loop to find
   position of switch of door i , and make a query at first :
   if current combination has last > i or last is -1 then we know that it's like
   last combination so we will invert all switches which isn't set to a door ,
   after that we will run a binary search to find the switch which door i is connected to
   and now if we inverted current range [l , mid] if the combination last is > i or -1 , then
   switch is between this range else then switch is in range [mid+1 , r].

   note : see comments for more clarification.

*/

#include "cave.h"
#include <bits/stdc++.h>

using namespace std ;

const int MAX = 5005 ;
int s[MAX] , d[MAX] , arr[MAX] , last , done[MAX];
int now ;

//return true if we invert all switches that isn't connected to door and their combination is -1 or > i
bool check(int l , int mid)
{
    for(int i = l ; i <= mid ; ++i)
    {
        if(done[i])
            continue ;
        s[i] = !s[i] ;
    }
    int x = tryCombination(s) ;
    for(int i = l ; i <= mid ; ++i)
    {
        if(done[i])
            continue;
        s[i] = !s[i] ;
    }
    if(x > now || x == -1)
        return 1 ;
    return 0 ;
}

void exploreCave(int N)
{
    memset(s , 0 , sizeof(s));
    for(int i = 0 ; i < N ; ++i)
    {
        now = i ;
        bool t = false ;
        last = tryCombination(s) ;
        //we need to invert all switches that aren't connected to door.
        if(last > i || last == -1)
        {
            for(int j = 0 ; j < N ; ++j)
            {
                if(done[j])
                    continue;
                s[j] = !s[j] ;
            }
        }
        //binary search to find idx of switch which is connected to door i
        int l = 0 , r = N-1 , ans = N-1;
        while(l <= r)
        {
            int mid = (l + r) / 2 ;
            if(check(l , mid))
                ans = mid , r = mid-1 , t = true;
            else
                l = mid+1 ;
        }
        d[ans] = i ;
        done[ans] = 1 ;
        s[ans] = !s[ans] ;
    }
    answer(s , d) ;
}
