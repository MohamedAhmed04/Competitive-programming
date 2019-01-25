/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest name : COCI 17 contest 7
   problem name : baza (COCI 17-baza)
   problem link : https://oj.uz/problem/view/COCI17_baza

*/

#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n , m ;
    scanf("%d %d" , &n , &m);
    int arr[n][m] , arr2[m];
    for(int i = 0 ; i < n ; ++i)
    {
        for(int j = 0 ; j < m ; ++j)
            scanf("%d" , &arr[i][j]);
    }
    int q ;
    scanf("%d" , &q);
    while(q--)
    {
        for(int i = 0 ; i < m ; ++i)
            scanf("%d" , &arr2[i]);
        int ans = 0 ;
        for(int i = 0 ; i < n ; ++i)
        {
            bool t = true ;
            for(int j = 0 ; j < m ; ++j)
            {
                if(!t)
                    break;
                if(arr[i][j] != arr2[j] && arr2[j] != -1)
                    t = false ;
            }
            if(t)
                ans++;
        }
        printf("%d\n" , ans);
    }
    return 0 ;
}
