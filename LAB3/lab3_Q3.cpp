#include <bits/stdc++.h>
using namespace std;

#define fr(i, a, b) for (int i = a; i < b; i++)
#define F first
#define S second
#define all(x) x.begin(), x.end()

using ll = long long;
using pi = pair<int, int>;
using vp = vector<pi>;

int K;

ll merge_count(vp &a, int l, int mid, int r) {
    int n = mid - l + 1;
    int m = r - mid;
    vp left_arr(n), right_arr(m);

    fr(i, 0, n) left_arr[i] = a[l + i];
    fr(i, 0, m) right_arr[i] = a[mid + 1 + i];

    ll inversions = 0;
    int i = 0, j = 0, k = l;

    while (i < n && j < m) {
        if (left_arr[i].F <= right_arr[j].F) {
            a[k] = left_arr[i];
            i++;
        } 
        else {
            for (int x = i; x < n; x++) {
                if (abs(right_arr[j].S - left_arr[x].S) <= K) {
                    inversions++;
                }
            }
            a[k] = right_arr[j];
            j++;
        }
        k++;
    }

    while (i < n) {
        a[k] = left_arr[i];
        k++; i++;
    }
    while (j < m) {
        a[k] = right_arr[j];
        k++; j++;
    }

    return inversions;
}

ll count_inv(vp &a, int l, int r) {
    ll count = 0;
    if (l < r) {
        int mid = l + (r - l) / 2;
        count += count_inv(a, l, mid);
        count += count_inv(a, mid + 1, r);
        count += merge_count(a, l, mid, r);
    }
    return count;
}

void solve() {
    int n;
    if (cin >> n >> K) {
        vp a(n);
        fr(i, 0, n) {
            cin >> a[i].F;
            a[i].S = i; 
        }
        cout << count_inv(a, 0, n - 1) << "\n";
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t = 1; 
    while (t--) {
        solve();
    }
    return 0;
}