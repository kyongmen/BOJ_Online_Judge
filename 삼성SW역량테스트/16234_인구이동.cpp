#include <iostream>
#include <memory.h>
#include <queue>

const int MAX = 50;
int mapPopulation[MAX][MAX];
bool bVisited[MAX][MAX];

const int dy[4] = {-1,1,0,0};
const int dx[4] = {0,0,-1,1};

int N, L, R;
int nAnswer;

void Solve();
bool MovePeople();
bool Move(int y, int x);
bool Check(int y, int x);

int main()
{
	// IO Setting
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	// INPUT
	std::cin >> N >> L >> R;
	for (int y = 0; y < N; ++y) {
		for (int x = 0; x < N; ++x) {
			std::cin >> mapPopulation[y][x];
		}
	}

	Solve();

	return 0;
}

void Solve()
{
	while (true) {
		bool bMoved = MovePeople();
		if (bMoved == false)
			break;

		memset(bVisited, false, sizeof(bVisited));

		nAnswer++;
	}
	
	std::cout << nAnswer << "\n";
}

bool MovePeople()
{
	bool bRet = false;

	for (int y = 0; y < N; ++y) {
		for (int x = 0; x < N; ++x) {
			if (!bVisited[y][x] && Check(y,x)) {
				if (Move(y, x))
					bRet = true;
			}
		}
	}

	return bRet;
}

bool Move(int y, int x)
{
	std::queue<std::pair<int, int>> qBFS;
	std::queue<std::pair<int, int>> qSave;

	bVisited[y][x] = true;
	qBFS.push({ y,x });

	int nSum = mapPopulation[y][x];
	qSave.push({ y,x });

	while (!qBFS.empty()) {
		int cy = qBFS.front().first;
		int cx = qBFS.front().second;
		qBFS.pop();

		for (int dir = 0; dir < 4; ++dir) {
			int ny = cy + dy[dir];
			int nx = cx + dx[dir];

			if (ny < 0 || ny >= N || nx < 0 || nx >= N)
				continue;

			if (bVisited[ny][nx])
				continue;

			int gap = std::abs(mapPopulation[cy][cx] - mapPopulation[ny][nx]);
			if (L <= gap && gap <= R) {
				bVisited[ny][nx] = true;
				qBFS.push({ ny,nx });

				qSave.push({ ny,nx });
				nSum += mapPopulation[ny][nx];
			}
		}
	}

	int nSize = qSave.size();
	if (nSize == 1) {
		return false;
	}

	while (!qSave.empty()) {
		int cy = qSave.front().first;
		int cx = qSave.front().second;
		qSave.pop();

		mapPopulation[cy][cx] = nSum / nSize;
	}

	return true;
}

bool Check(int y, int x)
{
	for (int dir = 0; dir < 4; ++dir) {
		int ny = y + dy[dir];
		int nx = x + dx[dir];

		if (ny < 0 || ny >= N || nx < 0 || nx >= N)
			continue;

		int gap = std::abs(mapPopulation[y][x] - mapPopulation[ny][nx]);
		if (L <= gap && gap <= R)
			return true;
	}

	return false;
}