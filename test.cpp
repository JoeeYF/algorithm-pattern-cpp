#include <string>
#include <iostream>
#include <vector>
using namespace std;
vector<int> res;
void dfs(int n,int idx,string path){
    if(n==idx){
        cout<<path<<endl;
        int val = std::stoi(path);
        if (val != 0) res.push_back(val);
        return;
    }
    for(int i=0;i<=9;i++){
        path[idx] = i+'0';
        dfs(n,idx+1,path);
    }
}
int main(){
    int n=2;
    string path(n,'0');
    dfs(n,0,path);
    return 0;
}