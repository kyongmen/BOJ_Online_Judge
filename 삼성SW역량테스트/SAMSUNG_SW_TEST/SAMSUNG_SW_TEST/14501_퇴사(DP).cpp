#include <iostream>
#include <algorithm>

const int MAX = 15+1;

int N;
int T[MAX], P[MAX];
int dp[MAX];

void Solve();

int main()
{
	// IO Setting
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	// INPUT
	std::cin >> N;
	for (int n = 1; n <= N; n++) {
		std::cin >> T[n] >> P[n];
	}

	Solve();
	
	return 0;
}

void Solve()
{
	for (int n = N; n >= 0; n--) {
		int nextDay = n + T[n];

		if (nextDay <= N + 1) {
			dp[n] = std::max(dp[n + 1], dp[nextDay] + P[n]);
		}
		else
			dp[n] = dp[n + 1];
	}

	std::cout << dp[0] << "\n";
}