#include <iostream>
#include <deque>
#include <queue>
#include <algorithm>

const int MAX = 10;
int map[MAX][MAX];
int mapFeed[MAX][MAX];

const int dy[8] = {-1,-1,0,1,1,1,0,-1};
const int dx[8] = {0,1,1,1,0,-1,-1,-1};

int N, M, K;

class Tree
{
public:
	explicit Tree(int y, int x, int age)
		:_y(y), _x(x), _age(age) {};

	int _y, _x, _age;

	const bool operator< (const Tree& other)
	{
		if (this->_age == other._age) {
			return false;
		}
		return this->_age < other._age;
	}
};

std::deque<Tree> deqTrees;
std::queue<Tree> qDied;
std::queue<std::pair<int,int>> qParentsPos;

void Solve();

void Spring();
void Summer();
void Autumn();
void Winter();

int main()
{
	// IO Setting
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	// INPUT
	std::cin >> N >> M >> K;
	for (int y = 0; y < N; ++y) {
		for (int x = 0; x < N; ++x) {
			std::cin >> mapFeed[y][x];
		
			// INIT
			map[y][x] = 5;
		}
	}

	for (int m = 0; m < M; ++m) {
		int y, x, age;
		std::cin >> y >> x >> age;

		deqTrees.emplace_back(y-1, x-1, age);
	}

	Solve();

	return 0;
}

void Solve()
{
	// Sort
	std::sort(deqTrees.begin(), deqTrees.end());

	for (int k = 0; k < K; ++k) {
		Spring();
		Summer();
		Autumn();
		Winter();
	}

	std::cout << deqTrees.size() << "\n";
}

void Spring()
{
	int nSize = deqTrees.size();
	for (int n = 0; n < nSize; ++n) {
		auto tree = deqTrees.front();
		deqTrees.pop_front();

		if (map[tree._y][tree._x] >= tree._age) {
			// Grow up
			map[tree._y][tree._x] -= tree._age;
			tree._age++;
			deqTrees.emplace_back(tree._y, tree._x, tree._age);

			if (tree._age % 5 == 0) {
				qParentsPos.emplace(tree._y, tree._x);
			}
		}
		else {
			// Died
			qDied.emplace(tree);
		}
	}
}

void Summer()
{
	while (!qDied.empty()) {
		// Nourishment
		auto tree = qDied.front();
		qDied.pop();

		map[tree._y][tree._x] += tree._age / 2;
	}
}

void Autumn()
{
	// Reproduce
	while (!qParentsPos.empty()) {
		int y = qParentsPos.front().first;
		int x = qParentsPos.front().second;
		qParentsPos.pop();

		for (int dir = 0; dir < 8; ++dir) {
			int ny = y + dy[dir];
			int nx = x + dx[dir];

			if (ny < 0 || ny >= N || nx < 0 || nx >= N)
				continue;

			deqTrees.emplace_front(ny, nx, 1);
		}
	}
}

void Winter()
{
	for (int y = 0; y < N; ++y) {
		for (int x = 0; x < N; ++x) {
			map[y][x] += mapFeed[y][x];
		}
	}
}