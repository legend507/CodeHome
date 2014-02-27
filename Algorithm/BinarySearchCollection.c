/*
1. 给定一个有序（非降序）数组A，求任意一个i使得A[i]等于target，不存在则返回-1
2. 给定一个有序（非降序）数组A，可含有重复元素，求最小的i使得A[i]等于target，不存在则返回-1
3. 给定一个有序（非降序）数组A，可含有重复元素，求最大的i使得A[i]等于target，不存在则返回-1
4. 给定一个有序（非降序）数组A，可含有重复元素，求最大的i使得A[i]小于target，不存在则返回-1
5. 给定一个有序（非降序）数组A，可含有重复元素，求最小的i使得A[i]大于target，不存在则返回-1
6. 给定一个有序（非降序）数组A，可含有重复元素，求target在数组中出现的次数。
7. 给定一个有序（非降序）数组A，若target在数组中出现，返回位置，若不存在，返回它应该插入的位置。
8. 给定一个有序（非降序）数组A，可含有重复元素，求绝对值最小的元素的位置
9. 给定一个有序（非降序）数组A和一个有序（非降序）数组B，可含有重复元素，求两个数组合并结果中的第k(k>=0)个数字。
10. 一个有序（升序）数组，没有重复元素，在某一个位置发生了旋转后，求target在变化后的数组中出现的位置，不存在则返回-1.
11. 一个有序（升序）数组，没有重复元素，在某一个位置发生了旋转后，求最小值所在位置
12. 一个有序（升序）数组，没有重复元素，在某一个位置发生了旋转后，求第k(k > 0)小元素
*/

//给定一个有序（非降序）数组A，可含有重复元素，求最大的i使得A[i]小于target，不存在则返回-1。
int searchLastPosLessThan(int A[], int n, int target){
	if (n <= 0)
		return -1;

	int low = 0, high = n - 1;
	while (low < high){
		int mid = low + (high - low + 1) >> 1; // avoid bad loop
		if (A[mid] < target)
			low = mid;
		else
			high = mid - 1;
	}

	return A[low] < target? low : -1;
}

// 给定一个有序（非降序）数组A，可含有重复元素，求target在数组中出现的次数
int count(int A[], int n, int target)
{
	int firstPos = binary_search_first_position(A, n, target); 
	if(firstPos == -1)
		return 0;
	int lastPos = binary_search_last_position(A, n, target); 

	return lastPos-firstPos+1;  // 出现次数
}
