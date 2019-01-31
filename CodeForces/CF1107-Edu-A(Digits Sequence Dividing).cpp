/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest name : Codeforces Educational round 59 (CF1107)
   problem name : Digits Sequence Dividing (CF1107-Edu-A(Digits Sequence Dividing))
   problem link : https://codeforces.com/contest/1107/problem/A
*/

#include <iostream>

using namespace std;

int main()
{
    int t ;
    cin>>t ;
    while(t--)
    {
        int n ;
        cin>>n ;
        char arr[n] ;
        for(int i = 0 ; i < n ; ++i)
            cin>>arr[i] ;
        if(n == 2)
        {
            if(arr[0] < arr[1])
            {
                cout<<"YES\n";
                cout<<2<<"\n";
                cout<<arr[0]<<" "<<arr[1]<<"\n";
            }
            else
                cout<<"NO\n";
        }
        else
        {
            cout<<"YES\n";
            cout<<2<<"\n";
            cout<<arr[0]<<" ";
            for(int i = 1 ; i < n ; ++i)
                cout<<arr[i];
            cout<<"\n";
        }
    }
    return 0 ;
}
