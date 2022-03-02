#include <iostream>
#include <vector>
#include <algorithm>
#include <array>

const int MAX_LENGTH = 12;
const int MAX_HORSE = 10;

const int WHITE = 0;
const int RED = 1;
const int BLUE = 2;

const int dy[5] = {0,0,0,-1,1};
const int dx[5] = {0,1,-1,0,0};

int mapColor[MAX_LENGTH][MAX_LENGTH];

int N, K;

class Horse
{
public:
	int _y, _x;
	int _dir;
};

// idx
std::vector<int> mapHorse[MAX_LENGTH][MAX_LENGTH];
std::array<Horse, MAX_HORSE> arrHorse;

void Solve();
int MoveHorse(int idx);

int main()
{
	// IO Setting
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	// INPUT
	std::cin >> N >> K;
	for (int y = 0; y < N; ++y) {
		for (int x = 0; x < N; ++x) {
			std::cin >> mapColor[y][x];
		}
	}

	for (int k = 0; k < K; ++k) {
		int y(0), x(0), dir(0);
		std::cin >> y >> x >> dir;

		mapHorse[--y][--x].push_back(k);
		arrHorse[k] = { y,x,dir };
	}

	Solve();

	return 0;
}

void Solve()
{
	bool bSuccess = false;
	int time = 0;

	while (time <= 1000 && !bSuccess) {
		for (int k = 0; k < K; ++k) {
			int nCnt = MoveHorse(k);
			if (nCnt >= 4) {
				bSuccess = true;
				break;
			}
		}
		time++;
	}
	
	if (time > 1000)
		time = -1;
	
	std::cout << time << "\n";
}

int MoveHorse(int idx)
{
	auto& horse = arrHorse[idx];
	int y = horse._y;
	int x = horse._x;

	int ny = y + dy[horse._dir];
	int nx = x + dx[horse._dir];

	if (ny < 0 || ny >= N || nx < 0 || nx >= N
		|| mapColor[ny][nx] == BLUE) {
		// Turn direction
		if (horse._dir & 1) {
			// Odd
			horse._dir++;
		}
		else {
			horse._dir--;
		}

		ny = y + dy[horse._dir];
		nx = x + dx[horse._dir];
		
		if (ny < 0 || ny >= N || nx < 0 || nx >= N
			|| mapColor[ny][nx] == BLUE)
			return 0;
	}

	auto& cur = mapHorse[y][x];
	auto& next = mapHorse[ny][nx];

	auto target = std::find(cur.begin(), cur.end(), idx);
	if (mapColor[ny][nx] == RED) {
		std::reverse(target, cur.end());
	}

	for (auto it = target; it != cur.end(); ++it) {
		arrHorse[*it]._y = ny;
		arrHorse[*it]._x = nx;
		
		next.push_back(*it);
	}

	cur.erase(target, cur.end());
	return next.size();
}