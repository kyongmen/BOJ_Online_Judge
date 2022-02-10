#include <iostream>
#include <vector>
#include <cmath>

const int MAX = 50;
int map[MAX][MAX];

int N, M;
int nAnswer = 1e6;

class Building
{
public:
	explicit Building(int y, int x) :_y(y), _x(x) {};
	virtual ~Building() {};

	int _y, _x;
};
class House : public Building 
{
public:
	explicit House(int y, int x) : Building(y, x) {};
};
class Market : public Building
{
public:
	explicit Market(int y, int x) :Building(y, x), _bOpened(false) {};

	bool _bOpened;
};

std::vector<House> vecHouse;
std::vector<Market> vecMarket;

void Solve();
int GetChickenDistance(const House& house);
void SelectMarkets(int nCnt, int idx);

int main()
{
	// IO Setting
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	// INPUT
	std::cin >> N >> M;
	for (int y = 0; y < N; ++y) {
		for (int x = 0; x < N; ++x) {
			std::cin >> map[y][x];

			if (map[y][x] == 1) {
				// HOUSE
				vecHouse.emplace_back(y,x);
			}
			else if (map[y][x] == 2) {
				vecMarket.emplace_back(y,x);
			}
		}
	}

	// INIT
	vecHouse.reserve(2 * N);
	vecMarket.reserve(13);

	Solve();

	return 0;
}

void Solve()
{
	SelectMarkets(0,0);
	std::cout << nAnswer << "\n";
}

int GetChickenDistance(const House& house)
{
	int nRet = MAX * MAX;

	for (const auto& market : vecMarket) {
		if (!market._bOpened)
			continue;

		int nDistance = std::abs(market._y - house._y) + std::abs(market._x - house._x);
		if (nDistance < nRet)
			nRet = nDistance;
	}

	return nRet;
}

void SelectMarkets(int nCnt, int idx)
{
	if (nCnt == M ) {
		int distance = 0;
		for (const auto& house : vecHouse) {
			distance += GetChickenDistance(house);
		}

		if (distance < nAnswer)
			nAnswer = distance;
		
		return;
	}

	int nMarketCnt = vecMarket.size();
	for (int i = idx; i < nMarketCnt; ++i) {
		if (vecMarket[i]._bOpened)
			continue;

		vecMarket[i]._bOpened = true;
		SelectMarkets(nCnt + 1, i + 1);
		vecMarket[i]._bOpened = false;
	}
}