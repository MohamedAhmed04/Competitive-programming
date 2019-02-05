/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest name : POI 11
   problem name : Sticks (POI11_PAT - Sticks)
   problem link : https://oj.uz/problem/view/POI11_pat

   problem description :
   we need to find 3 lengths that they have different colors and form
   non-degenerate triangle (has positive area)

   solution of the problem :
   first let's sort lengths of sticks in all colors then loop on all sticks ,
   so for each stick in every color we want to find the closest stick in length that's
   taller than it and another closest stick that's shorter than current stick and in every time
   and make binary search (lowerbound) to find closest stick to current stick (tallest and shortest) and
   try to form triangle with each other and if triangle is formed then print them and their lengths and before
   end of this loop see if their are closer to stick than the integers that there were closest to stick in length before.
   and if we didn't find any thing at end of loop print "NIE".
    - don't forget to handle case if the taller closest stick equal to stick itself so the shorter stick will be equal to taller
      stick equal to stick itself
   note : see my comments in code for more clarification.
*/

#include <bits/stdc++.h>

using namespace std;

const int MAXK = 55 ;
const int MAXN = 1e6+10 ;
int arr[MAXK][MAXN] , sz[MAXK];
int k ;

//Function to see if the lengths may form a non-degenerate triangle
bool is_triangle(long long x , long long y , long long z)
{
    return (x < y+z && y < x + z && z < x+y) ;
}

int main()
{
    int n ;
    cin>>n ;
    for(int i = 0 ; i < n ; ++i)
    {
        cin>>sz[i] ;
        for(int j = 0 ; j < sz[i] ; ++j)
            cin>>arr[i][j] ;
        sort(arr[i] , arr[i] + sz[i]) ;
    }
    for(int i = 0 ; i < n ; ++i)
    {
        for(int i2 = 0 ; i2 < sz[i] ; ++i2)
        {
            //assign current element and two closest sticks and their colors
            long long a = arr[i][i2] ;
            long long l = -1e12 , m = 1e12 , cl = -1 , cm = -1;
            for(int j = 0 ; j < n ; ++j)
            {
                if(i == j)
                    continue;
                //binary search to first stick >= current stick and from that we can find first stick <= current stick
                int high = lower_bound(arr[j] , arr[j] + sz[j] , a) - arr[j] ;
                int low = high-1 ;
                //try to see if we can form triangle with this stick
                if(high != sz[j])
                {
                    if(is_triangle(a*1ll , l*1ll ,  arr[j][high] * 1ll) && cl != -1)
                        return cout<<i+1<<" "<<a<<" "<<cl+1<<" "<<l<<" "<<j+1<<" "<<arr[j][high]<<"\n" , 0 ;
                }
                //handle case if taller equal to stick itself so the shorter will be equal to the stick itself
                if(arr[j][high] == a)
                    low = high ;
                //try to see if we can form triangle with this stick
                if(low >= 0)
                {
                    if(is_triangle(a * 1ll , m  * 1ll , arr[j][low] * 1ll) && cm != -1)
                        return cout<<i+1<<" "<<a<<" "<<cm+1<<" "<<m<<" "<<j+1<<" "<<arr[j][low]<<"\n" , 0 ;
                }
                //see if taller stick closest to current stick
                if(high != sz[j])
                {
                    if(arr[j][high] * 1ll >= a && arr[j][high] * 1ll < m)
                        cm = j , m = arr[j][high] ;
                }
                //see if shorter stick closest to current stick
                if(low >= 0)
                {
                    if(arr[j][low] * 1ll <= a && arr[j][low] * 1ll > l)
                        cl = j , l = arr[j][low] ;
                }
            }
        }
    }
    //if we didn't print any thing above so it will print "NIE".
    return cout<<"NIE\n" , 0 ;
}
