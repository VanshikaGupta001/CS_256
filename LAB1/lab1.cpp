#include <bits/stdc++.h>
using namespace std;

vector<int> sort_by_freq(const vector<int>& arr) {
    map<int, int> freq;
    map<int, int> first_pos;
    int n = arr.size();

    for (int i = 0; i < n; i++) {
        freq[arr[i]]++;
        if (first_pos.find(arr[i]) == first_pos.end()) {
            first_pos[arr[i]] = i;
        }
    }

    vector<int> ans = arr;
    sort(ans.begin(), ans.end(), [&](int a, int b) {
        if (freq[a] != freq[b]) {
            return freq[a] > freq[b];
        }
        return first_pos[a] < first_pos[b];
    });

    return ans;
}

void fixArray(vector<int>& arr) {
    sort(arr.begin(), arr.end());
}

void single_ele(vector<int>& arr) {
    int n = arr.size();
    if (n == 0) return;
    if (n == 1) {
        cout << arr[0] << endl;
        return;
    }

    if (arr[0] != arr[1]) {
        cout << arr[0] << endl;
        return;
    }
    if (arr[n - 1] != arr[n - 2]) {
        cout << arr[n - 1] << endl;
        return;
    }

    int low = 1;
    int high = n - 2;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] != arr[mid - 1] && arr[mid] != arr[mid + 1]) {
            cout << arr[mid] << endl;
            return;
        }

        if ((mid % 2 == 1 && arr[mid] == arr[mid - 1]) || 
            (mid % 2 == 0 && arr[mid] == arr[mid + 1])) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
}

int main() {
    vector<int> arr = {4, 5, 6, 5, 4, 3};
    vector<int> result = sort_by_freq(arr);
    for (int x : result) {
        cout << x << " ";
    }
    cout << endl;

    vector<int> sorted_arr = {5, 7, 3, 9};
    fixArray(sorted_arr);
    
    vector<int> a = {1, 1, 2, 2, 3, 4, 4, 5, 5};
    single_ele(a);

    return 0;
}