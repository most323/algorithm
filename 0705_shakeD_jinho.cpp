//https://www.acmicpc.net/problem/15823
//풀긴 풀었는데 너가 볼수 있을정도로 깨끗하게 짠건 아닌듯..
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

int N, M;
vector<int> v;

bool func(int mid)
{
	int cnt = 0;

	FOR(i, N - mid + 1)
	{
		map<int, int> m;
		bool isSet = true;
		for (int j = i; j < i + mid; ++j)
		{
			if (m.count(v[j]) == 1)
			{
				int tmp = v[j];
				int k = j - 1;
				while (v[k] != tmp)
				{
					k--;
				}

				i = k;
				isSet = false;
				break;
			}

			m.insert(make_pair(v[j], 0));
		}
		
		if (isSet)
		{
			i += mid - 1;
			cnt++;
			if (cnt == M)
			{
				return true;
			}
		}

	}

	return false;
}
int main()
{
	//freopen("shake1.txt", "r", stdin);
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	
	cin >> N;
	cin >> M;
	
	
	FOR(i, N)
	{
		int tmp;
		cin >> tmp;
		v.push_back(tmp);
	}

	int left = 1;
	int right = N;

	int mid;
	int answer = 1;
	while (left <= right)
	{
		mid = (left + right) / 2;

		if (func(mid))		//Success
		{
			left = mid + 1;
			answer = mid;
		}

		else
		{
			right = mid - 1;
		}
	}

	cout << answer << endl;

	return 0;
}
