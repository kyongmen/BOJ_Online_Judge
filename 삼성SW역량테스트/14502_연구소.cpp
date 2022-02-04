#include <iostream>
#include <vector>
#include <memory.h>
#include <queue>

const int MAX = 8;
int map[MAX][MAX];
bool bVisited[MAX][MAX];

// U D L R
const int dy[4] = {-1,1,0,0};
const int dx[4] = {0,0,-1,1};

int N, M;
int nAnswer;

std::vector<std::pair<int, int>> vecVirus;

void Solve();
void SetWalls(int y, int x, int nCnt);
void SpreadVirus();
inline int GetSafeZoneSize();

int main()
{
	// IO Setting
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	// INPUT
	vecVirus.reserve(10);
	std::cin >> N >> M;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			std::cin >> map[y][x];
			// virus
			if (map[y][x] == 2) {
				vecVirus.push_back({ y,x });
			}
		}
	}

	Solve();

	return 0;
}

void Solve()
{
	// Set Walls
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			if (map[y][x] == 0) {
				map[y][x] = 1;
				SetWalls(y, x, 1);
				map[y][x] = 0;
			}
		}
	}

	std::cout << nAnswer << "\n";
}

void SetWalls(int y, int x, int nCnt)
{
	if (nCnt >= 3) {
		// BFS
		memset(bVisited, false, sizeof(bVisited));
		SpreadVirus();
		return;
	}

	// Set Walls
	for (int cy = y; cy < N; cy++) {
		for (int cx = x; cx < M; cx++) {
			if (map[cy][cx] == 0) {
				map[cy][cx] = 1;
				SetWalls(cy, cx+1, nCnt + 1);
				map[cy][cx] = 0;
			}
		}
		x = 0;
	}
}

void SpreadVirus() 
{
	// SAVE
	int mapCopy[MAX][MAX];
	memcpy(mapCopy, map, sizeof(map));

	for (auto elem : vecVirus) {
		int y = elem.first;
		int x = elem.second;
		
		std::queue<std::pair<int, int>> q;
		bVisited[y][x] = true;
		q.push({ y,x });

		while (!q.empty()) {
			int cy = q.front().first;
			int cx = q.front().second;
			q.pop();

			for (int dir = 0; dir < 4; dir++) {
				int ny = cy + dy[dir];
				int nx = cx + dx[dir];

				if (ny < 0 || ny >= N || nx < 0 || nx >= M)
					continue;

				if (map[ny][nx] == 1)
					continue;

				if (bVisited[ny][nx])
					continue;

				bVisited[ny][nx] = true;
				map[ny][nx] = 2;
				q.push({ ny,nx });
			}
		}
	}

	// Update answer
	int nTemp = GetSafeZoneSize();
	if (nTemp > nAnswer)
		nAnswer = nTemp;

	// LOAD
	memcpy(map, mapCopy, sizeof(mapCopy));
}

int GetSafeZoneSize()
{
	int nRet = 0;

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			if (map[y][x] == 0)
				nRet++;
		}
	}

	return nRet;
}