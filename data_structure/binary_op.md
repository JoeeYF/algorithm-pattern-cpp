# 二进制

## 常见二进制操作

### 基本操作
- 任何数和 0 做异或运算，结果仍然是原来的数
```cpp
a=0^a=a^0
```
- 任何数和其自身做异或运算，结果是 0
```cpp
0=a^a
```
由上面两个推导出：
```cpp
a=a^b^b
```
### 交换两个数
```cpp
a=a^b
b=a^b
a=a^b
```

### 移除最后一个 1
```cpp
//与运算
a=n&(n-1)
```
### 获取最后一个 1
```cpp
diff=(n&(n-1))^n
```
## 常见题目

[single-number](https://leetcode-cn.com/problems/single-number/)

> 给定一个**非空**整数数组，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。

```cpp
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int a=0;
        for(int i=0;i<nums.size();i++)
        a = a ^ nums[i];
        return a;

    }
};
```

[single-number-ii](https://leetcode-cn.com/problems/single-number-ii/)

> 给定一个**非空**整数数组，除了某个元素只出现一次以外，其余每个元素均出现了三次。找出那个只出现了一次的元素。

利用`x&~x=0`,`x^x=0`进行计数。
1. 如果x出现一次，那么`a = (a^x)&~b=x`,`b = (b^x) &~a=0`
2. 出现第二次`a = (a^x)&~b=0`,`b = (b^x) &~a=x`
3. 第三次`a = (a^x)&~b=0`,`b = (b^x) &~a=0`
```cpp
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int a=0，b=0；
        for(auto num:nums)
        {
            a = (a^num) & ~b;
            b = (b^num) & ~a;
        }
        return a;
    }
};
```

[single-number-iii](https://leetcode-cn.com/problems/single-number-iii/)

> 给定一个整数数组  `nums`，其中恰好有两个元素只出现一次，其余所有元素均出现两次。 找出只出现一次的那两个元素。

```go
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int diff=0;
        for(auto num:nums){
            diff=diff^num;
        }
        vector<int> result = {diff,diff};;
        diff=((diff-1)&diff)^diff;
        for(auto num:nums){
            if ((diff&num)==0)
                result[0]^=num;
            else
            result[1]^=num;
        }
        return result;
    }
};
```

```cpp
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int bitmask=0;
        for(auto num:nums){
            bitmask=bitmask^num;
        }
        int diff = bitmask & (-bitmask);
        int x=0;
        for(auto num:nums){
            if (diff&num)
                x^=num;
        }
        return {x,x^bitmask};
    }
};
```

[number-of-1-bits](https://leetcode-cn.com/problems/number-of-1-bits/)

> 编写一个函数，输入是一个无符号整数，返回其二进制表达式中数字位数为 ‘1’  的个数（也被称为[汉明重量](https://baike.baidu.com/item/%E6%B1%89%E6%98%8E%E9%87%8D%E9%87%8F)）。

```cpp
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int res=0;
        while(n!=0){
            // n = n&(n-1);
            // res++;
            res+=n%2;
            n>>=1;

        }
        return res;
    }
};
```

[counting-bits](https://leetcode-cn.com/problems/counting-bits/)

> 给定一个非负整数  **num**。对于  0 ≤ i ≤ num  范围中的每个数字  i ，计算其二进制数中的 1 的数目并将它们作为数组返回。

```c++
class Solution {
public:
    vector<int> countBits(int num) {
        vector<int> result;
        for(int i=0;i<=num;i++)
        result.push_back(hammingWeight(i));
        return result;
    }

    int hammingWeight(uint32_t n) {
        int res=0;
        while(n!=0){
            n = n&(n-1);
            res++;
            // res+=n%2;
            // n>>=1;

        }
        return res;
    }c++
};
```

另外一种动态规划解法

```c++
class Solution {
public:
    vector<int> countBits(int num) {
    vector<int> res(num + 1);
    for(int i = 1; i <= num; i++){
        res[i] = res[i & (i - 1)] + 1; // 上一个缺1的元素+1即可
    }
    return res;

    }
};
```

[reverse-bits](https://leetcode-cn.com/problems/reverse-bits/)

> 颠倒给定的 32 位无符号整数的二进制位。

思路：依次颠倒即可

```c++
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t res = 0;
        int i = 32;
        while(i--)
        {
            res<<=1;
            res+=n&1;
            n>>=1;
        }
        return res;
    }
};
```

[bitwise-and-of-numbers-range](https://leetcode-cn.com/problems/bitwise-and-of-numbers-range/)

> 给定范围 [m, n]，其中 0 <= m <= n <= 2147483647，返回此范围内所有数字的按位与（包含 m, n 两端点）。

```c++
class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        int count=0;
        while(m!=n)
        {
            m>>=1;
            n>>=1;
            count++;
        }
        return m<<count;
    }
};

class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        while(m<n)
        {
            n=n&(n-1);
        }
        return m&n;
    }
};

```

## 练习

- [ ] [single-number](https://leetcode-cn.com/problems/single-number/)
- [ ] [single-number-ii](https://leetcode-cn.com/problems/single-number-ii/)
- [ ] [single-number-iii](https://leetcode-cn.com/problems/single-number-iii/)
- [ ] [number-of-1-bits](https://leetcode-cn.com/problems/number-of-1-bits/)
- [ ] [counting-bits](https://leetcode-cn.com/problems/counting-bits/)
- [ ] [reverse-bits](https://leetcode-cn.com/problems/reverse-bits/)
