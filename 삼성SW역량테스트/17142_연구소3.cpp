#include <iostream>
#include <array>
#include <memory.h>
#include <queue>
#include <tuple>

const int EMPTY = 0;
const int WALL = -1;
const int VIRUS = -2;

const int MAX = 50;
int map[MAX][MAX];
bool bVisited[MAX][MAX];

const int dy[4] = {-1,1,0,0};
const int dx[4] = {0,0,-1,1};

int N, M, numVirus;

int nAnswer = 1e6;

class Virus
{
public:
	int _y, _x;
	bool _bActivated;

	Virus() :_bActivated(false)
	{};

	Virus(int y, int x) 
		: _y(y),_x(x),_bActivated(false)
	{};
};
std::array<Virus ,10> arrVirus;

void Solve();
void ChooseVirus(int nCnt, int nIdx);
void Spread();
void UpdateAnswer();

int main()
{
	// IO Setting
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	// INPUT
	std::cin >> N >> M;
	int idx = 0;

	for (int y = 0; y < N; ++y) {
		for (int x = 0; x < N; ++x) {
			std::cin >> map[y][x];
			
			if (map[y][x] == 1) {
				map[y][x] = WALL;
			}
			else if (map[y][x] == 2) {
				map[y][x] = VIRUS;
				
				arrVirus[idx] = Virus(y,x);
				idx++;
			}
		}
	}
	numVirus = idx;

	Solve();

	return 0;
}

void Solve()
{
	// Choose Virus
	ChooseVirus(0, 0);

	if (nAnswer == 1e6)
		nAnswer = -1;

	std::cout << nAnswer << "\n";
}

void ChooseVirus(int nCnt, int nIdx)
{
	if (nCnt == M) {
		// Spread Virus
		Spread();
		return;
	}

	for (int idx = nIdx; idx < numVirus; ++idx) {
		if (!arrVirus[idx]._bActivated) {
			arrVirus[idx]._bActivated  = true;
			ChooseVirus(nCnt + 1, idx + 1);
			arrVirus[idx]._bActivated = false;
		}
	}
}

void Spread()
{
	int copyMap[MAX][MAX];
	memcpy(copyMap, map, sizeof(map));

	// BFS
	// y, x, time
	std::queue<std::tuple<int, int, int>> qVirus;
	for (int idx = 0; idx < numVirus; ++idx) {
		if (arrVirus[idx]._bActivated) {
			const auto& virus = arrVirus[idx];

			bVisited[virus._y][virus._x] = true;
			qVirus.emplace(virus._y, virus._x, 0);
		}
	}

	while (!qVirus.empty()) {
		int y(0), x(0), time(0);
		std::tie(y, x, time) = qVirus.front();
		qVirus.pop();

		for (int dir = 0; dir < 4; ++dir) {
			int ny = y + dy[dir];
			int nx = x + dx[dir];

			if (ny < 0 || ny >= N || nx < 0 || nx >= N)
				continue;		

			if (bVisited[ny][nx])
				continue;

			if (map[ny][nx] == WALL)
				continue;			

			bVisited[ny][nx] = true;
			qVirus.push(std::make_tuple(ny, nx, time + 1));

			if (map[ny][nx] == EMPTY) {
				map[ny][nx] = time + 1;
			}
		}
	}

	// Update Answer
	UpdateAnswer();

	memcpy(map, copyMap, sizeof(copyMap));
	memset(bVisited, false, sizeof(bVisited));
}

void UpdateAnswer()
{
	bool bSuccess = true;
	int time = 0;

	for (int y = 0; y < N; ++y) {
		for (int x = 0; x < N; ++x) {
			if (map[y][x] > time) {
				time = map[y][x];
			}
			else if (map[y][x] == EMPTY) {
				bSuccess = false;
				break;
			}			
		}
		if (!bSuccess)
			break;
	}

	if(bSuccess && (time < nAnswer)){
		nAnswer = time;
	}
}