# 栈和队列

## 简介

栈的特点是后入先出

![image.png](https://img.fuiboom.com/img/stack.png)

根据这个特点可以临时保存一些数据，之后用到依次再弹出来，常用于 DFS 深度搜索

队列一般常用于 BFS 广度搜索，类似一层一层的搜索

## Stack 栈

### [min-stack](https://leetcode-cn.com/problems/min-stack/)

> 设计一个支持 push，pop，top 操作，并能在常数时间内检索到最小元素的栈。

思路：用一个栈实现，在push的时候，将当前最小值也push进去，pop时，若当前栈顶为最小值，那就pop两次

```c++
class MinStack {
private:
    int min=INT_MAX;
    stack<int> minstack;
public:
    /** initialize your data structure here. */
    MinStack() {
        
    }
    
    void push(int x) {
        if(min>=x){
            minstack.push(min);
            min=x;
        }
        minstack.push(x);
    }
    
    void pop() {
        
        if(minstack.top()==min){
            minstack.pop();
            min = minstack.top();
            minstack.pop();
        }else{
            minstack.pop();
        }
        
    }
    
    int top() {
        return minstack.top();
    }
    
    int getMin() {
        return min;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
```

### [evaluate-reverse-polish-notation](https://leetcode-cn.com/problems/evaluate-reverse-polish-notation/)

> **波兰表达式计算** > **输入:** ["2", "1", "+", "3", "*"] > **输出:** 9
> **解释:** ((2 + 1) \* 3) = 9

思路：通过栈保存原来的元素，遇到表达式弹出运算，再推入结果，重复这个过程

```c++
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        if(tokens.size()==0)return 0;
        stack<int> res;
        for(int i = 0 ; i < tokens.size() ;++i){
            string s = tokens[i];
            if(s != "+" && s != "-" && s != "*" && s != "/"){
                res.push(stoi(s));
            }else{
                int b = res.top(); res.pop();
                int a = res.top(); res.pop();
                if(s == "+") res.push(a + b);
                if(s == "-") res.push(a - b);
                if(s == "*") res.push(a * b);
                if(s == "/") res.push(a / b);
            }
        }
        return res.top();

    }
};
```

### [decode-string](https://leetcode-cn.com/problems/decode-string/)

> 给定一个经过编码的字符串，返回它解码后的字符串。
> 
> s = "3[a]2[bc]", 返回 "aaabcbc".
> 
> s = "3[a2[c]]", 返回 "accaccacc".
> 
> s = "2[abc]3[cd]ef", 返回 "abcabccdcdcdef".

思路：通过栈辅助进行操作

```c++
class Solution {
public:
    string decodeString(string s) {
        stack<int> stackInt;
        stack<string> stackStr;
        string result;
        int num=0;
        for(char c : s){
            if (c >= '0' && c <= '9'){
                num=num*10+c-'0';
            }
            else if (c=='['){
                stackInt.push(num);
                num=0;
                stackStr.push(result);
                result="";
            }
            else if (c==']'){
                int times = stackInt.top();
                stackInt.pop();
                for(int i = 0; i < times; i++) stackStr.top()+=result;
                result = stackStr.top();
                stackStr.pop();
            }
            else{
                result=result+c;
            }
        }
        return result;
}};
```

利用栈进行 DFS 递归搜索模板

```c++
class Solution {
public:
    string analysis(string s, int& index) {
        string res;
        int num = 0;
        string tmp;
        while(index<s.size()){
            if (s[index]>= '0' && s[index] <= '9'){
                num = num*10+s[index]-'0';
            }
            else if (s[index]=='['){
                tmp = analysis(s,++index);
                while(num-->0) res+=tmp;
                num=0;
            }
            else if (s[index]==']') break;
            else res+=s[index];
            index++;
        }
        return res;
    }
    string decodeString(string s) {
        int index=0;
        return analysis(s,index);

    }

};
```

### [binary-tree-inorder-traversal](https://leetcode-cn.com/problems/binary-tree-inorder-traversal/)

> 给定一个二叉树，返回它的*中序*遍历。

```c++
// 思路：通过 stack 保存已经访问的元素，用于原路返回
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        if (root==NULL) return result;

        stack<TreeNode *> s;
        TreeNode* t=root;
        while(true){
            while(t){
                s.push(t);
                t=t->left;
            }
            if(s.empty()) break;
            t = s.top();
            s.pop();
            result.push_back(t->val);
            t = t->right;
        }
        return result;
        
    }
};
}
```
```c++
//通过NULL来确定是否访问
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        if (root==NULL) return result;

        stack<TreeNode *> s;
        s.push(root);

        while(!s.empty()){
            TreeNode *t = s.top();
            s.pop();
            if(t!=NULL){
                if(t->right) s.push(t->right);
                s.push(t);
                s.push(NULL);
                if(t->left) s.push(t->left);
            }else{
                result.push_back(s.top()->val);
                s.pop();
            }
        }
        return result;
        
    }
};
```
### [clone-graph](https://leetcode-cn.com/problems/clone-graph/)

> 给你无向连通图中一个节点的引用，请你返回该图的深拷贝（克隆）。

```c++
class Solution {
public:
    unordered_map<Node*, Node*> visited;
    Node* cloneGraph(Node* node) {
        if(node==NULL) return node;
        Node *clonenode = new Node(node->val, vector<Node*> {});
        visited[node] = clonenode;
        for (auto& neighbor: node->neighbors){
            if(visited.find(neighbor)!=visited.end())
            clonenode->neighbors.push_back(visited[neighbor]);
            else
            clonenode->neighbors.push_back(cloneGraph(neighbor));
        }
        return clonenode;
    }
};
```

### [number-of-islands](https://leetcode-cn.com/problems/number-of-islands/)

> 给定一个由  '1'（陆地）和 '0'（水）组成的的二维网格，计算岛屿的数量。一个岛被水包围，并且它是通过水平方向或垂直方向上相邻的陆地连接而成的。你可以假设网格的四个边均被水包围。

思路：通过深度搜索遍历可能性（注意标记已访问元素）

```c++
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int count=0;
        for(int i=0;i<grid.size();i++){
            for(int j=0;j<grid[0].size();j++){
                if(grid[i][j]=='1'&&dfs(grid,i,j)>=1) count++;
            }
        }
        return count;

    }
    int dfs(vector<vector<char>>& grid,int i,int j){
        if(i<0 ||i>=grid.size()||j<0||j>=grid[0].size()) return 0;
        if(grid[i][j]=='1'){
            grid[i][j]='0';
            return dfs(grid,i+1,j)+dfs(grid,i-1,j)+dfs(grid,i,j+1)+dfs(grid,i,j-1)+1;
        }
        return 0;
    }
};
```

### [largest-rectangle-in-histogram](https://leetcode-cn.com/problems/largest-rectangle-in-histogram/)

> 给定 _n_ 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。
> 求在该柱状图中，能够勾勒出来的矩形的最大面积。

思路：求以当前柱子为高度的面积，即转化为寻找小于当前值的左右两边值

![image.png](https://img.fuiboom.com/img/stack_rain.png)

用栈保存小于当前值的左的元素

![image.png](https://img.fuiboom.com/img/stack_rain2.png)

```c++
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        heights.push_back(0);
        stack<int> stk;
        int maxarea=0;
        for(int i=0;i<heights.size();i++){
            while(!stk.empty()&&heights[i]<heights[stk.top()]){
                int tmp=stk.top();
                stk.pop();
                maxarea=max(maxarea,heights[tmp]*(stk.empty()? i:(i-stk.top()-1)));
            }
            stk.push(i);
        }
        return maxarea;
        
    }
};
```

## Queue 队列

常用于 BFS 宽度优先搜索

### [implement-queue-using-stacks](https://leetcode-cn.com/problems/implement-queue-using-stacks/)

> 使用栈实现队列

```c++
class MyQueue {
public:
    stack<int> inStack;
    stack<int> outStack;
    /** Initialize your data structure here. */
    MyQueue() {

    }
    
    /** Push element x to the back of queue. */
    void push(int x) {
        while(!inStack.empty()){
            int tmp=inStack.top();
            outStack.push(tmp);
            inStack.pop();
        }
        inStack.push(x);
        while(!outStack.empty()){
            int tmp=outStack.top();
            inStack.push(tmp);
            outStack.pop();
        }
    }
    
    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        int tmp=inStack.top();
        inStack.pop();
        return tmp;
    }
    
    /** Get the front element. */
    int peek() {
        return inStack.top();
    }
    
    /** Returns whether the queue is empty. */
    bool empty() {
        return inStack.empty();

    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */
```


### [binary-tree-level-order-traversal](https://leetcode-cn.com/problems/binary-tree-level-order-traversal/)
二叉树层次遍历

给你一个二叉树，请你返回其按  **层序遍历**  得到的节点值。 （即逐层地，从左到右访问所有节点）

思路：用一个队列记录一层的元素，然后扫描这一层元素添加下一层元素到队列（一个数进去出来一次，所以复杂度 O(logN))

```cpp
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if(!root) return res;
        queue<TreeNode*> qu;
        qu.push(root);
        while(!qu.empty()){
            int temp=qu.size();
            vector<int> re;
            for(int i=0;i<temp;i++){
                TreeNode* x=qu.front();
                qu.pop();
                if(x->left!=NULL)qu.push(x->left);
                if(x->right!=NULL)qu.push(x->right);
                re.push_back(x->val);
            }
            res.push_back(re);
        }
        return res;
    }
};
}
```

### [01-matrix](https://leetcode-cn.com/problems/01-matrix/)

> 给定一个由 0 和 1 组成的矩阵，找出每个元素到最近的 0 的距离。
> 两个相邻元素间的距离为 1

```cpp
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        int r=matrix.size();
        int l=matrix[0].size();
        queue<pair<int, int>> q;
        vector<vector<int>> res(r,vector<int>(l,r+l));
        vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        for(int i=0;i<r;i++){
            for(int j=0;j<l;j++){
                if(matrix[i][j]==0){
                    q.push({i,j});
                    res[i][j] = 0;
                }
            }
        }

        while(!q.empty()){
            pair<int,int> tmp=q.front();
            q.pop();
            for(int i=0;i<4;i++){
                int x = directions[i].first+tmp.first;
                int y = directions[i].second+tmp.second;
                if(x>=0&&x<r&&y>=0&&y<l&&res[x][y]>res[tmp.first][tmp.second]+1){
                    res[x][y] = res[tmp.first][tmp.second]+1;
                    q.push({x,y});
                }
            }
        }
        return res;
}};
```

## 总结

- 熟悉栈的使用场景
  - 后入先出，保存临时值
  - 利用栈 DFS 深度搜索
- 熟悉队列的使用场景
  - 利用队列 BFS 广度搜索

## 练习

- [ ] [min-stack](https://leetcode-cn.com/problems/min-stack/)
- [ ] [evaluate-reverse-polish-notation](https://leetcode-cn.com/problems/evaluate-reverse-polish-notation/)
- [ ] [decode-string](https://leetcode-cn.com/problems/decode-string/)
- [ ] [binary-tree-inorder-traversal](https://leetcode-cn.com/problems/binary-tree-inorder-traversal/)
- [ ] [clone-graph](https://leetcode-cn.com/problems/clone-graph/)
- [ ] [number-of-islands](https://leetcode-cn.com/problems/number-of-islands/)
- [ ] [largest-rectangle-in-histogram](https://leetcode-cn.com/problems/largest-rectangle-in-histogram/)
- [ ] [implement-queue-using-stacks](https://leetcode-cn.com/problems/implement-queue-using-stacks/)
- [ ] [binary-tree-level-order-traversal](https://leetcode-cn.com/problems/binary-tree-level-order-traversal/)
- [ ] [01-matrix](https://leetcode-cn.com/problems/01-matrix/)
