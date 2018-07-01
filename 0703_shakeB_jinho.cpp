//https://www.acmicpc.net/problem/15821
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

	priority_queue<long double, vector<long double>, greater<long double> > pq;	//minHeap

	int K, N;
	cin >> N;
	cin >> K;

	FOR(i, N)
	{
		int num;
		cin >> num;
		long double sum = -1;

		FOR(j, num)
		{
			long double x, y;
			cin >> x;
			cin >> y;
			sum = max(sum, x * x + y * y);
		}
		pq.push(sum);
	}

	FOR(i, K - 1)			//remove minimum K-1
	{
		pq.pop();
	}

	long double answer = pq.top();


	cout.setf(ios::fixed, ios::floatfield);		//Set FloatPoint Precision 2
	cout << setprecision(2) << answer << endl;

	return 0;
}
