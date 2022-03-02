#include <iostream>
#include <queue>
#include <deque>
#include <algorithm>

int K;

std::queue<std::pair<int, int>> qCommand;
std::deque<std::pair<int, int>> qMove;

enum class GearPos
{
	NORTH = 0,
	EAST = 2,
	SOUTH = 4,
	WEST = 6
};

class Gear
{
public:
	int _component[8];

	void rotate(int dir)
	{
		switch (dir)
		{
		case 1:
			rotateCW();
			break;
		case -1:
			rotateCCW();
			break;
		default:
			break;
		}
	}

	void rotateCW()
	{
		auto begin = &_component[0];
		auto end = &_component[7]+1;

		std::rotate(begin, end-1, end);
	}

	void rotateCCW()
	{
		auto begin = &_component[0];
		auto end = &_component[7]+1;

		std::rotate(begin, begin + 1, end);
	}
};
Gear arrGear[4];

void Solve();
int GetScore();

int main()
{
	// IO Setting
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	// INPUT
	for (int idx = 0; idx < 4; idx++) {
		int component(0);
		std::cin >> component;

		// Initialize
		for (int j = 7; j >=0; j--) {
			arrGear[idx]._component[j] = component % 10;
			component /= 10;
		}
	}

	// Rotate Command
	std::cin >> K;
	for (int k = 0; k < K; k++) {
		int idx(0), dir(0);
		std::cin >> idx >> dir;
		qCommand.push({ --idx, dir });
	}

	Solve();

	return 0;
}

void Solve()
{
	while (!qCommand.empty()) {
		// Find Gears to move
		int curIdx = qCommand.front().first;
		int curDir = qCommand.front().second;
		qCommand.pop();

		qMove.push_back({curIdx , curDir});

		// Right side
		for (int idx = curIdx; idx +1 < 4; idx++) {
			int nIdx = idx + 1;
			if (nIdx >= 4)
				break;

			if (arrGear[idx]._component[static_cast<int>(GearPos::EAST)]
				!= arrGear[nIdx]._component[static_cast<int>(GearPos::WEST)]) {
				int nDir = qMove.back().second * (-1);
				qMove.push_back({ nIdx,nDir });
			}
			else
				break;
		}

		// Left side
		for (int idx = curIdx; idx - 1 >= 0; idx--) {
			int nIdx = idx - 1;
			if (nIdx < 0)
				break;

			if (arrGear[idx]._component[static_cast<int>(GearPos::WEST)]
				!= arrGear[nIdx]._component[static_cast<int>(GearPos::EAST)]) {
				int nDir = qMove.front().second * (-1);
				qMove.push_front({ nIdx,nDir });
			}
			else
				break;
		}

		// Move
		while (!qMove.empty()) {
			int idx = qMove.front().first;
			int dir = qMove.front().second;
			qMove.pop_front();

			arrGear[idx].rotate(dir);
		}
	}

	std::cout << GetScore() << "\n";
}

int GetScore()
{
	int nRet = 0;

	for (int idx = 0; idx < 4; idx++) {
		int temp = arrGear[idx]._component[static_cast<int>(GearPos::NORTH)];
		if (temp) {
			nRet += (1 << idx);
		}
	}

	return nRet;
}