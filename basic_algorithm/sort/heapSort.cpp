#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void push_down(vector<int> &q,int size,int u){
    int i=u,left=u*2+1,right=u*2+2;
    if(q[left]>q[i]&&left<=size)i=left;
    if(q[right]>q[i]&&right<=size)i=right;
    if(u!=i){
        swap(q[u],q[i]);
        push_down(q,size,i);
    }
}
void push_up(vector<int> &q,int u){
    while((u/2)>=0 && q[u/2]<q[u]){
        swap(q[u/2],q[u]);
        u=u/2;
    }
}
void heapSort(vector<int> &q)
{
    int n = q.size();
    int size = q.size()-1;
    for (int i = 0; i < n; i++)
        push_up(q, i);
                                for (int i = 0; i < n; i++)
                                cout << q[i] << ' ';
                                cout<<endl;
    for (int i = 0; i < n; i++)
    {
        swap(q[0], q[size]);
                                // for (int i = 0; i < n; i++)
                                // cout << q[i] << ' ';
                                // cout<<endl;
        size--;
        push_down(q, size, 0);
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