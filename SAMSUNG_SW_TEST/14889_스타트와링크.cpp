#include <iostream>
#include <cmath>

const int MAX = 20;

int mapAbility[MAX + 1][MAX + 1];
bool bSelected[MAX + 1];

int N, HalfN;
int nAnswer = 1e9;

void Solve();
void DFS(int nCurIdx, int nCnt);
int Calculate();

int main()
{
	// IO Setting
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	// INPUT
	std::cin >> N;
	HalfN = N / 2;

	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++) {
			std::cin >> mapAbility[y][x];
		}
	}

	Solve();

	return 0;
}

void Solve()
{
	// Set Team
	DFS(1, 1);

	std::cout << nAnswer << "\n";
}

void DFS(int nCurIdx, int nCnt)
{
	if (nCnt > HalfN) {
		// Update Answer
		int temp = Calculate();
		if (temp < nAnswer)
			nAnswer = temp;
		return;
	}

	for (int idx = nCurIdx; idx <= N; idx++) {
		if (bSelected[idx])
			continue;

		bSelected[idx] = true;
		DFS(idx + 1, nCnt + 1);
		bSelected[idx] = false;
	}
}

int Calculate()
{
	// StartTeam: bSelected-true
	// LinkTeam: bSelected-false

	int nStartScore = 0;
	int nLinkScore = 0;

	for (int y = 1; y <= N; y++) {
		if (bSelected[y]) {
			for (int x = 1; x <= N; x++) {
				if (bSelected[x]) {
					// StartTeam
					nStartScore += mapAbility[y][x];
				}
			}
		}
		else {
			for (int x = 1; x <= N; x++) {
				if (!bSelected[x]) {
					// LinkTeam
					nLinkScore += mapAbility[y][x];
				}
			}
		}		
	}

	return static_cast<int>(std::fabs(nStartScore - nLinkScore));
}