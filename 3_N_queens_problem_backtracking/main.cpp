#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

bool safe(const vector<vector<bool>> &mat, int x, int y) {
	const int n = mat.size();
	for (int i = 0; i < n; i++) {
		if (const int j = i + y - x, k = x - i + y;
			mat[x][i] || mat[i][y] // ред, колона
			|| (0 <= j && j < n && mat[i][j]) // главна дијагонала
			|| (0 <= k && k < n && mat[i][k])) return false; // обратна дијагонала
	}
	return true;
}

void nQueens(vector<vector<bool>> &mat, int row, vector<vector<int>> &ans, uint64_t &iter) {
	++iter;
	const int n = mat.size();
	if (row == n) {
		ans.emplace_back(n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (mat[i][j]) {
					ans.back()[i] = j;
					continue;
				}
			}
		}
		return;
	}
	for (int i = 0; i < n; i++) {
		if (safe(mat, row, i)) {
			mat[row][i] = true;
			nQueens(mat, row + 1, ans, iter);
			mat[row][i] = false;
		}
	}
}

// Врапер за помалку параметри и scoping
pair<vector<vector<int>>, uint64_t> nQueens(int n) {
	vector mat(n, vector(n, false));
	vector<vector<int>> ans;
	uint64_t iter = 0;
	nQueens(mat, 0, ans, iter);
	return {ans, iter};
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cout << "usage: " << *argv << " N\nN = size of array\n";
		return 1;
	}
	const int n = atoi(argv[1]);
	cout << "Solving " << n << " queens problem..." << endl;
	const auto start = steady_clock::now();
	auto [ans, iter] = nQueens(n);
	auto time = steady_clock::now() - start;
	cout << "TIME!\n";
	for (int i = 0; i < min<int>(ans.size(), 30); i++) {
		for (int j : ans[i]) cout << j << ' ';
		cout << '\n';
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				cout << (ans[i][j] == k ? "##" : "[]");
			}
			cout << '\n';
		}
		cout << '\n';
	}
	cout << "Answer: " << ans.size() << " found\n";
	cout << "Time elapsed: " << fixed << setprecision(6) << time.count() / 1e9 << "s\nnQueens calls: " << iter << '\n';
}