#include <iostream>
#include <memory.h>

const int MAX = 500;
int map[MAX][MAX];
bool bVisited[MAX][MAX];

int N, M;
int nAnswer;

// R D L U
const int dy[4] = {0,1,0,-1};
const int dx[4] = {1,0,-1,0};

// ぬ っ で た
// kind, {{y}, {x}}
int specificShape[4][2][4]=
{ 
	{{0,0,0,1},{0,-1,1,0}},		// ぬ
	{{0,-1,1,0},{0,0,0,-1}},	// っ
	{{0,-1,0,0},{0,0,-1,1}},	// で
	{{0,-1,1,0},{0,0,0,1}}		// た
};

void Solve();
void SearchSpecificShape(int y, int x);
void SearchWithDFS(int y, int x, int nCnt, int nSum);

int main()
{
	// IO Setting
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	// INPUT
	std::cin >> N >> M;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			std::cin >> map[y][x];
		}
	}

	Solve();

	return 0;
}

void Solve()
{
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			SearchSpecificShape(y, x);

			bVisited[y][x] = true;
			SearchWithDFS(y, x, 1 ,map[y][x]);
			bVisited[y][x] = false;
		}
	}

	std::cout << nAnswer << "\n";
}

void SearchSpecificShape(int y, int x)
{
	// Specific Shape
	for (int kind = 0; kind < 4; kind++) {
		int nSum = 0;

		for (int dir = 0; dir < 4; dir++) {
			int ny = y + specificShape[kind][0][dir];
			int nx = x + specificShape[kind][1][dir];

			if (ny < 0 || ny >= N || nx < 0 || nx >= M) {
				nSum = 0;
				break;
			}

			nSum += map[ny][nx];
		}

		if (nSum > nAnswer) {
			nAnswer = nSum;
		}
	}	
}

void SearchWithDFS(int y, int x, int nCnt, int nSum)
{
	// End Condition
	if (nCnt >= 4) {
		if (nSum > nAnswer)
			nAnswer = nSum;
		return;
	}

	for (int dir = 0; dir < 4; dir++) {
		int ny = y + dy[dir];
		int nx = x + dx[dir];

		if (ny < 0 || ny >= N || nx < 0 || nx >= M)
			continue;

		if (bVisited[ny][nx])
			continue;

		// Visit
		bVisited[ny][nx] = true;
		SearchWithDFS(ny, nx, nCnt + 1, nSum + map[ny][nx]);
		bVisited[ny][nx] = false;
	}
}