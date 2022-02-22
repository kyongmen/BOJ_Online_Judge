#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

const int MAX = 100;
int matrix[MAX][MAX];

int R = 3, C = 3;
int r, c, k;

void Solve();
void Calculate();

int main()
{
	// IO Setting
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	// INPUT
	std::cin >> r >> c >> k;
	--r, --c;
	for (int y = 0; y < R; ++y) {
		for (int x = 0; x < C; ++x) {
			std::cin >> matrix[y][x];
		}
	}

	Solve();

	return 0;
}

void Solve()
{
	int time = 0;
	
	while (true) {
		if (matrix[r][c] == k || time > 100)
			break;

		Calculate();
		time++;
	}

	if (time > 100)
		time = -1;

	std::cout << time << "\n";
}

void Calculate()
{
	if (R >= C) {
		// R Operation
		int cMax = 0;
		
		for (int y = 0; y < R; ++y) {
			// number, count
			std::map<int, int> mapNumber;

			for (int x = 0; x < C; ++x) {
				if (matrix[y][x]) {
					mapNumber[matrix[y][x]]++;
					matrix[y][x] = 0;
				}
			}

			// Sort
			std::vector<std::pair<int, int>> vecNumber;
			for (const auto& elem : mapNumber) {
				vecNumber.emplace_back(elem);
			}

			std::sort(vecNumber.begin(), vecNumber.end(), [](const auto& item1, const auto& item2) {
				if (item1.second == item2.second)
					return item1.first < item2.first;

				return item1.second < item2.second;
			});

			// Arrange
			int x = 0;
			for (const auto& elem : vecNumber) {
				matrix[y][x] = elem.first;
				matrix[y][x + 1] = elem.second;
				x += 2;
			}

			if (cMax <= x)
				cMax = x;
		}
		if (cMax > 100)
			cMax = 100;

		C = cMax;
	}
	else {
		// C Operation
		int rMax = 0;

		for (int x = 0; x < C; ++x) {
			// number, count
			std::map<int, int> mapNumber;

			for (int y = 0; y < R; ++y) {
				if (matrix[y][x]) {
					mapNumber[matrix[y][x]]++;
					matrix[y][x] = 0;
				}
			}

			// Sort
			std::vector<std::pair<int, int>> vecNumber;
			for (const auto& elem : mapNumber) {
				vecNumber.emplace_back(elem);
			}

			std::sort(vecNumber.begin(), vecNumber.end(), [](const auto& item1, const auto& item2) {
				if (item1.second == item2.second)
					return item1.first < item2.first;

				return item1.second < item2.second;
			});

			// Arrange
			int y = 0;
			for (const auto& elem : vecNumber) {
				matrix[y][x] = elem.first;
				matrix[y+1][x] = elem.second;
				y += 2;
			}

			if (rMax <= y)
				rMax = y;
		}

		if (rMax > 100)
			rMax = 100;

		R = rMax;
	}
}