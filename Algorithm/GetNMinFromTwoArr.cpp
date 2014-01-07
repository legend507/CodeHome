/*
Given two sorted arrays A, B of size m and n respectively. 
Find the k-th smallest element in the union of A and B. You can assume that there are no duplicate elements.
*/
//The trivial way, O(m+n):
//Merge both arrays and the k-th smallest element could be accessed directly. 
//Merging would require extra space of O(m+n).
void merge_helper(int a[], int a_len, int a_cur, int b[], int b_len, int b_cur, int k, int* result){
	if (a_cur + 1 >= a_len){
		memcpy(result+a_cur+b_cur, b+b_cur, k-a_cur-b_cur);
		return;
	}else if (b_cur + 1 >= b_len){
		memcpy(result+a_cur+b_cur, a+a_cur, k-a_cur-b_cur);
		return;
	}

	if (a_cur + b_cur >= k)
		return;

	if (a[a_cur] > b[b_cur]){
		result[a_cur+b_cur] = b[b_cur++];
	}else{
		result[a_cur+b_cur] = a[a_cur++];
	}

	merge_helper(a, a_len, a_cur, b, b_len, b_cur, k, result);
}

int* merge_two_array(int a[], int a_len, int b[], int b_len, int k){
	if (k > a_len+b_len)
		return NULL;

	int* presult = new int[a_len+b_len];
	if (presult == NULL)
		return NULL;

	merge_helper(a, a_len, 0, b, b_len, 0, k, presult);

	return presult;
}

//A better way, O(k):
//There is an improvement from the above method, Using two pointers, you can traverse both arrays without actually merging them,
//thus without the extra space. Both pointers are initialized to point to head of A and B respectively, 
//and the pointer that has the larger smaller of the two is incremented one step.
void merge_v1_helper(int a[], int** pa, int a_len, int b[], int** pb, int b_len, int k){
	if (*pa >= a+a_len-1){
		*pb += k - a_len - (*pb - b)/sizeof(int*);
		return;
	}else if (*pb >= b+b_len-1){
		*pa += k - b_len - (*pa - a)/sizeof(int*);
		return;
	}

	if ((*pb - b)/sizeof(int*) + (*pa - a)/sizeof(int*) >= k)
		return;

	if (**pa > **pb)
		*pb++;
	else
		*pa++;

	return merge_v1_helper(a, pa, a_len, b, pb, b_len, k);
}
