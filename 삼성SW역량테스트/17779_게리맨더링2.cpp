#include <iostream>
#include <memory.h>
#include <algorithm>

const int MAX = 20+1;
int map[MAX][MAX];
bool bSelected[MAX][MAX];

int N;
int nAnswer = 1e6;

void Solve();
void CheckRegion(int y, int x, int d1, int d2);

int main()
{
	// IO Setting
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	// INPUT
	std::cin >> N;
	for (int y = 1; y <= N; ++y) {
		for (int x = 1; x <= N; ++x) {
			std::cin >> map[y][x];
		}
	}

	Solve();

	return 0;
}

void Solve()
{
	for (int y = 1; y <= N; ++y) {
		for (int x = 1; x <= N; ++x) {

			for (int d1 = 1; d1 < N; ++d1) {
				for (int d2 = 1; d2 < N; ++d2) {

					if (y + d1 + d2 <= N && x - d1 >= 1 && x + d2 <= N)
						CheckRegion(y, x, d1, d2);
				}
			}
		}
	}

	std::cout << nAnswer << "\n";
}

void CheckRegion(int y, int x, int d1, int d2)
{
	// Region 5 Boundary
	for (int t = 1; t <= d1; ++t) {
		bSelected[y + t][x - t] = true;
		bSelected[y + d1 + d2 - t][x - d1 + d2 + t] = true;
	}
	for (int t = 1; t <= d2; ++t) {
		bSelected[y + d1 + t][x -d1 + t] = true;
		bSelected[y + d2 - t][x + d2 - t] = true;
	}

	// Calculate Sum
	int sum[6] = { 0, };
	
	for (int cy = 1; cy <= N; ++cy) {
		bool bStart = false;
		bool bEnd = false;

		for (int cx = 1; cx <= N; ++cx) {
			if (bSelected[cy][cx]) {
				sum[5] += map[cy][cx];

				if (bStart)
					bEnd = true;

				if (cy > y && cy < y + d1 + d2) 
					bStart = true;

				continue;
			}
					
			if (bStart && !bEnd) {
				sum[5] += map[cy][cx];
				continue;
			}

			if (cy < y + d1 && cx <= x) {
				// Region 1
				sum[1] += map[cy][cx];
			}
			else if (cy <= y + d2 && x<cx && cx <= N) {
				// Region 2
				sum[2] += map[cy][cx];
			}
			else if (y + d1 <= cy && cy <= N && cx < x - d1 + d2) {
				// Region 3
				sum[3] += map[cy][cx];
			}
			else if (y + d2 < cy && cy <= N && x - d1 + d2 <= cx && cx <= N) {
				// Region 4
				sum[4] += map[cy][cx];
			}
		}
	}

	std::sort(sum+1, sum+6);
	int gap = sum[5] - sum[1];
	if (gap < nAnswer)
		nAnswer = gap;

	// reset
	memset(bSelected, false, sizeof(bSelected));
}