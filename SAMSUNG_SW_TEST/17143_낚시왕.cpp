#include <iostream>
#include <vector>
#include <memory.h>
#include <algorithm>
#include <queue>

const int MAX = 100;
int map[MAX][MAX];

const int dy[5] = {0,-1,1,0,0};
const int dx[5] = {0,0,0,1,-1};

int nAnswer;
int R, C, M;

class Shark
{
public:
	int _y, _x;
	int _speed;
	int _dir;
	// unique value
	int _size;

	explicit Shark(int y, int x, int speed, int dir, int size)
		: _y(y), _x(x), _speed(speed), _dir(dir), _size(size)
	{};
};
std::vector<Shark> vecShark;

void Solve();
void CatchShark(int column);
void MoveShark();

int main()
{
	// IO Setting
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	// INPUT
	std::cin >> R >> C >> M;
	for (int m = 0; m < M; ++m) {
		int r(0), c(0), s(0), d(0), z(0);
		std::cin >> r >> c >> s >> d >> z;

		// Timeout
		if (d <= 2) {
			// U D
			s %= 2 * (R-1);
		}
		else {
			// R L
			s %= 2 * (C - 1);
		}

		vecShark.emplace_back(r - 1, c - 1, s, d, z);
		map[r - 1][c - 1] = z;
	}

	Solve();

	return 0;
}

void Solve()
{
	for (int column = 0; column < C; ++column) {
		CatchShark(column);
		MoveShark();
	}

	std::cout << nAnswer << "\n";
}

void CatchShark(int column)
{
	for (int y = 0; y < R; ++y) {
		if (map[y][column]) {
			auto it = std::find_if(vecShark.begin(), vecShark.end(), [=](auto shark) {
				return map[y][column] == shark._size;
			});

			if (it != vecShark.end()) {
				// Catch
				nAnswer += (*it)._size;
				vecShark.erase(it);

				map[y][column] = 0;
				break;
			}
		}
	}
}

void MoveShark()
{
	int copyMap[MAX][MAX];
	memset(copyMap, 0, sizeof(copyMap));

	std::queue<int> qDied;
	for (auto& shark : vecShark) {
		for (int s = 0; s < shark._speed; ++s) {
			int ny = shark._y + dy[shark._dir];
			int nx = shark._x + dx[shark._dir];

			if (ny < 0) {
				ny = 1;
				shark._dir = 2;
			}
			else if (ny >= R) {
				ny = R - 2;
				shark._dir = 1;
			}
			else if (nx < 0) {
				nx = 1;
				shark._dir = 3;
			}
			else if (nx >= C) {
				nx = C - 2;
				shark._dir = 4;
			}

			shark._y = ny;
			shark._x = nx;
		}		

		if (copyMap[shark._y][shark._x] == 0) {
			// One shark
			copyMap[shark._y][shark._x] = shark._size;
		}
		else {
			// Big Shark Eat small shark
			if (shark._size < copyMap[shark._y][shark._x]) {
				qDied.push(shark._size);
			}
			else {
				qDied.push(copyMap[shark._y][shark._x]);
				copyMap[shark._y][shark._x] = shark._size;
			}
		}
	}

	memcpy(map, copyMap, sizeof(copyMap));

	while (!qDied.empty()) {
		int id = qDied.front();
		qDied.pop();

		auto it = std::find_if(vecShark.begin(), vecShark.end(), [=](auto shark) {
			return shark._size == id;
		});
		if (it != vecShark.end()) {
			vecShark.erase(it);
		}
	}
}