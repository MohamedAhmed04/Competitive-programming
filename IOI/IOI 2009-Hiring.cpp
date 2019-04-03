/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest name : IOI 2013 day 1
   problem name : Hiring (IOI 2009-Hiring)
   problem link : https://contest.yandex.ru/ioi/contest/568/problems/B

   problem solution :
   if we sorted all candidates by salary / qualification level
   then we are sure now if we picked candidates in prefix [0 , i] we are sure
   we will pay salary / qualification level * sum , let's denote salary / qualification level
   by Ratio then we will loop and every time we will try to erase candidates with higher sums until
   until Ratio * sum <= W , to make that efficiently we will store them in priority queue.

   note : see comments in code for more clarification.

*/

#include <bits/stdc++.h>

using namespace std ;

//check function to return true if w >= sum * Ratio

bool check(long double w , long double sum , long double Ratio)
{
    return (w >= (sum * Ratio)) ;
}

int main()
{
    ios::sync_with_stdio(0) ;
    cin.tie(0) ;
    int n ;
    cin>>n ;
    long long tmp ;
    cin>>tmp ;
    long double w = tmp ;
    vector< pair<long double , pair<long double , int> > >vp ;
    for(int i = 0 ; i < n ; ++i)
    {
        long double x , y ;
        cin>>x>>y ;
        vp.push_back({x/y , {y , i}}) ;
    }
    //sort candidates according to salary / qualification level
    sort(vp.begin() , vp.end()) ;
    int MAX = 0 ;
    set<int>ans , cur;
    long double sum = 0.00 , MIN = 1e13;
    priority_queue< pair<long double , int> >q ;
    for(int i = 0 ; i < n ; ++i)
    {
        long double Ratio = vp[i].first ;
        q.push({vp[i].second.first , vp[i].second.second}) ;
        cur.insert(vp[i].second.second) ;
        sum += vp[i].second.first ;
        //loop until check function is true and q isn't empty
        while(!q.empty() && check(w , sum , Ratio) == 0)
        {
            pair<long double , int>p = q.top() ;
            q.pop() ;
            sum -= p.first ;
            cur.erase(p.second) ;
        }
        if(cur.size() > MAX)
            MAX = cur.size() , MIN = sum * Ratio ;
        else if(MAX == cur.size())
			MIN = min(MIN , sum * Ratio) ;
    }
    cur.clear() ;
    while(!q.empty())
        q.pop() ;
    sum = 0.0 ;
    cout<<MAX<<"\n" ;
    //make same loop as above to print the answer.
    for(int i = 0 ; i < n ; ++i)
    {
        long double Ratio = vp[i].first ;
        sum += vp[i].second.first ;
        q.push({vp[i].second.first , vp[i].second.second}) ;
        cur.insert(vp[i].second.second) ;
        while(!q.empty() && check(w , sum , Ratio) == 0)
        {
            pair<long double , int>p = q.top() ;
            q.pop() ;
            sum -= p.first ;
            cur.erase(p.second) ;
        }

        if(cur.size() == MAX && MIN == sum * Ratio)
        {
            for(auto &i : cur)
                cout<<i+1<<"\n";
            return 0 ;
        }
    }
    return 0 ;
}
