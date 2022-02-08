#include <iostream>

const int MAX_N = 10;
const int MAX_H = 30;
int map[MAX_H][MAX_N];

int N, M, H;
int nAnswer=MAX_N*MAX_H;

void Solve();
void SetLadders(int nCnt, int cy, int cx);
bool Check();

int main()
{
	// IO Setting
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	// INPUT
	std::cin >> N >> M >> H;
	for (int m = 0; m < M; ++m) {
		int h, n;
		std::cin >> h >> n;
		--h; --n;

		// Ladders
		// +1 --- -1
		map[h][n] = 1;
		map[h][n + 1] = -1;
	}

	Solve();

	return 0;
}

void Solve()
{
	if (Check()) {
		nAnswer = 0;
		std::cout << nAnswer << "\n";
		return;
	}

	SetLadders(1,0,0);

	if (nAnswer > 3){
		nAnswer = -1;		
	}

	std::cout << nAnswer << "\n";
}

void SetLadders(int nCnt, int cy, int cx)
{
	if (nCnt > 3) {
		bool bSuccess = Check();
		if (bSuccess) {
			if (nCnt < nAnswer)
				nAnswer = nCnt;
		}
		return;
	}

	for (int y = cy; y < H; ++y) {
		for (int x = cx; x < N-1; x++) {
			int nx = x+1;
			
			if (map[y][x] == 0 && map[y][nx] == 0) {
				map[y][x] = 1;
				map[y][nx] = -1;

				bool bSuccess = Check();
				if (bSuccess) {
					if(nCnt < nAnswer)
						nAnswer = nCnt;
				}
				else
					SetLadders(nCnt + 1, y, nx+1);

				map[y][x] = 0;
				map[y][nx] = 0;
			}
		}
		cx = 0;
	}
}

bool Check()
{
	bool bRet = true;

	for (int idx = 0; idx < N; ++idx) {
		int curIdx = idx;
		for (int y = 0; y < H; ++y) {
			if (map[y][curIdx]) {
				curIdx += map[y][curIdx];
			}
		}

		if (curIdx == idx)
			continue;
		else {
			bRet = false;
			break;
		}
	}

	return bRet;
}