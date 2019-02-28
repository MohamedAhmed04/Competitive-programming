/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest name : IOI 2010 (day 1)
   problem name : Quality of living (IOI 2010-Quality of living)
   problem statement link :
   https://ioi2010.org/Tasks/Day1/Quality_of_Living.shtml
   link to submit from it :
   https://contest.yandex.ru/ioi/contest/570/enter/

   problem description :
   given grid of R rows and C column that contains elements from 1 to R*C
   return minimum median possible of H*W rectangle inside the grid where
   median is numbers that the number of values smaller than it inside the
   H*W rectangle equal to number of values bigger than it.
   H is odd , W is odd

   problem solution :
   first we will make the grid 1-indexed to be easy for us in prefix array that we will
   make and after that we will binary search of possible values of median and now make
   2 prefix arrays so smaller[i][j] is number of elements in rectangle
   (1 , 1) to (i , j) that's < mid and bigger[i][j] is number of elements in rectangle
   (1 , 1) to (i , j) that's > mid and after that we will loop of all possible rectangles of
   size H*W that we can make and make bool t which will be true if number of elements more than mid
   is <= number of elements that less than median and if that condition is true then r will be equal
   to mid-1 as there's answer less than current mid else then the answer is greater than mid.

   note :
   - the rule to know number of smaller elements than mid in current rectangle is :
     smaller[i+H-1][j+W-1] - smaller[i+H-1][j-1] - smaller[i-1][j+W-1] + smaller[i-1][j-1]
     and role for bigger elements than mid is :
     bigger[i+H-1][j+W-1] - bigger[i+H-1][j-1] - bigger[i-1][j+W-1] + bigger[i-1][j-1]
   - if we found an rectangle which mid is the median then ans is min(ans , mid).
   - see comments bellow for more clarification.

*/

#include "grader.h"
#include <bits/stdc++.h>

using namespace std;

int rectangle(int R, int C, int H, int W, int Q[3001][3001])
{
    int smaller[R+1][C+1] , bigger[R+1][C+1] , arr[R+1][C+1];
    //make grid 1-indexed
    memset(smaller , 0 , sizeof(smaller)) ;
    memset(bigger , 0 , sizeof(bigger)) ;
    for(int i = 1 ; i <= R ; ++i)
    {
        for(int j = 1 ; j <= C ; ++j)
            arr[i][j] = Q[i-1][j-1] ;
    }
    //make binary search and return minimum answer
    int l = 1 , r = R*C , ans = R*C ;
    while(l <= r)
    {
        int mid = (l + r) / 2 ;
        //prepare prefix array
        for(int i = 1 ; i <= R ; ++i)
        {
            int s = 0 , b = 0 ;
            for(int j = 1 ; j <= C ; ++j)
            {
                smaller[i][j] = s + smaller[i-1][j];
                if(arr[i][j] < mid)
                    smaller[i][j]++ , ++s;
                bigger[i][j] = b + bigger[i-1][j] ;
                if(arr[i][j] > mid)
                    bigger[i][j]++ , ++b;
            }
        }
        //loop on all possible rectangles if size H*W.
        bool t = false ;
        for(int i = 1 ; i <= R-H+1 ; ++i)
        {
            for(int j = 1 ; j <= C-W+1 ; ++j)
            {
                int s = smaller[i+H-1][j+W-1] - smaller[i+H-1][j-1] - smaller[i-1][j+W-1] + smaller[i-1][j-1] ;
                int b = bigger[i+H-1][j+W-1] - bigger[i+H-1][j-1] - bigger[i-1][j+W-1] + bigger[i-1][j-1] ;
                if(s >= b)
                    t = true ;
                int n = R*C ;
                if(s == b && s <= n/2 && b <= n/2)
                    ans = min(ans , mid) ;
            }
        }
        if(t == true)
            r = mid-1 ;
        else
            l = mid+1 ;
    }
    return ans ;
}
