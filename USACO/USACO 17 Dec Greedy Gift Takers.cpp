/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest name : USACO 2017 December contest
   problem name : Greedy Gift Takers (USACO 2017 December Contest, Platinum , Problem 3. Greedy Gift Takers)
   problem link : http://usaco.org/index.php?page=viewproblem2&cpid=770

   problem solution :
   let's take an example first :
   5
   3 2 2 1 1
   so first we will convert array for each index to position after receiving gift
   so array will be : 2 3 3 4 4
   so now let's simulate what will happen :
   1 ) 1 2 3 4 5
   2 ) 2 1 3 4 5
   3 ) 1 3 2 4 5
   4 ) 3 1 2 4 5
   5 ) 1 2 3 4 5
   since there's a cycle now so it will repeat until infinity so 4 and 5 won't receive a gift
   we need now to find shortest prefix such that all will receive gifts and remaining won't receive gifts
   so we will observe two things :
   first if there's an element which is arr[idx] is 1 then there will be a cycle
   if there are two elements which arr[idx] = 2 there will be cycle
   if there are two elements which arr[idx] = 3 and one element value is 2 then there
   will be a cycle , and it will continue
   in example above there are two 3 and one 2 so there are a cycle.
   so two 3 = one 2 , two 2 = one 1..so we will try to loop on prefix until if we combine
   some of elements we will have one at end.
   so now let's use a set which will have all elements from 1 to n , and in each time
   we will erase from set first element <= arr[i[ and if it's 1 then print n - i.
   so in above example if we simulate it :
   1 ) remove first element <= 2 which is 2 : 1 3 4 5
   2 ) remove first element <= 3 which is 3 : 1 4 5
   3 ) remove first element <= 3 which is 1 : print n - i and end program as we arrived to 1.
*/

#include <bits/stdc++.h>

using namespace std;

int main()
{
    freopen("greedy.in" , "r" , stdin) ;
    freopen("greedy.out" , "w" , stdout) ;
    int n ;
    scanf("%d" , &n) ;
    int arr[n+1] ;
    for(int i = 1 ; i <= n ; ++i)
        scanf("%d" , &arr[i]) ;
    for(int i = 1 ; i <= n ; ++i)
        arr[i] = n-arr[i] ;
    set<int>s ;
    for(int i = 1 ; i <= n ; ++i)
        s.insert(i) ;
    for(int i = 1 ; i <= n ; ++i)
    {
        auto it = s.upper_bound(arr[i]) ;
        it-- ;
        if(*it == 1)
            return cout<<n - i<<"\n" , 0 ;
        s.erase(*it) ;
    }
}
