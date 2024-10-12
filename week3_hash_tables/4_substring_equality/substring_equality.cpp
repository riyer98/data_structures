#include <iostream>
#include<string>

using namespace std;

class Solver {
	string s;
	vector<unsigned long long int> hashes;
	const unsigned long long int x = 263,  prime = 4294967291;
	
public:	
	Solver(string s) : s(s) {	
		// initialization, precalculation
		hashes.resize(s.size()+1); hashes[0] = 0;
		for (int i = 0;i<s.size(); i++){
			hashes[i+1] = (hashes[i]*x + (unsigned long long int)s[i])%prime;
		}
	}
	bool ask(int a, int b, int l) {
		unsigned long long int xpl = 1;
		for (int i=0; i<l; i++) xpl *= x;

		unsigned long long int ahash = (hashes[a+l]-hashes[a]*xpl)%prime;
		unsigned long long int bhash = (hashes[b+l]-hashes[b]*xpl)%prime;
		if (ahash != bhash) return false;
		else return s.substr(a,l) == s.substr(b,l);
	}
};

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);

	string s;
	int q;
	cin >> s >> q;
	Solver solver(s);
	for (int i = 0; i < q; i++) {
		int a, b, l;
		cin >> a >> b >> l;
		cout << (solver.ask(a, b, l) ? "Yes\n" : "No\n");
	}
}
