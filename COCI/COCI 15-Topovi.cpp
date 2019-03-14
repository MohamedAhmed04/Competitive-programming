/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest name : COCI 2015 contest 1
   problem name : Topovi (COCI 15-Topovi)
   problem link : https://oj.uz/problem/view/COCI15_topovi

   problem solution :
     if there's a row which have xor x and there's a column which have the
   same xor then the cell which is the intersect of the row and column isn't attacked.
   based on that then on each row which have xor x , number of elements that aren't attacked is
   number of columns that have same xor (x) , and same also for each column have xor x , number of elements
   aren't attacked in it is number of rows have the same xor.
   so now in every update we will subtract from answer the attacked cell and transfer the cell and after that add
   to answer number of new attacked cells.

   note : see comments in code for more clarification.

*/

#include <bits/stdc++.h>

using namespace std;

map< pair<int , int> , long long> mp ;
map<int , long long>rows , columns ;
map<int , long long>rowcnt , columncnt ;

long long n , k , p ;

long long ans = 0ll ;

//the update function
void update(int r , int c , int x)
{
    //subtract number of attacked cells in the old xor
    ans -= (n - rowcnt[columns[c]]) ;
    ans -= (n - columncnt[rows[r]]) ;
    //handle double counting
    if(rows[r] == columns[c])
        ans++ ;
    //transform the cell
    rowcnt[rows[r]]-- ;
    rows[r] ^= x ;
    rowcnt[rows[r]]++;
    columncnt[columns[c]]-- ;
    columns[c] ^= x ;
    columncnt[columns[c]]++ ;
    //add number of attacked cell in the new xor
    ans += (n - rowcnt[columns[c]]) ;
    ans += (n - columncnt[rows[r]]) ;
    //handle double counting
    if(rows[r] == columns[c])
        ans-- ;
    return ;
}

int main()
{
    scanf("%lld %lld %lld" , &n , &k , &p) ;
    rowcnt[0] = columncnt[0] = n ;
    for(int i = 0 ; i < k ; ++i)
    {
        int a , b ;
        long long c ;
        scanf("%d %d %lld" , &a , &b , &c) ;
        mp[{a , b}] = c ;
        update(a , b , c) ;
    }
    while(p--)
    {
        int a , b , c , d ;
        scanf("%d %d %d %d" , &a , &b , &c , &d) ;
        int x = mp[{a , b}] ;
        update(a , b , x) ;
        update(c , d , x) ;
        mp[{c , d}] = x ;
        printf("%lld\n" , ans) ;
    }
    return 0 ;
}
