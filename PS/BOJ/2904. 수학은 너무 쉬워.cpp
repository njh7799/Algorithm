#include <cstdio>
#include <vector>
#include <map>
#include <iostream>
#define MAX 1000000
#define abs(a,b) (((a)-(b)>=0)?((a)-(b)):(0))

using namespace std;

vector<int> getPrimeNumbers() {
	bool isPrime[MAX + 1];
	vector<int> primeNumbers;
	for (int i = 0; i < MAX + 1; i++) {
		isPrime[i] = true;
	}
	for (int i = 2; i <= MAX; i++) {
		if (!isPrime[i]) {
			continue;
		}
		primeNumbers.push_back(i);
		for (int j = 2; i * j <= MAX; j++) {
			isPrime[i * j] = false;
		}
	}
	return primeNumbers;
}

map<int, int> primeFactorization(int num, vector<int>& primeNumbers) {
	map<int, int> m;
	for (int i = 0; num > 1; i++) {
		int divider = primeNumbers[i];
		int factor = 0;
		if (num % divider) {
			continue;
		}
		while (num % divider == 0) {
			num /= divider;
			factor += 1;
		}
		m.insert(make_pair(divider, factor));
	}
	return m;
}

map<int, int > getTarget(vector<map<int, int>> numbers) {
	map<int, int > m;

	int* e = (int *)malloc(sizeof(int) * (MAX + 1));
	for (int i = 0; i <= MAX + 1; i++) {
		e[i] = 0;
	}
	for (auto number : numbers) {
		for (auto primeFactor : number) {
			e[primeFactor.first]+= primeFactor.second;
		}
	}
	for (int i = 0; i <= MAX; i++) {
		if (!e[i]) {
			continue;
		}
		m.insert(make_pair(i, e[i]/ numbers.size()));
	}
	return m;
}

int cmp(map<int, int> target, map<int, int> comparator) {
	int cnt = 0;
	for (auto primeNumber : comparator) {
		auto iter = target.find(primeNumber.first);
		if (iter == target.end()) {
			cnt += primeNumber.second;
			continue;
		}
		cnt += abs(primeNumber.second, iter->second);
	}
	return cnt;
}

int pow(int a, int b) {
	int target = 1;
	while (b--) {
		target *= a;
	}
	return target;
}

int turnToInteger(map<int, int > m) {
	int target = 1;
	for (auto I : m) {
		target *= pow(I.first, I.second);
	}
	return target;
}

int main() {
	freopen("input.txt", "r", stdin);
	vector<int> primeNumbers = getPrimeNumbers();
	vector<map<int, int>> numbers;
	map<int, int> a = primeFactorization(480, primeNumbers);
	int N;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		int n;
		scanf("%d", &n);
		numbers.push_back(primeFactorization(n, primeNumbers));
	}
	map<int, int > target = getTarget(numbers);
	int cnt = 0;
	for (auto number: numbers) {
		cnt += cmp(number, target);
	}
	printf("%d %d", turnToInteger(target), cnt);
}