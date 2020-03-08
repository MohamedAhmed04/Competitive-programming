/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : USACO 2017 February Platinum
   problem name : Why Did The Cow Cross The Road III
   problem link : http://usaco.org/index.php?page=viewproblem2&cpid=722

   Problem's solution : 
    - First realize that: 
      number of unfriendly crossing pairs = number of crossing pairs - number of friendly crossing pairs.
    - let pos1[i] is position of i in first array
      and pos2[i] is position of i in second array
      then a pair (i , j) is crossing pair if :
      (pos1[i] < pos1[j]) != (pos2[i] < pos2[j])
    - so if we iterate on the second array then at each iteration we can 
      add to the answer
                         N
      					---
                        \    val[j]
                        /
                        ---
                        j = pos1[arr2[i]]
    
      and then val[pos1[arr2[i]]] = 1
    - and to find number of friendly pairs we need to add to answer
      number of j such that j > pos1[arr2[i]] and j <= N and arr2[i]-k <= arr1[j] <= arr2[i]+k
    - so we need a data structure that can handle type of this 2 queries efficiently : 
      1 - update a value at a position
      2 - given L , R , A , B 
          find number of j that satisfy
          L <= j <= R and A <= arr1[j] <= B
	  so we can handle this query by doing 2D segment tree but I did segment tree which every node
	  carries Binary indexed tree to make it faster and have better constant factor.

    - here some other implementations/ideas to solve the problem :
        https://codeforces.com/blog/entry/50329

*/



#include <bits/stdc++.h>

using namespace std ;

struct BIT
{
	vector<int>v ;
	vector<long long> tree ;
	int sz ;
	bool flag ;
	void init(vector<int>v2)
	{
		sz = (int)v2.size() ;
		v = v2 ;
		sort(v.begin() , v.end()) ;
		tree.resize(sz+5) ;
		for(int i = 0 ; i <= sz ; ++i)
			tree[i] = 0 ;
	}
	int getidx1(int idx)
	{
		int idx2 = lower_bound(v.begin() , v.end() , idx) - v.begin() ;
		return idx2 ;
	}
	int getidx2(int idx)
	{
		int idx2 = upper_bound(v.begin() , v.end() , idx) - v.begin() ;
		idx2-- ;
		return idx2 ;
	}
	
	void upd(int idx , int val)
	{
		for(int i = idx ; i <= sz ; i += i & -i)
			tree[i] += val * 1ll ;
	}
 
	void update(int idx , int val)
	{
		idx = getidx1(idx) ;
		upd(idx+1 , val) ;
	}

	int query(int idx)
	{
		if(idx <= 0)
			return 0 ;
		long long sum = 0 ;
		for(int i = idx ; i > 0 ; i -= i & -i)
			sum += tree[i] ;
		return sum ;
	}

	int query(int idx , int idx2)
	{
		idx = getidx1(idx) ;
		idx2 = getidx2(idx2) ;
		return (query(idx2+1) - query(idx)) ;
	}
};

const int MAX = 1e5 + 5 ;

int arr[2][MAX] , pos[2][MAX] ;

int n , k ;

BIT tree[4 * MAX] ;

vector<int>v[4 * MAX] ;
 
void pre(int node , int l , int r , int idx , int val)
{
	if(l > idx || r < idx)
		return ;
	v[node].push_back(val) ;
	if(l == r)
		return ;
	int mid = (l + r) >> 1 ;
	pre(node << 1 , l , mid , idx , val) ;
	pre(node << 1 | 1 , mid+1 , r , idx , val) ;
}

void update(int node , int l , int r , int idx , int val)
{
	if(l > idx || r < idx)
		return ;
	tree[node].update(val , 1) ;
	if(l == r)
		return ;
	int mid = (l + r) >> 1 ;
	update(node << 1 , l , mid , idx , val) ;
	update(node << 1 | 1 , mid+1 , r , idx , val) ;
}
 
long long query(int node , int l , int r , int from , int to , int x , int y)
{
	if(from > r || to < l)
		return 0 ;
	if(l >= from && r <= to)
		return tree[node].query(x , y) ;
	int mid = (l + r) >> 1 ;
	long long a = query(node << 1 , l , mid , from , to , x , y) ;
	long long b = query(node << 1 | 1 , mid+1 , r , from , to , x , y) ;
	return (a+b) ;
}

void init_values()
{
	for(int i = 1 ; i < MAX * 4 ; ++i)
	{
		if(v[i].size())
			tree[i].init(v[i]) ;
	}
	return ;
}

int main()
{
	freopen("friendcross.in" , "r" , stdin) ;
	freopen("friendcross.out" , "w" , stdout) ;
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	cin>>n>>k ;
	for(int i = 0 ; i < 2 ; ++i)
	{
		for(int j = 1 ; j <= n ; ++j)
		{
			cin>>arr[i][j] ;
			pos[i][arr[i][j]] = j ;
		}
	}
	long long cnt = 0 , cnt2 = 0 ;
	for(int i = 1 ; i <= n ; ++i)
		pre(1 , 1 , n , pos[0][arr[1][i]] , arr[1][i]) ;
	init_values() ;
	for(int i = 1 ; i <= n ; ++i)
	{
		cnt += query(1 , 1 , n , pos[0][arr[1][i]] , n , 1 , n) ;
		cnt2 += query(1 , 1 , n , pos[0][arr[1][i]] , n , max(1 , arr[1][i]-k) , min(n , arr[1][i]+k)) ;
		update(1 , 1 , n , pos[0][arr[1][i]] , arr[1][i]) ;
	}
	return cout<<cnt-cnt2<<"\n" , 0 ;
}