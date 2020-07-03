/* Author: Mohamed Bakry (handle: MohamedAhmed04)

   contest name: Internation Olympiad In Informatics (IOI) 2016 training round 2 
   problem name: Increasing Subarrays (IOI 2016-Practice Increasing Subarrays)
   problem link: https://csacademy.com/contest/ioi-2016-training-round-2/task/increasing_subarrays/

   Problem's solution:
    We can solve this problem with two pointers.
    To move the right pointer we will add to the cost max(arr[l] , arr[l+1] , ... , arr[r]) - arr[r],
    I used monotonic queue to compute the maximum in the subarray fast.
    If the cost is more than m then we will move the left pointer.
    Moving the left pointer is harder, we need to preprocess the next greater element for every number and let we name it to[i]
    in the array, the to move the left pointer:
    since all numbers from [l+1, min(r, to[l]-1)] we made them equal to arr[l] so we will subtract from the answer this cost,
    and then calculate the new cost by moving from idx l+1 to to[l+1].

    see my code for more clarification.

*/

#include <bits/stdc++.h>

using namespace std ;

const int MAX = 1e6 + 10 ;

struct Monoqueue
{
    deque<pair<int, int>> m_deque; //pair.first: the actual value. 
                                   //pair.second: idx of the number.
    public:
        void push(int val , int idx)
        {
            while(!m_deque.empty() && m_deque.back().first < val)
                m_deque.pop_back();
            m_deque.emplace_back(val, idx);
        };

        int idxmax()
        {
        	if(m_deque.size() == 0)
        		return -1 ;
        	return m_deque.front().second ;
        }
        int max()
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

long long arr[MAX] , pref[MAX] ;
int to[MAX] , mark[MAX] ;
int n ;
long long m ;

int main()
{
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	cin>>n>>m ;
	for(int i = 0 ; i < n ; ++i)
		cin>>arr[i] ;
	for(int i = 0 ; i < n ; ++i)
	{
		if(i)
			pref[i] = pref[i-1] ;
		pref[i] += arr[i] ;
	}
	stack<int>s ;
	for(int i = n-1 ; i >= 0 ; --i)
	{
		while(s.size() > 0 && arr[i] >= arr[s.top()])
			s.pop() ;
		if(s.size())
			to[i] = s.top() ;
		else
			to[i] = n ;
		s.push(i) ;
	}
	int l = 0 , r = 0 ;
	long long cost = 0 , ans = 0 ;
	Monoqueue q ;
	mark[0] = 1 ;
	while(r < n)
	{
		q.push(arr[r] , r) ;
		if(q.idxmax() == r)
			mark[r] = 1 ;
		cost += q.max() - arr[r] ;
		while(cost > m)
		{
			int idx = min(r , to[l]-1) ;
			cost -= arr[l] * (idx - l) - (pref[idx] - pref[l]) ;
			q.pop(l) ;
			++l ;
			int now = l ;
			while(!mark[now] && now <= r)
			{
				idx = min(r , to[now]-1) ;
				cost += arr[now] * (idx - now) - (pref[idx] - pref[now]) ;
				mark[now] = 1 ;
				now = to[now] ;
			}
		}
		//cout<<l<<" "<<r<<" : "<<cost<<"\n" ;
		ans += r-l+1 ;
		++r ;
	}
	return cout<<ans<<"\n" , 0 ;
}		