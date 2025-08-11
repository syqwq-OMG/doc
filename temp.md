[P4721 【模板】分治 FFT](https://www.luogu.com.cn/problem/P4721)
## 思路
题目已知 $g_0=0, g_{1, \ldots ,n-1}, f_0=1$，并且 $f_i=\sum_{j=1}^{i}f_{i-j}g_{j}$，求 $f$
### 多项式求逆
主要要注意常数项。考虑记 $F(x)=\sum_{i=0}^{+\infty}f_ix^{i}, G(x)=\sum_{i=0}^{+\infty}g_ix^{i}$，我们发现 $f_i$ 的形式和多项式卷积很像，于是可以写出 $F(x)G(x)=\sum_{i=0}^{+\infty}x^{i}(\sum_{j=0}^{i}f_{i-j}g_{j})$，对于 $i\ge 1$，我们可以发现 $\sum_{j=0}^{i}f_{i-j}g_{j}=f_i\cdot g_0+\sum_{j=1}^{i}f_{i-j}g_{j}=\sum_{j=1}^{i}f_{i-j}g_{j}=f_i$，但是对于 $[x^{0}]F(x)G(x)=0=[x^{0}]F(x)-1$，于是我们得到 $FG=F-1\iff F=(1-G)^{-1}$，套多项式逆的模板就行。时间复杂度为 $O(n \log n)$
### 分治 NTT
分治就是分而治之，这里类似 CDQ分治，就是要考虑小区间之间的影响和内部自己的问题。
我们将求解 $f[0\cdots n-1]$，拆分成一个个子问题，假设要求 $f[l, \ldots ,r]$，我们定义一个函数 `CDQ(l,r)`，表示求解区间 $[i,r]$ 的子问题。
- 首先我们将区间二分，$[l,d], [d+1,r]$ 这两个小区间, 其中$d=\left\lfloor \frac{l+r}{2} \right\rfloor$
- 假设我们在调用 `CDQ(l,d)` 之后，第一个区间的 $f$ **已经处理好了**
- 接下来，我们考虑 $[l,d]$ 区间的 $f$ 对 $[d+1,r]$ 的贡献。我们来分析一下贡献

对于任意一个右半区间的下标 $i \in [d+1, r]$，它的值由递推公式决定：
$$f_i = \sum_{j=1}^{i} f_{i-j} g_j$$

我们可以把求和的下标 $i-j$ 进行分类：
* **第一部分：** $i-j \in [l, d]$。这部分是左半区间对右半区间的贡献。
* **第二部分：** $i-j \in [d+1, r]$。这部分是右半区间内部的贡献。
* **第三部分：** $i-j \in [0, l-1]$。这部分是 `[l, r]` 之前区间的贡献。

在 `CDQ(l, r)` 这个函数中，我们的任务就是计算**第一部分**的贡献。

我们把第一部分的贡献记为 $\Delta f_i$:
$$\Delta f_i = \sum_{k=l}^{d} f_k g_{i-k}$$
这里我们令 $k = i-j$，那么 $j = i-k$。当 $k$ 从 $l$ 遍历到 $d$ 时，$f_k$ 就是左半区间的项。

这个求和 $\sum_{k=l}^{d} f_k g_{i-k}$ 是一个典型的卷积形式。为了计算它，我们可以构造两个多项式：
* 一个代表左半区间的 $f$ 值：$A(x) = \sum_{k=l}^{d} f_k x^k$
* 一个代表 $g$ 值：$B(x) = \sum_{j=1}^{r-l} g_j x^j$

那么，它们的乘积 $C(x) = A(x) \cdot B(x)$ 中，$x^{i}$ 项的系数 $c_i$ 是什么呢？
$$c_i = [x^i]C(x) = \sum_{k=l}^{d} f_k g_{i-k}$$

这正是我们想要的贡献 $\Delta f_i$！所以，我们可以通过一次多项式乘法来批量计算出所有左半区间 $f[l\cdots d]$ 对右半区间 $f[d+1 \cdots r]$ 的贡献。

这里为了减小常数，由于 $A(x)$ 前面全都是 0 ，于是我们可以对 $A(x)$ 整体除以 $x^{l}$，这样在计算对右边区间的影响的时候 $c_i$ 变成 $c^{i-l}$ 即可。

最后我们还要计算右半区间内部的影响，只要调用 `CDQ(d+1,r)` 即可。时间复杂度为 $O(n \log^{2} n)$
## 蒟蒻代码
用的是分治 NTT
``` cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define all(x, n) (x) + 1, (x) + 1 + n
#define vc vector
#define NN " "
#define NL "\n"
using namespace std;
typedef long long ll;
typedef pair<ll, ll> PII;
typedef vc<ll> vi;
typedef vc<PII> vpii;
template <class T, class S>
bool chmax(T &x, S y) { return x < y ? x = y, 1 : 0; }
template <class T, class S>
bool chmin(T &x, S y) { return x > y ? x = y, 1 : 0; }
#define int long long
// #define CF
// ===========================================================
// Problem: P4721 【模板】分治 FFT
// URL: https://www.luogu.com.cn/problem/P4721
// ===========================================================
constexpr int N = 4e6 + 5;
constexpr ll P = 998244353;
constexpr ll G = 3;          // primitive root
constexpr ll iG = 332748118; // inv(G)
#define mod P

int n, m;
ll f[N], g[N];
ll a[N], b[N];
ll L, limit, rev[N];

ll qmi(int a, int b) {
    ll res = 1;
    for (ll t = a; b; t = t * t % P, b >>= 1)
        if (b & 1) res = res * t % P;
    return res;
}

void NTT(ll a[], int lim, int sign) {
    for (int i = 0; i < lim; i++)
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    ll gn, g, x, y;
    for (ll mid = 1; mid < lim; mid <<= 1) {
        gn = qmi((sign == 1 ? G : iG), (P - 1) / (mid << 1));
        for (int r = mid << 1, j = 0; j < lim; j += r) {
            g = 1;
            for (int k = 0; k < mid; k++, g = g * gn % P) {
                x = a[j + k] % P, y = g * a[j + mid + k] % P;
                a[j + k] = (x + y + P) % P, a[j + mid + k] = (x - y + P) % P;
            }
        }
    }
    if (sign == -1) {
        ll inv = qmi(lim, P - 2);
        for (int i = 0; i < lim; i++) a[i] = a[i] * inv % P;
    }
}

void convolve(ll f[], ll g[], int df, int dg) {
    limit = 1, L = 0;
    while (limit <= df + dg) limit <<= 1, L++;
    for (int i = df + 1; i < limit; i++) f[i] = 0;
    for (int i = dg + 1; i < limit; i++) g[i] = 0;
    for (int i = 0; i < limit; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1));
    NTT(f, limit, 1), NTT(g, limit, 1);
    for (int i = 0; i < limit; i++) f[i] = f[i] * g[i] % P;
    NTT(f, limit, -1);
}

void CDQ(int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    CDQ(l, mid);
    int da = mid - l, db = r - l;
    for (int i = 0; i <= da; i++) a[i] = f[i + l];
    for (int i = 0; i <= db; i++) b[i] = g[i];
    convolve(a, b, da, db);
    for (int i = mid + 1; i <= r; i++) f[i] = (f[i] + a[i - l]) % mod;
    CDQ(mid + 1, r);
}

void solve() {
    cin >> n;
    for (int i = 1; i < n; i++) cin >> g[i];
    f[0] = 1;
    CDQ(0, n - 1);
    for (int i = 0; i < n; i++) cout << f[i] << NN;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cout.setf(ios::fixed), cout.precision(5);
    // ================================================
    int T = 1;
#ifdef CF
    cin >> T;
#endif
    while (T--) solve();
    // ================================================
    return 0;
}
```