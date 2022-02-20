#include <iostream>
#include <memory.h>

const int MAX = 50;
int map[MAX][MAX];

const int dy[4] = {-1,0,1,0};
const int dx[4] = {0,1,0,-1};

int yTop, yBottom;
int R, C, T;

void Solve();
void Diffusion();
void Blow();

inline void PrintAnswer();

int main()
{
	// IO Setting
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	// INPUT
	std::cin >> R >> C >> T;
	for (int y = 0; y < R; ++y) {
		for (int x = 0; x < C; ++x) {
			std::cin >> map[y][x];

			if (map[y][x] == -1) {
				if (!yTop)
					yTop = y;
				else
					yBottom = y;
			}
		}
	}

	Solve();

	return 0;
}

void Solve()
{
	while (T--) {
		Diffusion();
		Blow();
	}

	PrintAnswer();
}

void Diffusion()
{
	int copyMap[MAX][MAX];
	memset(copyMap, 0, sizeof(copyMap));

	for (int y = 0; y < R; ++y) {
		for (int x = 0; x < C; ++x) {
			if (map[y][x] > 0) {
				int nRemain = map[y][x];

				for (int dir = 0; dir < 4; ++dir) {
					int ny = y + dy[dir];
					int nx = x + dx[dir];

					// Out of range
					if (ny < 0 || ny >= R || nx < 0 || nx >= C)
						continue;

					// Air Cleaner
					if (map[ny][nx]==-1)
						continue;

					copyMap[ny][nx] += map[y][x] / 5;
					nRemain -= map[y][x] / 5;
				}

				copyMap[y][x] += nRemain;
			}
			else if (map[y][x] == -1) {
				copyMap[y][x] = -1;
			}
		}
	}

	memcpy(map, copyMap, sizeof(copyMap));
}

void Blow()
{
	typedef std::pair<int, int> position;
	
	// CCW
	{
		// search dir: 0 1 2 3
		int dir = 0;
		position prev(yTop + dy[dir], 0);
		position next(prev.first + dy[dir], 0);
		position end(yTop, 0);

		while (true) {
			map[prev.first][prev.second] = map[next.first][next.second];

			int ny = next.first + dy[dir];
			int nx = next.second + dx[dir];
			if (ny<0 || ny>yTop || nx < 0 || nx >= C) {
				// out of range
				dir = (dir + 1 + 4) % 4;

				ny = next.first + dy[dir];
				nx = next.second + dx[dir];
			}

			prev = next;
			next = { ny, nx };

			if (next == end) {
				// new air
				map[prev.first][prev.second] = 0;
				break;
			}
		}
	}

	// CW
	{
		// search dir: 2 1 0 3
		int dir = 2;
		position prev(yBottom + dy[dir], 0);
		position next(prev.first + dy[dir], 0);
		position end(yBottom, 0);

		while (true) {
			map[prev.first][prev.second] = map[next.first][next.second];

			int ny = next.first + dy[dir];
			int nx = next.second + dx[dir];
			if (ny<yBottom || ny>=R || nx < 0 || nx >= C) {
				// out of range
				dir = (dir - 1 + 4) % 4;

				ny = next.first + dy[dir];
				nx = next.second + dx[dir];
			}

			prev = next;
			next = { ny, nx };

			if (next == end) {
				// new air
				map[prev.first][prev.second] = 0;
				break;
			}
		}
	}
}

void PrintAnswer()
{
	int nAnswer = 0;
	for (int y = 0; y < R; ++y) {
		for (int x = 0; x < C; ++x) {
			if (map[y][x] == 0 || map[y][x] == -1)
				continue;

			nAnswer += map[y][x];
		}
	}

	std::cout << nAnswer << "\n";
}