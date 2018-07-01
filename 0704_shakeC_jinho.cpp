//https://www.acmicpc.net/problem/15822
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

int N;
int **dp;
int **arr;
int func(int i, int j)
{
	int minV = INTEGER_MAX;
	if (i >= 1)
	{
		if (dp[i - 1][j] == -1)
		{
			dp[i - 1][j] = func(i - 1, j);
		}

		minV = min(minV, dp[i - 1][j]);
	}

	if (j >= 1)
	{
		if (dp[i][j - 1] == -1)
		{
			dp[i][j - 1] = func(i, j - 1);
		}
		
		minV = min(minV, dp[i][j - 1]);
	}

	if (i >= 1 && j >= 1)
	{
		if (dp[i - 1][j - 1] == -1)
		{
			dp[i - 1][j - 1] = func(i - 1, j - 1);
		}
		minV = min(minV, dp[i - 1][j - 1]);
	}

	dp[i][j] = minV + (arr[i][0] - arr[j][1]) * (arr[i][0] - arr[j][1]);

	return dp[i][j];
}
int main()
{
	//freopen("shake1.txt", "r", stdin);
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	
	cin >> N;

	dp = new int *[N];
	arr = new int *[N];

	FOR(i, N)
	{
		dp[i] = new int[N];
		FOR(j, N)
		{
			dp[i][j] = -1;
		}
	}

	
	FOR(i, N)
	{
		arr[i] = new int[2];
	}

	FOR(i, N)
	{
		cin >> arr[i][0];
	}

	FOR(i, N)
	{
		cin >> arr[i][1];
	}

	dp[0][0] = (arr[0][0] - arr[0][1]) * (arr[0][0] - arr[0][1]);
	dp[1][0] = (arr[1][0] - arr[0][1]) * (arr[1][0] - arr[0][1]) + dp[0][0];
	dp[0][1] = (arr[0][0] - arr[1][1]) * (arr[0][0] - arr[1][1]) + dp[0][0];

	
	cout << func(N - 1, N - 1) << endl;

	FOR(i, N)
	{
		delete(dp[i]);
		delete(arr[i]);
	}

	delete(arr);
	delete(dp);

	return 0;
}
