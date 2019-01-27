/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest name : Atcoder regular contest 92
   problem name : D - Two sequences (arc092_d - Two sequences)
   problem link : https://atcoder.jp/contests/arc092/tasks/arc092_b

   solution of the problem : first we can handle each bit individually
   so we will loop on all bits and after that we will mod it by 2 * (2 power current bit)
   to get first (current bits+1) from right and after that we will notice that if
   we add element from arra and element from arrb then if their sum is
   (more than or equal (2 power current bit) and less than (2 power current bit) * 2) or
   (more than or equal (2 power current bit)*3 and less than (2 power current bit) * 4)
   then the bit in their sum will be 1...so we will calculate it by binary search to find
   first of the interval and end of the interval and add them to the cnt.
   and now if cnt is odd then add (2 power current bit) in the answer.
*/

#include <bits/stdc++.h>

using namespace std;

const int MAX = 200010 ;
long long a[MAX] , b[MAX] , arra[MAX] , arrb[MAX] ;
int n ;

int leftidx(long long now , long long cur)
{
    int l = 0 , r = n-1 ;
    int ans = n-1 ;
    while(l <= r)
    {
        int mid = (l + r) >> 1 ;
        if(now + arrb[mid] >= cur)
            r = mid-1 , ans = min(ans , mid) ;
        else
            l = mid+1 ;
    }
    return ans ;
}

int rightidx(long long now , long long cur)
{
    int l = 0 , r = n-1 ;
    int ans = 0 ;
    while(l <= r)
    {
        int mid = (l + r) >> 1 ;
        if(now + arrb[mid] <= cur)
            l = mid+1 , ans = max(ans , mid) ;
        else
            r = mid-1 ;
    }
    return ans ;
}

bool check(long long x , long long y)
{
    return (x >= y && x <= y*2-1) ;
}

int main()
{
    cin>>n ;
    for(int i = 0 ; i < n ; ++i)
        cin>>a[i] ;
    for(int i = 0 ; i < n ; ++i)
        cin>>b[i] ;
    long long ans = 0 ;
    for(int i = 0 ; i <= 28 ; ++i)
    {
        long long mod = (1ll << i) * 2 ;
        for(int j = 0 ; j < n ; ++j)
            arra[j] = a[j] % mod , arrb[j] = b[j] % mod ;
        sort(arrb , arrb + n) ;
        int cnt = 0 ;
        for(int j = 0 ; j < n ; ++j)
        {
            int l = leftidx(arra[j] , (1 << i));
            int r = rightidx(arra[j] , (1 << i)*2-1);
            if(check(arra[j] + arrb[l] , (1 << i)) && check(arra[j] + arrb[r] , (1 << i)))
                cnt += r-l+1 ;
            l = leftidx(arra[j] , (1 << i) * 3) ;
            r = rightidx(arra[j] , (1 << i) * 4 - 1) ;
            if(check(arra[j] + arrb[l] , (1 << i)*3) && check(arra[j] + arrb[r] , (1 << i)*3))
                cnt += r-l+1 ;
        }
        if(cnt & 1)
            ans += (1 << i) ;
    }
    return cout<<ans<<"\n" , 0 ;
}
