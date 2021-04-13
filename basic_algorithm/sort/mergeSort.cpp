#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void mergeSort(vector<int> &q,int l,int r){
    if(l>=r) return;
    int mid = l+r>>1;
    mergeSort(q,l,mid);
    mergeSort(q,mid+1,r);
    static vector<int> w;
    w.clear();
    int i=l,j=mid+1;
    while(i<=mid&&j<=r){
        if(q[i]>q[j]) w.push_back(q[j++]);
        if(q[i]<=q[j]) w.push_back(q[i++]);
    }
    while(i<=mid) w.push_back(q[i++]);
    while(j<=r) w.push_back(q[j++]);
    for(int i : w)
        q[l++] = i;
}


int main()
{
    vector<int> q= {3245,234,123,523,5623,323,31114,3,2,7,4};
    for(auto x : q)
        cout << x << ' ';
    cout << endl;
    mergeSort(q,0,q.size()-1);
    for(auto x : q)
        cout << x << ' ';
    cout << endl;
    return 0;
}