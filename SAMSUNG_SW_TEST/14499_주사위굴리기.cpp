#include <iostream>
#include <queue>

const int MAX = 20;
int map[MAX][MAX];

// E W N S
const int dy[5] = {0,0,0,-1,1};
const int dx[5] = {0,1,-1,0,0};

int N, M, K;
std::queue<int> qCommand;

void Solve();
bool Move(int dir);

void TurnEast();
void TurnWest();
void TurnNorth();
void TurnSouth();

enum eCardinalDir
{
	EAST=1,
	WEST,
	NORTH,
	SOUTH
};

enum eDiceFace
{
	UP=0,
	BACK,
	RIGHT,
	LEFT,
	FRONT,
	DOWN
};

class Dice
{
public:
	int _y, _x;
	int _num[6];

	explicit Dice():
		_y(0),_x(0),
		_num{0,}
	{}

	void print() const
	{
		std::cout << _num[eDiceFace::UP] << "\n";
	}
};
Dice dice;

int main()
{
	// IO Setting
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	// INPUT
	int initY(0), initX(0);
	std::cin >> N >> M >> initY >> initX >> K;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			std::cin >> map[y][x];
		}
	}

	for (int k = 0; k < K; k++) {
		int dir = 0;
		std::cin >> dir;
		qCommand.push(dir);
	}

	// Init
	dice._y = initY;
	dice._x = initX;

	Solve();

	return 0;
}

void Solve()
{
	while (!qCommand.empty()) {
		int dir = qCommand.front();
		qCommand.pop();

		bool bMoved = Move(dir);
		if (bMoved) {
			dice.print();
		}
	}
}

bool Move(int dir)
{
	int ny = dice._y + dy[dir];
	int nx = dice._x + dx[dir];

	// Out of range
	if (ny < 0 || ny >= N || nx < 0 || nx >= M) {
		// No move
		// No print
		return false;
	}

	// Turn
	switch (dir)
	{
	case eCardinalDir::EAST:
		TurnEast();
		break;
	case eCardinalDir::WEST:
		TurnWest();
		break;
	case eCardinalDir::NORTH:
		TurnNorth();
		break;
	case eCardinalDir::SOUTH:
		TurnSouth();
		break;
	default:
		return false;
	}

	// NumCopy
	if (map[ny][nx] == 0) {
		map[ny][nx] = dice._num[eDiceFace::DOWN];
	}
	else {
		dice._num[eDiceFace::DOWN] = map[ny][nx];
		map[ny][nx] = 0;
	}

	// Move
	dice._y = ny;
	dice._x = nx;
	
	return true;
}

void TurnEast()
{
	int temp = dice._num[eDiceFace::UP];

	dice._num[eDiceFace::UP] = dice._num[eDiceFace::LEFT];
	dice._num[eDiceFace::LEFT] = dice._num[eDiceFace::DOWN];
	dice._num[eDiceFace::DOWN] = dice._num[eDiceFace::RIGHT];
	dice._num[eDiceFace::RIGHT] = temp;
}

void TurnWest()
{
	int temp = dice._num[eDiceFace::UP];

	dice._num[eDiceFace::UP] = dice._num[eDiceFace::RIGHT];
	dice._num[eDiceFace::RIGHT] = dice._num[eDiceFace::DOWN];
	dice._num[eDiceFace::DOWN] = dice._num[eDiceFace::LEFT];
	dice._num[eDiceFace::LEFT] = temp;
}

void TurnNorth()
{
	int temp = dice._num[eDiceFace::UP];

	dice._num[eDiceFace::UP] = dice._num[eDiceFace::FRONT];
	dice._num[eDiceFace::FRONT] = dice._num[eDiceFace::DOWN];
	dice._num[eDiceFace::DOWN] = dice._num[eDiceFace::BACK];
	dice._num[eDiceFace::BACK] = temp;
}

void TurnSouth()
{
	int temp = dice._num[eDiceFace::UP];

	dice._num[eDiceFace::UP] = dice._num[eDiceFace::BACK];
	dice._num[eDiceFace::BACK] = dice._num[eDiceFace::DOWN];
	dice._num[eDiceFace::DOWN] = dice._num[eDiceFace::FRONT];
	dice._num[eDiceFace::FRONT] = temp;
}