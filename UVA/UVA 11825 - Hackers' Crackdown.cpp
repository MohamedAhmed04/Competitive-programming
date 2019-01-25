/* Author : MohamedAhmed (handle : MohamedAhmed04)

   problem name : UVA 11825 - Hackers' Crackdown

   solution of the problem :
      we should every time make the nodes that this nodes and their
    neighbors cover all nodes..so we should first see which masks cover
    all nodes...after that we can make dp on all submasks that cover the nodes
    and answer will be largest number subset of nodes that cover them.
*/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 16 ;
const int MAX = 1 << MAXN ;
int cover[MAX] , dp[MAX] ;

int solve(int mask)
{
    if(mask == 0)
        return 0 ;
    int &ret = dp[mask] ;
    if(ret != -1)
        return dp[mask] ;
    ret = 0 ;
    for(int submask = mask ; submask != 0 ; submask = (submask-1) & mask)
    {
        //see if current submask can cover all nodes so we will remove it in mask and add 1 (subset which cover all nodes)
        if(cover[submask])
            ret = max(ret , solve(mask & (~submask))+1);
    }
    return ret ;
}

int main()
{
    int n;
    int cases = 0 ;
    while(cin>>n)
    {
        if(n == 0)
            break;
        memset(cover , 0 , sizeof(cover));
        memset(dp , -1 , sizeof(dp));
        int arr[n] ;
        for(int i = 0 ; i < n ; ++i)
        {
            int x ;
            cin>>x ;
            arr[i] = 1 << i ;
            while(x--)
            {
                int a ;
                cin>>a ;
                arr[i] |= (1 << a) ;
            }
        }
        //see which masks cover all nodes
        for(int i = 0 ; i < (1 << n) ; ++i)
        {
            int sum = 0 ;
            for(int j = 0 ; j < n ; ++j)
            {
                if((i & (1 << j)))
                    sum |= arr[j] ;
            }
            if(sum == (1 << n) - 1)
                cover[i] = 1 ;
            else
                cover[i] = 0 ;
        }
        cout<<"Case "<<++cases<<": "<<solve((1 << n)-1)<<"\n";
    }
    return 0 ;
}
