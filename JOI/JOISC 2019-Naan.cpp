/* Author: Mohamed Bakry (handle: MohamedAhmed04)

   contest name: Japanese Olympiad In Informatisc (JOI) spring camp 2019 day 1
   problem name: Naan (JOI spring Camp 2019 - Naan)
   problem link: https://oj.uz/problem/view/JOI19_naan

   Problem's solution:
     same like this two solutions: https://github.com/quangloc99/CompetitiveProgramming/blob/master/olympiad/JOISC/2019/naan.cpp
                                   https://github.com/dolphingarlic/CompetitiveProgramming/blob/master/JOI/JOI%2019-naan.cpp

*/

#include <bits/stdc++.h>

using namespace std ;

struct Fraction
{
	long long number, numerator, denominator ;

	Fraction(long long num = 0): number(num) , numerator(0) , denominator(1) {}
	Fraction(long long whole , long long num , long long den): number(whole) , numerator(num) , denominator(den)
	{
		norm() ;
	}
	Fraction(long long num , long long den): Fraction(0 , num , den) {}

	Fraction& norm()
	{
		if(numerator > denominator)
		{
			number += numerator / denominator ;
			numerator %= denominator ;
		}
		long long g = __gcd(numerator , denominator) ;
		numerator /= g ;
		denominator /= g ;
		return *this ;
	}
};

bool operator < (const Fraction& a , const Fraction& b)
{
	if(a.number != b.number)
		return a.number < b.number ;
	else
		return a.numerator * b.denominator < b.numerator * a.denominator ;
}

ostream& operator << (ostream& cout , const Fraction& a)
{
	return cout<<a.number * a.denominator + a.numerator<<" "<<a.denominator ;
}

const int MAX = 2000 + 4 ;

long long arr[MAX][MAX] , sum[MAX] ;
Fraction split[MAX][MAX] ;
int order[MAX] , mark[MAX] ;

int n , l ;

int main()
{
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	cin>>n>>l ;
	for(int i = 0 ; i < n ; ++i)
	{
		for(int j = 0 ; j < l ; ++j)
		{
			cin>>arr[i][j] ;
			sum[i] += arr[i][j] ;
		}
	}
	for(int i = 0 ; i < n ; ++i)
	{
		long long now = 0 ;
		int idx = 0 ;
		for(int j = 1 ; j <= n ; ++j)
		{
			while((now + arr[i][idx]) * n <= sum[i] * j)
			{
				now += arr[i][idx] ;
				++idx ;
			}
			long long cur = sum[i] * j - now * n ;
			split[i][j] = Fraction(idx , cur , n * arr[i][idx]) ;
		}
	}
	for(int i = 1 ; i < n ; ++i)
	{
		int idx ;
		Fraction Min(1e9) ;
		for(int j = 0 ; j < n ; ++j)
		{
			if(mark[j] == 0 && split[j][i] < Min)
			{
				idx = j ;
				Min = split[j][i] ;
			}
		}
		order[i] = idx+1 ;
		mark[idx] = 1 ;
		cout<<Min<<"\n" ;
	}
	for(int i = 0 ; i < n ; ++i)
	{
		if(mark[i] == 0)
			order[n] = i+1 ;
	}
	for(int i = 1 ; i <= n ; ++i)
		cout<<order[i]<<" " ;
	cout<<"\n" ;
	return 0 ;
}		