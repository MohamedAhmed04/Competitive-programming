/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest name : COCI 15 contest 1
   problem name : Karte (COCI 15 -Karte)
   problem link : https://oj.uz/problem/view/COCI15_karte

   make two maps one to see if we current character and value added
   before so print "GRESKA" and another one to count number of different
   values added for each character and at end print
   13 - different values added to each character.
*/


#include <bits/stdc++.h>

using namespace std;

int main()
{
    string s ;
    cin>>s ;
    map< pair<char ,int> , int>mp ;
    map<char , int>ans ;
    for(int i = 0 ; i < s.size() ; ++i)
    {
        if(s[i] >= '0' && s[i] <= '9')
            continue;
        int num = 0 ;
        for(int j = i+1 ; j <= i+2 ; ++j)
            num = num * 10 + (s[j]-'0') ;
        if(mp[{s[i] , num}] == 0)
            mp[{s[i] , num}] = 1 , ans[s[i]]++;
        else
            return cout<<"GRESKA\n" , 0 ;
    }
    return cout<<13 - ans['P']<<" "<<13 - ans['K']<<" "<<13 - ans['H']<<" "<<13 - ans['T']<<"\n" , 0 ;
}
