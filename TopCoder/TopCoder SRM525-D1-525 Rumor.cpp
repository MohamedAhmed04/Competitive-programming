/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   problem name : TopCoder SRM525-d1-525 Rumor

   solution of the problem : since n is 16 so we can loop on all
   submasks until 2^n...and for each time we need to make array
   to know day which idx and rumor know...so at first it's 0 if he
   knows it and -1 if he don't know...and for each time we loop
   until there's no any changes and loop for all rabbits and loop
   another time for 2 times(one for (i>>j)&1 and if there's no rumor
   sent so it will be (!((i >> j)&1)) )..and handle case if he don't
   know this rumor or he knew it today (so he can't share it)
   and after that share it and after ending of days loop we see if
   all knows then minimize the answer and if answer is inf then return
   -1 else then return ans
*/

#include <bits/stdc++.h>

using namespace std;

class Rumor
{
public:
    const int inf = 1e9 ;
    int getMinimum(string knowledge, vector <string> graph)
    {
        int ans = inf ;
        int n = knowledge.size() ;
        for(int i = 0 ; i < (1 << n) ; ++i)
        {
            int know[n][2] ;
            for(int j = 0 ; j < n ; ++j)
                knowledge[j] == 'Y' ? (know[j][0] = know[j][1] = 0) : (know[j][0] = know[j][1] = -1) ;
            int days2 ;
            for(int days = 1 ; ; ++days)
            {
                bool done = 1 ;
                for(int j = 0 ; j < n ; ++j)
                {
                    bool t = (i >> j) & 1;
                    for(int x = 0 ; x < 2 ; ++x)
                    {
                        if(know[j][t] == days || know[j][t] == -1)
                            continue;
                        bool send = 0 ;
                        for(int k = 0 ; k < n ; ++k)
                        {
                            if(graph[j][k] == 'Y' && know[k][t] == -1)
                            {
                                send = 1 , know[k][t] = days , done = 0;
                            }
                        }
                        if(send)
                            break;
                        t = !t ;
                    }
                }
                if(done)
                {
                    //cout<<days<<"\n";
                    days2 = days-1 ;
                    break;
                }
            }
            bool rumors = 1 ;
            for(int j = 0 ; j < n ; ++j)
            {
                if(know[j][0] == -1 || know[j][1] == -1)
                {
                    rumors = 0 ;
                    break ;
                }
            }
            if(rumors)
                ans = min(ans , days2) ;
        }
        if(ans == inf)
            ans = -1 ;
        return ans ;
    }
};
