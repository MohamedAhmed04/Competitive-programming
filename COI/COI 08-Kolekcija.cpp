/* Author: Mohamed Ahmed Bakry (handle: MohamedAhmed04)

   contest name: Croatian Olympiad In Informatics (COI) 2008
   problem name: Kolekcija (COI 2008-Kolekcija)
   problem link: https://wcipeg.com/problem/coi07p2

   Problem's solution:
    same idea like: https://github.com/stefdasca/CompetitiveProgramming/blob/master/COI/COI%2007-Kolekcija.cpp

*/

#include <bits/stdc++.h>

using namespace std ;

const int MAX = 3e5 + 10 ;

struct Monoqueue
{
    deque<pair<int, int>> m_deque; //pair.first: the actual value. 
                                   //pair.second: idx of the number.
    public:
        void push(int val , int idx)
        {
            while(!m_deque.empty() && m_deque.back().first > val)
                m_deque.pop_back();
            m_deque.emplace_back(val, idx);
        };

        int idxmin()
        {
        	if(m_deque.size() == 0)
        		return -1 ;
        	return m_deque.front().second ;
        }
        int min()
        {
        	if(m_deque.size() == 0)
        		return 0 ;
            return m_deque.front().first ;
        }
        void pop(int idx)
        {
        	if(m_deque.size() == 0)
        		return ;
            if(m_deque.front().second == idx)
            	m_deque.pop_front();
        }
        int size()
        {
        	return m_deque.size() ;
        }
};

int arr[MAX] , arr2[MAX] ;
pair<int , int>dp[MAX] ;
int n , k , m ;

int main()
{
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	cin>>n>>k ;
	cin>>m ;
	for(int i = 1 ; i <= m ; ++i)
	{
		cin>>arr[i] ;
		arr2[i] = arr[i] ;
	}
	sort(arr + 1 , arr + m + 1) ;
	Monoqueue q ;
	pair<int , int>Min = {1e9 , 1} ;
	for(int i = 1 ; i <= m ; ++i)
	{
		while(q.size())
		{
			int idx = q.idxmin() ;
			if(arr[idx] + k - 1 >= arr[i])
				break ;
			q.pop(idx) ;
			Min = min(Min , {dp[idx-1].first - arr[idx] + 1, arr[idx]}) ;
		}
		dp[i].first = dp[i-1].first + k , dp[i].second = arr[i] ;
		dp[i] = min(dp[i] , {arr[i] + Min.first , Min.second}) ;
		if(q.size())
			dp[i] = min(dp[i] , {q.min() , arr[q.idxmin()]}) ;
		q.push(dp[i-1].first + k , i) ;
	}
	vector< pair<int , int> >vp ;
	int prv = 1e9 ;
	for(int i = m ; i >= 1 ; --i)
	{
		if(arr[i] >= prv)
			continue ;
		int l = dp[i].second , r = max(dp[i].second + k - 1 , arr[i]) ;
		if(arr[i]-l+1 <= k)
		{
			if(r > n)
				l -= r-n , r -= r-n ;
			vp.emplace_back(l , r) ;
		}
		else
		{
			for(int j = l ; j <= arr[i] ; j += k)
			{
				if(j+k-1 <= arr[i])
					vp.emplace_back(j , j+k-1) ;
				else
					vp.emplace_back(arr[i]-k+1 , arr[i]) ;
			}
		}
		prv = l ;
	}
	sort(vp.begin() , vp.end()) ;
	cout<<dp[m].first<<"\n" ;
	for(int i = 1 ; i <= m ; ++i)
	{
		int idx = upper_bound(vp.begin() , vp.end() , make_pair(arr2[i]+1 , -1)) - vp.begin() ;
		idx-- ;
		int l = vp[idx].first , r = vp[idx].second ;
		if(r > n)
			l -= r-n , r -= r-n ;
		cout<<l<<" "<<r<<"\n" ;
	}
	return 0 ;
}		