#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
#include <algorithm>
#include <memory.h>

const int MAX = 20;
int map[MAX][MAX];
bool bVisited[MAX][MAX];

const int dy[4] = {-1,1,0,0};
const int dx[4] = {0,0,-1,1};

int N;
int nAnswer;

class Shark
{
public:
	int _y, _x;
	int _size;
	int _nCntEat;
};
Shark babyShark;

// dist,y,x
std::vector<std::tuple<int, int, int>> vecFish;

void Solve();
bool FindFish();
int Move();

int main()
{
	// IO Setting
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	// INPUT
	std::cin >> N;
	for (int y = 0; y < N; ++y) {
		for (int x = 0; x < N; ++x) {
			std::cin >> map[y][x];
			if (map[y][x] == 9) {
				// Init
				babyShark._y = y;
				babyShark._x = x;
				babyShark._size = 2;
				babyShark._nCntEat = 0;

				map[y][x] = 0;
			}
		}
	}

	Solve();

	return 0;
}

void Solve()
{
	// Init
	vecFish.reserve(MAX*MAX);

	while (FindFish()) {
		nAnswer += Move();
	}

	std::cout << nAnswer << "\n";
}

bool FindFish()
{
	int y = babyShark._y;
	int x = babyShark._x;

	bVisited[y][x] = true;

	// y,x,dist
	std::queue<std::tuple<int, int,int>> qBFS;
	qBFS.push(std::make_tuple(y,x,0));

	while (!qBFS.empty()) {
		int cy(0), cx(0), dist(0);

		std::tie(cy, cx, dist) = qBFS.front();
		qBFS.pop();

		for (int dir = 0; dir < 4; ++dir) {
			int ny = cy + dy[dir];
			int nx = cx + dx[dir];

			if (ny < 0 || ny >= N || nx < 0 || nx >= N)
				continue;

			if (bVisited[ny][nx])
				continue;

			bVisited[ny][nx] = true;

			if (map[ny][nx] == 0 || babyShark._size == map[ny][nx]) {
				// Just move
				qBFS.push(std::make_tuple(ny, nx, dist + 1));
			}
			else if (babyShark._size < map[ny][nx]) {
				// Can't move
				continue;
			}			
			else {	// babyShark._size > map[ny][nx]
				// Move
				qBFS.push(std::make_tuple(ny, nx, dist + 1));

				// Can eat
				vecFish.push_back(std::make_tuple(dist+1, ny, nx));
			}
		}
	}

	if (vecFish.empty())
		return false;

	return true;
}

int Move()
{
	if (vecFish.empty())
		return 0;

	std::sort(vecFish.begin(), vecFish.end());

	// Neareast fish
	int time(0), y(0), x(0);
	std::tie(time, y, x) = vecFish[0];

	// Move
	babyShark._y = y;
	babyShark._x = x;

	// Eat
	map[y][x] = 0;

	babyShark._nCntEat++;
	if (babyShark._nCntEat == babyShark._size) {
		babyShark._size++;
		babyShark._nCntEat = 0;
	}

	// Reset
	vecFish.clear();
	memset(bVisited, false, sizeof(bVisited));

	return time;
}