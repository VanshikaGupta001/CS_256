#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    bool swapped;
    for(int i =0; i <n-1; i++) {
        swapped= false;
        for(int j=0; j< n -i-1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}

void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin>>n;

    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    vector<int> arrBubble = v;
    vector<int> arrMerge = v;
    vector<int> arrQuick = v;

    auto startBubble = high_resolution_clock::now();
    bubbleSort(arrBubble);
    auto stopBubble = high_resolution_clock::now();
    auto durationBubble = duration_cast<milliseconds>(stopBubble - startBubble);

    auto startMerge = high_resolution_clock::now();
    mergeSort(arrMerge, 0, n - 1);
    auto stopMerge = high_resolution_clock::now();
    auto durationMerge = duration_cast<milliseconds>(stopMerge - startMerge);

    auto startQuick = high_resolution_clock::now();
    quickSort(arrQuick, 0, n - 1);
    auto stopQuick = high_resolution_clock::now();
    auto durationQuick = duration_cast<milliseconds>(stopQuick - startQuick);

    if(arrBubble==v) cout<<"Sorted output remains unchanged"<<endl;
    else {
        for (auto &x: arrBubble) cout<<x<<" ";
        cout<<endl;
    }


    // cout << "BubbleSort: " << durationBubble.count() << " ms" << endl;
    // cout << "MergeSort: " << durationMerge.count() << " ms" << endl;
    // cout << "QuickSort: " << durationQuick.count() << " ms" << endl;

    return 0;
}