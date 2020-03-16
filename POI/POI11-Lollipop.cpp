/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : Polish Olympiad in Informatics 2011 (POI 2011)
   problem name : Lollipop (POI11 - Lollipop)
   problem link : https://szkopul.edu.pl/problemset/problem/YPme8cPuC1zbS3oA0euLxywx/site/?key=statement

   Problem's solution :
   - We will preprocess the answers first before taking queries.
   - every number has a window (subarray) for its solution, let ans[i] is a pair such that
     ans[i].first is starting of the window (subarray) and ans[i].second is the ending of the window.
   - for every number, we need the first window such that its sum is i.
   - first bruteforce on first window of sum 1 appears and first window of sum 2 appears.
   - we will try to find ans[i] where i > 2 using ans[i-1], and using ans[i-2] and take the first window.
   - let's take the first case : 
     we want to move the window of ans[i-1] or extend it so the sum is i
     there're 2 cases : 
     1 - arr[ans[i-1].second+1] = 1 then window of ans[i] is (ans[i-1].first , ans[i-1].second+1) 
     2 - arr[ans[i-1].second+1] = 2 then there's 2 cases : 
         A - arr[ans[i-1].first] = 1 then if we extend the mirror to (ans[i-1].first+1 , ans[i-1].second+1)
             sum will be i-1+2-1 = i+1 so we found the window.
         B - arr[ans[i-1].first] = 2 so we will keep moving the window until case 1 happens or case 2A.
             to extend the window in O(1), we realize that we need the nearest 1 (either to ans[i-1].second or ans[i-1].first)
             if there's no 1 then the answer is -1, else then move to the nearest 1 and return the answer.
             (you can see bruteforce way to find the window commented in the code so you will have better understanding of the way
              of doing it in O(1))
   - for the second case there's 1 case only : 
     if arr[ans[i-2].second+1] = 2 then window is (ans[i-2].first , ans[i-2].second+1)
     if arr[ans[i-2].second+1] = 1 then we will find the window anyway in ans[i-1].
   - if no window found then answer for this sum is -1.

*/

#include <bits/stdc++.h>

using namespace std ;

const int MAX = 1e6 + 10 ;

int arr[MAX] , Nxt[MAX] ;
int n , q ;

pair<int , int>ans[2*MAX] ;

bool flag = false ;

pair<int , int>calc(pair<int , int>p , int x)
{
	pair<int , int>ans = p ;
	if(x == 2)
	{
		if(p.first == -1)
			return ans ;
		if(arr[p.second+1] == 2)
			return {p.first , p.second+1} ;
		return {-1 , -1} ;
	}
	if(p.first == -1)
		return ans ;
	p.second++ ;
	int a = min(Nxt[p.second] - p.second , Nxt[p.first] - p.first) ;
	if(p.second+a >= n)
		return {-1 , -1} ;
	else
	{
		if(Nxt[p.second] - p.second == a)
			return {p.first+a , p.second+a} ;
		else
			return {p.first+a+1 , p.second+a} ;
	}
	// bruteforce way to find window of sum x
	/*while(p.second < n)
	{
		if(arr[p.second] == 1)
			return {p.first , p.second} ;
		if(arr[p.second] == 2 && arr[p.first] == 1)
			return {p.first+1 , p.second} ;
		p.first++ , p.second++ ;
	}
	return {-1 , -1} ;*/
}

int main()
{
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	cin>>n>>q ;
	for(int i = 0 ; i < n ; ++i)
	{
		char c ;
		cin>>c ;
		if(c == 'T')
			arr[i] = 2 ;
		else
			arr[i] = 1 ;
	}
	Nxt[n] = 1e9 ;
	for(int i = n-1 ; i >= 0 ; --i)
	{
		Nxt[i] = Nxt[i+1] ;
		if(arr[i] == 1)
			Nxt[i] = i ;	
	}
	ans[1] = ans[2] = {-1 , -1} ;
	for(int i = 0 ; i < n ; ++i)
	{
		if(arr[i] == 1)
		{
			ans[1] = {i , i} ;
			break ;
		}
	}
	for(int i = 0 ; i < n ; ++i)
	{
		if(arr[i] == 2)
		{
			ans[2] = {i , i} ;
			break ;
		}
		if(i < n-1 && arr[i] == arr[i+1])
		{
			ans[2] = {i , i+1} ;
			break ;
		}
	}
	for(int i = 3 ; i < 2*MAX ; ++i)
	{
		ans[i] = calc(ans[i-1] , 1) ;
		pair<int , int>p = calc(ans[i-2] , 2) ;
		if(ans[i].second == -1 || (p.second != -1 && p.second < ans[i].second))
			ans[i] = p ;
	}
	while(q--)
	{
		int x ;
		cin>>x ;
		if(ans[x].first == -1)
			cout<<"NIE\n" ;
		else
			cout<<ans[x].first+1<<" "<<ans[x].second+1<<"\n" ;
	}
	return 0 ;
}		