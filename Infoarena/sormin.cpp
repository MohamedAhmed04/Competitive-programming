/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   problem name : Sormin
   problem link : https://www.infoarena.ro/problema/sormin

   Problem's solution:
    since we need to minimize the or so there's bits that we don't want
    it to be in the answer so let mask represents this bits, starting from
    the most significat bit we will add current bit to mask and try to find a
    subset of sum s without choosing any number contains a bit in mask, if we didn't
    find a subset we will erase current bit from the subset.
    to find subset sum we can use bitset, but still it will TLE, since numbers are <= 4000
    so we will represent every number as 1 * a[i], 2*a[i], 4*a[i], ... and apply the idea above.

*/

#include <bits/stdc++.h>

using namespace std ;

const int MAX = 1e5 + 10 ;

int arr[MAX] , freq[5010] ;
int n , s ;

vector< pair<int , int> >vp ;

int main()
{
	freopen("sormin.in" , "r" , stdin) ;
	freopen("sormin.out" , "w" , stdout) ;
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	cin>>n>>s ;
	for(int i = 0 ; i < n ; ++i)
	{
		cin>>arr[i] ;
		freq[arr[i]]++ ;
	}
	for(int i = 0 ; i < n ; ++i)
	{
		if(!freq[arr[i]])
			continue ;
		for(; freq[arr[i]] ;)
		{
			for(int j = 1 ; j <= freq[arr[i]] ; j *= 2)
			{
				vp.emplace_back(arr[i]*j , arr[i]) ;
				freq[arr[i]] -= j ;
			}
		}
	}
	int mask = 0 , ans = 0 ;
	for(int i = 12 ; i >= 0 ; --i)
	{
		mask |= (1 << i) ;
		bitset<50010>bit ;
		bit[0] = 1 ;
		for(auto &j : vp)
		{
			if((j.second & mask))
				continue ;
			bit |= (bit << j.first) ;
		}
		if(!bit[s])
		{
			mask ^= (1 << i) ;
			ans += (1 << i) ;
		}
	}
	vector<int>v ;
	while(s > 0)
	{
		bitset<50010>bit ;
		bit[0] = 1 ;
		for(auto &i : vp)
		{
			if((i.second & mask))
				continue ;
			bit |= (bit << i.first) ;
			if(bit[s])
			{
				s -= i.first ; 
				for(int j = 0 ; j < i.first / i.second ; ++j)
					v.push_back(i.second) ;
				break ;
			}
		} 
	}
	cout<<ans<<" "<<v.size()<<"\n" ;
	for(auto &i : v)
		cout<<i<<" " ;
	cout<<"\n" ;
	return 0 ;
}		