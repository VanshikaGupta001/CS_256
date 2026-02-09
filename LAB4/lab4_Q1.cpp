#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, int> iPair;

ll primMST(int V, const vector<vector<pair<int, int>>>& adjList) {
    // Min-heap: (weight, vertex)
    priority_queue<iPair, vector<iPair>, greater<iPair>> pq;

    vector<ll> key(V + 1, LLONG_MAX); 
    vector<bool> inMST(V + 1, false); 

    int src = 1;
    key[src] = 0;
    pq.push({0, src});

    ll mstWeight = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        ll k = pq.top().first;
        pq.pop();

        // If already included in MST, skip
        if (inMST[u]) continue;

        // Include vertex in MST
        inMST[u] = true;
        mstWeight += k;

        // Iterate over neighbors
        for (auto& edge : adjList[u]) {
            int v = edge.first;
            int weight = edge.second;

            // If v is not in MST and weight of (u,v) is smaller than current key of v
            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                pq.push({key[v], v});
            }
        }
    }
    return mstWeight;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    if (cin >> n >> m) {
        vector<vector<pair<int, int>>> adjList(n + 1);
        
        ll totalEdgeWeight = 0;

        for (int i = 0; i < m; i++) {
            int u, v, w;
            cin >> u >> v >> w; 
            totalEdgeWeight += w;
            adjList[u].push_back({v, w});
            adjList[v].push_back({u, w});
        }

        ll minSpanningTreeWeight = primMST(n, adjList);
        cout << totalEdgeWeight - minSpanningTreeWeight << endl;
    }
    return 0;
}