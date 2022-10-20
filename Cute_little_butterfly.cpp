#include<bits/stdc++.h>
using namespace std ;

#define ll              long long 
#define pb              push_back
#define all(v)          v.begin(),v.end()
#define sz(a)           (ll)a.size()
#define F               first
#define S               second
#define INF             2000000000000000000
#define popcount(x)     __builtin_popcountll(x)
#define pll             pair<ll,ll>
#define pii             pair<int,int>
#define ld              long double

template<typename T, typename U> static inline void amin(T &x, U y){ if(y < x) x = y; }
template<typename T, typename U> static inline void amax(T &x, U y){ if(x < y) x = y; }

#ifdef LOCAL
#define debug(...) debug_out(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) 3000
#endif

const int N = 1e5 + 5;
struct node
{
    ll sum = -INF;
}fake;
struct SEGTREE
{
    ll a[N];
    SEGTREE(){ }
    node tree[4*N];
    ll lazy[4*N];
    inline node combine(node a,node b)
    {
        node ret;
        ret.sum=max(a.sum,b.sum);
        return ret;
    }
    inline node make_node(ll val)
    {
        node ret;
        ret.sum=val;
        return ret;
    }
    inline void pushdown(ll v,ll st,ll en)
    {
        tree[v].sum+=lazy[v];
        if(st!=en)
        {
            lazy[v<<1]+=lazy[v];
            lazy[v<<1 | 1]+=lazy[v];
        }
        lazy[v]=0;
        return ;
    }
    void buildTree(ll v,ll st,ll en)
    {
        lazy[v] = 0;
        if(st==en)
        {
            tree[v]=make_node(a[st]);
            return ;
        }
        ll mid=(st+en)>>1;
        buildTree(v<<1,st,mid);
        buildTree(v<<1 | 1,mid+1,en);
        tree[v]=combine(tree[v<<1],tree[v<<1 | 1]);
    }
    void update(ll v,ll st,ll en,ll in,ll val)
    {
        ll mid=(st+en)>>1;
        if(st==en)
        {
            tree[v]=make_node(val);
            a[st]=val;
            return ;
        }
        if(in<=mid)
            update(v<<1,st,mid,in,val);
        else
            update(v<<1 | 1,mid+1,en,in,val);
        tree[v]=combine(tree[v<<1],tree[v<<1 | 1]);
    }
    void rupdate(ll v,ll st,ll en,ll l,ll r,ll val)
    {
        if(lazy[v]!=0)
        {
            pushdown(v,st,en);
        }
        if(en<l || st>r)return ;
        if(st>=l && en<=r)
        {
            lazy[v]=val;
            pushdown(v,st,en);
            return ;
        }
        ll mid=(st+en)>>1;
        rupdate(v<<1,st,mid,l,r,val);
        rupdate(v<<1 | 1,mid+1,en,l,r,val);
        tree[v]=combine(tree[v<<1],tree[v<<1 | 1]);
    }
    node query(ll v,ll st,ll en,ll l,ll r)
    {
        if(en<l || st>r)
            return fake;
        if(lazy[v]!=0)
        {
            pushdown(v,st,en);
        }
        if(st>=l && en<=r)
            return tree[v];
        ll mid=(st+en)>>1;
        return combine(query(v<<1,st,mid,l,r),query(v<<1 | 1,mid+1,en,l,r));
    }
}seg_0, seg_1;

// 0 means left, 1 means right facing

int _runtimeTerror_()
{
    int n;
    ll e;
    cin >> n >> e;
    vector<array<int, 3>> a(n);
    for(int i=0;i<n;++i) {
        cin >> a[i][1] >> a[i][0] >> a[i][2];
    }
    sort(all(a));
    reverse(all(a));
    for(int i=0;i<=1e5;++i) {
        seg_1.a[i] = -INF;
        seg_0.a[i] = -INF;
    }
    seg_1.a[0] = 0;
    const int mx = 1e5;
    seg_0.buildTree(1, 0, mx);
    seg_1.buildTree(1, 0, mx);
    ll ans = 0;
    for(int i=0;i<n;++i) {
        int j = i;
        vector<pii> t;
        while(j < n and a[j][0] == a[i][0]) {
            t.push_back({a[j][1], a[j][2]});
            ++j;
        }
        i = j - 1;

        sort(all(t));
        int s = sz(t);
        vector<ll> dp_0(s, -INF), dp_1 = dp_0;
        ll sum = 0;
        for(int j=0;j<s;++j) {
            sum += t[j].S;
            amax(dp_1[j], seg_0.query(1, 0, mx, 0, t[j].F).sum + sum - e);
            amax(dp_0[j], seg_0.query(1, 0, mx, t[j].F, t[j].F).sum + t[j].S);
            amax(dp_1[j], seg_1.query(1, 0, mx, t[j].F, t[j].F).sum + t[j].S);
        }
        sum = 0;
        for(int j=s-1;j>=0;--j) {
            sum += t[j].S;
            amax(dp_0[j], seg_1.query(1, 0, mx, t[j].F, mx).sum + sum - e);
        }

        for(int j=0;j<s;++j) {
            seg_1.rupdate(1, 0, mx, 0, t[j].F, t[j].S);
            amax(dp_1[j], seg_1.query(1, 0, mx, 0, t[j].F).sum);
        }
        for(int j=0;j<s;++j) {
            seg_1.rupdate(1, 0, mx, 0, t[j].F, -t[j].S);
        }

        for(int j=s-1;j>=0;--j) {
            seg_0.rupdate(1, 0, mx, t[j].F, mx, t[j].S);
            amax(dp_0[j], seg_0.query(1, 0, mx, t[j].F, mx).sum);
        }
        for(int j=s-1;j>=0;--j) {
            seg_0.rupdate(1, 0, mx, t[j].F, mx, -t[j].S);
        }

        for(int j=0;j<s;++j) {
            amax(ans, dp_0[j]);
            amax(ans, dp_1[j]);
            auto u = seg_0.query(1, 0, mx, t[j].F, t[j].F).sum;
            seg_0.rupdate(1, 0, mx, t[j].F, t[j].F, max(u, dp_0[j]) - u);
            u = seg_1.query(1, 0, mx, t[j].F, t[j].F).sum;
            seg_1.rupdate(1, 0, mx, t[j].F, t[j].F, max(u, dp_1[j]) - u);
        }
    }
    cout << ans << "\n";
    return 0;
}

int main()
{
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    #ifdef runSieve
        sieve();
    #endif
    #ifdef NCR
        initncr();
    #endif
    int TESTS = 1;
    cin >> TESTS;
    for(int i=1;i<=TESTS;++i) {
        cout << "Case #" << i << ": ";
        _runtimeTerror_();
    }
    return 0;
}
