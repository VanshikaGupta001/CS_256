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

int rec(int n){
    if(n<0) return 0;
    if(n==0) return 1;
    
    int a= rec(n-1);
    int b= rec(n-2);
    
    return a+b;
}
void solve() {
    int n;
    cin>>n;
    cout<<rec(n);
    
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    // cin >> t;
    t=1;
    while (t--)
    {
        solve();
    }
}