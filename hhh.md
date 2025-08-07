#### NTT

假设质数 $p \in {\mathbb{P}}$ 可以表示成 $p = r \cdot 2^{l} + 1$, $g$ 是$p$ 的原根, 那么我们可以使用 $g_{n} = g^{\frac{p - 1}{n}}$ 来代替$\omega_{n}$, 在此基础上进行的 FFT 就是 NTT. ( 注意这里的 $n$ 依然是$n = 2^{k},k \leq l$ )

这是因为它具有和 $\mathbb{C}$ 上单位根一样良好的性质:

- $g_{2n}^{2k} \equiv g_{n}^{k}\left( \operatorname{mod}p \right)\left( 2n < 2^{l} \right)$

- $g_{2n}^{n} \equiv - 1\left( \operatorname{mod}p \right)\left( 2n < 2^{l} \right)$

- $\sum_{k = 0}^{n - 1}g_{n}^{ik}g_{n}^{- kj} \equiv \begin{cases}
  n & \text{ if }i = j \\
  0 & \text{ otherwise }
  \end{cases}\left( \operatorname{mod}p \right)$, 其中 $0 \leq i,j < n$

因此, 对于 DFT 和 IDFT $g_{n}$ 在 ${\mathbb{Z}}_{p}$ 下 与 $\omega_{n}$在 $\mathbb{C}$ 下的推导过程是一致的.

常见模数:

- $65537 = 2^{16} + 1,g = 3,g^{- 1} = 21846$

- $998244353 = 119 \cdot 2^{23} + 1,g = 3,g^{- 1} = 332748118$

<!-- -->

- $1004535809 = 479 \cdot 2^{21} + 1 > 10^{9},g = 3,g^{- 1} = 334845270$

- $4179340454199820289 = 29 \cdot 2^{57} + 1 > 4 \times 10^{18},g = 3,g^{- 1} = 1393113484733273430$

``` cpp
constexpr int N = 4e6 + 5;
constexpr ll P = 998244353;
constexpr ll G = 3;          // primitive root
constexpr ll iG = 332748118; // inv(G)

int n, m;
ll f[N], g[N];
ll L, limit, rev[N];

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

void solve() {
    convolve(f, g, n, m);
    for (int i = 0; i <= n + m; i++) cout << f[i] << NN;
}
```
