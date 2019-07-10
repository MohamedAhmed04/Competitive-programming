/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : Polish Olympiad in Informatics 2010/2011 (POI 2011)
   problem name : POI11-Conductor (POI11_pio - Conductor)
   problem link : https://oj.uz/problem/view/POI11_pio

   problem's solution :
    since we want following inequality to be hold in all elements :
    h[j] <= h[i] + p - ceil(sqrt(abs(i - j)))
    h[j] + ceil(sqrt(abs(i - j))) <= h[i] + p
    and since we want to minimize p then
    p = max(0 , h[j] + ceil(sqrt(abs(i - j))) - h[i])
    then we want at every i to find maximum value of h[j] + ceil(sqrt(abs(i - j)))
    so for every element we will loop and for every start of new value of ceil(sqrt(abs(i - j)))
    we will make it max(new value , its old value).
    and do same for suffix.
    we will observe that we need to loop to update value if current element is > max element in elements before it.
    and after loop on prefix array and suffix array and make
    prefix[i] = max(prefix[i-1] , prefix[i])
    suffix[i] = max(suffix[i+1] , suffix[i])
    and print max(prefix[i] , suffix[i]) - arr[i]).

note : if you didn't understand above explanation well see the code for more clarification.

*/

#include <bits/stdc++.h>

using namespace std ;

const int MAX = 5e5 + 5 ;

int arr[MAX] , pref[MAX] , suff[MAX];

int n ;

int main()
{
	scanf("%d" , &n) ;
	for(int i = 0 ; i < n ; ++i)
		scanf("%d" , &arr[i]) ;
	int MAX = -1 ;
	for(int i = 0 ; i < n ; ++i)
	{
		if(arr[i] <= MAX)
			continue ;
		MAX = arr[i] ;
		for(int j = 1 ; i + (j-1) * (j-1) + 1 < n ; ++j)
		{
			pref[i + (j-1) * (j-1) + 1] = max(pref[i + (j-1) * (j-1) + 1] , arr[i] + j) ;
		}
	}
	MAX = -1 ;
	for(int i = n-1 ; i >= 0 ; --i)
	{
		if(arr[i] <= MAX)
			continue ;
		MAX = arr[i] ;
		for(int j = 1 ; i - (j-1) * (j-1) - 1 >= 0 ; ++j)
		{
			suff[i - (j-1) * (j-1) - 1] = max(suff[i - (j-1) * (j-1) - 1] , arr[i] + j) ;
		}
	}
	for(int i = 1 ; i < n ; ++i)
		pref[i] = max(pref[i] , pref[i-1]) ;
	for(int i = n-2 ; i >= 0 ; --i)
		suff[i] = max(suff[i] , suff[i+1]) ;
	for(int i = 0 ; i < n ; ++i)
		printf("%d\n" , max(0 , max(pref[i] , suff[i]) - arr[i])) ;
	return 0 ;
}
