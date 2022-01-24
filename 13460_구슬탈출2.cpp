#include <iostream>

const int MAX = 10;

int nAnswer = 1e9;

int N, M;
char map[MAX][MAX];

const int dy[4] = {0,1,0,-1};
const int dx[4] = {-1,0,1,0};

struct Ball
{
	int _y, _x;
	bool _bSuccess;

	explicit Ball(int y, int x)
		: _y(y), _x(x),
		_bSuccess(false)
	{
		
	}
};

// Ball
Ball redBall(0, 0);
Ball blueBall(0, 0);

void Solve();
void MoveDir(int dir);
void DFS(int nCnt);

int main()
{
	// IO Setting
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	// Init Map
	std::cin >> N >> M;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			std::cin >> map[y][x];
			if (map[y][x] == 'R') {
				redBall._y = y;
				redBall._x = x;
				map[y][x] = '.';
			}
			else if (map[y][x] == 'B') {
				blueBall._y = y;
				blueBall._x = x;
				map[y][x] = '.';
			}
		}
	}

	Solve();

	return 0;
}

void Solve()
{
	DFS(0);

	if (nAnswer > 10)
		nAnswer = -1;

	std::cout << nAnswer << "\n";
}

void MoveDir(int dir)
{
	// L D R U
	int redMove = 0;
	int blueMove = 0;

	// Red Move
	while (true) {
		int ny = redBall._y + dy[dir];
		int nx = redBall._x + dx[dir];

		if (map[ny][nx] == '#') {
			break;
		}
		else if (map[ny][nx] == 'O') {
			redBall._bSuccess = true;
			break;
		}
		else {
			redBall._y += dy[dir];
			redBall._x += dx[dir];
			redMove++;
		}
	}

	// Blue Move
	while (true) {
		int ny = blueBall._y + dy[dir];
		int nx = blueBall._x + dx[dir];

		if (map[ny][nx] == '#') {
			break;
		}
		else if (map[ny][nx] == 'O') {
			blueBall._bSuccess = true;
			break;
		}
		else {
			blueBall._y += dy[dir];
			blueBall._x += dx[dir];
			blueMove++;
		}
	}

	// Result
	if (blueBall._bSuccess) {
		// BlueBall Out. Fail
		return;
	}
	else {
		if (redBall._bSuccess) {
			// Only Red Ball Out. Success
			return;
		}
		
		// Same Position
		if((redBall._y == blueBall._y)
		&& (redBall._x == blueBall._x)){
			if (redMove > blueMove) {
				redBall._y -= dy[dir];
				redBall._x -= dx[dir];
			}
			else {
				blueBall._y -= dy[dir];
				blueBall._x -= dx[dir];
			}
		}
	}
}

void DFS(int nCnt)
{
	if (nCnt > 10)
		return;

	if (blueBall._bSuccess)
		return;
	else if(!blueBall._bSuccess
		&& redBall._bSuccess){
		nAnswer = (nCnt < nAnswer ? nCnt : nAnswer);
	}

	// L D R U
	for (int d = 0; d < 4; d++) {
		// SAVE
		int ry = redBall._y;
		int rx = redBall._x;
		bool rSuccess = redBall._bSuccess;

		int by = blueBall._y;
		int bx = blueBall._x;
		int bSuccess = blueBall._bSuccess;

		MoveDir(d);
		DFS(nCnt + 1);

		// LOAD
		redBall._y = ry;
		redBall._x = rx;
		redBall._bSuccess = rSuccess;

		blueBall._y = by;
		blueBall._x = bx;
		blueBall._bSuccess = bSuccess;
	}
}