/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : IOI 2002 day 2
   problem name : Batch Scheduling (IOI 2002 Batch Scheduling)
   problem link : https://dmoj.ca/problem/ioi02p4

   problem solution :
    https://jeffreyxiao.me/blog/convex-hull-trick

*/

#include <bits/stdc++.h>

using namespace std ;

const int MAX = 1e4 + 5 ;

int T[MAX] , F[MAX] , dp[MAX];
int n ;
int s ;

long double calc(int k , int i)
{
    return (((dp[k] * 1.00) - (dp[i]*1.00)) / ((T[k] * 1.00) - (T[i] * 1.00))) ;
}

int main()
{
    scanf("%d %d" , &n , &s) ;
    for(int i = 0 ; i < n ; ++i)
        scanf("%d %d" , &T[i] , &F[i]) ;
    for(int i = n-1 ; i >= 0 ; --i)
    {
        T[i] += T[i+1] ;
        F[i] += F[i+1] ;
    }
    deque<int>q ;
    q.push_back(n) ;
    for(int i = n-1 ; i >= 0 ; --i)
    {
        while(q.size() >= 2 && calc(q[0] , q[1]) < (double)(F[i]))
            q.pop_front() ;
        int j = q.front() ;
        dp[i] = (dp[j] + (s + T[i] - T[j]) * F[i]) ;
        while(q.size() >= 2 && calc(q[q.size() - 2] , q[q.size() - 1]) > calc(q[q.size() - 1] , i))
            q.pop_back() ;
        q.push_back(i) ;
    }
    return printf("%d\n" , dp[0]) , 0 ;
}
