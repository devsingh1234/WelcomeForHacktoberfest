#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
using namespace std;
using ll = long long int;
template<typename T>
ostream& operator+(ostream& out, const vector<T> &vec){
    for(const auto &x : vec){
        out<<x<<" ";
    }
    out<<"\n";
    return out;
}
template<typename T>
ostream& operator*(ostream& out, const vector<T> &vec){
    for(const auto &x : vec){
        out+x;
    }
    return out;
}
template<typename T>
istream& operator>>(istream& in, vector<T> &vec){
    for(auto &x : vec){
        in>>x;
    }
    return in;
}
template<typename T>
struct segment_tree {
    int n;
    vector<T> segtree;
    function<T(const T&,const T&)> join;
    T base = T();
    segment_tree(int n, function<T(const T&,const T&)> join, T base = T()) : n(n), join(join), base(base){
        segtree.resize(n << 1, base);
    }
    void build() {
        for (int i = n - 1; i > 0; --i) {
            segtree[i] = join(segtree[(i << 1)], segtree[(i << 1) | 1]);
        }
    }
    segment_tree(vector<T> seq, function<T(const T&,const T&)> join, T base = T()) : n(seq.size()), join(join), base(base){
        segtree.resize(n << 1, base);
        for (int i = 0; i < n; i++) {
            segtree[n + i] = seq[i];
        }
        build();
    }
    void calc(int pos){
        pos >>= 1;
        while (pos) {
            segtree[pos] = join(segtree[pos << 1], segtree[(pos << 1) | 1]);
            pos >>= 1;
        }
    }
    void set(int pos, T val){
        pos+=n;
        segtree[pos] = val;
        calc(pos);
    }
    void increment(int pos, T val){
        pos+=n;
        segtree[pos] = join(segtree[pos], val);
        calc(pos);
    }
    T query(int l, int r) {
        T ansl = base;
        T ansr = base;
        l += n;
        r += n + 1;
        while (l < r) {
            if (l & 1) {
                ansl = join(ansl, segtree[l++]);
            }
            if (r & 1) {
                ansr = join(segtree[--r], ansr);
            }
            l >>= 1;
            r >>= 1;
        }
        return join(ansl, ansr);
    }
};
using hash_t = unsigned long long;
hash_t rand_ll(){
    return (hash_t(rand()) << 48) | (hash_t(rand()) << 32) | (hash_t(rand()) << 16) | hash_t(rand());
}
void solve(){
    string a;
    cin>>a;
    int n = a.size();
    int q;
    cin>>q;
    map<char, hash_t> hasher;
    segment_tree<hash_t> hash_tree(n, [&](hash_t x, hash_t y){
        return x + y;
    }, hash_t(0));
    map<ll, set<int>> hash_location;
    for(int i=0;i<n;i++){
        auto it = hasher.find(a[i]);
        if(it == hasher.end()){
            hasher[a[i]] = rand_ll();
            it = hasher.find(a[i]);
        }
        hash_tree.set(i, (*it).second);
        hash_location[(*it).second].insert(i);
    }
    int ans = 0;
    while(q--){
        int l,r;
        cin>>l>>r;
        --l;--r;
        if((r - l) % 2 == 1){
            continue;
        }
        if(l == r){
            ans++;
            continue;
        }
        hash_t hash_left = hash_tree.query(l, l + (r - l) / 2 - 1);
        hash_t hash_right = hash_tree.query(r - (r - l) / 2 + 1, r);
        hash_t hash_middle = hash_tree.query(l + (r - l) / 2, r - (r - l) / 2);
        auto& set_left = hash_location[hash_left + hash_middle - hash_right];
        auto& set_right = hash_location[hash_right + hash_middle - hash_left];
        auto it_right = set_right.lower_bound((r + l) / 2);
        auto it_left = set_left.upper_bound((r + l) / 2);
        if(set_left.size() > 0 && it_left != set_left.begin()){
            --it_left;
            if(*it_left >= l){
                ans++;
                continue;
            }
        }
        if(set_right.size() > 0 && it_right != set_right.end()){
            if(*it_right <= r){
                ans++;
                continue;
            }
        }
    }
    cout<<ans<<"\n";
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin>>t;
    for(int i=1;i<=t;i++){
        cout<<"Case #"<<i<<": ";
        solve();
    }
}
