#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    
    vector<pair<int, pair<int, int>>> list;
    
    for(int i=0;i<n;i++){
        int s,f;
        cin>>s>>f;
        list.push_back({f, {s, i}});
    }

    sort(list.begin(), list.end());
    
    vector<int> ans;
    int last_finish = -1;

    for(int i=0;i<n;i++){
        int finish = list[i].first;
        int start = list[i].second.first;
        int id = list[i].second.second;

        if(start >= last_finish){
            ans.push_back(id);
            last_finish = finish;
        }
    }

    cout<<ans.size()<<endl;
    for(int i=0;i<ans.size();i++){
        cout<<ans[i]<<" ";
    }
}