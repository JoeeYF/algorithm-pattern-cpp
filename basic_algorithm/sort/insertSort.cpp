#include <iostream>
#include <algorithm>
#include <vector>
 
using namespace std;

void insertionSort(vector<int> &a){
    for(int i=1;i<a.size();i++){
        int temp=a[i],j;
        for(j=i-1;j>=0;j--){
            if (a[j]>temp){
                a[j+1]=a[j];
            }
            else{
                break;
            }
        }
        a[j+1]=temp;
    }
}

int main(){
    int n;
    vector<int> q;
    cin >> n;
    for(int i = 0, t; i < n; i++){
        cin >> t;
        q.push_back(t);
    }
    insertionSort(q);
    for(auto x : q)
        cout << x << ' ';
    cout << endl;
    return 0;
}