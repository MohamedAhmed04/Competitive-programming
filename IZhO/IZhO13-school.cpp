/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : IZhO 2013 day 1
   problem name : Schools (IZhO 13-School)
   problem link : https://oj.uz/problem/view/IZhO13_school

   Problem's solution : 
   - sort the numbers according to difference between M[i] and S[i]
   - let pref[i] = sum of highest m of value M[i] from index 0 to i
     and suff[i] = sum of highest s of value S[i] from index n-1 to i
   - answer is max(pref[i] + suff[i+1]) for all 0 <= i <= n-1

*/

#include <bits/stdc++.h>

using namespace std ;

const int MAX = 300000 + 10 ;

long long M[MAX] , S[MAX] ;
long long prefM[MAX] , suffS[MAX] ;
int n , m , s ;

int main()
{
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	cin>>n>>m>>s ;
	vector< pair<int , int> >vp ;
	for(int i = 0 ; i < n ; ++i)
	{
		cin>>M[i]>>S[i] ;
		vp.push_back({M[i]-S[i] , i}) ;
	}
	sort(vp.rbegin() , vp.rend()) ;
	priority_queue< long long , vector<long long> , greater<long long> >q ;
	long long sum = 0 ;
	for(int i = 0 ; i < n ; ++i)
	{
		int idx = vp[i].second ;
		if(q.size() < m)
		{
			sum += M[idx] ;
			q.push(M[idx]) ;
		}
		else if(q.top() < M[idx])
		{
			sum -= q.top() ;
			q.pop() ;
			sum += M[idx] ;
			q.push(M[idx]) ;
		}
		prefM[i] = sum ;
	}
	while(q.size() > 0)
		q.pop() ;
	sum = 0 ;
	for(int i = n-1 ; i >= 0 ; --i)
	{
		int idx = vp[i].second ;
		if(q.size() < s)
		{
			sum += S[idx] ;
			q.push(S[idx]) ;
		}
		else if(q.top() < S[idx])
		{
			sum -= q.top() ;
			q.pop() ;
			sum += S[idx] ;
			q.push(S[idx]) ;
		}
		suffS[i] = sum ;
	}
	long long ans = suffS[0] ;
	for(int i = 0 ; i < n ; ++i)
		ans = max(ans , prefM[i] + suffS[i+1]) ;
	return cout<<ans<<"\n" , 0 ;
}		