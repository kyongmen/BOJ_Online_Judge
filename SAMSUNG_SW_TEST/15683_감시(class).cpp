#include <iostream>
#include <vector>
#include <memory.h>
#include <memory>

const int MAX = 8;
int map[MAX][MAX];

int N, M, K;
int nAnswer = 100;

class CCTV {
public:
	int _y, _x;
	int _dir;

	CCTV(int y, int x) :_y(y), _x(x), _dir(0) {}
	virtual ~CCTV() {}

	virtual void Watch() const {};

	inline bool Search(int y, int x) const
	{
		if (map[y][x] == 6) {
			// Wall
			return false;
		}
		else if (map[y][x] == 0) {
			// Empty -> Searched
			map[y][x] = 9;
		}
		else if ((1 <= map[y][x] && map[y][x] <= 5)
			|| map[y][x] == 9) {
			// Another CCTV
			// OR already searched
		}

		return true;
	}

	void WatchLeft() const
	{
		int y = _y;
		for (int x = _x; x >= 0; --x) {
			bool bContinue = Search(y, x);
			if (!bContinue)
				break;
		}
	}

	void WatchRight() const
	{
		int y = _y;
		for (int x = _x; x <M; ++x) {
			bool bContinue = Search(y, x);
			if (!bContinue)
				break;
		}
	}
	void WatchUp() const
	{
		int x = _x;
		for (int y = _y; y >= 0; --y) {
			bool bContinue = Search(y, x);
			if (!bContinue)
				break;
		}
	}
	void WatchDown() const
	{
		int x = _x;
		for (int y = _y; y <N; ++y) {
			bool bContinue = Search(y, x);
			if (!bContinue)
				break;
		}
	}
};

class CCTV1 : public CCTV{
public:
	CCTV1(int y, int x) : CCTV(y,x) {}

	void Watch() const override
	{
		switch (_dir)
		{
		case 0:
			WatchRight();
			break;
		case 1:
			WatchDown();
			break;
		case 2:
			WatchLeft();
			break;
		case 3:
			WatchUp();
			break;
		default:
			break;
		}
	}
};

class CCTV2 : public CCTV {
public:
	CCTV2(int y, int x) :CCTV(y, x) {}

	void Watch() const override
	{
		switch (_dir)
		{
		case 0:
		case 2:
			WatchLeft();
			WatchRight();
			break;
		case 1:
		case 3:
			WatchUp();
			WatchDown();
			break;
		default:
			break;
		}
	}
};
class CCTV3 : public CCTV {
public:
	CCTV3(int y, int x) :CCTV(y, x) {}

	void Watch() const override
	{
		switch (_dir)
		{
		case 0:
			WatchUp();
			WatchRight();
			break;
		case 1:
			WatchRight();
			WatchDown();
			break;
		case 2:
			WatchDown();
			WatchLeft();
			break;
		case 3:
			WatchLeft();
			WatchUp();
			break;
		default:
			break;
		}
	}
};

class CCTV4 : public CCTV {
public:
	CCTV4(int y, int x) :CCTV(y, x) {}

	void Watch() const override
	{
		switch (_dir)
		{
		case 0:
			WatchLeft();
			WatchUp();
			WatchRight();
			break;
		case 1:
			WatchUp();
			WatchRight();
			WatchDown();
			break;
		case 2:
			WatchRight();
			WatchDown();
			WatchLeft();
			break;
		case 3:
			WatchDown();
			WatchLeft();
			WatchUp();
			break;
		default:
			break;
		}
	}
};

class CCTV5 : public CCTV {
public:
	CCTV5(int y, int x) :CCTV(y, x) {}

	void Watch() const override
	{
		WatchUp();
		WatchDown();
		WatchLeft();
		WatchRight();
	}
};

void Solve();
void SetDirection(int nCnt);
void GetAnswer();

std::vector<std::shared_ptr<CCTV>> vecCamera;
std::vector<std::shared_ptr<CCTV5>> vecSpecialCamera;

int main()
{
	// IO Setting
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	// Init
	vecCamera.reserve(8);
	vecSpecialCamera.reserve(8);

	// INPUT
	std::cin >> N >> M;
	for (int y = 0; y < N; ++y) {
		for (int x = 0; x < M; ++x) {
			std::cin >> map[y][x];

			if (map[y][x] == 0 || map[y][x] == 6)
				continue;

			switch (map[y][x])
			{
			case 1:
			{
				auto sp1 = std::make_shared<CCTV1>(y, x);
				vecCamera.push_back(sp1);
				break;
			}
			case 2:
			{
				auto sp2 = std::make_shared<CCTV2>(y, x);
				vecCamera.push_back(sp2);
				break;
			}
			case 3:
			{
				auto sp3 = std::make_shared<CCTV3>(y, x);
				vecCamera.push_back(sp3);
				break;
			}
			case 4:
			{
				auto sp4 = std::make_shared<CCTV4>(y, x);
				vecCamera.push_back(sp4);
				break;
			}
			case 5:
			{
				auto sp5 = std::make_shared<CCTV5>(y, x);
				vecSpecialCamera.push_back(sp5);
				break;
			}
			default:
				break;
			}
		}
	}

	K = vecCamera.size();

	Solve();

	return 0;
}

void Solve()
{
	SetDirection(0);

	std::cout << nAnswer << "\n";
}

void SetDirection(int nCnt)
{
	if (nCnt >= K) {
		// SAVE map
		int mapCopy[MAX][MAX];
		memcpy(mapCopy, map, sizeof(map));

		// CCTV Operation
		for (const auto& cctv : vecCamera) {
			cctv->Watch();
		}

		for (const auto& cctv : vecSpecialCamera) {
			cctv->Watch();
		}

		// Update Answer
		GetAnswer();

		// LOAD map
		memcpy(map, mapCopy, sizeof(mapCopy));
		
		return;
	}

	for (int dir = 0; dir < 4; dir++) {
		(vecCamera[nCnt].get())->_dir = dir;
		SetDirection(nCnt + 1);
	}
}

void GetAnswer()
{
	int nTemp = 0;
	for (int y = 0; y < N; ++y) {
		for (int x = 0; x < M; ++x) {
			if (map[y][x] == 0)
				nTemp++;
		}
	}

	if (nTemp < nAnswer)
		nAnswer = nTemp;
}