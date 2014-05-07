/*
Q: 两个数组，从每个数组中取一个数相加，求最大的前k个和 
     数组A：1,2,3 
     数组B：4,5,6 
     则最大的前2个和：9,8。
/*
solution 1:
B数组排序，从大到小。 构造一个大顶堆h。对于i=0,1,2,...,len(A)-1，把三元组(A[i]+B[0], i, 0)放入堆，按三元组第一个元素排大小。 
  
每次从堆里取出堆顶元素，设其为(s,i,j)。输出s。 
设m=j+1。如果m小于B的长度减一，那么将三元组(A[i]+B[m], i, m)压入堆中。 重复，直到输出了k个数为止。 
时间复杂度：O(len(B)*log(len(B)) + len(A) + k*log(len(A))) 
*/
/*
That can be easily done in O(k*logk). I'll only assume arrays are sorted in descending order, to simplify notation.
The idea is simple. We'll find 1st, 2nd, .., k-th maximum values one by one.
But to even consider pair (i, j) we need to have both (i-1, j) and (i, j-1) already selected, because they both are greater or equal than (i, j).
It's much like if we push all n*m pairs into the heap and then remove max k times. Only we don't need all n*m pairs.
*/
void GetKthLargestSum(int arrA[], int lenA, int arrB[], int lenB, int k){
	if (arrA == NULL || lenA == 0 || lenB == NULL || lenB == 0)
		return;

	// sort array A and B, descending order...
	qsort(arrA, lenA, sizeof(int), compare);
	qsort(arrB, lenB, sizeof(int), compare);

	// key: sum(A, B), value: pair<indexOfA, indexOfB>
	priority_queue<int, pair<int, int> > maxHeap;

	int idxA = 0, idxB = 0;
	maxHeap.push(pair<int, pair<int, int> >(arrA[0]+arrB[0], make_pair(idxA, idxB)));
	for (int idx = 0; idx < k; ++idx){
		pair<int, pair<int, int> > val = maxHeap.top();
		cout << val.first << " ";
		maxHeap.pop();

		maxHeap.push(pair<int, pair<int, int> >(arrA[val.second.first+1]+arrB[val.second.second], make_pair(val.second.first+1, val.second.second)));
		maxHeap.push(pair<int, pair<int, int> >(arrA[val.second.first]+arrB[val.second.second+1], make_pair(val.second.first, val.second.second+1)));
	}
	// TODO: 1. Duplicated pairs can be added to the heap, this can be prevented with hash.
	//		 2. Indexes need to be validated, e.g. that max.i + 1 < arrA.length.
}

/*
solution 2:
假设两个数组都是升序的） 
二分sum的下限x。 
对于这个x，一个指针从A数组的头开始往后扫，一个指针从B数组的尾开始往前扫，这样扫一次可以O(A+B)求出不小于x的sum的个数t。 
根据t与k的大小关系继续二分x。 最后确定了x后可以扫一次并求出所有数对。 O((A+B)lg(sum)+k)
*/


/*
All in All: 
1、碰到这个问题的一般思路是，把m*n个数先求出来，然后用Nth-Elemnet，找出第k大的数。Nth-Element就是快排变形的那个partition，
线性时间，这里不延伸讲了。这样的话时间复杂度O(m*n)，空间复杂度O(m*n)。

2、对于第一种方法，时间复杂度还好说，空间复杂度实在问题比较大，是否可以不求出这m*n个元素就直接找打第K大的数呢？
可以这样，先对A，B分别排序。复杂度n*log(n) + m*log(m)，排序后我们就发现第k大的数一定在
Min = A[0] + B[0] <= C[k] <= A[n] + B[m] = Max，而且从Min到Max，K是递减，如果用二分法找这个C[k]，然后在A和B中判断，
有多少个数比C[k]大。如果恰好有k-1个数比C[k]大，则C[k]是第K大的数。考虑有相等的情况，如果比C[K]大的数不到K个，
而比C[K]小的数不到m*n - k个，则说明等于C[K]的数有多个（当然直接判断=也可以），那么C[K]就是第k大的数。

总结一下这个思路，就是在Min和Max之间，二分找这个和，然后在排序好的数组A,B中，统计有多少个数大于这个和。
在这个思路的基础上，如何统计有多少个数的和大于给定的数C[k]呢？我们可以枚举数组A中的元素，然后利用二分，
在数组B中找到C[k] - A[i]对应的元素B[j]，那么所有比B[j]大的元素同A[i]的和，都大于C[k]。
这样就可以写出一个n*log(m)*log(Max - Min) + n*log(n) + m*log(m)的程序来解决这个问题，空间复杂度O(1)

3、对于方法2，有一个简单的优化，就是如果n > m，也就是数组B的长度大于数组A的长度，如果枚举数组B，效率会更高，
空间还是O(1)，时间变为了min(m,n)*log(max(n,m))*log(max - min) + n*log(n) + m*log(m)

4、对于方法2和3，都还可以进一步优化，优化的关键点在于：枚举数组A，在数组B中二分找一个数。如果改用头尾指针的方式，
平摊下来是线性的。方法如下：
先用一个指针指向数组A的头，一个指向数组B的尾，如果A[0] + B[m] < C[k]，A的指针后移，
判断A[1] + B[m]，如果A[0] + B[m] > C[k]，则B的指针前移，判断A[0] + B[m-1]。简单说就是< C[k]，A的指针后移，> C[k]，
B的指针前移。不过问题的关键在于计数，同时统计大于C[k]的小于C[k]的数有多少个。如果A[0] + B[m] < C[k]，
则A[0] + B[0],B[1]......B[m-1]都小于<C[k]，小于的计数+m,如果A[0] + B[m] > C[k]，则A[1],A[2]......A[n]+B[m]都大于C[k]，
大于计数+n，这样，就可以写出一个(m+n)*log(Max-Min)+ n*log(n) + m*log(m)的程序，来解决这个问题。

到此为止，优化到头了么？其实此问题可以转为在杨氏矩阵中找第k大的值，问题还有优化的空间，关键在于Log(Max - Min)，
可以优化到Log(m*n)，后者适用范围就不仅仅是整数了，实数范围都可以
*/

