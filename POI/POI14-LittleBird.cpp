/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : Polish Olympiad In Informatics (POI) 2014
   problem name : Little Bird (POI 14-LittleBird)
   problem link : https://szkopul.edu.pl/problemset/problem/xfpVU8vFP2RzZ0hrqWq9kTZM/site/?key=statement

   Problem's solution:
   	- Let dp[i] represents minimum number of tiresome to land the bird on i.
   	- we can observe that there's at most two different dp values in range [i, i+k]
   	- so for every i, let x represents the minimum value of dp[j] where (i-k <= j < i).
   	  so dp[i] will equal to either x or x+1.
    - keep two monotonic queues for different values in range and q1 store maximum arr[j] such that
      dp[j] equals x, and q2 store maximum arr[j] such that dp[j] equals x+1.
    - if maximum value in q1 > arr[i], then dp[i] equal x, else then dp[i] = x+1. and add it in the monotonic queue.

*/

#include <bits/stdc++.h>

using namespace std ;

const int MAX = 1e6 + 10 ;

int arr[MAX] , dp[MAX] , mark[MAX] ;
int n ;

struct MonoqueueMax
{
    deque<pair<int, int>> m_deque; //pair.first: the actual value. 
                                   //pair.second: idx of the number.
    public:
        void push(int val , int idx)
        {
            while(!m_deque.empty() && m_deque.back().first <= val)
                m_deque.pop_back();
            m_deque.emplace_back(val, idx);
        };
        int size()
        {
        	return m_deque.size() ;
        }
        int max()
        {
            return m_deque.front().first;
        }
        int lastmaxidx()
        {
        	return m_deque.front().second ;
        }
        void pop(int idx)
        {
            if(m_deque.front().second == idx)
            	m_deque.pop_front();
        }
};

int main()
{
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	cin>>n ;
	for(int i = 0 ; i < n ; ++i)
		cin>>arr[i] ;
	int q ;
	cin>>q ;
	while(q--)
	{
		int k ; 
		cin>>k ;
		dp[0] = 0 ;
		MonoqueueMax q1, q2 ;
		q1.push(arr[0] , 0) ;
		mark[0] = 0 ;
		for(int i = 1 ; i < n ; ++i)
		{
			if(i-k-1 >= 0)
			{
				if(mark[i-k-1])
					q2.pop(i-k-1) ;
				else
					q1.pop(i-k-1) ;
			}
			if(!q1.size())
			{
				swap(q1 , q2) ;
				for(int j = i-k ; j < i ; ++j)
					mark[j] = 0 ;
			}
			if(q1.max() > arr[i])
			{
				dp[i] = dp[q1.lastmaxidx()] ;
				q1.push(arr[i] , i) ;
				mark[i] = 0 ;
			}
			else
			{
				dp[i] = dp[q1.lastmaxidx()] + 1 ;
				q2.push(arr[i] , i) ;
				mark[i] = 1 ;
			}
		}
		cout<<dp[n-1]<<"\n" ;
	}
	return 0 ;
}		