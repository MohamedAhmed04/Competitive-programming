/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   problem name : eq (Easy Query)
   problem link : https://infoarena.ro/problema/eq

   problem's solution :
    - first realize that maximum number in range [l , r] will always be in Y answer 
      and minimum number in range [l , r] will always be in Z answer.
    - then now answer for array Y will be maximum number + maximum difference in range [l, r] where larger
      number become first.
    - same for Z but we need to know minimum difference between two numbers (difference can be negative.)
    - to find maximum/minimum difference, we can make segment tree and every node carry 4 informations : 
      maximum number in range of node
      minimum number in range of node
      maximum difference between two numbers in range of node
      minimum difference between two numbers in range of node
    - to merge values of two nodes then.
      maximum number = max(max number in first node , max number in second node)
      minimum number = min(min number in first node , min number in second node)
      maximum difference = max(max difference in first node,
                               max difference in second node,
                               max number in first node - min number in second node)
      mininmum difference = min(min difference in first node,
                                min difference in second node,
                                min number in first node - max number in second node)  

*/


#include <bits/stdc++.h>

using namespace std ;

const int MAX = 1e5 + 10 ;

struct Node
{
	int Max = -1e9 , Min = 1e9 , Maxdiff = 0 , Mindiff = 0 ;
};

int arr[MAX] ;
Node tree[4 * MAX] ;
int n , q ;

Node Merge(Node a , Node b)
{
	Node x ;
	x.Max = max(a.Max , b.Max) ;
	x.Min = min(a.Min , b.Min) ;
	x.Maxdiff = max(a.Maxdiff , b.Maxdiff) ;
	x.Maxdiff = max(x.Maxdiff , a.Max - b.Min) ;
	x.Mindiff = min(a.Mindiff , b.Mindiff) ;
	x.Mindiff = min(x.Mindiff , a.Min - b.Max) ;
	return x ;
}

void build(int node , int l , int r)
{
	if(l == r)
	{
		tree[node].Max = tree[node].Min = arr[l] ;
		return ;
	}
	int mid = (l + r) >> 1 ;
	build(node << 1 , l , mid) ;
	build(node << 1 | 1 , mid+1 , r) ;
	tree[node] = Merge(tree[node << 1] , tree[node << 1 | 1]) ;
}

Node tmp ;

Node query(int node , int l , int r , int from , int to)
{
	if(from > r || to < l)
		return tmp ;
	if(l >= from && r <= to)
		return tree[node] ;
	int mid = (l + r) >> 1 ;
	return Merge(query(node << 1 , l , mid , from , to) , query(node << 1 | 1 , mid+1 , r , from , to)) ;
}

int main()
{
	freopen("eq.in" , "r" , stdin) ;
	freopen("eq.out" , "w" , stdout) ;
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	cin>>n>>q ;
	for(int i = 1 ; i <= n ; ++i)
		cin>>arr[i] ;
	build(1 , 1 , n) ;
	while(q--)
	{
		int l , r ;
		cin>>l>>r ;
		Node ans = query(1 , 1 , n , l , r) ;
		cout<<ans.Maxdiff + ans.Max + ans.Mindiff + ans.Min<<"\n" ;
	}
	return 0 ;
}		