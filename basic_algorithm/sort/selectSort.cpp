#include <iostream>
#include <algorithm>
#include <vector>
 
using namespace std;

void selectSort(vector<int> &a){
    int begin=0,end=a.size()-1;
    while(begin<end){
        int min=begin,max=end;
        for(int i=begin;i<=end;i++){
            if(a[i]<a[min]) min=i;
            if(a[i]>a[max]) max=i;
        }
        int temp;
        temp=a[min];
        a[min]=a[begin];
        a[begin]=temp;
        if(max==begin) max=min;
        temp=a[max]; 
        a[max]=a[end];
        a[end]=temp;
        begin++;
        end--;
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
    selectSort(q);
    for(auto x : q)
        cout << x << ' ';
    cout << endl;
    return 0;
}