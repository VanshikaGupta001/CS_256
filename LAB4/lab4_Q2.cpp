#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w, id;
    // Sort by weight
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

struct DSU {
    vector<int> parent;
    DSU(int n) {
        parent.resize(n + 1);
        iota(parent.begin(), parent.end(), 0); // 0, 1, 2...
    }
    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }
    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) parent[root_i] = root_j;
    }
};

// --- DFS for LCA and Tree Setup ---
// depth: depth of node
// up: binary lifting table for LCA
// edge_index_to_parent: stores the ID of the edge connecting node to its parent
void dfs(int u, int p, int d, int edge_id, 
         const vector<vector<pair<int, int>>>& adj, 
         vector<int>& depth, 
         vector<vector<int>>& up, 
         vector<int>& edge_index_to_parent,
         int LOG) {
    
    depth[u] = d;
    up[u][0] = p;
    edge_index_to_parent[u] = edge_id;

    // Binary Lifting Precomputation
    for (int i = 1; i < LOG; i++) {
        up[u][i] = up[up[u][i-1]][i-1];
    }

    for (auto& edge : adj[u]) {
        int v = edge.first;
        int id = edge.second;
        if (v != p) {
            dfs(v, u, d + 1, id, adj, depth, up, edge_index_to_parent, LOG);
        }
    }
}

// --- Get Lowest Common Ancestor ---
int get_lca(int u, int v, const vector<int>& depth, const vector<vector<int>>& up, int LOG) {
    if (depth[u] < depth[v]) swap(u, v);

    // Lift u to same depth as v
    for (int i = LOG - 1; i >= 0; i--) {
        if (depth[u] - (1 << i) >= depth[v]) {
            u = up[u][i];
        }
    }

    if (u == v) return u;

    // Lift both until just below LCA
    for (int i = LOG - 1; i >= 0; i--) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[u][0];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<Edge> all_edges;
    all_edges.reserve(m);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        all_edges.push_back({u, v, w, i + 1}); // 1-based index
    }

    // 1. Sort edges by weight
    vector<Edge> sorted_edges = all_edges;
    sort(sorted_edges.begin(), sorted_edges.end());

    // 2. Build MST using Kruskal's
    DSU dsu(n);
    vector<bool> is_mst_edge(m + 1, false);
    vector<vector<pair<int, int>>> adj(n + 1); // Tree adjacency list
    vector<Edge> non_mst_edges;

    for (const auto& e : sorted_edges) {
        if (dsu.find(e.u) != dsu.find(e.v)) {
            dsu.unite(e.u, e.v);
            is_mst_edge[e.id] = true;
            adj[e.u].push_back({e.v, e.id});
            adj[e.v].push_back({e.u, e.id});
        } else {
            non_mst_edges.push_back(e);
        }
    }

    // 3. Prepare LCA structures
    int LOG = 20; // Sufficient for 10^5
    vector<int> depth(n + 1, 0);
    vector<int> edge_index_to_parent(n + 1, 0);
    vector<vector<int>> up(n + 1, vector<int>(LOG));

    // Root the tree at node 1
    dfs(1, 1, 0, -1, adj, depth, up, edge_index_to_parent, LOG);

    // 4. Process Non-MST edges to find replacement costs
    vector<int> ans(m + 1, -1);
    
    // Use a new DSU for path compression on the tree
    // This helps us skip over edges we have already painted
    DSU path_dsu(n); 

    for (const auto& e : non_mst_edges) {
        int u = e.u;
        int v = e.v;
        int lca = get_lca(u, v, depth, up, LOG);

        // Paint path u -> LCA
        // We use path_dsu.find() to jump to the highest unpainted ancestor
        int curr = path_dsu.find(u);
        while (depth[curr] > depth[lca]) {
            ans[edge_index_to_parent[curr]] = e.w; // Found best replacement
            
            // Compress: unite current node with its parent in the path_dsu
            // This effectively removes this edge from future consideration
            path_dsu.parent[curr] = path_dsu.find(up[curr][0]);
            
            curr = path_dsu.find(curr);
        }

        // Paint path v -> LCA
        curr = path_dsu.find(v);
        while (depth[curr] > depth[lca]) {
            ans[edge_index_to_parent[curr]] = e.w;
            path_dsu.parent[curr] = path_dsu.find(up[curr][0]);
            curr = path_dsu.find(curr);
        }
    }

    // 5. Output results
    // Iterate through original edges in input order
    for (int i = 0; i < m; i++) {
        int id = all_edges[i].id;
        if (is_mst_edge[id]) {
            cout << id << " " << ans[id] << "\n";
        }
    }

    return 0;
}