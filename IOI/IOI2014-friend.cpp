/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : IOI 2014 
   problem name : Friend (IOI2014-Friend)
   problem link : https://oj.uz/problem/view/IOI14_friend

   problem's solution :
   	http://blog.brucemerry.org.za/2014/07/

*/

#include "friend.h"
//#include "grader.cpp"
#include <bits/stdc++.h>

using namespace std ;

int findSample(int n,int confidence[],int host[],int protocol[])
{
	int ans = 0 ;
	int val[n] ;
	for(int i = 0 ; i < n ; ++i)
		val[i] = confidence[i] ;
	for(int i = n-1 ; i >= 0 ; --i)
	{
		if(protocol[i] == 0)
		{
			ans += val[i] ;
			val[host[i]] -= val[i] ;
			val[host[i]] = max(0 , val[host[i]]) ;
		}
		else if(protocol[i] == 1)
			val[host[i]] += val[i] ;	
		else if(protocol[i] == 2)
			val[host[i]] = max(val[host[i]] , val[i]) ;
	}
	ans += val[0] ;
	return ans ;
}
