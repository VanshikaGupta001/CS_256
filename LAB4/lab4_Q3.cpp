#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    vector<vector<int>> pref_A(n, vector<int>(n)), pref_B(n, vector<int>(n));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++) cin>>pref_A[i][j];
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            int A_id;
            cin>>A_id;
            pref_B[i][A_id]=j;
        }
    }

    vector<int> A_match(n, -1), B_match(n,-1), next_proposal_id(n,0);
    queue<int> free_A;
    for(int i=0;i<n;i++){
        free_A.push(i);
    }

    while(!free_A.empty()){
        int s = free_A.front();
        free_A.pop();
        int c= pref_A[s][next_proposal_id[s]];
        
        next_proposal_id[s]++;

        if (B_match[c]== -1) {
            B_match[c] = s;
            A_match[s] = c;
        } 
        else {
            int current_partner = B_match[c];

            if (pref_B[c][s] <pref_B[c][current_partner]) {
                B_match[c] = s;
                A_match[s] = c;
                A_match[current_partner] = -1;
                free_A.push(current_partner);
            } 
            else free_A.push(s);
        }
    }

    for(int i=0;i<n;i++){
        cout<<i<< " "<< A_match[i]<<endl;
    }

}