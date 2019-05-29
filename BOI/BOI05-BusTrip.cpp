/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : Baltic Olympiad in informatics 2005 day 2
   problem name : BusTrip (BOI2005-BusTrip)
   problem link : https://cses.fi/116/list/

   problem solution :
    https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/Baltic/official/boi2005_solutions/trip-sol-en.txt

*/

#include <bits/stdc++.h>

using namespace std;

const int MAXM = 1e5 + 5 , MAXN = 50005 ;
int n , m , dest , T;

struct bus
{
    int s , t , a , b , c , d ;
};

bus arr[MAXM] ;

vector< vector< pair<int , int> > >v(MAXN) ;

bool cmp(bus &x , bus &y)
{
    return x.d < y.d ;
}

int main()
{
    //freopen("TRIP.in" , "r" , stdin) ;
    //freopen("TRIP.out" , "w" , stdout) ;
    cin>>n>>m>>dest>>T ;
    for(int i = 0 ; i < m ; ++i)
        cin>>arr[i].s>>arr[i].t>>arr[i].a>>arr[i].b>>arr[i].c>>arr[i].d ;
    sort(arr , arr + m , cmp) ;
    v[1].push_back({0 , 0}) ;
    for(int i = 0 ; i < m ; ++i)
    {
        int now = arr[i].s ;
        if(v[now].size() == 0)
            continue ;
        if(arr[i].d > T)
            continue ;
        if(v[now][0].second > arr[i].a)
            continue ;
        //cout<<arr[i].s<<" "<<arr[i].t<<" "<<arr[i].a<<" "<<arr[i].b<<" "<<arr[i].c<<" "<<arr[i].d<<" : ";
        int l = 0 , r = v[now].size() - 1 ;
        int ans = 0 ;
        while(l <= r)
        {
            int mid = (l + r) >> 1 ;
            if(v[now][mid].second <= arr[i].a)
                l = mid+1 , ans = max(ans , mid) ;
            else
                r = mid-1 ;
        }
        int wait = v[now][ans].first + arr[i].b - arr[i].a + arr[i].d - arr[i].c + arr[i].a - v[now][ans].second;
        //cout<<wait<<" , "<<v[now][ans].first<<"\n";
        if(v[arr[i].t].size() == 0)
            v[arr[i].t].push_back({wait , arr[i].d}) ;
        else if(v[arr[i].t].back().first + (arr[i].d - v[arr[i].t].back().second) >= wait)
            v[arr[i].t].push_back({wait , arr[i].d}) ;
    }
    if(v[dest].size() == 0)
        return cout<<-1<<"\n" , 0 ;
    return cout<<v[dest].back().first + (T - v[dest].back().second)<<"\n" , 0 ;
}
