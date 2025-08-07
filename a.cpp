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
#define int long long
//  ================================================
constexpr int N=4e6+5;
constexpr ll P=998244353;
constexpr ll G=3;   // primitive root
constexpr ll iG=332748118;  // inv(G)

ll f[N],g[N];
ll L,limit,rev[N];

ll qmi(int a,int b){
    ll res=1;
    for(ll t=a;b;t=t*t%P,b>>=1) if(b&1) res=res*t%P;
    return res;
}

void NTT(ll a[],int lim,int sign){
    for(int i=0;i<lim;i++) if(i<rev[i]) swap(a[i],a[rev[i]]);
    ll gn,g,x,y;
    for(ll mid=1;mid<lim;mid<<=1){
        gn=qmi((sign==1?G:iG),(P-1)/mid);
        for(int r=mid<<1,j=0;j<lim;j+=r){
            g=1;
            for(int k=0;k<mid;k++,g=g*gn%P){
                x=a[j+k]%P,y=g*a[j+mid+k]%P;
                a[j+k]=(x+y+P)%P, a[j+mid+k]=(x-y+P)%P;
            }
        }
    }
    if(sign==-1){
        ll inv=qmi(lim,P-2);
        for(int i=0;i<lim;i++) a[i]=a[i]*inv%P; 
    }
}

void convolve(ll f[],ll g[],int df,int dg){
    limit=1,L=0;
    while(limit<=df+dg) limit<<=1,L++;
    for(int i=df+1;i<limit;i++) f[i]=0;
    for(int i=dg+1;i<limit;i++) g[i]=0;
    for(int i=0;i<limit;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(L-1));
    NTT(f,limit,1),NTT(g,limit,1);
    for(int i=0;i<limit;i++) f[i]=f[i]*g[i]%P;
    NTT(f,limit,-1);
}

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