/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest name : BOI 13 (Baltic olympiad in Informatics 2013)
   problem name : Palindrome-Free Numbers (BOI 13-Numbers)
   problem link : https://oj.uz/problem/view/BOI13_numbers

   problem solution :
   we will make digit dp to find number of palindrome free numbers from
   0 to B - number of palindrome free numbers from 0 to (A-1).
   and now a substring from number is palindrome if :
   - the number is same as previous number like 11 so it's palindrome
   - the number is same as previous of previous number.
     like 131 so it's palindrome.
   from that our state is dp[idx][f][f2][prv][prv2]
   where idx is the current idx and f is bool to see if we picked number
   less than the limit before and f2 to tell us if we picked a number or no
   prv is the previous number and prv2 is previous of previous number.

   note : see the comments bellow for more clarification.
*/

#include <bits/stdc++.h>

using namespace std;

long long dp[19][2][2][11][11] ;
vector<int>v ;

//count number of palindromic free numbers of current number
long long cnt(int idx , bool f , bool f2 , int prv , int prv2)
{
    if(idx == v.size())
        return 1 ;
    long long &ret = dp[idx][f][f2][prv][prv2] ;
    if(ret != -1)
        return ret ;
    int LMT ;
    if(f)
        LMT = 9 ;
    else
        LMT = v[idx] ;
    ret = 0ll ;
    for(int i = 0 ; i <= LMT ; ++i)
    {
        int nf = f ;
        int nf2 = f2 ;
        if(i < LMT)
            nf = 1 ;
        if(i == prv || i == prv2)
            continue;
        if(i != 0)
            nf2 = 1 ;
        //if we didn't pick a number before so prv and prv2 will be 10
        if(nf2 == 0)
            ret += cnt(idx+1 , nf , nf2 , 10 , 10) ;
        else
            ret += cnt(idx+1 , nf , nf2 , i , prv) ;
    }
    return ret ;
}

long long solve(long long x)
{
    //handle case when x < 0
    if(x < 0)
        return 0 ;
    v.clear();
    memset(dp , -1 , sizeof(dp)) ;
    while(x > 0)
    {
        v.push_back(x % 10) ;
        x /= 10 ;
    }
    reverse(v.begin() , v.end()) ;
    long long ans = cnt(0 , 0 , 0 , 10 , 10) ;
    return ans ;
}

int main()
{
    long long a , b ;
    cin>>a>>b ;
    return cout<<solve(b) - solve(a-1)<<"\n" , 0 ;
}
