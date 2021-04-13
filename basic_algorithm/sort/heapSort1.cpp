#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void maxheap(vector<int> &q,int size){
    for(int i=(size+1)/2-1;i>=0;i--){
        int left=i*2+1, right=i*2+2;
        if(q[left]>q[i]&&left<=size)swap(q[left],q[i]);
        if(q[right]>q[i]&&right<=size)swap(q[right],q[i]);
    }
}

void heapSort(vector<int> &q)
{
    int size = q.size();
    for (int i = size-1; i > 0; i--){
        maxheap(q,i);
        swap(q[0], q[i]);
    }
}

int main()
{
    
    vector<int> q= {3245,234,123,523,5623,323,31114,3,2,7,4};
    for(auto x : q)
        cout << x << ' ';
    cout << endl;
    heapSort(q);
    for(auto x : q)
        cout << x << ' ';
    cout << endl;
    return 0;
}