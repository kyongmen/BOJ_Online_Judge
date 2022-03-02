#include <iostream>
#include <vector>
#include <memory.h>

const int MAX = 8;
int map[MAX][MAX];

int N, M;
int aDirection[8];

int answer = 1e9;

struct Camera
{
	int _y, _x;
	int _type;

	Camera()
	{
		_y = _x = 0;
		_type = 1;
	}
	Camera(int y, int x, int type)
	{
		_y = y;
		_x = x;
		_type = type;
	}
};

std::vector<Camera> vecCameras;

void WatchLeft(int y, int x);
void WatchRight(int y, int x);
void WatchUp(int y, int x);
void WatchDown(int y, int x);

void DFS(int nCnt);
void Calculate();
void Watch(Camera camera, int dir);

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	std::cin >> N >> M;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			std::cin >> map[y][x];
			if (map[y][x] != 0 && map[y][x] != 6) {
				Camera cam(y, x, map[y][x]);
				vecCameras.push_back(cam);
			}
		}
	}

	DFS(0);

	std::cout << answer << "\n";
	return 0;
}

void Watch(Camera camera, int dir)
{
	int y = camera._y;
	int x = camera._x;
	int type = camera._type;

	switch (type) {
	case 1:
	{
		if (dir == 0)
			WatchRight(y, x);
		else if (dir == 1)
			WatchDown(y, x);
		else if (dir == 2)
			WatchLeft(y, x);
		else if (dir == 3)
			WatchUp(y, x);
		break;
	}
	case 2:
	{
		if (dir == 0 || dir == 2) {
			WatchRight(y, x);
			WatchLeft(y, x);
		}
		else if (dir == 1 || dir == 3) {
			WatchUp(y, x);
			WatchDown(y, x);
		}
		break;
	}
	case 3:
	{
		if (dir == 0) {
			WatchRight(y, x);
			WatchUp(y, x);
		}
		else if (dir == 1) {
			WatchDown(y, x);
			WatchRight(y, x);
		}
		else if (dir == 2) {
			WatchLeft(y, x);
			WatchDown(y, x);
		}
		else if (dir == 3) {
			WatchLeft(y, x);
			WatchUp(y, x);
		}
		break;
	}
	case 4:
	{
		if (dir == 0) {
			WatchLeft(y, x);
			WatchUp(y, x);
			WatchRight(y, x);
		}
		else if (dir == 1) {
			WatchUp(y, x);
			WatchRight(y, x);
			WatchDown(y, x);
		}
		else if (dir == 2) {
			WatchLeft(y, x);
			WatchRight(y, x);
			WatchDown(y, x);
		}
		else if (dir == 3) {
			WatchLeft(y, x);
			WatchUp(y, x);
			WatchDown(y, x);
		}
		break;
	}
	case 5:
	{
		WatchLeft(y, x);
		WatchUp(y, x);
		WatchRight(y, x);
		WatchDown(y, x);
		break;
	}
	}
}

void Calculate()
{
	int nCameraNum = vecCameras.size();

	for (int i = 0; i < nCameraNum; i++) {
		Watch(vecCameras[i], aDirection[i]);
	}

	int nCnt = 0;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			if (map[y][x] == 0)
				nCnt++;
		}
	}

	if (nCnt < answer)
		answer = nCnt;
}

void DFS(int nCnt)
{
	if (nCnt == vecCameras.size()) {
		// Calculate
		int copyMap[MAX][MAX];
		memcpy(copyMap, map, sizeof(map));

		Calculate();

		memcpy(map, copyMap, sizeof(copyMap));
		return;
	}

	for (int i = 0; i < 4; i++) {
		aDirection[nCnt] = i;
		DFS(nCnt + 1);
	}
}

void WatchLeft(int y, int x)
{
	if (map[y][x] != 9)
		map[y][x] = 9;

	int nx = x - 1;
	while (true) {
		if (nx < 0 || map[y][nx] == 6)
			break;

		map[y][nx--] = 9;
	}

	return;
}

void WatchRight(int y, int x)
{
	if (map[y][x] != 9)
		map[y][x] = 9;

	int nx = x + 1;
	while (true) {
		if (nx >= M || map[y][nx] == 6)
			break;

		map[y][nx++] = 9;
	}

	return;
}

void WatchUp(int y, int x)
{
	if (map[y][x] != 9)
		map[y][x] = 9;

	int ny = y - 1;
	while (true) {
		if (ny < 0 || map[ny][x] == 6)
			break;

		map[ny--][x] = 9;
	}

	return;
}

void WatchDown(int y, int x)
{
	if (map[y][x] != 9)
		map[y][x] = 9;

	int ny = y + 1;
	while (true) {
		if (ny >= N || map[ny][x] == 6)
			break;

		map[ny++][x] = 9;
	}

	return;
}
