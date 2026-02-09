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

int merge_count(vi &a, int l, int mid, int r){
    int n= mid-l+1;
    int m= r-mid;
    vi left_arr(n), right_arr(m);

    fr(i,0,n) left_arr[i]=a[l+i];
    fr(i,0,m) right_arr[i]= a[mid+1+i];


    int inversions= 0;
    int i=0,j=0,k=l;

    while(i<n && j<m){
        if(left_arr[i]<= right_arr[j]){
            
            a[k]= left_arr[i];
            i++;


        }

        else{
            
            a[k]= right_arr[j];
            j++;
            inversions+= n-i;
            
        }
        k++;
    }

    while(i<n){
        a[k]= left_arr[i];
        k++;
        i++;
    }
    while(j<m){
        a[k]= right_arr[j];
        k++;
        j++;

    }

    return inversions;


}
int count_inv(vi &a, int l, int r){
      int count=0;
      if(l<r){
        int mid= l+ (r-l)/2;
        count += count_inv(a, l, mid);
        count+= count_inv (a, mid+1, r);
        count+= merge_count(a, l, mid, r);
      }
      return count;
}
void solve() {
    int n;
    cin>>n;
    vi a(n);
    fr(i,0,n) cin>>a[i];

    cout<< count_inv(a, 0, n-1);

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