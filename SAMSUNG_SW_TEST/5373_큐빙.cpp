#include <iostream>

enum class Face
{
	_BEGIN=0,
	UP=0,
	DOWN,
	FRONT,
	BACK,
	LEFT,
	RIGHT,
	_END = RIGHT
};

char Cube[6][3][3];

void Init();
int GetFaceSide(char side);

void RotateCW(int side);
void RotateCCW(int side);

int main()
{
	// IO Setting
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	

	// INPUT
	int T(0);
	std::cin >> T;
	for (int testCase = 1; testCase <= T; ++testCase) {
		// Init
		Init();

		int N(0);
		std::cin >> N;

		for (int n = 0; n < N; ++n) {
			char side, dir;
			std::cin >> side >> dir;

			int nSide = GetFaceSide(side);
			if (dir == '+') {
				RotateCW(nSide);
			}
			else {
				RotateCCW(nSide);
			}
		}

		// Print 
		for (int y = 0; y < 3; ++y) {
			for (int x = 0; x < 3; ++x) {
				std::cout << Cube[static_cast<int>(Face::UP)][y][x];
			}
			std::cout << "\n";
		}
	}

	return 0;
}
int GetFaceSide(char side)
{
	int nSide = -1;
	switch (side) {
	case 'U':
		nSide = 0;
		break;
	case 'D':
		nSide = 1;
		break;
	case 'F':
		nSide = 2;
		break;
	case 'B':
		nSide = 3;
		break;
	case 'L':
		nSide = 4;
		break;
	case 'R':
		nSide = 5;
		break;
	default:
		break;
	}
	return nSide;
}

void RotateCW(int side)
{
	// Copy
	char temp[3][3];
	for (int y = 0; y < 3; ++y) {
		for (int x = 0; x < 3; ++x) {
			temp[y][x] = Cube[side][y][x];
		}
	}

	// Rotate CW
	for (int y = 0; y < 3; ++y) {
		for (int x = 0; x < 3; ++x) {
			Cube[side][y][x] = temp[2-x][y];
		}
	}

	// Remain Side
	// a: ascending / d: descending
	char save[3];
	if (side == static_cast<int>(Face::UP)) {
		// F(0,a) <- R(0,a) <- B(0,a) <- L(a,0)
		int y = 0;
		for (int x = 0; x < 3; ++x) {
			char temp = Cube[static_cast<int>(Face::FRONT)][y][x];
			
			Cube[static_cast<int>(Face::FRONT)][y][x] = Cube[static_cast<int>(Face::RIGHT)][y][x];
			Cube[static_cast<int>(Face::RIGHT)][y][x] = Cube[static_cast<int>(Face::BACK)][y][x];
			Cube[static_cast<int>(Face::BACK)][y][x] = Cube[static_cast<int>(Face::LEFT)][y][x];
			Cube[static_cast<int>(Face::LEFT)][y][x] = temp;
		}
	}
	else if (side == static_cast<int>(Face::DOWN)) {
		// F(2,a) <- L(2,a) <- B(2,a) <- R(2,a)
		int y = 2;
		for (int x = 0; x < 3; ++x) {
			char temp = Cube[static_cast<int>(Face::FRONT)][y][x];

			Cube[static_cast<int>(Face::FRONT)][y][x] = Cube[static_cast<int>(Face::LEFT)][y][x];
			Cube[static_cast<int>(Face::LEFT)][y][x] = Cube[static_cast<int>(Face::BACK)][y][x];
			Cube[static_cast<int>(Face::BACK)][y][x] = Cube[static_cast<int>(Face::RIGHT)][y][x];
			Cube[static_cast<int>(Face::RIGHT)][y][x] = temp;
		}
	}
	else if (side == static_cast<int>(Face::FRONT)) {
		// U(2,a) <- L(d,2) <- D(0,d) <- R(a,0)
		for (int idx = 0; idx < 3; ++idx) {
			char temp = Cube[static_cast<int>(Face::UP)][2][idx];

			Cube[static_cast<int>(Face::UP)][2][idx] = Cube[static_cast<int>(Face::LEFT)][2-idx][2];
			Cube[static_cast<int>(Face::LEFT)][2-idx][2] = Cube[static_cast<int>(Face::DOWN)][0][2-idx];
			Cube[static_cast<int>(Face::DOWN)][0][2-idx] = Cube[static_cast<int>(Face::RIGHT)][idx][0];
			Cube[static_cast<int>(Face::RIGHT)][idx][0] = temp;
		}
	}
	else if (side == static_cast<int>(Face::BACK)) {
		// U(0,d) <- R(d,2) <- D(2,a) <- L(a,0)
		for (int idx = 0; idx < 3; ++idx) {
			char temp = Cube[static_cast<int>(Face::UP)][0][2-idx];

			Cube[static_cast<int>(Face::UP)][0][2-idx] = Cube[static_cast<int>(Face::RIGHT)][2 - idx][2];
			Cube[static_cast<int>(Face::RIGHT)][2 - idx][2] = Cube[static_cast<int>(Face::DOWN)][2][idx];
			Cube[static_cast<int>(Face::DOWN)][2][idx] = Cube[static_cast<int>(Face::LEFT)][idx][0];
			Cube[static_cast<int>(Face::LEFT)][idx][0] = temp;
		}
	}
	else if (side == static_cast<int>(Face::LEFT)) {
		// U(a,0) <- B(d,2) <- D(a,0) <- F(a,0)
		for (int idx = 0; idx < 3; ++idx) {
			char temp = Cube[static_cast<int>(Face::UP)][idx][0];

			Cube[static_cast<int>(Face::UP)][idx][0] = Cube[static_cast<int>(Face::BACK)][2 - idx][2];
			Cube[static_cast<int>(Face::BACK)][2 - idx][2] = Cube[static_cast<int>(Face::DOWN)][idx][0];
			Cube[static_cast<int>(Face::DOWN)][idx][0] = Cube[static_cast<int>(Face::FRONT)][idx][0];
			Cube[static_cast<int>(Face::FRONT)][idx][0] = temp;
		}
	}
	else if (side == static_cast<int>(Face::RIGHT)) {
		// U(d,2) <- F(d,2) <-D(d,2) <-B(a,0)
		for (int idx = 0; idx < 3; ++idx) {
			char temp = Cube[static_cast<int>(Face::UP)][2-idx][2];

			Cube[static_cast<int>(Face::UP)][2-idx][2] = Cube[static_cast<int>(Face::FRONT)][2 - idx][2];
			Cube[static_cast<int>(Face::FRONT)][2 - idx][2] = Cube[static_cast<int>(Face::DOWN)][2-idx][2];
			Cube[static_cast<int>(Face::DOWN)][2-idx][2] = Cube[static_cast<int>(Face::BACK)][idx][0];
			Cube[static_cast<int>(Face::BACK)][idx][0] = temp;
		}
	}
}

void RotateCCW(int side)
{
# if 1
	for (int nCnt = 0; nCnt < 3; nCnt++) {
		RotateCW(side);
	}
#else
	// Copy
	char temp[3][3];
	for (int y = 0; y < 3; ++y) {
		for (int x = 0; x < 3; ++x) {
			temp[y][x] = Cube[side][y][x];
		}
	}

	// Rotate CCW
	for (int y = 0; y < 3; ++y) {
		for (int x = 0; x < 3; ++x) {
			Cube[side][y][x] = temp[x][2-y];
		}
	}
#endif
}

void Init()
{
	// Init
	for (int y = 0; y < 3; ++y) {
		for (int x = 0; x < 3; ++x) {
			Cube[static_cast<int>(Face::UP)][y][x] = 'w';
			Cube[static_cast<int>(Face::DOWN)][y][x] = 'y';
			Cube[static_cast<int>(Face::FRONT)][y][x] = 'r';
			Cube[static_cast<int>(Face::BACK)][y][x] = 'o';
			Cube[static_cast<int>(Face::LEFT)][y][x] = 'g';
			Cube[static_cast<int>(Face::RIGHT)][y][x] = 'b';
		}
	}
}