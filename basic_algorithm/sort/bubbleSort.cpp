#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void bubbleSort(vector<int> &q){
    int size = q.size();
    for(int i=size;i>=0;i--){
        bool flag=false;
        for(int j=0;j<i;j++){
            if(q[j]>q[j+1]){
                swap(q[j],q[j+1]);
                flag=true;
            }
        }
        if(!flag) break;
    }
}


int main()
{
    vector<int> q= {3245,234,123,523,5623,323,31114,3,2,7,4};
    for(auto x : q)
        cout << x << ' ';
    cout << endl;
    bubbleSort(q);
    for(auto x : q)
        cout << x << ' ';
    cout << endl;
    return 0;
}