/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest name : COCI 2016/2017 contest 4
   problem name : Kas (COCI 17-Kas)
   problem link : https://oj.uz/problem/view/COCI17_kas

   problem solution :
   first notice that each time we need to pick or leave and maximize sum of two
   numbers..so we will use dp.
   state is dp[i][j] where i is current idx and j is the difference between two numbers.
   we will start j with value called CONS which will represent 0 so the difference is
   diff - CONS so if it's 99999 it will be -1 , to handle the negative values.
   now each time in dp either we leave current element or take first element to first person and increase
   difference by arr[idx] or decrease it by arr[idx]..and at n we will check if difference is 0 so two numbers
   are same and if it's not we will return very small number.
   after ending dp we will print ans / 2 + sum - ans which is the value that every person will return to home with it.

   note : see my comments below.
*/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 505 ;
const int MAXSUM = 100010 ;
const int CONS = 100000 ;
int arr[MAXN] ;
int dp[MAXN][MAXSUM+CONS] ;
int n ;

//solve function to find maximum sum
int solve(int idx , int diff)
{
    if(idx == n)
    {
        if(diff - CONS == 0)
            return 0 ;
        return -1e8 ;
    }
    int &ret = dp[idx][diff] ;
    if(ret != -1)
        return ret ;
    //leave
    ret = solve(idx+1 , diff) ;
    //pick to first person
    ret = max(ret , solve(idx+1 , diff + arr[idx]) + arr[idx]) ;
    //pick to second person
    ret = max(ret , solve(idx+1 , diff - arr[idx]) + arr[idx]) ;
    return ret ;
}

int main()
{
    memset(dp , -1 , sizeof(dp)) ;
    cin>>n ;
    int sum = 0 ;
    for(int i = 0 ; i < n ; ++i)
    {
        cin>>arr[i] ;
        sum += arr[i] ;
    }
    //sum of values of two persons
    int ans = solve(0 , CONS) ;
    //number that every time the person will return to home with it.
    return cout<<ans/2+sum-ans<<"\n" , 0 ;
}
