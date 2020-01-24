/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : OSN Informatika 2015 - Hari 1
   problem name : Bisa Jadi Tebak Angka (OSN 2015 - 1C)
   problem link : https://tlx.toki.id/problems/osn-2015-1/C

   problem's solution :
   	- First realize that number of queries is always >= log3(N)
   	- the solution always will be inside vector v so we need to partition the 
   	  vector into 3 partitions, and when querying on a vector then if answer is "YA"
   	  then answer inside first partition, if answer is "BISAJADI" then answer is in 
   	  second partition, else if answer is "TIDAK" then answer is in the 3rd partition.
    - let's denote the vector that we will query on is v1.
      then since if answer is "YA" then it's partition one, so all numbers from partition one
      will be inside v1, since answer is "BISAJADI" for partition two, so for all numbers in partition 
      two, v1 will include (any number in partition two) - 1, and it won't include any adjacent number
      or any number from partition 3
    - let size of parition one = size of partition two = (v.size() + 2) / 3 and denote it as sz
      then partition one will contain numbers : {v[0] , v[2] , v[4] , ..., v[sz*2-2]} and
      parition 2 is {v[1] , v[3] , v[5] , ... , v[sz*2-1]} and partition 3 will contain remaining numbers.
    - v1 will contain all partition one and all numbers in partition two - 1.

*/      


#include <bits/stdc++.h>

using namespace std ;

const int MAX = 6505 ;

int arr[MAX] ;
int n , k ;
string s ;

string Query1(vector<int>&v)
{
	cout<<v.size() ;
	for(auto &i : v)
		cout<<" "<<i ;
	cout<<endl ;
	cin>>s ;
	return s ;
}

string Query2(int x)
{
	cout<<1<<" "<<x<<endl ;
	cin>>s ;
	return s ;
}

void Answer(int x)
{
	cout<<0<<" "<<x<<endl ;
	return ;
}

void solve(vector<int>&v)
{
	if(v.size() == 1)
	{
		Answer(v[0]) ;
		return ;
	}
	if(v.size() == 2)
	{
		if(Query2(v[0]) == "YA")
			Answer(v[0]) ;
		else
			Answer(v[1]) ;
		return ;
	}
	int sz = ((v.size() + 2) / 3)*2 ;
	vector<int>v1 ;
	for(int i = 0 ; i < sz ; ++i)
	{
		if(i % 2 == 0)
			v1.push_back(v[i]) ;
		else
		{
			if(v[i] != v[i-1]+1)
				v1.push_back(v[i]-1) ;
		}
	}
	string s2 = Query1(v1) ;
	v1.clear() ;
	if(s2 == "YA")
	{
		for(int i = 0 ; i < sz ; ++i)
		{
			if(i % 2 == 0)
				v1.push_back(v[i]) ;
		}
	}
	else if(s2 == "BISAJADI")
	{
		for(int i = 0 ; i < sz ; ++i)
		{
			if(i % 2 == 1)
				v1.push_back(v[i]) ;
		}
	}
	else if(s2 == "TIDAK")
	{
		for(int i = sz ; i < v.size() ; ++i)
			v1.push_back(v[i]) ;
	}
	solve(v1) ;
	return ;
}

int main()
{
	//ios_base::sync_with_stdio(0) ;
	//cin.tie(0) ;
	cin>>s ;
	cin>>n>>k ;
	vector<int>v ;
	for(int i = 1 ; i <= n ; ++i)
		v.push_back(i) ;
	solve(v) ;
	return 0 ;
}		