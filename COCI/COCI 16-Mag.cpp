/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : COCI 2016 contest 1
   problem name : mag (COCI 16-Mag)
   problem link : https://oj.uz/problem/view/COCI16_mag

   Problem's Solution : 
    https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/COCI/official/2017/contest1_solutions/solutions.pdf

*/

#include <bits/stdc++.h>

using namespace std ;

const int MAX = 1e6 + 10 ;

int arr[MAX] , dpdown[MAX] , dpup[MAX] ;
int n ;

vector< vector<int> >adj(MAX) ;

int Max = 0 ;

void dfs(int node , int par)
{
	if(arr[node] == 1)
		dpdown[node] = 1 ;
	else
		dpdown[node] = 0 ;
	int a = 0 , b = 0 ;
	for(auto &child : adj[node])
	{
		if(child == par)
			continue ;
		dfs(child , node) ;
		if(dpdown[node])
		{
			dpdown[node] = max(dpdown[node] , dpdown[child]+1) ;
			if(dpdown[child] > a)
				b = a , a = dpdown[child] ;
			else if(dpdown[child] > b)
				b = dpdown[child] ;
		}
	}
	if(arr[node] == 1)
		Max = max(Max , a+b+1) ;
}

bool flag = false ;

void dfs2(int node , int par)
{
	int cnt = 0 ;
	for(auto &child : adj[node])
	{
		if(child == par)
			continue ;
		dfs2(child , node) ;
		if(arr[node] == 2)
			cnt += (dpdown[child] == Max) ;
	}
	if(cnt > 1)
		flag = true ;
	return ;
}

void dfs3(int node , int par , int best)
{
	dpup[node] = best + 1 ;
	if(arr[node] != 1)
	{
		dpup[node] = 0 ;
		for(auto &child : adj[node])
		{
			if(child == par)
				continue ;
			dfs3(child , node , 0) ;
		}
		if(arr[node] == 2)
		{
			for(auto &child : adj[node])
			{
				if(child == par)
					continue ;
				if(dpdown[child] == Max && best == Max)
					flag = true ;
			}
		}
		return ;
	}
	int mx = dpup[node] , c = node ;
	for(auto &child : adj[node])
	{
		if(child == par)
			continue ;
		if(dpdown[child]+1 > mx)
			mx = dpdown[child]+1 , c = child ;
	}
	for(auto &child : adj[node])
	{
		if(child == par)
			continue ;
		if(c != child)
			dfs3(child , node , mx) ;
		else
		{
			int mx2 = dpup[node] ;
			for(auto &child2 : adj[node])
			{
				if(child2 == par || child == child2)
					continue ;
				if(dpdown[child2]+1 > mx2)
					mx2 = dpdown[child2]+1 ;
			}
			dfs3(child , node , mx2) ;
		}
	}
	return ;
}

int main()
{
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	cin>>n ;
	for(int i = 0 ; i < n-1 ;  ++i)
	{
		int x , y ;
		cin>>x>>y ;
		adj[x].push_back(y) ;
		adj[y].push_back(x) ;
	}
	int cnt = 0 ;
	for(int i = 1 ; i <= n ; ++i)
	{
		cin>>arr[i] ;
		cnt += (arr[i] == 1) ;
	}
	if(!cnt)
		return cout<<*min_element(arr+1 , arr+n+1)<<"/"<<1<<"\n" , 0 ;
	dfs(1 , -1) ;
	int ans = Max ;
	dfs2(1 , -1) ;
	dfs3(1 , -1 , 0) ;
	if(flag == true)
		return cout<<2<<"/"<<ans*2+1<<"\n" , 0 ;
	else
		return cout<<1<<"/"<<ans<<"\n" , 0 ;
}		