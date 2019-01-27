/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest name : COCI 13 contest 1
   problem name : Trener (COCI 13-Trener)
   problem link : https://dmoj.ca/problem/coci13c1p1

   solution of problem : just save first letter of every word in a map
   and loop on all letters and if current letter was first letter of
   >= 5 words then print it and if we didn't print anything then print
   PREDAJA
*/

#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n ;
    cin>>n ;
    map<char , int>mp ;
    for(int i = 0 ; i < n ; ++i)
    {
        string s ;
        cin>>s ;
        mp[s[0]]++;
    }
    bool t = false ;
    for(int i = 0 ; i < 26 ; ++i)
    {
        char c = (char)('a' + i) ;
        if(mp[c] >= 5)
            cout<<c , t = true ;
    }
    if(!t)
        cout<<"PREDAJA";
    return 0 ;
}
