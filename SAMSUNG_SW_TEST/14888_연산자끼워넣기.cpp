#include <iostream>

const int MAX = 11;

int Array[MAX];

// + - * /
int Operator[4];

int N;
int minAnswer=1e9;
int maxAnswer=-1e9;

void Solve();
void DFS(int nCurNum, int nCnt);
int Calculate(int num1, int num2, int Operator);

int main()
{
	// IO Setting
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	// INPUT
	std::cin >> N;
	for (int n = 0; n < N; n++) {
		std::cin >> Array[n];
	}

	for (int i = 0; i < 4; i++) {
		std::cin >> Operator[i];
	}

	Solve();

	return 0;
}

void Solve()
{
	DFS(Array[0], 0);

	std::cout << maxAnswer << "\n" << minAnswer << "\n";
}

void DFS(int nCurNum, int nCnt)
{
	if (nCnt >= N-1) {
		// Update Answer
		if (nCurNum > maxAnswer)
			maxAnswer = nCurNum;
		
		if (nCurNum < minAnswer)
			minAnswer = nCurNum;
	}

	for (int i = 0; i < 4; i++) {
		if (Operator[i] <= 0)
			continue;

		Operator[i]--;
		int temp = Calculate(nCurNum, Array[nCnt+1], i);
		DFS(temp, nCnt + 1);
		Operator[i]++;
	}
}

int Calculate(int num1, int num2, int Operator)
{
	switch (Operator)
	{
	case 0:
		return num1 + num2;
	case 1:
		return num1 - num2;
	case 2:
		return num1 * num2;
	case 3:
		return num1 / num2;
	default:
		break;
	}
}