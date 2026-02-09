#include <bits/stdc++.h>
using namespace std;

#define fr(i, a, b) for (int i = a; i < b; i++)
#define fl(i, a, b) for (int i = b - 1; i >= a; i--)
#define F first
#define S second
#define all(x) x.begin(), x.end()
#define clr(x) memset(x, false, sizeof(x))
#define go(a, x) for (auto &a : x)
#define ter(a, b, c) ((a) ? (b) : (c))
#define yn(a) cout << ((a) ? "YES\n" : "NO\n")

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using vii = vector<pair<int, int>>;
using pi = pair<int, int>;

const ll mod= 1e9+7;
const ll INF=1e18;

ll merge_sums(vi &a, int l, int mid, int r){
    ll left_sum= -1e18; 
    ll sum= 0;
    for(int i= mid; i>=l;i--) {
        sum+= a[i];
        if (sum >left_sum) left_sum =sum;
    }

    ll right_sum = -1e18;
    sum = 0;
    for (int i = mid + 1; i <= r; i++) {
        sum += a[i];
        if (sum > right_sum) right_sum = sum;
    }

    return left_sum+ right_sum;


}
ll max_sum(vi &a, int l, int r){
      if(l==r) return a[l];
      
        int mid= l+ (r-l)/2;
        ll left_max = max_sum(a, l, mid);
        ll right_max= max_sum(a, mid+1, r);
        ll sum= merge_sums(a, l, mid, r);
      
      return max(max(left_max, right_max), sum);
}


void solve() {
    int n;
    cin>>n;
    vi a(n);
    fr(i,0,n) cin>>a[i];

    cout<< max_sum(a, 0, n-1);


}
    




int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    // cin>>t;
    t=1;
    while (t--)
    {
        solve();
    }
}