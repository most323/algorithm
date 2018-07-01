//https://www.acmicpc.net/problem/15820
#include <iostream>			
#include <string>			
#include <vector>			
#include <algorithm>			
#include <cassert>			
#include <functional>			
#include <queue>			
#include <cmath>			
#include <map>			
#include <unordered_map>			
#include <set>			
#include <unordered_set>			
#include <list>			
#include <stack>			
#include <iomanip>
#define DOUBLE_MAX 1.7976931348623158e+308			
#define INTEGER_MAX	2147483647		
#define FOR(x, n) for(int x = 0 ; x < n ; ++x)			
#define vi vector<int>			
#define vvi vector<vector<int>>			
#define vd vector<double>			
#define vvd vector<vector<double>>			


#pragma warning(disable : 4996)			
using namespace std;


int main()
{
	freopen("shake1.txt", "r", stdin);
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int S1, S2;
	cin >> S1;
	cin >> S2;

	bool testCase, sampleCase;
	testCase = sampleCase = true;

	FOR(i, S1)		//sampleCase
	{
		int a, b;
		cin >> a;
		cin >> b;
		if (a != b)
		{
			sampleCase = false;
		}
	}

	FOR(i, S2)		//testCase
	{
		int a, b;
		cin >> a;
		cin >> b;
		if (a != b)
		{
			testCase = false;
		}
	}

	if (!sampleCase)
	{
		cout << "Wrong Answer" << endl;
	}

	else
	{
		if (testCase)
		{
			cout << "Accepted" << endl;
		}

		else
		{
			cout << "Why Wrong!!!" << endl;
		}
	}
	return 0;
}
