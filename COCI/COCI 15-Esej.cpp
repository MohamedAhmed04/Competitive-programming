/* Author : Mohamed Ahmed (MohamedAhmed04)
   contest name : COCI 15 contest 3
   problem name : Esej (COCI 15-Esej)
   problem link : https://oj.uz/problem/view/COCI15_esej

   make a string of first 9 characters and loop on all permutations on them
   (Factorial) and if number of strings we print equals the stop which is
   max(a , (b+1)/2) then end the program.
*/

#include <bits/stdc++.h>

using namespace std;

int main()
{
    int a , b ;
    cin>>a>>b ;
    string ans = "" ;
    for(int i = 0 ; i < 9 ; ++i)
        ans += (char)('a' + i) ;
    int stop = max(a , (b+1)/2);
    int cnt = 0 ;
    do
    {
        cout<<ans<<" ";
        cnt++;
        if(cnt == stop)
            return 0 ;
    }
    while(next_permutation(ans.begin() , ans.end()));
}
