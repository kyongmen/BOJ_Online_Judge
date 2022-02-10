#include <iostream>
#include <queue>
#include <vector>
#include <tuple>

const int MAX = 101;
int map[MAX][MAX];

const int dy[4] = {0,-1,0,1};
const int dx[4] = {1,0,-1,0};

int N;
int nAnswer;

std::vector<int> vecCurveDir;

std::queue<std::tuple<int,int,int,int>> qCurves;

void Solve();
void UpdateAnswer();
void MakeCurves();

int main()
{
	// IO Setting
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	// INIT
	vecCurveDir.reserve(1 << 10);

	// INPUT
	std::cin >> N;
	for (int n = 0; n < N; n++) {
		int x(0), y(0), d(0), g(0);
		std::cin >> x >> y >> d >> g;
		qCurves.push(std::make_tuple(y, x, d, g));
	}

	Solve();

	return 0;
}

void Solve()
{
	MakeCurves();

	UpdateAnswer();

	std::cout << nAnswer << "\n";
}

void UpdateAnswer()
{
	for (int y = 0; y < MAX; ++y) {
		for (int x = 0; x < MAX-1; ++x) {
			if (map[y][x]) {
				int ny = y + 1;
				int nx = x + 1;

				if (ny < 0 || ny >= MAX || nx < 0 || nx >= MAX) {
					continue;
				}

				if (map[y][nx]
					&& map[ny][x]
					&& map[ny][nx])
					nAnswer++;
			}
		}
	}
}

void MakeCurves()
{
	while (!qCurves.empty()) {
		int y(0), x(0), dir(0), gen(0);
		std::tie(y, x, dir, gen) = qCurves.front();
		qCurves.pop();

		// Start point
		map[y][x] = 1;

		// End point
		int ny = y + dy[dir];
		int nx = x + dx[dir];
		map[ny][nx] = 1;

		int lines = 1 << gen;
		vecCurveDir.push_back(dir);

		while (true) {
			int nCnt = vecCurveDir.size();
			if (nCnt == lines)
				break;

			for (int i = nCnt - 1; i >= 0; --i) {
				int nd = (vecCurveDir[i] +1 + 4) % 4;
				ny += dy[nd];
				nx += dx[nd];

				map[ny][nx] = 1;
				vecCurveDir.push_back(nd);
			}			
		}
		vecCurveDir.clear();
	}
}