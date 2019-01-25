/* Author : Mohamed Ahmed (MohamedAhmed04)

   contest name : COCI 15 contest 4
   problem name : Yoda (COCI 15-Yoda)
   problem link : https://dmoj.ca/problem/coci15c4p1

   just make as problem said and after that remove zeros at first and
   add characters that aren't added in the greater string
*/

#include <bits/stdc++.h>

using namespace std;

string remove_zeros(string s)
{
    string s1 = "" ;
    int idx = s.size() - 1 ;
    for(int i = 0 ; i < s.size() - 1 ; ++i)
    {
        if(s[i] != '0')
        {
            idx = i ;
            break;
        }
    }
    for(int i = idx ; i < s.size() ; ++i)
        s1 += s[i] ;
    return s1 ;
}

int main()
{
    string x , y ;
    cin>>x>>y ;
    string ans1 = "" , ans2 = "" ;
    int idx = min(x.size() , y.size()) ;
    for(int i = 1 ; i <= idx ; ++i)
    {
        if(x[x.size()-i] == y[y.size()-i])
            ans1 += x[x.size()-i] , ans2 += y[y.size()-i];
        else if(x[x.size()-i] > y[y.size()-i])
            ans1 += x[x.size()-i] ;
        else
            ans2 += y[y.size()-i] ;
    }
    for(int i = idx+1 ; i <= x.size() ; ++i)
        ans1 += x[x.size()-i];
    for(int i = idx+1 ; i <= y.size() ; ++i)
        ans2 += y[y.size()-i];
    reverse(ans1.begin() , ans1.end());
    reverse(ans2.begin() , ans2.end());
    if(ans1.size() == 0)
        ans1 = "YODA";
    else
        ans1 = remove_zeros(ans1);
    if(ans2.size() == 0)
        ans2 = "YODA" ;
    else
        ans2 = remove_zeros(ans2);
    return cout<<ans1<<"\n"<<ans2<<"\n" , 0 ;
}
