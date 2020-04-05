#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;
using u128 = __uint128_t;

ull bpow(ull a, ull b, ull mod) {
    ull ret = 1;
    while(b) {
        if(b & 1) ret = ((u128)ret * a) % mod;
        a = ((u128)a * a) % mod, b >>= 1;
    }
    return ret;
}
bool check_composite(ull num, ull a, ull d, int s) {
    ull x = bpow(a, d, num);
    if(x == 1 or x == num - 1) return false;
    for(int r = 1; r < s; ++r) {
        x = (u128)x * x % num;
        if(x == num - 1) return false;
    }
    return true;
}
bool miller_rabin(long long n) {
    if(n < 2) return false;
    int r = 0;
    ull d = n - 1;
    while((d & 1) == 0) d >>= 1, r++;
    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if(n == a) return true;
        if(check_composite(n, a, d, r)) return false;
    }
    return true;
}
int main() {
    long long n;
    scanf("%lld", &n);
    miller_rabin(n);
    return 0;
}