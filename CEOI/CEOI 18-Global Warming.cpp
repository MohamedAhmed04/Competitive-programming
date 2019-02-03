/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest name : CEOI 2018 day 1
   problem name : Global Warming (CEOI 18-Global Warming)
   problem link :
   https://csacademy.com/contest/ceoi-2018-day-1/task/global-warming/

   problem solution :
   so if we made a brute force solution..we will observe that every time
   we need to decrease value of prefix by value equal to x...so the problem now
   is to choose best prefix to decrease it to make the longest increasing subsequence
   so we now need to loop on all prefixes and try to change value of every element and
   everytime see LIS and maximize answer..but now the problem that it will get TLE..so we
   need a way to optimize it..so we will use segment tree to calculate LIS
   and since values are large and upto (10 power 9) so we will make coordinate compression
   but now there's another problem that maybe if we subtract x from values maybe there will be
   values with negative so we can't use segment tree..so to fix that we will add all elements by
   x and we will extend our coordinate compression array to n * 2 so first n will be array + x and
   last n elements will be the array without adding x (value after removing x)..so now we fixed the
   problem of negative values..so now we don't have problems to use segment tree and coordinate compression
   but we will use them why ?...since the LIS of every element while we decrease prefix by x is :
   maximum LIS of element less than current element + len[i] which is maximum LIS greater than the current
   element + 1....so we will calculate len[i] that we will loop and calculate LIS from last element to first element
   and len[i+n] = query(1 , 1 , n*2+1 , arr[i+n] + 1 , n*2+1)...so after calculating len[i] we will loop on elements
   (prefix) and decrease every element and calculate LIS after decreasing current element.

   note : see comments below for more clarification.
*/

#include <bits/stdc++.h>

using namespace std;

const int MAX = 200010 * 2;
const long long inf = 2e9 ;
int arr[MAX] , arr2[MAX] , len[MAX] , tree[4 * MAX] ;

void update(int node , int l , int r , int idx , int val)
{
    if(l > idx || r < idx)
        return ;
    if(l == r)
    {
        tree[node] = max(tree[node] , val);
        return ;
    }
    int mid = (l + r) >> 1 ;
    update(node << 1 , l , mid , idx , val) ;
    update(node << 1 | 1 , mid + 1 , r , idx , val) ;
    tree[node] = max(tree[node << 1] , tree[node << 1 | 1]);
}

int query(int node , int l , int r , int x , int y)
{
    if(x > r || y < l)
        return 0 ;
    if(l >= x && r <= y)
        return tree[node] ;
    int mid = (l + r) >> 1 ;
    int a = query(node << 1 , l , mid , x , y) ;
    int b = query(node << 1 | 1 , mid + 1 , r , x , y) ;
    return max(a , b) ;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0) ;
    int n , x ;
    cin>>n>>x ;
    //vector for coordinate compression
    vector< pair<int , int> >vp ;
    for(int i = 1 ; i <= n ; ++i)
    {
        cin>>arr2[i] ;
        //add x to all elements to handle negative values in segment tree after decreasing each prefix
        arr2[i] += x ;
        vp.push_back({arr2[i] , i}) ;
        //add value after decreasing current element by x and its idx is n+i
        vp.push_back({arr2[i]-x , n+i});
    }
    sort(vp.begin() , vp.end());
    int idx = 1 ;
    //make the coordinate compression
    for(int i = 0 ; i < vp.size() ; ++i)
    {
        if(i != 0)
        {
            if(vp[i].first == vp[i-1].first)
                --idx;
        }
        arr[vp[i].second] = idx ;
        idx++ ;
    }
    int ans = 0 ;
    //calculate len[i] for all elements
    for(int i = n ; i > 0 ; --i)
    {
        len[i+n] = query(1 , 1 , n*2+1 , arr[i+n] + 1 , n*2+1) ;
        int a = query(1 , 1 , n * 2 + 1 , arr[i]+1 , n * 2 + 1) + 1;
        update(1 , 1 , n * 2 + 1 , arr[i] , a) ;
    }
    //clear the tree
    memset(tree , 0 , sizeof(tree));
    //loop on prefixes after decreasing by x and calculate answer
    for(int i = n+1 ; i <= n*2 ; ++i)
    {
        int a = query(1 , 1 , n * 2 + 1 , 1 , arr[i]-1) + 1;
        update(1 , 1 , n * 2 + 1 , arr[i] , a) ;
        //answer is max(ans , LIS of elements < arr[i] until now + len[i])
        ans = max(ans , a + len[i]);
    }
    return cout<<ans<<"\n" , 0 ;
}
