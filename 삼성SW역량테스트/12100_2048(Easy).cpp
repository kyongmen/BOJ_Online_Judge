#include <iostream>
#include <memory.h>
#include <queue>

const int MAX = 20;
int map[MAX][MAX];

int N;
int nAnswer;

void Solve();
void Move(int dir);
void DFS(int nCnt);
inline int GetMaxValue();

void MoveLeft();
void MoveRight();
void MoveUp();
void MoveDown();

int main()
{
	// IO Setting
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	// INPUT
	std::cin >> N;
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
	DFS(0);

	std::cout << nAnswer << "\n";
}

void Move(int dir)
{
	// L D R U
	switch (dir)
	{
	case 0:
		MoveLeft();
		break;
	case 1:
		MoveDown();
		break;
	case 2:
		MoveRight();
		break;
	case 3:
		MoveUp();
		break;
	default:
		break;
	}
}

void DFS(int nCnt)
{
	if (nCnt >= 5) {
		// Answer Update
		int nTemp = GetMaxValue();
		if (nTemp > nAnswer)
			nAnswer = nTemp;

		return;
	}

	for (int d = 0; d < 4; d++) {
		// SAVE
		int mapCopy[MAX][MAX];
		memcpy(mapCopy, map, sizeof(map));

		Move(d);
		DFS(nCnt + 1);

		// LOAD
		memcpy(map, mapCopy, sizeof(mapCopy));
	}
}

inline int GetMaxValue()
{
	int nRet=0;
	
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (map[y][x]) {
				if (nRet < map[y][x])
					nRet = map[y][x];
			}
		}
	}

	return nRet;
}

void MoveLeft()
{
	std::queue<int> q;
	for (int y = 0; y < N; y++){
		for (int x = 0; x < N; x++) {
			if (map[y][x]) {
				q.push(map[y][x]);
				map[y][x] = 0;
			}
		}

		for (int x = 0; x < N; x++) {
			if (q.empty())
				break;

			int nTemp = q.front();
			q.pop();

			// next block == cur block
			if (!q.empty() && (nTemp == q.front())) {
				nTemp *= 2;
				q.pop();
			}

			map[y][x] = nTemp;
		}
	}
}

void MoveDown()
{
	std::queue<int> q;
	for (int x = 0; x < N; x++) {
		for (int y = N - 1; y >= 0; y--) {
			if (map[y][x]) {
				q.push(map[y][x]);
				map[y][x] = 0;
			}
		}

		for (int y = N - 1; y >= 0; y--) {
			if (q.empty())
				break;

			int nTemp = q.front();
			q.pop();

			// next block == cur block
			if (!q.empty() && (nTemp == q.front())) {
				nTemp *= 2;
				q.pop();
			}

			map[y][x] = nTemp;
		}
	}	
}

void MoveRight()
{
	std::queue<int> q;
	for (int y = 0; y < N; y++) {
		for (int x = N-1; x >= 0; x--) {
			if (map[y][x]) {
				q.push(map[y][x]);
				map[y][x] = 0;
			}
		}

		for (int x = N-1; x >= 0; x--) {
			if (q.empty())
				break;

			int nTemp = q.front();
			q.pop();

			// next block == cur block
			if (!q.empty() && (nTemp == q.front())) {
				nTemp *= 2;
				q.pop();
			}

			map[y][x] = nTemp;
		}
	}
}

void MoveUp()
{
	std::queue<int> q;
	for (int x = 0; x < N; x++) {
		for (int y = 0; y < N; y++) {
			if (map[y][x]) {
				q.push(map[y][x]);
				map[y][x] = 0;
			}
		}

		for (int y = 0; y < N; y++) {
			if (q.empty())
				break;

			int nTemp = q.front();
			q.pop();

			// next block == cur block
			if (!q.empty() && (nTemp == q.front())) {
				nTemp *= 2;
				q.pop();
			}

			map[y][x] = nTemp;
		}
	}
}