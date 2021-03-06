/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest name : Codeforces Educational round 59 (CF1107)
   problem name : Brutality (CF1107-Edu-C(Brutality))
   problem link : https://codeforces.com/contest/1107/problem/C
*/

#include <bits/stdc++.h>

using namespace std;

const int MAX = 2e5 + 10 ;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n , k ;
    cin>>n>>k ;
    long long arr[n+1] ;
    for(int i = 0 ; i < n ; ++i)
        cin>>arr[i] ;
    string s ;
    cin>>s ;
    vector<int>v ;
    char c = s[0] ;
    long long ans = 0 ;
    for(int i = 0 ; i < s.size() ; ++i)
    {
        if(s[i] != c)
        {
            sort(v.begin() , v.end() , greater<int>());
            for(int i = 0 ; i < min(k , (int)v.size()) ; ++i)
                ans += v[i];
            v.clear();
            c = s[i] ;
            v.push_back(arr[i]);
        }
        else
            v.push_back(arr[i]);
    }
    sort(v.begin() , v.end() , greater<int>());
    for(int i = 0 ; i < min(k , (int)v.size()) ; ++i)
        ans += v[i];
    return cout<<ans<<"\n" , 0 ;
}
