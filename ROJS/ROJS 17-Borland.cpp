/* Author: Mohamed Bakry (handle: MohamedAhmed04)

   problem name: Borland (ROJS 2017-Borland)
   problem link: https://csacademy.com/contest/archive/task/borland/statement/

   Problem's solution:
    my idea is same like Editorial: https://csacademy.com/contest/archive/task/borland/solution/

*/

#include <bits/stdc++.h>

using namespace std ;

const int mod2 = 1e9 + 7 ;
const int MAX = 1e5 + 10 ;

int n , s , a , b , mod , modinv_a ;

int powlog(int base , int power)
{
	if(power == 0)
		return 1 ;
	int x = powlog(base , power / 2) ;
	x = (x * 1ll * x) % mod ;
	if(power & 1)
		x = (x * 1ll * base) % mod ;
	return x ;
}

int Next(int x)
{
	return (a * 1ll * x + b * 1ll) % mod ;
}

int Prev(int x)
{
	int y = (x - b + mod) % mod ;
	return (y * 1ll * modinv_a) % mod ;
}

int solve(int l , int r , int st)
{
	if(l == r)
		return st ;
	if(l > r)
		return 0 ;
	int mid = (l + r) >> 1 ;
	int ans = 0 ;
	int cur = st ;
	for(int i = l+1 ; i <= mid+1 ; ++i)
		cur = Next(cur) ;
	int Max = 0 , idx = mid , now = Prev(cur) ;
	for(int i = mid ; i >= l ; --i)
	{
		cur = Prev(cur) ;
		Max = max(Max , cur) ;
		while(idx < r && Next(now) < Max)
			idx++ , now = Next(now) ;
		int y = (Max * 1ll * (idx - mid + 1)) % mod2 ;
		ans = (ans + y) % mod2 ;
	}
	cur = st ;
	for(int i = l+1 ; i <= mid ; ++i)
		cur = Next(cur) ;
	Max = 0 , idx = mid+1 , now = Next(cur) ;
	for(int i = mid+1 ; i <= r ; ++i)
	{
		cur = Next(cur) ;
		Max = max(Max , cur) ;
		while(idx > l && Prev(now) <= Max)
			idx-- , now = Prev(now) ;
		int y = (Max * 1ll * (mid - idx + 1)) % mod2 ;
		ans = (ans + y) % mod2 ;
	}
	int x = st ;
	for(int i = l+1 ; i <= mid+1 ; ++i)
		x = Next(x) ;
	ans = (ans + solve(l , mid-1 , st)) % mod2 ;
	ans = (ans + solve(mid+1 , r , x)) % mod2 ;
	return ans ;
}

int main()
{
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	cin>>n>>s>>a>>b>>mod ;
	modinv_a = powlog(a , mod-2) ;
	return cout<<solve(1 , n , s)<<"\n" , 0 ;
}		