// binary search
int binary_search(int* A, int n, int target){
	int low = 0, high = n-1;
	assert(A != NULL && n >= 0);
	while (low <= high){
		int mid = low + (high - low)/2;
		if (A[mid] == target)
			return mid;
		else if (A[mid] < target)
			low = mid + 1;
		else
			high = mid - 1;
	}

	return -1;
}
