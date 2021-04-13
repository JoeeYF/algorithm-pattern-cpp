#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void quickSort(vector<int> &q,int l,int r){
    if(l>=r) return;
    int i=l,j=r;
    while(i<j){
        while(q[j]>=q[l]&&i<j) j--;
        while(q[i]<=q[l]&&i<j) i++;
        swap(q[i],q[j]);
        // for(auto x : q)
        // cout << x << ' ';
        // cout << endl;
    }
    swap(q[i],q[l]);
    quickSort(q,l,i-1);
    quickSort(q,i+1,r);
}


int main()
{
    vector<int> q= {3245,234,123,6,523,5623,323,31114,0,3,2,7,4};
    for(auto x : q)
        cout << x << ' ';
    cout << endl;
    quickSort(q,0,q.size()-1);
    for(auto x : q)
        cout << x << ' ';
    cout << endl;
    return 0;
}