# 二叉树
<!-- TOC -->

- [二叉树](#二叉树)
  - [知识点](#知识点)
    - [二叉树遍历](#二叉树遍历)
      - [前序递归](#前序递归)
      - [前序非递归](#前序非递归)
      - [中序递归](#中序递归)
      - [中序非递归](#中序非递归)
      - [后序非递归](#后序非递归)
      - [DFS 深度搜索-从上到下](#dfs-深度搜索-从上到下)
      - [DFS 深度搜索-从下向上（分治法）](#dfs-深度搜索-从下向上分治法)
      - [BFS 层次遍历](#bfs-层次遍历)
    - [分治法应用](#分治法应用)
      - [典型示例](#典型示例)
        - [归并排序](#归并排序)
        - [快速排序](#快速排序)
  - [常见题目示例](#常见题目示例)
    - [分治法](#分治法)
      - [maximum-depth-of-binary-tree](#maximum-depth-of-binary-tree)
      - [balanced-binary-tree](#balanced-binary-tree)
      - [binary-tree-maximum-path-sum](#binary-tree-maximum-path-sum)
      - [lowest-common-ancestor-of-a-binary-tree](#lowest-common-ancestor-of-a-binary-tree)
    - [BFS 层次应用](#bfs-层次应用)
      - [binary-tree-level-order-traversal](#binary-tree-level-order-traversal)
      - [binary-tree-level-order-traversal-ii](#binary-tree-level-order-traversal-ii)
      - [binary-tree-zigzag-level-order-traversal](#binary-tree-zigzag-level-order-traversal)
    - [二叉搜索树应用](#二叉搜索树应用)
      - [validate-binary-search-tree](#validate-binary-search-tree)
      - [insert-into-a-binary-search-tree](#insert-into-a-binary-search-tree)
  - [总结](#总结)
  - [练习](#练习)

<!-- /TOC -->
## 知识点

### 二叉树遍历

**前序遍历**：**先访问根节点**，再前序遍历左子树，再前序遍历右子树  
**中序遍历**：先中序遍历左子树，**再访问根节点**，再中序遍历右子树  
**后序遍历**：先后序遍历左子树，再后序遍历右子树，**再访问根节点**  

注意点

- 以根访问顺序决定是什么遍历
- 左子树都是优先右子树

#### 前序递归

```cpp
template<typename T, typename VST>
void preorderTraversal(BinNodePosi(T) x, VST& visit){
    if (!x) return;
    visit(x->data);
    preorderTraversal(x->lc,visit);
    preorderTraversal(x->rc,visit);
}
```

#### 前序非递归

```c++
// 沿着左侧支路一直向下
template<typename T, typename VST>
static void visitAlongLeftBranch(BinNodePosi(T) x,VST& vist,Stack<BinNodePosi(T)>& S){
    while(x){
        visit(x->data);
        S.push(x->rc); //沿途右孩子入栈
        x = x->lc;
    }
}
template<typename T, typename VST>
void preorderTraversalIter(BinNodePosi(T) x, VST& visit){
    Stack<BinNodePosi(T)> S;
    while(true){
        visitAlongLeftBranch(x,visit,S);
        if(S.empty()) break;
        x = S.pop();
    }
}
```

#### 中序递归

```cpp
template<typename T, typename VST>
void inorderTraversal(BinNodePosi(T) x, VST& visit){
    if (!x) return;
    preorderTraversal(x->lc,visit);
    visit(x->data);
    preorderTraversal(x->rc,visit);
}
```

#### 中序非递归

```cpp
// 沿着左侧支路一直向下,直接入栈，不操作，直到无左孩子
template<typename T, typename VST>
static void goAlongLeftBranch(BinNodePosi(x),Stack<BinNodePosi(T)>& S){
    while(x){
        S.push(x);
        x = x->lc;
    }
}
template<typename T, typename VST>
void inorderTraversalIter(BinNodePosi(T) x, VST& visit){
    Stack<BinNodePosi(T)> S;
    while(true){
        goAlongLeftBranch(x,S);
        if(S.empty()) break;
        x = S.pop();
        visit(x -> data);
        x = x ->rc;
    }
}
```

#### 后序非递归

```cpp
template<typename T, typename VST>
static void gotoHLVFL(Stack<BinNodePosi(T)>& S){
    while(BinNodePosi(T) x=S.top()){
        if(HasLChild(*x)){
            if(HasRChild) S.push(x->rc);
            S.push(x->lc)
        }
        else{
            S.push(x->rc)
        }
    }

    S.pop();
}

template<typename T, typename VST>
void postorderTraversalIter(BinNodePosi(T) x, VST& visit){
    Stack<BinNodePosi(T)> S;
    if(x) S.push(x);

    while(!S.empty()){
        if(S.top() !x->parent) gotoHLVFL(S);
        x = S.pop();
        visit(x->data);
    }
}
```

注意点

- 核心就是：根节点必须在右节点弹出之后，再弹出



#### DFS 深度搜索-从上到下

```cpp
template <typename T, typename VST>
void BinNode<T>::dfs( VST& visit){
    Stack<BinNodePosi(T)> S;
    S.push(this);
    while(!Q.empty()){
        BinNodePosi(T) x=S.pop(); visit(x->data);
        if(HasRChild(*x)) S.push(x->rc)
        if(HasLChild(*x)) Q.push(x->lc);
    }
}

```

#### DFS 深度搜索-从下向上（分治法）

```go
// V2：通过分治法遍历
func preorderTraversal(root *TreeNode) []int {
    result := divideAndConquer(root)
    return result
}
func divideAndConquer(root *TreeNode) []int {
    result := make([]int, 0)
    // 返回条件(null & leaf)
    if root == nil {
        return result
    }
    // 分治(Divide)
    left := divideAndConquer(root.Left)
    right := divideAndConquer(root.Right)
    // 合并结果(Conquer)
    result = append(result, root.Val)
    result = append(result, left...)
    result = append(result, right...)
    return result
}
```

注意点：

> DFS 深度搜索（从上到下） 和分治法区别：前者一般将最终结果通过指针参数传入，后者一般递归返回结果最后合并

#### BFS 层次遍历

```cpp
template <typename T, typename VST>
void BinNode<T>::bfs( VST& visit){
    Queue<BinNodePosi(T)> Q;
    Q.enqueue(this);
    while(!Q.empty()){
        BinNodePosi(T) x=Q.dequeue(); visit(x->data);
        if(HasLChild(*x)) Q.enqueue(x->lc);
        if(HasRChild(*x)) Q.enqueue(x->rc);
    }
}
```

### 分治法应用

先分别处理局部，再合并结果

适用场景

- 快速排序
- 归并排序
- 二叉树相关问题

分治法模板

- 递归返回条件
- 分段处理
- 合并结果

```go
##go
func traversal(root *TreeNode) ResultType  {
    // nil or leaf
    if root == nil {
        // do something and return
    }

    // Divide
    ResultType left = traversal(root.Left)
    ResultType right = traversal(root.Right)

    // Conquer
    ResultType result = Merge from left and right

    return result
}
```

#### 典型示例

```go
##go
// V2：通过分治法遍历二叉树
func preorderTraversal(root *TreeNode) []int {
    result := divideAndConquer(root)
    return result
}
func divideAndConquer(root *TreeNode) []int {
    result := make([]int, 0)
    // 返回条件(null & leaf)
    if root == nil {
        return result
    }
    // 分治(Divide)
    left := divideAndConquer(root.Left)
    right := divideAndConquer(root.Right)
    // 合并结果(Conquer)
    result = append(result, root.Val)
    result = append(result, left...)
    result = append(result, right...)
    return result
}
```

##### 归并排序  

```go
##go
func MergeSort(nums []int) []int {
    return mergeSort(nums)
}
func mergeSort(nums []int) []int {
    if len(nums) <= 1 {
        return nums
    }
    // 分治法：divide 分为两段
    mid := len(nums) / 2
    left := mergeSort(nums[:mid])
    right := mergeSort(nums[mid:])
    // 合并两段数据
    result := merge(left, right)
    return result
}
func merge(left, right []int) (result []int) {
    // 两边数组合并游标
    l := 0
    r := 0
    // 注意不能越界
    for l < len(left) && r < len(right) {
        // 谁小合并谁
        if left[l] > right[r] {
            result = append(result, right[r])
            r++
        } else {
            result = append(result, left[l])
            l++
        }
    }
    // 剩余部分合并
    result = append(result, left[l:]...)
    result = append(result, right[r:]...)
    return
}
```

注意点

> 递归需要返回结果用于合并

##### 快速排序  

```go
##go
func QuickSort(nums []int) []int {
	// 思路：把一个数组分为左右两段，左段小于右段，类似分治法没有合并过程
	quickSort(nums, 0, len(nums)-1)
	return nums

}
// 原地交换，所以传入交换索引
func quickSort(nums []int, start, end int) {
	if start < end {
        // 分治法：divide
		pivot := partition(nums, start, end)
		quickSort(nums, 0, pivot-1)
		quickSort(nums, pivot+1, end)
	}
}
// 分区
func partition(nums []int, start, end int) int {
	p := nums[end]
	i := start
	for j := start; j < end; j++ {
		if nums[j] < p {
			swap(nums, i, j)
			i++
		}
	}
    // 把中间的值换为用于比较的基准值
	swap(nums, i, end)
	return i
}
func swap(nums []int, i, j int) {
	t := nums[i]
	nums[i] = nums[j]
	nums[j] = t
}
```

注意点：

> 快排由于是原地交换所以没有合并过程
> 传入的索引是存在的索引（如：0、length-1 等），越界可能导致崩溃

## 常见题目示例
### 分治法
#### maximum-depth-of-binary-tree

[maximum-depth-of-binary-tree](https://leetcode-cn.com/problems/maximum-depth-of-binary-tree/)


> 给定一个二叉树，找出其最大深度。

思路：分治法

```cpp
class Solution {
public:
    int maxDepth(TreeNode* root) {
        int leftd,rightd;
        if(root==NULL){
            return 0;
        }
        leftd = maxDepth(root->left);
        rightd = maxDepth(root->right);
        if(leftd>rightd){
            return leftd+1;
        }
        else{
            return rightd+1;
        }
    }
};
```

#### balanced-binary-tree
[balanced-binary-tree](https://leetcode-cn.com/problems/balanced-binary-tree/)

> 给定一个二叉树，判断它是否是高度平衡的二叉树。

思路：分治法，左边平衡 && 右边平衡 && 左右两边高度 <= 1，
因为需要返回是否平衡及高度，要么返回两个数据，要么合并两个数据，
所以用-1 表示不平衡，>0 表示树高度（二义性：一个变量有两种含义）。

```cpp
class Solution {
public:
    int maxdepth(TreeNode* root){
        int leftd,rightd;
        if(root==NULL){
            return 0;
        }
        leftd = maxdepth(root->left);
        rightd = maxdepth(root->right);
        if(leftd==-1||rightd==-1||leftd-rightd>1||rightd-leftd>1){
            return -1;
        }
        else if(leftd>rightd){
            return leftd+1;
        }
        else{
            return rightd+1;
        }
    }

    bool isBalanced(TreeNode* root) {
        if(maxdepth(root)==-1){
            return false;
        }
        return true;
    }
};
```

注意

> 一般工程中，结果通过两个变量来返回，不建议用一个变量表示两种含义

#### binary-tree-maximum-path-sum

[binary-tree-maximum-path-sum](https://leetcode-cn.com/problems/binary-tree-maximum-path-sum/)


> 给定一个**非空**二叉树，返回其最大路径和。

思路：分治法，分为三种情况：左子树最大路径和最大，右子树最大路径和最大，左右子树最大加根节点最大，需要保存两个变量：一个保存子树最大路径和，一个保存左右加根节点和，然后比较这个两个变量选择最大值即可

```cpp
class Solution {
public:
    int maxpath;
    int findmaxpath(TreeNode* root){
        if(root==NULL){
            return 0;
        }

        int leftmax = max(findmaxpath(root->left),0);
        int rightmax = max(findmaxpath(root->right),0);
        maxpath = max(maxpath,leftmax+rightmax+root->val);
        return max(leftmax,rightmax)+root->val;
    }


    int maxPathSum(TreeNode* root) {
        if(root==NULL){
            return 0;
        }
        maxpath = root->val;
        findmaxpath(root);
        return maxpath;
    }
};
```

#### lowest-common-ancestor-of-a-binary-tree
[lowest-common-ancestor-of-a-binary-tree](https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/)
> 给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。

思路：分治法，有左子树的公共祖先或者有右子树的公共祖先，就返回子树的祖先，否则返回根节点

```cpp
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root==p||root==q||root==NULL){
            return root;
        }

        TreeNode* left = lowestCommonAncestor(root->left,p,q);
        TreeNode* right = lowestCommonAncestor(root->right,p,q);

        if(left!=NULL&&right!=NULL)
            return root;
        else if (left==NULL)
            return right;
        else if (right==NULL)
            return left;
        else
            return NULL;
    
    }
};
```

### BFS 层次应用

#### binary-tree-level-order-traversal

[binary-tree-level-order-traversal](https://leetcode-cn.com/problems/binary-tree-level-order-traversal/)

> 给你一个二叉树，请你返回其按  **层序遍历**  得到的节点值。 （即逐层地，从左到右访问所有节点）

思路：用一个队列记录一层的元素，然后扫描这一层元素添加下一层元素到队列（一个数进去出来一次，所以复杂度 O(logN)）

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
```

#### binary-tree-level-order-traversal-ii

[binary-tree-level-order-traversal-ii](https://leetcode-cn.com/problems/binary-tree-level-order-traversal-ii/)

> 给定一个二叉树，返回其节点值自底向上的层次遍历。 （即按从叶子节点所在层到根节点所在的层，逐层从左向右遍历）

思路：在层级遍历的基础上，翻转一下结果即可

```cpp
class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
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
        reverse(res.begin(),res.end());
        return res;
    }
};
```

#### binary-tree-zigzag-level-order-traversal

[binary-tree-zigzag-level-order-traversal](https://leetcode-cn.com/problems/binary-tree-zigzag-level-order-traversal/)

> 给定一个二叉树，返回其节点值的锯齿形层次遍历。Z 字形遍历

```go
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if(root==NULL) return res;
        queue<TreeNode*> qu;
        qu.push(root);
        bool rev=false;
        while(!qu.empty()){
            int temp = qu.size();
            vector<int> re;
            for(int i=0;i<temp;i++){
                TreeNode* x =qu.front();
                qu.pop();
                re.push_back(x->val);
                if(x->left!=NULL)qu.push(x->left);
                if(x->right!=NULL)qu.push(x->right);
            }
            if (rev) reverse(re.begin(),re.end());
            rev = !rev;
            res.push_back(re);
        }

        return res;
    }
};
```

### 二叉搜索树应用

#### validate-binary-search-tree

[validate-binary-search-tree](https://leetcode-cn.com/problems/validate-binary-search-tree/)

> 给定一个二叉树，判断其是否是一个有效的二叉搜索树。

思路 1：中序遍历，检查结果列表是否已经有序

思路 2：分治法，判断左 MAX < 根 < 右 MIN

```cpp
class Solution {
public:
    long last=LONG_MIN;
    bool isValidBST(TreeNode* root) {
        if(root==NULL) return true;
        if(!isValidBST(root->left)) return false;
        if (last>=root->val) return false;
        last = root->val;
        if(!isValidBST(root->right)) return false;
        return true;
    }
};
```

#### insert-into-a-binary-search-tree

[insert-into-a-binary-search-tree](https://leetcode-cn.com/problems/insert-into-a-binary-search-tree/)

> 给定二叉搜索树（BST）的根节点和要插入树中的值，将值插入二叉搜索树。 返回插入后二叉搜索树的根节点。

思路：找到最后一个叶子节点满足插入条件即可

```cpp
// DFS查找插入位置
class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if(!root) return new TreeNode(val);
        if (root->val>val) root->left = insertIntoBST(root->left,val);
        else root->right = insertIntoBST(root->right,val);
        return root;
    }
};
```

## 总结

- 掌握二叉树递归与非递归遍历
- 理解 DFS 前序遍历与分治法
- 理解 BFS 层次遍历

## 练习

- [ ] [maximum-depth-of-binary-tree](https://leetcode-cn.com/problems/maximum-depth-of-binary-tree/)
- [ ] [balanced-binary-tree](https://leetcode-cn.com/problems/balanced-binary-tree/)
- [ ] [binary-tree-maximum-path-sum](https://leetcode-cn.com/problems/binary-tree-maximum-path-sum/)
- [ ] [lowest-common-ancestor-of-a-binary-tree](https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/)
- [ ] [binary-tree-level-order-traversal](https://leetcode-cn.com/problems/binary-tree-level-order-traversal/)
- [ ] [binary-tree-level-order-traversal-ii](https://leetcode-cn.com/problems/binary-tree-level-order-traversal-ii/)
- [ ] [binary-tree-zigzag-level-order-traversal](https://leetcode-cn.com/problems/binary-tree-zigzag-level-order-traversal/)
- [ ] [validate-binary-search-tree](https://leetcode-cn.com/problems/validate-binary-search-tree/)
- [ ] [insert-into-a-binary-search-tree](https://leetcode-cn.com/problems/insert-into-a-binary-search-tree/)
