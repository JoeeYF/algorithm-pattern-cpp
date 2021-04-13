#include <iostream>
#include <algorithm>
#include <vector>
 
using namespace std;

void shellSort(vector<int> &a){
    int gap = a.size()/2;

    while(gap){
        for(int i=gap;i<a.size();i+=gap){
            int temp=a[i], j;
            for(j=i-gap;j>=0;j-=gap){
                if(a[j]>temp){
                    a[j+gap] = a[j];
                }
                else break;
            }
            a[j+gap]=temp;
        }
        gap=gap/2;
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
    shellSort(q);
    for(auto x : q)
        cout << x << ' ';
    cout << endl;
    return 0;
}