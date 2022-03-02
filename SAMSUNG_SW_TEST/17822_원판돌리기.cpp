#include <iostream>
#include <queue>
#include <tuple>
#include <algorithm>
#include <memory.h>

const int MAX = 50;
int plate[MAX][MAX];
bool bVisited[MAX][MAX];

const int dy[4] = {-1,1,0,0};
const int dx[4] = {0,0,-1,1};

int N, M, T;

// x, d, k
std::queue<std::tuple<int, int, int>> qCommand;

void Solve();
void Rotate(int x, int d, int k);
void PopNumber();
void PrintAnswer();

int main()
{
	// IO Setting
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	// INPUT
	std::cin >> N >> M >> T;
	for (int y = 0; y < N; ++y) {
		for (int x = 0; x < M; ++x) {
			std::cin >> plate[y][x];
		}
	}

	for (int t = 0; t < T; ++t) {
		int x(0), d(0), k(0);
		std::cin >> x >> d >> k;
		qCommand.push(std::make_tuple(x, d, k));
	}

	Solve();

	return 0;
}

void Solve()
{
	while (!qCommand.empty()) {
		int x, d, k;
		std::tie(x, d, k) = qCommand.front();
		qCommand.pop();

		// Rotate
		Rotate(x, d, k);	

		// Pop
		PopNumber();
	}

	PrintAnswer();
}

void Rotate(int x, int d, int k)
{
	for (int idx = x - 1; idx < N; idx += x) {
		auto begin = &plate[idx][0];
		auto end = &plate[idx][0] + M;

		if (d == 0) {
			// CW
			std::rotate(begin, end - k, end);
		}
		else if (d == 1) {
			// CCW
			std::rotate(begin, begin + k, end);
		}
	}
}

void PopNumber()
{
	// y,x,number
	std::queue<std::tuple<int, int,int>> qBFS;
	bool bPopped = false;

	int sum = 0;
	int nCnt = 0;

	for (int y = 0; y < N; ++y) {
		for (int x = 0; x < M; ++x) {
			if (plate[y][x] && !bVisited[y][x]) {
				bVisited[y][x] = true;
				qBFS.push(std::make_tuple(y,x,plate[y][x]));

				while (!qBFS.empty()) {
					int cy, cx, number;
					std::tie(cy, cx,number) = qBFS.front();
					sum += number;
					nCnt++;
					qBFS.pop();

					for (int dir = 0; dir < 4; ++dir) {
						int ny = cy + dy[dir];
						int nx = cx + dx[dir];

						if (ny < 0 || ny >= N)
							continue;

						if (nx < 0)
							nx = M - 1;
						else if (nx >= M)
							nx = 0;

						if (bVisited[ny][nx])
							continue;

						if (plate[ny][nx] == number) {
							bPopped = true;

							bVisited[ny][nx] = true;
							qBFS.push(std::make_tuple( ny,nx, plate[ny][nx] ));

							plate[cy][cx] = 0;
							plate[ny][nx] = 0;
						}
					}
				}
			}
		}
	}

	// Arrange
	double avg = sum / (double)nCnt;
	if (!bPopped) {
		for (int y = 0; y < N; ++y) {
			for (int x = 0; x < M; ++x) {
				if (plate[y][x]) {
					if (plate[y][x] > avg)
						plate[y][x]--;
					else if(plate[y][x]<avg)
						plate[y][x]++;
				}
			}
		}
	}

	memset(bVisited, false, sizeof(bVisited));
}

void PrintAnswer()
{
	int nAnswer = 0;
	for (int y = 0; y < N; ++y) {
		for (int x = 0; x < M; ++x) {
			if (plate[y][x])
				nAnswer += plate[y][x];
		}
	}

	std::cout << nAnswer << "\n";
}