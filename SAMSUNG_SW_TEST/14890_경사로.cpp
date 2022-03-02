#include <iostream>
#include <memory.h>

const int MAX = 100;
int map[MAX][MAX];
bool bSelected[MAX][MAX];

int N, L;
int nAnswer;

void Solve();

int main()
{
	// IO Setting
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	// INPUT
	std::cin >> N >> L;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			std::cin >> map[y][x];
		}
	}

	Solve();

	return 0;
}

void Solve()
{
	// Check Row
	for (int y = 0; y < N; y++) {
		bool bSuccess = true;

		for (int x = 0; x < N - 1; x++) {
			int gap = map[y][x] - map[y][x + 1];

			if (gap == 0) {
				// pass
				continue;
			}
			else if (gap == 1) {
				// Downstair
				int temp = map[y][x + 1];
				for (int tx = x + 1; tx <= x + L; tx++) {
					if (tx > N - 1) {
						bSuccess = false;
						break;
					}

					if (map[y][tx] != temp
						|| bSelected[y][tx]) {
						bSuccess = false;
						break;
					}
				}
				if (!bSuccess)
					break;
				else {
					// Put runway
					for (int tx = x + 1; tx <= x + L; tx++) {
						bSelected[y][tx] = true;
					}
					x = x + L-1;
				}
			}
			else if (gap == -1) {
				// Upstair
				int temp = map[y][x];
				for (int tx = x; tx >= x-L+1; tx--) {
					if (tx <0) {
						bSuccess = false;
						break;
					}

					if (map[y][tx] != temp
						|| bSelected[y][tx]) {
						bSuccess = false;
						break;
					}
				}
				if (!bSuccess)
					break;
				else {
					// Put runway
					for (int tx = x; tx >= x - L + 1; tx--) {
						bSelected[y][tx] = true;
					}
				}
			}
			else {
				bSuccess = false;
				break;
			}			
		}
		if (bSuccess)
			nAnswer++;
	}

	// Reset bSelected[][]
	memset(bSelected, false, sizeof(bSelected));

	// Check Column
	for (int x = 0; x < N; x++) {
		bool bSuccess = true;

		for (int y = 0; y < N - 1; y++) {
			int gap = map[y][x] - map[y+1][x];

			if (gap == 0) {
				// pass
				continue;
			}
			else if (gap == 1) {
				// Downstair
				int temp = map[y+1][x];
				for (int ty = y + 1; ty <= y + L; ty++) {
					if (ty > N - 1) {
						bSuccess = false;
						break;
					}

					if (map[ty][x] != temp
						|| bSelected[ty][x]) {
						bSuccess = false;
						break;
					}
				}
				if (!bSuccess)
					break;
				else {
					// Put runway
					for (int ty = y + 1; ty <= y + L; ty++) {
						bSelected[ty][x] = true;
					}
					y = y + L-1;
				}
			}
			else if (gap == -1) {
				// Upstair
				int temp = map[y][x];
				for (int ty = y; ty >= y - L + 1; ty--) {
					if (ty < 0) {
						bSuccess = false;
						break;
					}

					if (map[ty][x] != temp
						|| bSelected[ty][x]) {
						bSuccess = false;
						break;
					}
				}
				if (!bSuccess)
					break;
				else {
					// Put runway
					for (int ty = y; ty >= y - L + 1; ty--) {
						bSelected[ty][x] = true;
					}
				}
			}
			else {
				bSuccess = false;
				break;
			}
		}
		if (bSuccess)
			nAnswer++;
	}

	std::cout << nAnswer << "\n";
}