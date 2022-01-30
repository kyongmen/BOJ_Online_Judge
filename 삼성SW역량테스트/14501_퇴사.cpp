#include <iostream>

const int MAX = 15;

int N;
int T[MAX], P[MAX];
int nAnswer;

bool bSelect[MAX];

void Solve();
void Select(int idx, int price);

int main()
{
	// IO Setting
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	// INPUT
	std::cin >> N;
	for (int n = 0; n < N; n++) {
		std::cin >> T[n] >> P[n];
	}

	Solve();

	return 0;
}

void Solve()
{
	Select(0, 0);

	std::cout << nAnswer << "\n";
}

void Select(int idx, int price)
{
	if (price > nAnswer)
		nAnswer = price;

	for (int i = idx; i < N; i++) {
		if (bSelect[i])
			continue;

		if (i + T[i] > N)
			continue;

		bSelect[i] = true;
		Select(i + T[i], price + P[i]);
		bSelect[i] = false;
	}
}
