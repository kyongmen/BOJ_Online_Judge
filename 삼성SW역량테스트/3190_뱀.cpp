#include <iostream>
#include <deque>
#include <map>

const int MAX = 100;
int map[MAX][MAX];

// R D L U
const int dy[4] = {0,1,0,-1};
const int dx[4] = {1,0,-1,0};

int N, K, L;
std::deque<std::pair<int, int>> snake;
std::map<int, int> mapCommand;

void Solve();
int Move();

int main()
{
	// IO Setting
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	// INPUT
	// empty: 0, snake: 1, apple: 2
	std::cin >> N >> K;
	for (int k = 0; k < K; k++) {
		int yApple, xApple;
		std::cin >> yApple >> xApple;
		map[--yApple][--xApple] = 2;
	}

	std::cin >> L;
	for (int l = 0; l < L; l++) {
		int time;
		char dir;

		std::cin >> time >> dir;

		int nDir;
		if (dir == 'L')
			nDir = -1;
		else if (dir == 'D')
			nDir = 1;

		mapCommand[time] = nDir;
	}

	// Init (Snake)
	snake.push_back({ 0,0 });
	map[0][0] = 1;

	Solve();

	return 0;
}

void Solve()
{
	int nAnswer = 0;

	nAnswer = Move();
	std::cout << nAnswer << "\n";
}

int Move()
{
	int nTime = 0;
	int dir = 0;
	
	while (true) {
		// Direction
		auto it = mapCommand.find(nTime);
		if (it != mapCommand.end()) {
			dir = (dir + it->second + 4) % 4;
		}

		// Head Move
		int yHead = snake.front().first;
		int xHead = snake.front().second;

		int ny = yHead + dy[dir];
		int nx = xHead + dx[dir];

		// Game Over
		if (ny < 0 || ny>=N || nx<0 || nx>=N)
			return ++nTime;

		if (map[ny][nx] == 2) {
			// Apple
			// Head Move
			snake.push_front({ ny,nx });
			map[ny][nx] = 1;
		}
		else if (map[ny][nx] == 1) {
			// Snake
			// Game Over
			return ++nTime;
		}
		else {
			// Empty
			// Head Move
			snake.push_front({ ny,nx });
			map[ny][nx] = 1;

			// Tail Move
			map[snake.back().first][snake.back().second] = 0;
			snake.pop_back();
		}
			
		nTime++;
	}	
}
