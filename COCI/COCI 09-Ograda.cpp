/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : COCI 2009 contest 4 problem 4
   problem name : OGRADA (COCI 09-OGRADA)
   problem link : https://wcipeg.com/problem/coci094p4

   problem's solution :
   - to calculate first number we need to know minimum number in every
     subarray of size k, let submin[i] be minimum number of subarray starting
     from i to i+k-1.
   - so I made monotonic queue to calculate it for every number in O(N)
   - after that we need to calculate ansMax[i] where 
     ansMax[i] = largest submin[j] where i-k+1 <= j <= i 
   - I made another monotonic queue to calculate that.
   - first number will be summation of arr[i] - ansMax[i] where 0 <= i < n. (0 indexed)
   - to calculate second number, for each number we will take subarray which maximize
     Maxans[i] and if there're many choices then pick the farthest one (I handled it in monotonic queue)
   - handle case if subarray that maximize Maxans[i] is already taken so we won't take any subarray in this time.
   - see code for more clarification.

*/ 

#include <bits/stdc++.h>

using namespace std ;

const int MAX = 1e6 + 10 ;
int n , k ;
int arr[MAX] , submin[MAX] , ansMax[MAX] , taken[MAX];

struct MonoqueueMin
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
        int min()
        {
            return m_deque.front().first;
        }
        int lastminidx()
        {
        	return m_deque.front().second ;
        }
        void pop(int idx)
        {
            if(m_deque.front().second == idx)
            	m_deque.pop_front();
        }
};

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
	scanf("%d %d" , &n , &k) ;
	for(int i = 0 ; i < n ; ++i)
		scanf("%d" , &arr[i]) ;
	MonoqueueMin q ;
	for(int i = 0 ; i < n ; ++i)
	{
		q.push(arr[i] , i) ;
		if(i-k+1 >= 0)
		{
			submin[i-k+1] = q.min() ;
			q.pop(i-k+1) ;
		}
	}
	long long ans = 0ll , ans2 = 0 ;
	MonoqueueMax q2 ;
	int cover = -1 , lastcover = -1 ;
	for(int i = 0 ; i < n ; ++i)
	{
		if(i+k-1 < n)
			q2.push(submin[i] , i) ;
		ansMax[i] = q2.max() ;
		ans += (arr[i] - ansMax[i]) * 1ll ;
		if(cover != ansMax[i] || lastcover < i)
			taken[q2.lastmaxidx()] = 1 , cover = ansMax[i] , lastcover = q2.lastmaxidx()+k-1;
		if(i-k+1 >= 0)
			q2.pop(i-k+1) ;
	}
	for(int i = 0 ; i < n ; ++i)
		ans2 += taken[i] ;
	return cout<<ans<<"\n"<<ans2<<"\n" , 0 ;
}