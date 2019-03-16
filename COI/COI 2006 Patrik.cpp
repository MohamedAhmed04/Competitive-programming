/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest name : COI 2006
   problem name : Patrik (COI 2006 problem 1 Patrik)
   problem link : https://dmoj.ca/problem/coi06p1

   problem solution :
   we will make monotonic stack that's decreasing and make stack of pair
   to handle equal elements.

   note : to learn monotonic stack/queue :
   https://medium.com/algorithms-and-leetcode/monotonic-queue-explained-with-leetcode-problems-7db7c530c1d6

*/

#include <bits/stdc++.h>

using namespace std ;

int main()
{
    int n ;
    scanf("%d" , &n) ;
    int arr[n] ;
    for(int i = 0 ; i < n ; ++i)
        scanf("%d" , &arr[i]) ;
    stack< pair<int , int> >s ;
    long long ans = 0ll ;
    for(int i = 0 ; i < n ; ++i)
    {
        int now = 1 ;
        while(s.size() > 0 && s.top().first <= arr[i])
        {
            ans += (s.top().second * 1ll) ;
            if(s.top().first == arr[i])
                now += s.top().second ;
            s.pop() ;
        }
        if(s.size())
            ans++ ;
        s.push({arr[i] , now}) ;
    }
    return printf("%lld" , ans) , 0 ;
}
