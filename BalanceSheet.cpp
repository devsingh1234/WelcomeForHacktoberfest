#pragma GCC optimize("Ofast,unroll-loops")
//#include <bits/extc++.h>
#include <bits/stdc++.h>
//#define int long long
#define ll long long
#define pii pair<int, int>
#define pdd pair<double, double>
#define pll pair<ll, ll>
#define F first
#define S second
#define pb(x) emplace_back(x)
#define MOD 1000000007
#define MOD2 998244353
#define fast ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
// using namespace __gnu_pbds;

template <class T, class U>
istream &operator>>(istream &is, pair<T, U> &val)
{
    is >> val.first >> val.second;
    return is;
}

template <class T>
istream &operator>>(istream &is, vector<T> &val)
{
    for (T &iter : val)
        is >> iter;
    return is;
}

struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

const ll mod = 1'000'000'007;
ll A[1000006], B[1000006], X[1000006], Y[10000006];
vector<pll> sale[1000006];
vector<pair<pll, ll>> event[2000006];

vector<pll> mono(vector<pll> &v, vector<pll> &u)
{
    int vdx = 0, udx = 0;
    vector<pll> res;
    while (vdx < v.size() || udx < u.size())
    {
        if (udx >= u.size())
            res.emplace_back(v[vdx++]);
        else if (vdx >= v.size())
            res.emplace_back(u[udx++]);
        else if (v[vdx].F - v[vdx].S >= u[udx].F - u[udx].S)
            res.emplace_back(v[vdx++]);
        else
            res.emplace_back(u[udx++]);
    }
    return res;
}

vector<pll> best(vector<pll> &v, vector<pll> &u)
{
    int vdx = 0, udx = 0;
    vector<pll> res;
    while (vdx < v.size() || udx < u.size())
    {
        if (udx >= u.size())
            res.emplace_back(v[vdx++]);
        else if (vdx >= v.size())
            res.emplace_back(u[udx++]);
        else if (v[vdx].F >= u[udx].F)
            res.emplace_back(v[vdx++]);
        else
            res.emplace_back(u[udx++]);
    }
    return res;
}


ll solve()
{
    ll ans = 0;
    int N, K;
    cin >> N >> K;
    vector<int> v;
    for (int i = 1; i <= N; i++)
    {
        cin >> A[i] >> B[i] >> X[i] >> Y[i];
        v.emplace_back(A[i]);
        v.emplace_back(B[i]);
        sale[i].clear();
    }
    for (int i = 1; i <= 2 * N; i++)
        event[i].clear();

    sort(v.begin(), v.end());
    v.resize(unique(v.begin(), v.end()) - v.begin());
    for (int i = 1; i <= N; i++)
    {
        A[i] = lower_bound(v.begin(), v.end(), A[i]) - v.begin() + 1;
        B[i] = lower_bound(v.begin(), v.end(), B[i]) - v.begin() + 1;
        event[A[i]].emplace_back(make_pair(pll(X[i], 1), i));
        event[B[i]].emplace_back(make_pair(pll(Y[i], 2), i));
    }

    for (int t = 1; t <= 2 * N; t++)
    {
        sort(event[t].begin(), event[t].end());
        vector<pll> cur = {};
        for (auto [f, i] : event[t])
        {
            auto [p, tp] = f;
            if (tp == 2)
            {
                cur = mono(cur, sale[i]);
                if (cur.size() > K)
                    cur.resize(K);
            }
            else if (tp == 1)
            {
                for (auto [earn, last] : cur)
                    sale[i].emplace_back(pll(earn + X[i] - last, Y[i]));
                if (sale[i].size() < K)
                    sale[i].emplace_back(pll(0, Y[i]));
            }
        }
    }

    vector<pll> fin;
    for (int i = 1; i <= N; i++)
    {
        fin = best(fin, sale[i]);
        if (fin.size() > K)
            fin.resize(K);
    }

    for(auto [p, y] : fin)
       ans = (ans + p) % mod;
     

    return ans;
}

signed main()
{
    fast;
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        cout << "Case #" << t << ": ";
        cout << solve() << '\n';
        cerr << "End Case " << t << ".\n";
    }
}
