/**
 * Description: Segment tree with ability to add or set values of large intervals, and compute max of intervals.
 * Can be changed to other things e.g. min, max, sum, xor, gcd, lcm (by replacing "max" function, replacing "val" neutral value, and sometimes other things specified).
 * Use with a bump allocator for better performance, and SmallPtr or implicit indices to save memory.
 * Time: O(\log N) query, O(N) non-sparse build
 * Usage: Node* tr = new Node(v, 0, sz(v));
 * Status: stress-tested a bit
 */
#pragma once
#include "../various/BumpAllocator.h"
//  1. add(l, r, x): add x to every element in range [l, r)
//  2. set(l, r, x): set every element in range [l, r) to x
//  3. query(l, r): find the sum of values in range [l, r)
struct Tree {
    int n;
    vector<ll> sum;
    vector<ll> lazy_add;
    vector<ll> lazy_set;

    Tree(int n) : n(n), sum(n * 4), lazy_add(n * 4), lazy_set(n * 4) {}

    void add(int s, int l, int r, int ql, int qr, int x) {
        if (r <= ql || qr <= l) return;
        if (ql <= l && r <= qr) {
            apply_add(s, r - l, x);
            return;
        }
        push(s, r - l);
        int m = (l + r) / 2;
        add(s * 2 + 0, l, m, ql, qr, x);
        add(s * 2 + 1, m, r, ql, qr, x);
        sum[s] = sum[s * 2] + sum[s * 2 + 1];
    }

    void set(int s, int l, int r, int ql, int qr, int x) {
        if (r <= ql || qr <= l) return;
        if (ql <= l && r <= qr) {
            apply_set(s, r - l, x);
            return;
        }
        push(s, r - l);
        int m = (l + r) / 2;
        set(s * 2 + 0, l, m, ql, qr, x);
        set(s * 2 + 1, m, r, ql, qr, x);
        sum[s] = sum[s * 2] + sum[s * 2 + 1];
    }

    ll query(int s, int l, int r, int ql, int qr) {
        if (r <= ql || qr <= l) return 0;
        if (ql <= l && r <= qr) return sum[s];
        push(s, r - l);
        int m = (l + r) / 2;
        return query(s * 2, l, m, ql, qr) + query(s * 2 + 1, m, r, ql, qr);
    }

    void push(int s, int len) {
        if (lazy_set[s]) {
            apply_set(s * 2, len / 2, lazy_set[s]);
            apply_set(s * 2 + 1, (len + 1) / 2, lazy_set[s]);
            lazy_set[s] = 0;
        }
        if (lazy_add[s]) {
            apply_add(s * 2, len / 2, lazy_add[s]);
            apply_add(s * 2 + 1, (len + 1) / 2, lazy_add[s]);
            lazy_add[s] = 0;
        }
    }

    void apply_add(int s, int len, ll x) {
        sum[s] += x * len;
        lazy_add[s] += x;
    }

    void apply_set(int s, int len, ll x) {
        sum[s] = x * len;
        lazy_add[s] = 0;
        lazy_set[s] = x;
    }

    void add(int l, int r, int x) { add(1, 0, n, l, r, x); }
    void set(int l, int r, int x) { set(1, 0, n, l, r, x); }
    ll query(int l, int r) { return query(1, 0, n, l, r); }
};
