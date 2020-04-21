/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : Polish Olympiad In Informatics (POI) 2018
   problem name : Plan Metra (POI 2018-Plan Metra)
   problem link : https://szkopul.edu.pl/problemset/problem/vvd6w7n7EXFVEg3nkqGxEirV/site/?key=statement

   Problem's solution:
   - Let's root the tree at 1 so there will be 2 cases:
      1- N is direct child of 1
      2- N isn't direct child of 1
   - for the first case, N is child of 1 if abs(a[i] - b[i]) is constant for all 2 <= i <= n-1 and abs(a[i] - b[i]) != 0
   - for the second case: there will be a path from 1 to N and nodes in path is the nodes have minimum a[i] + b[i], and then put
     other nodes as children to the nodes in this path, a node j will be child of node i in the path if a[i] - b[i] = a[j] - b[j].

*/

#include <bits/stdc++.h>

using namespace std ;

const int MAX = 5e5 + 10 ;

int a[MAX] , b[MAX] ;
int n ;

int main()
{
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	cin>>n ;
	for(int i = 2 ; i <= n-1 ; ++i)
		cin>>a[i] ;
	for(int i = 2 ; i <= n-1 ; ++i)
		cin>>b[i] ;
	bool flag = true ;
	for(int i = 3 ; i <= n-1 ; ++i)
		flag &= (abs(a[i] - b[i]) == abs(a[i-1] - b[i-1])) ;
	if(flag && a[2] != b[2])
	{
		cout<<"TAK\n" ;
		cout<<1<<" "<<n<<" "<<abs(a[2] - b[2])<<"\n" ;
		for(int i = 2 ; i <= n-1 ; ++i)
		{
			if(a[i] < b[i])
				cout<<1<<" "<<i<<" "<<a[i]<<"\n" ;
			else
				cout<<n<<" "<<i<<" "<<b[i]<<"\n"  ;
		}
		return 0 ;
	}
	int Min = 2e9 ; 
	for(int i = 2 ; i <= n-1 ; ++i)
		Min = min(Min , a[i] + b[i]) ;
	vector< pair<int , int> >vp ;
	map<int , int>mp ;
	a[1] = 0 , a[n] = Min ;
	b[1] = Min , b[n] = 0 ;
	mp[-Min] = 1 ;
	mp[Min] = n ;
	for(int i = 2 ; i <= n-1 ; ++i)
	{
		if(a[i] + b[i] == Min)
		{
			mp[a[i] - b[i]] = i ;
			vp.emplace_back(a[i] , i) ;
		}
	}
	for(int i = 2 ; i <= n-1 ; ++i)
	{
		if(a[i] + b[i] == Min)
			continue ;
		if(mp.find(a[i] - b[i]) == mp.end())
			return cout<<"NIE\n" , 0 ;
		int idx = mp[a[i] - b[i]] ;
		if(a[i] <= a[idx] || b[i] <= b[idx])
			return cout<<"NIE\n" , 0 ;
	}
	sort(vp.begin() , vp.end()) ;
	int prv = 1 , prv2 = 0 ;
	for(auto &i : vp)
	{
		if(i.first - prv2 <= 0)
			return cout<<"NIE\n" , 0 ; 
		prv = i.second ;
		prv2 = i.first ;
	}
	cout<<"TAK\n" ;
	prv = 1 , prv2 = 0 ;
	for(auto &i : vp)
	{
		cout<<prv<<" "<<i.second<<" "<<i.first - prv2<<"\n" ;
		prv = i.second ;
		prv2 = i.first ;
	}
	assert(Min != prv2) ;
	cout<<prv<<" "<<n<<" "<<Min-prv2<<"\n" ;
	for(int i = 2 ; i <= n-1 ; ++i)
	{
		if(a[i] + b[i] == Min)
			continue ;
		int idx = mp[a[i] - b[i]] ;
		cout<<idx<<" "<<i<<" "<<a[i] - a[idx]<<"\n" ;
	}
	return 0 ;
}		