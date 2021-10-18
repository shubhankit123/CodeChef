#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <string>

using namespace std;

#define FOR(start, end, label) for(int label = start; label < end; label++)

template<typename T>
vector<T> input(int N) {
	vector<T> out;
	FOR(0, N, i) {
		T t;
		cin >> t;
		out.push_back(t);
	}
	return out;
}

template<typename T>
T inputOne() {
	T t;
	cin >> t;
	return t;
}

template<typename T>
constexpr bool between(const T& start, const T& test, const T& end) {
	return start <= test && test < end;
}

int main() {

	const int T = inputOne<int>();

	FOR(0, T, i){

		const int N = inputOne<int>();

		const vector<vector<int>> inMat = [&]{
			vector<vector<int>> out{};
			FOR(0, N-1, r) out.push_back(input<int>(N-1));
			return out;
		}();

		vector<vector<int>> outMat = [&]{
			vector<vector<int>> out{};
			FOR(0, N, r) out.push_back(vector<int>(N, 0));
			return out;
		}();

		const auto neighbors = [&](int row, int col) {
			vector<int> out{};
			for(auto [r, c] : vector<pair<int, int>> {{row, col}, {row-1, col}, {row, col-1}, {row-1, col-1}}) {
				if (between(0, r, N-1) && between(0, c, N-1)) {
					out.push_back(inMat[r][c]);
				}
			}
			return out;
		};

		const auto posns = [&]{
			vector<vector<pair<int, int>>> out(N*N+1, vector<pair<int, int>>{});
			FOR(0, N-1, row) {
				FOR(0, N-1, col) {
					out[inMat[row][col]].push_back({row, col});
				}
			}
			return out;
		}();

		vector<pair<int, int>> avail{};

		for(int n = N*N; n > 0; n--) {
			if(!posns[n].empty()) {
				bool nFilled = false;
				vector<pair<int, int>> visited{};
				for(auto [rowN, colN] : posns.at(n)) {
					for(auto [outR, outC] : vector<pair<int, int>> {{rowN, colN}, {rowN+1, colN}, {rowN, colN+1}, {rowN+1, colN+1}}){
						if(find(visited.cbegin(), visited.cend(), pair<int, int>{outR, outC}) == visited.end()) {
							auto nbrs = neighbors(outR, outC);
							if(all_of(nbrs.cbegin(), nbrs.cend(), [&](int k){return k >= n;}) && outMat[outR][outC] == 0) {
								if(!nFilled && posns.at(n).size() == count(nbrs.cbegin(), nbrs.cend(), n)) {
									outMat[outR][outC] = n;
									nFilled = true;
								}
								else {
									avail.push_back({outR, outC});
								}
							}
							visited.push_back({outR, outC});
						}
					}
				}
			}
			else {
				const auto [outR, outC] = avail.back();
				avail.pop_back();
				outMat[outR][outC] = n;
			}
		}

		const string print = [&]{
			string out = "";
			FOR(0, N, row) {
				FOR(0, N, col) {
					out += to_string(outMat[row][col]) + " ";
				}
				out += "\n";
			}
			return out;
		}();

		std::cout << print;

	}

}



