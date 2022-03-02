#include <iostream>

const int MAX = 1e6;
int room[MAX];

int N, B, C;
long long nAnswer;

void Solve();

int main()
{
	// IO Setting
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	// INPUT
	std::cin >> N;
	for (int n = 0; n < N; n++) {
		int nPeople(0);
		std::cin >> nPeople;
		room[n] = nPeople;
	}

	std::cin >> B >> C;

	Solve();

	return 0;
}

void Solve()
{
	for (int n = 0; n < N; n++) {
		if (room[n] <= B) {
			room[n] = 0;
			nAnswer++;
		}
		else {
			room[n] -= B;
			nAnswer++;

			// remain
			if (room[n] % C != 0) {
				nAnswer += (room[n] / C + 1);
			}
			else {
				nAnswer += (room[n] / C);
			}
		}
	}

	std::cout << nAnswer << "\n";
}