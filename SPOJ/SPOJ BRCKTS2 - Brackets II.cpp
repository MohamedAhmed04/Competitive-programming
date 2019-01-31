/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   problem name : SPOJ BRCKTS2 - Brackets II
   problem link : https://www.spoj.com/problems/BRCKTS2/

   problem solution :
   - First we should match every pair of brackets to know start and end
     of each bracket sequence so we now know the width of every bracket sequence.
   - After that we should know the color of each bracket sequence so we will
     loop on them and make cnt which is 0 and if it's opening of bracket then
     add 1 to cnt and if it's closing of bracket then subtract 1 from cnt and
     color[idx] is cnt..and if cnt is odd then it's black else then it's White.
   - Now we should know the height of every bracket sequence , we know that :
     height of current bracket sequence is max(height between opening and closing of it) + 1
     so now we will loop on them and if current idx is closing bracket ) then we should
     query using segment tree to find maximum number in the range and if color is black
     then add to answer the area height * width else then subtract from answer
     the area.
   - Now update the range with current height using segment tree and lazy propagation.
*/

#include <bits/stdc++.h>

using namespace std;

const int MAX = 350010 ;
int match[MAX] , tree[8 * MAX] , lazy[8 * MAX];

void shift(int node)
{
    if(lazy[node] == 0)
        return ;
    tree[node] = lazy[node] ;
    lazy[node << 1] = lazy[node] ;
    lazy[node << 1 | 1] = lazy[node] ;
    lazy[node] = 0 ;
}

void update(int node , int l , int r , int x , int y , int value)
{
    shift(node) ;
    if(x > r || y < l)
        return ;
    if(l == r)
    {
        tree[node] = value ;
        return ;
    }
    if(l >= x && r <= y)
    {
        lazy[node] = value ;
        shift(node) ;
        return ;
    }
    int mid = (l + r) >> 1 ;
    update(node << 1 , l , mid , x , y , value) ;
    update(node << 1 | 1 , mid+1 , r , x , y , value) ;
    tree[node] = max(tree[node << 1] , tree[node << 1 | 1]);
}

int query(int node , int l , int r , int x , int y)
{
    shift(node) ;
    if(x > r | y < l)
        return 0 ;
    if(l >= x && r <= y)
    {
        return tree[node] ;
    }
    int mid = (l + r) >> 1 ;
    int a = query(node << 1 , l , mid , x , y) ;
    int b = query(node << 1 | 1 , mid + 1 , r , x , y) ;
    return max(a , b) ;
}

int main()
{
    int t ;
    cin>>t ;
    while(t--)
    {
        memset(tree , 0 , sizeof(tree));
        memset(lazy , 0 , sizeof(lazy));
        string s ;
        cin>>s ;
        vector<int>v ;
        int n = s.size() ;
        int color[n] ;
        for(int i = 0 ; i < n ; ++i)
        {
            if(s[i] == '(')
                v.push_back(i) ;
            else
            {
                int x = v.back();
                v.pop_back();
                match[x] = i ;
                match[i] = x ;
            }
        }
        int cnt = 0 ;
        for(int i = 0 ; i < n ; ++i)
        {
            if(s[i] == '(')
                cnt++ , color[i] = cnt ;
            else
                cnt-- , color[i] = cnt ;
        }
        long long ans = 0ll ;
        for(int i = 0 ; i < n ; ++i)
        {
            if(s[i] == ')')
            {
                int from = match[i] ;
                int x = query(1 , 0 , n , from , i) + 1;
                update(1 , 0 , n , from , i , x) ;
                if(color[from] & 1)
                    ans += ((i-from) * 1ll * x * 1ll) ;
                else
                    ans -= ((i - from) * 1ll * x * 1ll) ;
            }
        }
        cout<<ans<<"\n";
    }
    return 0 ;
}
