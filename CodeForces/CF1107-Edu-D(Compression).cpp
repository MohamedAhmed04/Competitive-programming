/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest name : Codeforces Educational round 59 (CF1107)
   problem name : Compression (CF1107-Edu-D(Compression))
   problem link : https://codeforces.com/contest/1107/problem/D
*/

#include <bits/stdc++.h>

using namespace std;

const int MAX = 5201 ;
string arr2[MAX] ;
char arr[MAX][MAX] ;

string s = "" ;

void HexToBin(string hexdec)
{
    long int i = 0;

    while (hexdec[i]) {

        switch (hexdec[i]) {
        case '0':
            s += "0000";
            break;
        case '1':
            s += "0001";
            break;
        case '2':
            s += "0010";
            break;
        case '3':
            s += "0011";
            break;
        case '4':
            s += "0100";
            break;
        case '5':
            s += "0101";
            break;
        case '6':
            s += "0110";
            break;
        case '7':
            s += "0111";
            break;
        case '8':
            s += "1000";
            break;
        case '9':
            s += "1001";
            break;
        case 'A':
        case 'a':
            s += "1010";
            break;
        case 'B':
        case 'b':
            s += "1011";
            break;
        case 'C':
        case 'c':
            s += "1100";
            break;
        case 'D':
        case 'd':
            s += "1101";
            break;
        case 'E':
        case 'e':
            s += "1110";
            break;
        case 'F':
        case 'f':
            s += "1111";
            break;
        }
        i++;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0) ;
    int n ;
    cin>>n ;
    for(int i = 0 ; i < n ; ++i)
    {
        string s1 ;
        cin>>s1 ;
        HexToBin(s1) ;
        arr2[i] = s ;
        s = "" ;
    }
    for(int i = 1 ; i <= n ; ++i)
    {
        for(int j = 1 ; j <= n ; ++j)
            arr[i][j] = arr2[i-1][j-1] ;
    }
    vector<int>divisors ;
    for(int i = 1 ; i*i <= n ; ++i)
    {
        if(n % i == 0)
        {
            if(i * i == n)
                divisors.push_back(i) ;
            else
                divisors.push_back(i) , divisors.push_back(n/i) ;
        }
    }
    int ans = 0 ;
    for(auto &d : divisors)
    {
        bool t = true ;
        for(int i = 1 ; i <= n ; i += d)
        {
            for(int j = 1 ; j <= n ; j += d)
            {
                for(int a = i ; a < i+d ; ++a)
                {
                    for(int b = j ; b < j+d ; ++b)
                    {
                        if(arr[a][b] != arr[i][j])
                        {
                            t = false ;
                            break;
                        }
                    }
                    if(t == false)
                        break;
                }
                if(t == false)
                    break;
            }
            if(t == false)
                break;
        }
        if(t == true)
            ans = max(ans , d) ;
    }
    return cout<<ans<<"\n" , 0 ;
}
