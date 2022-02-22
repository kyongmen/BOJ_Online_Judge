#include <iostream>

const int MAX = 1e6;
int num[MAX];
int sorted[MAX];

int N;

void Solve();
void MergeSort(int start, int end);
void Merge(int start, int middle, int end);

int main()
{
	// IO Setting
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	// INPUT
	std::cin >> N;
	for (int n = 0; n < N; ++n) {
		std::cin >> num[n];
	}

	Solve();

	return 0;
}

void Solve()
{
	MergeSort(0, N - 1);

	for (int n = 0; n < N; ++n) {
		std::cout << num[n] << "\n";
	}
}

void MergeSort(int start, int end)
{
	if (start >= end)
		return;

	int middle = (start + end) / 2;
	MergeSort(start, middle);
	MergeSort(middle + 1, end);
	Merge(start, middle, end);
}

void Merge(int start, int middle, int end)
{
	int left = start;
	int right = middle + 1;
	int idx = start;

	while (left <= middle && right <= end) {
		if (num[left] <= num[right]) {
			sorted[idx] = num[left];
			left++;
		}
		else {
			sorted[idx] = num[right];
			right++;
		}
		idx++;
	}

	// Remain
	if (left > middle) {
		for (int t = right; t <= end; ++t) {
			sorted[idx] = num[t];
			idx++;
		}
	}
	else {
		for (int t = left; t <= middle; ++t) {
			sorted[idx] = num[t];
			idx++;
		}
	}

	for (int i = start; i <= end; ++i) {
		num[i] = sorted[i];
	}
}