# 排序

## 常考排序

### 快速排序

```cpp
void quickSort(vector<int> &q,int l,int r){
    if(l>=r) return;
    int i=l,j=r;
    while(i<j){
        while(q[j]>=q[l]&&i<j) j--;
        while(q[i]<=q[l]&&i<j) i++;
        swap(q[i],q[j]);
    }
    swap(q[i],q[l]);
    quickSort(q,l,i-1);
    quickSort(q,i+1,r);
}
```

### 归并排序

```cpp
void mergeSort(vector<int> &q,int l,int r){
    if(l>=r) return;
    int mid = l+r>>1;
    mergeSort(q,l,mid);
    mergeSort(q,mid+1,r);
    static vector<int> w;
    w.clear();
    int i=l,j=mid+1;
    while(i<=mid&&j<=r){
        if(q[i]>q[j]) w.push_back(q[j++]);
        if(q[i]<=q[j]) w.push_back(q[i++]);
    }
    while(i<=mid) w.push_back(q[i++]);
    while(j<=r) w.push_back(q[j++]);
    for(int i : w)
        q[l++] = i;
}

```

### 堆排序

用数组表示的完美二叉树 complete binary tree

> 完美二叉树 VS 其他二叉树

![image.png](https://img.fuiboom.com/img/tree_type.png)

[动画展示](https://www.bilibili.com/video/av18980178/)

![image.png](https://img.fuiboom.com/img/heap.png)

核心代码

```cpp
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

```

## 参考

[十大经典排序](https://www.cnblogs.com/onepixel/p/7674659.html)

[二叉堆](https://labuladong.gitbook.io/algo/shu-ju-jie-gou-xi-lie/er-cha-dui-xiang-jie-shi-xian-you-xian-ji-dui-lie)

## 练习

- [ ] 手写快排、归并、堆排序
