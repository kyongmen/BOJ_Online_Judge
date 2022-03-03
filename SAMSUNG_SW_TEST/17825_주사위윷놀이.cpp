#include <iostream>
#include <array>
#include <memory.h>

int map[5][21]
= { {0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40},
	{10,13,16,19},
	{0, 20,22,24},
	{30,28,27,26},
	{25,30,35,40,0} };
bool bExist[5][21];

struct Position
{
	int _y, _x;
};

const Position posFinish = { 4,4 };
const std::array<const Position,4> posBlue = { 0,5,0,10,0,15,0,20 };
const std::array<const Position,4> posBlueJump = { 1,0,2,1,3,0,4,3 };
const Position posBlueLastWay = {4,0};

const int maxBlueIdx = 3;

class Horse
{
public:
	Position _pos;
	bool _bFinished;

	Horse() :_pos{ 0,0 }, _bFinished(false) {};
};
std::array<Horse,4> arrHorse;

int nAnswer;
std::array<int,10> arrCommand;

void Solve();
void ChooseHorse(int nCnt, int score);
bool MoveHorse(Horse& horse, int nLength);

int main()
{
	// IO Setting
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	// INPUT
	for (int i = 0; i < 10; ++i) {
		std::cin >> arrCommand[i];
	}

	Solve();

	return 0;
}

void Solve()
{
	ChooseHorse(0, 0);

	std::cout << nAnswer << "\n";
}

void ChooseHorse(int nCnt, int score)
{
	// break condition
	if (nCnt >= 10) {
		if (score > nAnswer)
			nAnswer = score;

		return;
	}

	for (int idx = 0; idx < 4; ++idx) {
		auto& horse = arrHorse[idx];
		if (!horse._bFinished) {
			int y = horse._pos._y;
			int x = horse._pos._x;
			bool bFinished = horse._bFinished;

			bool bMoved = MoveHorse(horse, arrCommand[nCnt]);
			if (!bMoved)
				continue;

			ChooseHorse(nCnt + 1, score + map[horse._pos._y][horse._pos._x]);

			bExist[y][x] = true;
			bExist[horse._pos._y][horse._pos._x] = false;

			horse._pos._y = y;
			horse._pos._x = x;
			horse._bFinished = bFinished;
		}
	}
}

bool MoveHorse(Horse& horse, int nLength)
{
	// move
	int y = horse._pos._y;
	int x = horse._pos._x;

	if (y == 0) {
		int ny = y;
		int nx = x + nLength;

		bool bMoved = false;
		if (nx > 20) {
			horse._pos._y = posFinish._y;
			horse._pos._x = posFinish._x;
			horse._bFinished = true;

			bMoved = true;
		}

		if (!bMoved) {
			for (int i = 0; i < posBlue.size(); ++i) {
				if (nx == posBlue[i]._x) {
					ny = posBlueJump[i]._y;
					nx = posBlueJump[i]._x;
					break;
				}
			}

			if (!bExist[ny][nx]) {
				horse._pos._y = ny;
				horse._pos._x = nx;
			}
		}
	}
	else if (1 <= y && y <= 3) {
		int ny = y;
		int nx = x + nLength;

		bool bMoved = false;
		if (nx <= maxBlueIdx && !bExist[ny][nx]) {
			horse._pos._y = ny;
			horse._pos._x = nx;
			bMoved = true;
		}

		if (!bMoved) {
			if (nx > maxBlueIdx) {
				ny = posBlueLastWay._y;
				nx -= (maxBlueIdx + 1);

				if (nx >= posFinish._x) {
					nx = posFinish._x;
				}

				if (!bExist[ny][nx]) {
					horse._pos._y = ny;
					horse._pos._x = nx;

					if (nx == posFinish._x) {
						horse._bFinished = true;
					}
				}
			}			
		}
	}
	else {
		// last way
		int ny = y;
		int nx = x + nLength;
		if (nx >= posFinish._x) {
			horse._pos._x = posFinish._x;
			horse._bFinished = true;
		}
		else if (!bExist[ny][nx]) {
			horse._pos._y = ny;
			horse._pos._x = nx;
		}
	}

	if (y == horse._pos._y && x == horse._pos._x) {
		// can't move
		return false;
	}
	else {
		bExist[y][x] = false;
		if(horse._pos._y != posFinish._y || horse._pos._x != posFinish._x)
			bExist[horse._pos._y][horse._pos._x] = true;
	}

	return true;
}