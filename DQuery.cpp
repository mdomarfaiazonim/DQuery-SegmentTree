
//         MOHAMMED OMAR FAIAZ ONIM
//         戦え

#include <bits/stdc++.h>
#define pb push_back
#define NN "\n"
#define yes cout << "YES" \
                 << "\n";
#define no cout << "NO" \
                << "\n";
#define all(onim) onim.begin(), onim.end()
#define c(onim) cout << (onim) << NN;
#define fast_n_furious                \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);
using namespace std;
typedef long long ll;
typedef vector<ll> vll;
#define S second
#define F first
#define fout(x) fixed << setprecision(x)
#define mem(arr, val) memset(arr, val, sizeof(arr))
#define lb lower_bound
#define ub upper_bound
#define FF(v, i) for (auto &i : v)
#define V2(dp, sz, sz2, val) vector<vector<ll>> dp(sz, vector<ll>(sz2, val))

#define getbit(n, i) (((n) & (1LL << (i))) != 0)
#define setbit0(n, i) ((n) & (~(1LL << (i))))
#define setbit1(n, i) ((n) | (1LL << (i)))
#define togglebit(n, i) ((n) ^ (1LL << (i)))
#define lowetset(n) ((n) & (-(n)))
#define rmv_last(n) (n & (n - 1))

const ll INF = 1e17;
const ll SZ = 2e5 + 1;

bool isvalid(int i, int j, int n, int m) { return (i >= 0 && j >= 0 && i < n && j < m); }
bool SC(pair<ll, ll> &a, pair<ll, ll> &b) { return (a.F != b.F) ? (a.F < b.F) : (a.S > b.S); } // F=> Ascending; S=> Descending
// More On segment tree

struct SegmentTree
{
    ll Sum;
};

SegmentTree tree[SZ << 3];
ll par[SZ];
SegmentTree merge(SegmentTree a, SegmentTree b)
{
    SegmentTree res;

    res.Sum = a.Sum + b.Sum;

    return res;
}

void BUILD(ll node, ll start, ll end)
{
    if (start == end)
    {
        ll X;
        X = 0;
        
        par[start] = node ;
        tree[node].Sum = X;

        return;
    }

    ll l = node << 1;
    ll r = node << 1 | 1;

    ll mid = (start + end) >> 1;

    BUILD(l, start, mid);
    BUILD(r, mid + 1, end);

    tree[node] = merge(tree[l], tree[r]);
}

SegmentTree Query(ll node, ll start, ll end, ll x, ll y)
{
    if (start == x && end == y)
        return tree[node];

    ll l = node << 1;
    ll r = node << 1 | 1;

    ll mid = (start + end) >> 1;

    if (y <= mid)
        return Query(l, start, mid, x, y); // whole side is in left

    else if (x > mid)
        return Query(r, mid + 1, end, x, y); // whole side is in right

    else
    {
        return merge(Query(l, start, mid, x, mid), Query(r, mid + 1, end, mid + 1, y)); // split in two side so merging
    }
}
void Update(ll ind , ll val )
{
    ll node = par[ind];

    tree[node].Sum = val ;

    node >>= 1 ;

    while( node > 0 ) {
        ll l = node<<1 ;
        ll r = node<<1|1;
        tree[ node ] = merge( tree[l] , tree[r] );
        node >>= 1 ;
    }
}

int main()
{
    fast_n_furious

        int testcase = 1;
    // cin >> testcase;
    while (testcase--)
    {
        ll n;
        cin>>n;

        set<ll>st;
        vll v(n+1),li(n+2);
        unordered_map<ll,deque<ll>>ocr;

        BUILD(1,1,n);

        for(int i=0;i<n;i++){
            cin>>v[i+1];
            ocr[v[i+1]].pb(i+1);
            st.insert(v[i+1]);
        }
        for(auto to : ocr){
            li[to.S.back()]=1;
        }
        ll tot=st.size();
        ll q;
        cin>>q;
        vector<pair<pair<ll,ll>,ll>>query;

        for(int i=1;i<=q;i++){
            ll l,r;
            cin>>l>>r;
            query.pb({{l,r},i});
        }
        sort(all(query));

        vector<ll>res(q+1);

        st.clear();
        for(int i=0;i<n;i++) st.insert(i+1);

        for(auto to : ocr){
            Update(to.S[0],1);
        }

        for(auto to : query){
            ll l=to.F.F,r=to.F.S,ind=to.S;

            while(!st.empty() && *st.begin()<l){
                ll x=*st.begin();
                st.erase(x);

                while(!ocr[v[x]].empty() && ocr[v[x]].front()<l){
                    ocr[v[x]].pop_front();
                }
                if(!ocr[v[x]].empty()){
                    Update(ocr[v[x]].front(),1);
                }
                tot-=li[x];
            }

            ll ans=tot-(r+1<=n ? Query(1,1,n,r+1,n).Sum : 0);
            res[ind]=ans;
        }
        for(int i=1;i<=q;i++){
            cout<<res[i]<<NN;
        }
    }
}
