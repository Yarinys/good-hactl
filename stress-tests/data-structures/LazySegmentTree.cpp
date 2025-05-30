#include "../utilities/template.h"

#include "../../content/data-structures/LazySegmentTree.h"

static unsigned R;
int ra() {
	R *= 791231;
	R += 1231;
	return (int)(R >> 1);
}
volatile int res;
signed main() {
	int N = 10;
	vi v(N);
	iota(all(v), 0);
	random_shuffle(all(v), [](int x) { return ra() % x; });
	Tree tree(N);
    rep(i, 0, N){
        tree.set(i,i+1,v[i]);
    }
	rep(i,0,N) rep(j,0,N) if (i <= j) {
		int ma = 0;
		rep(k,i,j) ma = ma + v[k];
		assert(ma == tree.query(i,j));
	}
	rep(it,0,1000000) {
		int i = ra() % (N+1), j = ra() % (N+1);
		if (i > j) swap(i, j);
		int x = (ra() % 10) - 5;

		int r = ra() % 100;
		if (r < 30) {
			::res = tree.query(i, j);
			int ma = 0;
			rep(k,i,j) ma = ma + v[k];
			assert(ma == ::res);
		}
		else if (r < 70) {
			tree.add(i, j, x);
			rep(k,i,j) v[k] += x;
		}
		else {
			tree.set(i, j, x);
			rep(k,i,j) v[k] = x;
		}
	}
	cout<<"Tests passed!"<<endl;
}
