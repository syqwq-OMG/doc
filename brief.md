[TOC]
## general
``` cpp
#include <bits/stdc++.h>
#define pb push_back
#define vc vector
#define fi first
#define se second
#define all(x, n) (x) + 1, (x) + 1 + n
#define NL "\n"
#define NN " "
using namespace std;
typedef long long ll;
typedef vc<ll> vi;
typedef pair<ll, ll> PII;
typedef vc<PII> vpii;
template<class T,class S>
bool chmax(T& x,S y){ return x<y?x=y,1:0; }
template<class T,class S>
bool chmin(T& x,S y){ return x>y?x=y,1:0; }
// #define CF
// #define int long long
//  ================================================

void solve() {
}
//  ================================================
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cout.setf(ios::fixed), cout.precision(5);
    int T = 1;
#ifdef CF
    cin >> T;
#endif // CF
    while (T--) solve();
    return 0;
}
```
## math
### number theory
#### eular sieve
``` cpp
vi primes;
bool st[N];
void ss(int maxn){
    for(int i=2;i<=maxn;i++){
        if(!st[i]) primes.pb(i);
        for(int j:primes){
            if(j>maxn/i) break;
            st[i*j]=1;
            if(i%j==0) break;
        }
    }
}
```
#### eratothenes sieve
``` cpp
vi primes;
bitset<N> st;
void ass(int maxn){
    for(int i=2;i<=maxn;i++){
        if(st[i]) continue;
        primes.pb(i);
        for(int j=i*2;j<=maxn;j+=i) st[j]=1;
    }
}
```
#### exgcd
``` cpp
void exgcd(int a, int b, int &x, int &y) {
    if(!b) return x = 1, y = 0, void();
    exgcd(b, a % b, y, x), y -= a / b * x;
}
```
#### $\phi(n)$
``` cpp
// $O(log n)$ 求单点欧拉函数
ll get_phi(ll x){
	ll phi=1;
	for(ll i=2;i<=x/i;i++){
		if(x%i==0){
			phi*=(i-1);
			x/=i;
			while(x%i==0) phi*=i,x/=i;
		}
	}
	if(x>1) phi*=(x-1);
	return phi;
}
// $O(n)$  递推求 $1$ 到 $n$ 欧拉函数
bool st[N];
vi primes;
ll phi[N];
void get_phi(ll maxn){
	phi[1]=1;
	for(ll i=2;i<=maxn;i++){
		if(!st[i]) primes.pb(i),phi[i]=i-1;
		for(ll j:primes){
			if(j>maxn/i) break;
			st[i*j]=1;
			if(i%j==0) { phi[i*j]=phi[i]*j; break; }
			phi[i*j]=phi[i]*(j-1);
		}
	}
}
```
#### multiplicative func
``` cpp
// 完全积性函数
bool st[N];
vi primes;
ll f[N];
void ss(int maxn){
    for(int i=2;i<=maxn;i++){
        if(!st[i]) primes.pb(i),f[i]=initial_value(i);
        for(int j:primes){
            if(j>maxn/i) break;
            st[i*j]=1,f[i*j]=f[i]*f[j];
            if(i%j==0) break;
        }
    }
}
// 求 p perp q 的积性函数
// 单点求
ll get_f(ll n){
	ll ans=1;
	for(int i=2;i<=n/i;i++){
		int cnt=0;
		while(n%i==0) cnt++,n/=i;
		ans=ans*f(i,cnt)%mod; // f(p,k)=f(p^k)
	}
	if(n>1) ans=ans*f(n,1)%mod;
	return ans;
}
// 也可以利用最小的质数来递推 1 ~ n
// cnt[] 记录最小质数出现的次数
bool st[N];
vi primes;
ll f[N],cnt[N];
void ss(int maxn){
	f[1]=1;
    for(int i=2;i<=maxn;i++){
        if(!st[i]) primes.pb(i),cnt[i]=1,f[i]=calc_f(i,1);
        for(int j:primes){
            if(j>maxn/i) break;
            st[i*j]=1;
            if(i%j==0){
                cnt[i*j]=cnt[i]+1;
                f[i*j]=f[i]/calc_f(j,cnt[i])*calc_f(j,cnt[i]+1);
                break;
            }
            cnt[i*j]=1;
            f[i*j]=f[i]*calc_f(j,1);
        }
    }
}
```
#### $\mu(n)$
``` cpp
bool st[N];
vi primes;
int mu[N];
void get_mu(int maxn){
	mu[1]=1;
    for(int i=2;i<=maxn;i++){
        if(!st[i]) primes.pb(i),mu[i]=-1;
        for(int j:primes){
            if(j>maxn/i) break;
            st[i*j]=1;
            if(i%j==0){ mu[i*j]=0; break; }
            mu[i*j]=-mu[i];
        }
    }
}
```
### matrix
#### matrix mul
``` cpp
const int N=105;
const ll mod=1e9+7;
template<class T>
struct mat{
	int n,m;    // 0~n-1, 0~m-1
	T a[N][N];
	mat(int n,int m) { this->n=n,this->m=m; memset(a, 0, sizeof a); }
    T* operator[](int x) { return a[x]; }
    const T* operator[](int x) const { return a[x]; }
    mat operator-(const mat &rhs) const {
        mat<T> res(n,m);
        for(int i=0;i<n;i++) for(int j=0;j<m;j++)
            res[i][j]=(a[i][j]+mod-rhs[i][j])%mod;
        return res;
    }
    mat operator+(const mat &rhs) const {
        mat<T> res(n,m);
        for(int i=0;i<n;i++) for(int j=0;j<m;j++)
            res[i][j]=(a[i][j]+rhs[i][j])%mod;
        return res;
    }
    mat operator*(const mat &rhs) const {
    	// assert(m==rhs.n);
        mat<T> res(n,rhs.m);
		for(int i=0;i<n;i++) for(int j=0;j<rhs.m;j++) for(int k=0;k<m;k++)
			res[i][j]+=a[i][k]*rhs[k][j], res[i][j]%=mod;
        return res;
    }
    mat qmi(int k) {
    	// assert(n==m);
        mat<T> res(n, n), t=*this;
        for(int i=0;i<n;i++) res[i][i]=1;
        for(;k;t=t*t,k>>=1) if(k&1) res=res*t;
        return res;
    }
};
```
#### gauss elimination
``` cpp
constexpr int N=105;
constexpr double eps=1e-6;
template<class T=double>
struct gmat{
	int n,m;	// 0~n-1, 0~m-1
	T a[N][N];
	gmat(int n,int m) { this->n=n,this->m=m; memset(a, 0, sizeof a); }
    T* operator[](int x) { return a[x]; }
    const T* operator[](int x) const { return a[x]; }
    // 0: no solution || 1: one solution || -1: inf solution
	int gauss(){
		int c,r;
		for(c=0,r=0;c<n;c++){
			int t=r;
			for(int i=r+1;i<n;i++) if(fabs(a[t][c])<fabs(a[i][c])) t=i;
			if(fabs(a[t][c])<eps) continue;
			for(int i=c;i<m;i++) swap(a[t][i],a[r][i]);
			for(int i=m-1;i>=c;i--) a[r][i]/=a[r][c];
			for(int i=r+1;i<n;i++)
				if(fabs(a[i][c])>eps)
					for(int j=m-1;j>=c;j--) a[i][j]-=a[i][c]*a[r][j];
			r++;
		}
		if(r<n){
			for(int i=r;i<n;i++) if(fabs(a[i][m-1])>eps) return 0;
			return -1;
		}
		for(int i=n-1;i>=0;i--) for(int j=0;j<i;j++) a[j][m-1]-=a[i][m-1]*a[j][i];
		return 1;
	}
};
```
bit matrix
``` cpp
constexpr int N = 105;
struct bmat {
    int n, m;
    bitset<N> a[N];
    bmat(int n, int m) {
        this->n = n, this->m = m;
        for (int i = 0; i < n; i++) a[i] &= 0;
    }
    bitset<N> &operator[](int x) { return a[x]; }
    const bitset<N> &operator[](int x) const { return a[x]; }
    int gauss() {
        int c, r;
        for (r = c = 0; c < n; c++) {
            int t = r;
            for (; t < n && !a[t][c]; t++);
            if (!a[t][c]) continue;
            swap(a[t], a[r]);
            for (int i = r + 1; i < n; i++) if (a[i][c]) a[i] ^= a[r];
            r++;
        }
        if (r < n) {
            for (int i = r; i < n; i++) if (a[i][m - 1]) return 0;
            return -1;
        }
        for (int i = n - 1; i >= 0; i--)
            for (int j = 0; j < i; j++)
                a[j][m - 1] = a[j][m - 1] ^ a[i][m - 1] & a[j][i];
        return 1;
    }
};
```
#### linear basis
``` cpp
typedef unsigned long long ull;
constexpr int N=105;
constexpr int B=50;
int rk=0;
ull p[N];
void insert(ull x){
	for(int i=B;i>=0;i--){
		if(!(x>>i&1)) continue;
		if(!p[i]) return p[i]=x,++rk,void();
		x^=p[i];
	}
}
```
### polynomial
#### FFT
``` cpp
namespace Poly {
using cd = complex<double>;
const double PI = acos(-1.0);
constexpr int N = 4e6 + 5;

void FFT(vc<cd> &a, int lim, int sign, const ll rev[]) {
    for (int i = 0; i < lim; i++)
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int mid = 1; mid < lim; mid <<= 1) {
        cd wn(cos(PI / mid), sign * sin(PI / mid));
        for (int r = mid << 1, j = 0; j < lim; j += r) {
            cd w(1, 0);
            for (int k = 0; k < mid; k++, w *= wn) {
                cd x = a[j + k];
                cd y = w * a[j + mid + k];
                a[j + k] = x + y;
                a[j + mid + k] = x - y;
            }
        }
    }
    if (sign == -1) {
        for (int i = 0; i < lim; i++) 
            a[i] /= lim;
    }
}
using poly = vc<ll>;
poly get(int deg) { return poly(deg + 1, 0); }
poly operator+(poly f, poly g) {
    int d = max(f.size(), g.size());
    f.resize(d), g.resize(d);
    poly res = get(d - 1);
    for (int i = 0; i < d; ++i) res[i] = f[i] + g[i];
    return res;
}
poly operator-(poly f, poly g) {
    int d = max(f.size(), g.size());
    f.resize(d), g.resize(d);
    poly res = get(d - 1);
    for (int i = 0; i < d; ++i) res[i] = f[i] - g[i];
    return res;
}
poly operator*(poly f, poly g) {
    static ll rev[N];
    int df = f.size() - 1, dg = g.size() - 1, limit = 1, L = 0;
    while (limit <= df + dg) limit <<= 1, L++;
    for (int i = 0; i < limit; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1));
    vc<cd> fa(f.begin(), f.end()), fb(g.begin(), g.end());
    fa.resize(limit), fb.resize(limit);
    FFT(fa, limit, 1, rev), FFT(fb, limit, 1, rev);
    for (int i = 0; i < limit; i++) fa[i] *= fb[i];
    FFT(fa, limit, -1, rev);
    poly res = get(df + dg);
    for (int i = 0; i <= df + dg; i++) res[i] = static_cast<ll>(round(fa[i].real()));
    return res;
}
poly operator*(poly f, ll x) {
    for (int i = 0; i < f.size(); i++) f[i] *= x;
    return f;
}
poly mod(poly f, int n) {
    f.resize(n, 0);
    return f;
}
poly inv(poly h) {
    int n = h.size();
    if (n == 0) return poly();
    poly f = get(0), d = get(0);
    f[0] = 1, d[0] = 2;
    for (int len = 2; (len >> 1) < n; len <<= 1)
        f = mod(f * (d - mod(h, len) * f), len);
    return f;
}
poly sqrt(poly h) {
    int n = h.size();
    poly f = get(0);
    f[0] = 1;
    for (int len = 2; (len >> 1) < n; len <<= 1) {
        poly invf = inv(mod(f, len));
        poly t = mod(h, len) * invf;
        f.resize(len);
        f = (f + t) * 0.5; // New f is (f_old + h/f_old)/2
        f.resize(len);
    }
    return f;
}
} // namespace Poly
```

#### NTT
``` cpp
constexpr ll MOD = 998244353;
namespace Poly {
constexpr int N = 4e6 + 5;
constexpr ll P = 998244353;
constexpr ll G = 3;          // primitive root
constexpr ll iG = 332748118; // inv(G)

ll limit, L, rev[N];
ll qmi(int a, int b) {
    ll res = 1;
    for (ll t = a; b; t = t * t % P, b >>= 1)
        if (b & 1) res = res * t % P;
    return res;
}
void NTT(vi &a, int lim, int sign, const ll rev[]) { // lim=2^k
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
using poly = vi;
poly get(int deg) { return poly(deg + 1, 0); }
poly operator+(poly f, poly g) {
    int d = max(f.size(), g.size());
    f.resize(d), g.resize(d);
    poly res = get(d - 1);
    for (int i = 0; i < d; ++i) res[i] = (f[i] + g[i]) % P;
    return res;
}
poly operator-(poly f, poly g) {
    int d = max(f.size(), g.size());
    f.resize(d), g.resize(d);
    poly res = get(d - 1);
    for (int i = 0; i < d; ++i) res[i] = (f[i] - g[i] + P) % P;
    return res;
}
poly operator*(poly f, poly g) {
    if (f.empty() || g.empty()) return {};
    static ll rev[N];
    int df = f.size() - 1, dg = g.size() - 1, limit = 1, L = 0;
    while (limit <= df + dg) limit <<= 1, L++;
    for (int i = 0; i < limit; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1));
    f.resize(limit), g.resize(limit);
    NTT(f, limit, 1, rev), NTT(g, limit, 1, rev);
    for (int i = 0; i < limit; ++i) f[i] = f[i] * g[i] % P;
    NTT(f, limit, -1, rev);
    poly res = get(df + dg);
    ll inv = qmi(limit, P - 2);
    for (int i = 0; i <= df + dg; i++) res[i] = f[i];
    return res;
}
poly operator*(poly f, ll x) {
    for (int i = 0; i < f.size(); i++) f[i] = f[i] * x % P;
    return f;
}
poly mod(poly f, int n) {
    f.resize(n, 0);
    return f;
}
poly inv(poly h) {
    poly f = get(0), d = get(0);
    f[0] = qmi(h[0], P - 2), d[0] = 2;
    ll n = h.size();
    for (int len = 2; (len >> 1) < n; len <<= 1) // f0(x) 已经有了 len>>1 项，接下来是要 mod x^(len)
        f = mod(f * (d - mod(h, len) * f), len);
    return f;
}
poly sqrt(poly h) {
    poly f = get(0);
    f[0] = 1;
    ll inv2 = qmi(2, P - 2), n = h.size();
    for (int len = 2; (len >> 1) < n; len <<= 1) {
        poly exf = f;
        exf.resize(len);
        poly invf = inv(exf);
        poly t = mod(h, len);
        t = mod(t * invf, len);
        f.resize(len);
        f = (f + t) * inv2;
    }
    return f;
}
poly dervt(poly f) {
    if (f.empty()) return poly();
    int n = f.size() - 1;
    if (n == 0) return get(-1); // Derivative of a constant is 0
    poly res = get(n - 1);
    for (int i = 0; i < n; i++)
        res[i] = (ll)f[i + 1] * (i + 1) % P;
    return res;
}
poly integ(poly f) {
    int n = f.size() - 1;
    poly res = get(n + 1);
    for (int i = 0; i <= n; i++) 
        res[i + 1] = (ll)f[i] * qmi(i + 1, P - 2) % P;
    return res;
}
poly ln(poly f) {
    int n = f.size();
    assert(n == 0 || f[0] == 1);
    poly t = dervt(f) * inv(f);
    return integ(mod(t, n - 1));
}
poly exp(poly f) {
    int n = f.size();
    assert(n == 0 || f[0] == 0);
    poly B = get(0);
    B[0] = 1;
    for (int len = 2; (len >> 1) < n; len <<= 1) {
        poly lnB = ln(mod(B, len)), t = mod(f, len) - lnB;
        t[0] = (t[0] + 1 + P) % P;
        B = B * t;
        B.resize(len);
    }
    B.resize(n);
    return B;
}
} // namespace Poly
using namespace Poly;
```

#### primitive root
``` cpp
///// require /////
// get_phi(), qmi()
///////////////////
const int N = 1e6 + 5;
ll n, d;
vi primes;
ll phi[N];
#define gcd __gcd
bool exist(ll x) {  // 判断 x 是否有原根
    if (x == 2 || x == 4) return 1;
    if (x % 2 == 0) x /= 2;
    for (ll p = 0, i = 1; p <= x; i++) {
        p = primes[i];
        if (x % p == 0) {
            while (x % p == 0) x /= p;
            return x == 1;
        }
    }
    return 0;
}
vi divide(ll x) { // 分解质因数到 fac 中
    vi fac; fac.clear();
    for (ll i = 2; i <= x / i; i++) {
        if (x % i == 0) {
            fac.push_back(i);
            while (x % i == 0) x /= i;
        }
    }
    if (x > 1) fac.push_back(x);
    return fac;
}
ll min_pr(ll x) {   // 找到 x 的最小的原根
    auto fac = divide(phi[x]);
    for (ll i = 1;; i++) {
        if (gcd(x, i) != 1) continue;
        bool flg = 1;
        for (ll p : fac)
            if (qmi(i, phi[x] / p, n) == 1) {
                flg = 0;
                break;
            }
        if (flg) return i;
    }
    return 0;
}
vi all_pr(ll g, ll x) { // 根据最小的原根 g 找到所有 x 的原根
    vi pr; pr.clear();
    // gk = g ^ k
    for (ll gk = g, k = 1; pr.size() < phi[phi[x]]; k++, gk = gk * g % x) {
        if (gcd(k, phi[x]) == 1) pr.push_back(gk);
    }
    return pr;
}
void solve() {
    get_phi(1e6);
    if (!exist(n)) return;
    ll g = min_pr(n);
    auto pr = all_pr(g, n);
    cout << phi[phi[n]] << NL;  // 原根的数量
    for(ll x:pr) cout << x << NN;
    cout<<NL;
}
```

#### BSGS
``` cpp
// min x s.t. a^x=b ( mod p) p in PP
ll BSGS(ll a, ll b, ll p) {
    if (b == 1) return 0;
    if (a % p == b % p) return 1;
    a %= p, b %= p;

    ll B = ceil(sqrt(p));
    ll ia = inv(a, p), aB = qmi(a, B, p);
    map<ll, ll> mp;
    for (ll t = 0, val = b; t < B; t++, val = val * ia % p)
        if (!mp[val]) mp[val] = t + 1; // 区分没有初始化的哈希表的值
    for (ll s = 0, val = 1; s <= B; s++, val = val * aB % p)
        if (mp[val]) return s * B + mp[val] - 1;
    return -1;  // no sol
}
```

#### Lagrange interpolation
以下代码为拉插求 $f(n)=sum_{i=1}^n i^k$，可以知道 $\text{deg} f=k+1$，所以需要 $k+2$ 个点）
``` cpp
const ll mod = 1e9 + 7;
const ll K = 1e6 + 5;
ll n, k;     // f(n) deg(f)=k+1
ll y[K], fac[K], pre[K], suf[K];
void solve() {
    fac[0] = pre[0] = suf[k + 3] = 1;
    for (int i = 1; i <= k + 2; i++) fac[i] = fac[i - 1] * i % mod;
    for (int i = 1; i <= k + 2; i++) pre[i] = pre[i - 1] * (n - i) % mod;
    for (int i = k + 2; i > 0; i--) suf[i] = suf[i + 1] * (n - i) % mod;
    for (int i = 1; i <= k + 2; i++) y[i] = (y[i - 1] + qmi(i, k)) % mod;
    ll ans = 0;
    for (int i = 1; i <= k + 2; i++) {
        ll q = pre[i - 1] * suf[i + 1] % mod;
        ll p = (k - i) & 1 ? -1 : 1;
        p = (p + mod) * fac[i - 1] % mod * fac[k + 2 - i] % mod;
        ans = (ans + y[i] * q % mod * inv(p) % mod) % mod;
    }
    cout << (ans + mod) % mod;
}
```
