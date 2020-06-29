/* Author: Mohamed Bakry (handle: MohamedAhmed04)

   contest name: Polish Olympiad In Informatics (POI) 2005
   problem name: Banknote (POI 2005-Banknote)
   problem link: https://szkopul.edu.pl/problemset/problem/klvaggzD-q4Acz_WLtkn0JXJ/site/?key=statement

   Problem's solution:
    This problem is known as Bounded knapsack problem where evere we can pick item i
    at most cnt[i] time, my solution goes as follows:
    let dp[i][j] is minimum number of Banknotes used from any type from idx 0 to i to obtain value j.
    then dp[i][j] = max(dp[i-1][j] , dp[i][j-x*value[i]]+x) where 1 <= x <= cnt[i].
    we can compute it using monotonic queue.
    total time complexity: O(NK)
*/

#include <bits/stdc++.h>

using namespace std ;

const int MAXN = 205 , MAXK = 20005 ;

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
        void clear()
        {
        	m_deque.clear() ;
        }
};

int val[MAXN] , cnt[MAXN] , ans[MAXN] ;
int n , k ;
int dp[MAXN][MAXK] , prv[MAXN][MAXK] ;

int main()
{
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	cin>>n ;
	for(int i = 1 ; i <= n ; ++i)
		cin>>val[i] ;
	for(int i = 1 ; i <= n ; ++i)
		cin>>cnt[i] ;
	cin>>k ;
	for(int i = 0 ; i <= n ; ++i)
	{
		for(int j = 0 ; j <= k ; ++j)
			dp[i][j] = 1e9 ;
	}
	dp[0][0] = 0 ;
	Monoqueue q ;
	for(int i = 1 ; i <= n ; ++i)
	{
		for(int st = 0 ; st < val[i] ; ++st)
		{
			for(int j = st ; j <= k ; j += val[i])
			{
				while(q.size() > 0 && (j-q.idxmin()) / val[i] > cnt[i])
					q.pop(q.idxmin()) ;
				q.push(dp[i-1][j] - (j - st) / val[i] , j) ;
				dp[i][j] = q.min() + (j-st) / val[i] ;
				prv[i][j] = q.idxmin() ;
			}
			q.clear() ;
		}
	}
	int i = n , j = k ;
	while(i > 0)
	{
		ans[i] += (j - prv[i][j]) / val[i] ;
		j = prv[i][j] ;
		i-- ;
	}
	cout<<dp[n][k]<<"\n" ;
	for(int i = 1 ; i <= n ; ++i)
		cout<<ans[i]<<" " ;
	cout<<"\n" ;
	return 0 ;
}		