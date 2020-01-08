/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : COCI 2015 contest 3
   problem name : Domino (COCI 15-Domino)
   problem link : https://dmoj.ca/problem/coci15c3p6

   problem's solution : 
    so at first I modeled it as graph problem
	every cell is node
	and there's an edge between every cell (i , j) to (i , j+1) (If exists) with weight val[i][j] + val[i][j+1]
	and there's an edge between every cell(i , j) to (i+1 , j) (If exists) with weight val[i][j] + val[i+1][j]
	the problem now
	we have m edges
	and we want to choose k edges from them (k <= 8) such that no end point appear in more than an edge and summation of weights of edges is maximum
	so I sorted the edges with maximum weights
	and since degree of every node is at most 4
	I picked edges until number of unique pairs is = k.
	and it can be proofed that taking k edges from vector v will make best answer (since I'm sure best k pairs are in the vector)
	after that I made backtracking to choose best possible k edges
	let sz = v.size()
	time complexity O(sz C k + mlogm) and since sz isn't large so it passes fast

*/

#include <bits/stdc++.h>

using namespace std ;

const int MAX = 2010 ;

long long arr[MAX][MAX] , mark[MAX*MAX] , taken[MAX*MAX] ;
int n , k ;

vector< pair<long long , pair<int , int> > >v ;

int index(int x , int y)
{
	return n*x+y ;
}

long long cur = 0ll ;
int sz ;

void solve(int idx , int rem , long long sum)
{
	if(rem == 0)
	{
		cur = max(cur , sum) ;
		return ;
	}
	if(idx == sz)
		return ;
	solve(idx+1 , rem , sum) ;
	if(taken[v[idx].second.first] == 0 && taken[v[idx].second.second] == 0)
	{
		taken[v[idx].second.first] = 1 ;
		taken[v[idx].second.second] = 1 ;
		solve(idx+1 , rem-1 , sum+v[idx].first) ;
		taken[v[idx].second.first] = 0 ;
		taken[v[idx].second.second] = 0 ;
	}
	return ;
}

int main()
{
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	cin>>n>>k ;
	long long sum = 0 ;
	for(int i = 0 ; i < n ; ++i)
	{
		for(int j = 0 ; j < n ; ++j)
		{
			cin>>arr[i][j] ;
			sum += arr[i][j] * 1ll ;
		}
	}
	vector< pair<int , pair<int , int> > >vp ;
	for(int i = 0 ; i < n ; ++i)
	{
		for(int j = 0 ; j < n ; ++j)
		{
			if(j < n-1)
				vp.push_back({arr[i][j] + arr[i][j+1] , {index(i , j) , index(i , j+1)}}) ;
			if(i < n-1)
				vp.push_back({arr[i][j] + arr[i+1][j] , {index(i , j) , index(i+1 , j)}}) ;
		}
	}
	sort(vp.rbegin() , vp.rend()) ;
	int cnt = 0 ;
	for(auto &i : vp)
	{
		v.push_back(i) ;
		if(mark[i.second.first] == 0 && mark[i.second.second] == 0)
			cnt++ ;
		mark[i.second.first] = 1 ;
		mark[i.second.second] = 1 ;
		if(cnt == k)
			break ;
	}
	sz = v.size() ;
	solve(0 , k , 0) ;
	return cout<<sum-cur<<"\n" , 0 ;
}		