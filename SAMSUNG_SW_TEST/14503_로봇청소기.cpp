#include <iostream>

const int MAX = 50;
int map[MAX][MAX];

// U R D L
const int dy[4] = {-1,0,1,0};
const int dx[4] = {0,1,0,-1};

int N, M;
int nAnswer;

class RobotCleaner
{
public:
	int _y, _x;
	int _dir;

	RobotCleaner()
		: _y(0), _x(0), _dir(0)
	{}
};
RobotCleaner robotCleaner;

void Solve();

int main()
{
	// IO Setting
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	// INPUT
	std::cin >> N >> M;
	std::cin >> robotCleaner._y >> robotCleaner._x >> robotCleaner._dir;
	
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
	// 0: Empty
	// 1: Wall
	// 2: Cleaned
	
	while (true) {
		int cy = robotCleaner._y;
		int cx = robotCleaner._x;

		// Step 1. Clean Current Location
		if (map[cy][cx] == 0) {
			map[cy][cx] = 2;
			nAnswer++;
		}

		// Step 2. Turn Left
		bool bCleaned = false;
		for (int nCnt = 0; nCnt < 4; nCnt++) {
			int curDir = robotCleaner._dir;
			int nextDir = ((--curDir) + 4) % 4;

			int ny = cy + dy[nextDir];
			int nx = cx + dx[nextDir];
			
			if (map[ny][nx] == 0) {
				robotCleaner._dir = nextDir;
				robotCleaner._y = ny;
				robotCleaner._x = nx;
				bCleaned = true;
				break;
			}
			else if (map[ny][nx] == 1 || map[ny][nx]==2) {
				robotCleaner._dir = nextDir;
				continue;
			}
		}

		// After Search 4 directions
		if (!bCleaned) {
			// Go back
			int ny = robotCleaner._y - dy[robotCleaner._dir];
			int nx = robotCleaner._x - dx[robotCleaner._dir];

			if (map[ny][nx] == 1) {
				break;
			}
			else {
				robotCleaner._y = ny;
				robotCleaner._x = nx;
				continue;
			}
		}
	}
	
	std::cout << nAnswer << "\n";
}