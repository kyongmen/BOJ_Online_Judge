#include <iostream>
#include <queue>
#include <tuple>

int blue_map[4][6];
int green_map[6][4];

int N;
int answer;

// type, y, x
std::queue<std::tuple<int, int, int>> qCommand;

void Solve();
void PutBlock(int type, int y, int x);
void PopBlock();
void CheckSpecial();

int main()
{
	// IO Setting
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	// INPUT
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		int type(0), y(0), x(0);
		std::cin >> type >> y >> x;
		qCommand.push(std::make_tuple(type, y, x));
	}

	Solve();

	return 0;
}

void Solve()
{
	while (!qCommand.empty()) {
		int type(0), y(0), x(0);
		std::tie(type, y, x) = qCommand.front();
		qCommand.pop();

		// Operate
		PutBlock(type, y, x);
		PopBlock();
		CheckSpecial();
	}

	int nCntTiles(0);
	for (int y = 0; y < 4; ++y) {
		for (int x = 2; x < 6; ++x) {
			if (blue_map[y][x])
				nCntTiles++;
		}
	}
	for (int y = 2; y < 6; ++y) {
		for (int x = 0; x < 4; ++x) {
			if (green_map[y][x])
				nCntTiles++;
		}
	}

	std::cout << answer << "\n";
	std::cout << nCntTiles << "\n";
}

void PutBlock(int type, int y, int x)
{
	if (type == 1) {
		// blue
		int nx = 0;
		while (true) {
			if (nx>=6 || blue_map[y][nx]) {
				blue_map[y][nx-1] = 1;
				break;
			}
			nx++;
		}
		// green
		int ny = 0;
		while (true) {
			if (ny >= 6 || green_map[ny][x]) {
				green_map[ny - 1][x] = 1;
				break;
			}
			ny++;
		}
	}
	else if (type == 2) {
		// blue
		int nx = 0;
		while (true) {
			if (nx + 2 >= 6 || blue_map[y][nx + 2]) {
				blue_map[y][nx] = 1;
				blue_map[y][nx + 1] = 1;
				break;
			}
			nx++;
		}
		// green
		int x1(x),x2(x+1);
		int ny = 0;
		while (true) {
			if (ny >= 6 || green_map[ny][x1] || green_map[ny][x2]) {
				green_map[ny-1][x1] = 1;
				green_map[ny - 1][x2] = 1;
				break;
			}
			ny++;
		}
	}
	else if (type == 3) {
		// blue
		int y1(y), y2(y + 1);
		int nx = 0;
		while (true) {
			if (nx >= 6 || blue_map[y1][nx] || blue_map[y2][nx]) {
				blue_map[y1][nx - 1] = 1;
				blue_map[y2][nx - 1] = 1;
				break;
			}
			nx++;
		}
		// green
		int ny = 0;
		while (true) {
			if (ny + 2 >= 6 || green_map[ny + 2][x]) {
				green_map[ny][x] = 1;
				green_map[ny + 1][x] = 1;
				break;
			}
			ny++;
		}
	}
}

void PopBlock()
{
	// blue
	for (int x = 5; x >= 0; --x) {
		bool bPop(true);
		for (int y = 0; y < 4; ++y) {
			if (!blue_map[y][x]) {
				bPop = false;
				break;
			}
		}

		if (bPop) {
			answer++;
			for (int tx = x; tx > 0; --tx) {
				for (int y = 0; y < 4; ++y) {
					blue_map[y][tx] = blue_map[y][tx - 1];
				}
			}
			x++;
		}
	}

	// green
	for (int y = 5; y >= 0; --y) {
		bool bPop(true);
		for (int x = 0; x < 4; ++x) {
			if (!green_map[y][x]) {
				bPop = false;
				break;
			}
		}

		if (bPop) {
			answer++;
			for (int ty = y; ty > 0; --ty) {
				for (int x = 0; x < 4; ++x) {
					green_map[ty][x] = green_map[ty - 1][x];
				}
			}
			y++;
		}
	}
}

void CheckSpecial()
{
	// blue
	int nLine = 0;
	for (int x = 1; x >= 0; --x) {
		for (int y = 0; y < 4; ++y) {
			if (blue_map[y][x]) {
				nLine++;
				break;
			}
		}
	}
	if (nLine) {
		for (int x = 5; x >= 2; --x) {
			for (int y = 0; y < 4; ++y) {
				blue_map[y][x] = blue_map[y][x - nLine];
			}
		}
		for (int x = 1; x >= 0; --x) {
			for (int y = 0; y < 4; ++y) {
				blue_map[y][x] = 0;
			}
		}
	}

	// green
	nLine = 0;
	for (int y = 1; y >= 0; --y) {
		for (int x = 0; x < 4; ++x) {
			if (green_map[y][x]) {
				nLine++;
				break;
			}
		}
	}

	if (nLine) {
		for (int y = 5; y >= 2; --y) {
			for (int x = 0; x < 4; ++x) {
				green_map[y][x] = green_map[y - nLine][x];
			}
		}
		for (int y = 1; y >= 0; --y) {
			for (int x = 0; x < 4; ++x) {
				green_map[y][x] = 0;
			}
		}
	}
}