/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : International Olympiad in informatics (IOI) 2006
   problem name : Pyramid (IOI 2006-Pyramid)
   problem link : https://wcipeg.com/problem/ioi0612

   Problem's solution :
    https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/IOI/official/2006/ioi06_pyramid_sol.pdf

*/

#include <bits/stdc++.h>

using namespace std ;

const int MAX = 1010 ;

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
        int min()
        {
        	if(m_deque.size() == 0)
        		return 0 ;
            return m_deque.front().first;
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

int arr[MAX][MAX] , sum[MAX][MAX] , Min[MAX][MAX] , Minsum[MAX][MAX] ;
int n , m , a , b , c , d ;

int SUM(int x , int y , int x2 , int y2)
{
	if(x2 > n || y2 > m)
		return 0 ;
	return (sum[x2][y2] - sum[x-1][y2] - sum[x2][y-1] + sum[x-1][y-1]) ;
}

int main()
{
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	cin>>m>>n>>b>>a>>d>>c ;
	for(int i = 1 ; i <= n ; ++i)
	{
		for(int j = 1 ; j <= m ; ++j)
			cin>>arr[i][j] ;
	}
	for(int i = 1 ; i <= n ; ++i)
	{
		for(int j = 1 ; j <= m ; ++j)
			sum[i][j] = arr[i][j] + sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] ;
	}
	for(int i = 1 ; i <= n ; ++i)
	{
		Monoqueue q ;
		int last = m , now ;
		for(int j = m ; j >= 1 ; --j)
		{
			now = SUM(i , j , i+c-1 , j+d-1) ;
			q.push(now , j) ;
			while(last+d-1 >= j+b-2)
				q.pop(last--) ;
			Min[i][j] = q.min() ;
		}
	}
	for(int j = 1 ; j <= m ; ++j)
	{
		Monoqueue q ;
		int last = n , cursum = 0 ;
		for(int i = n ; i >= 1 ; --i)
		{
			q.push(Min[i][j] , i) ;
			while(last+c-1 >= i+a-2)
				q.pop(last--) ;
			Minsum[i][j] = q.min() ;
		}
	}
	int ans = -1e9 , x = -1 , y = -1 , Sum = -1 ;
	for(int i = 1 ; i <= n ; ++i)
	{
		for(int j = 1 ; j <= m ; ++j)
		{
			if(i+a-1 > n || j+b-1 > m)
				continue ;
			int now = SUM(i , j , i+a-1 , j+b-1) ;
			now -= Minsum[i+1][j+1] ;
			if(now > ans)
				ans = now , x = i , y = j , Sum = Minsum[i+1][j+1] ;
		}
	}
	assert(x != -1 && y != -1) ;
	cout<<y<<" "<<x<<"\n" ;
	for(int i = 1 ; i <= n ; ++i)
	{
		for(int j = 1 ; j <= m ; ++j)
		{
			if(i >= x+1 && i+c-1 <= x+a-2 && j >= y+1 && j+d-1 <= y+b-2)
			{
				int now = SUM(i , j , i+c-1 , j+d-1) ;
				if(now == Sum)
					return cout<<j<<" "<<i<<"\n" , 0 ;
			}
		}
	}
	assert(0) ;
	return 0 ;
}		