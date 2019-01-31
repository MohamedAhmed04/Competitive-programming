/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest name : Codeforces Educational round 59 (CF1107)
   problem name : Digital root (CF1107-Edu-B(Digital root))
   problem link : https://codeforces.com/contest/1107/problem/B
*/

#include <bits/stdc++.h>

using namespace std;

int main()
{
    int t ;
    cin>>t ;
    while(t--)
    {
        long long k , x ;
        cin>>k>>x ;
        cout<<(k-1ll)*9ll+x<<"\n";
    }
    return 0 ;
}
