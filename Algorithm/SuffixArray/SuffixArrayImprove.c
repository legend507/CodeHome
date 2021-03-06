//Suffix Array
/*
Prefix-doubling Algorithm ：各回合拿前一個、前二個、前四個、前八個、……字元實施排序，總共 logT 回合。
每回合可以採用 Quicksort 或 Counting Sort 。

http://www.csie.ntnu.edu.tw/~u91029/StringMatching2.html#1
*/

#define maxn 100
int wa[maxn], wb[maxn], wv[maxn], ws[maxn];
int rank[maxn],height[maxn];
int cmp(int* r, int a, int b, int i){
	return r[a]==r[b]&&r[a+i]==a[b+i];
}
void da(int *r, int *sa, int n, int m){
	int i, j, p, *x = wa, *y = wb, *t;

	for (i = 0; i < m; ++i) 
		ws[i] = 0;
	for (i = 0; i < n; ++i)
		ws[x[i]=r[i]]++;
	for (i = 1; i < m; ++i)
		ws[i] += ws[i-1];
	for (i = n-1; i >= 0; --i)
		sa[--ws[x[i]]] = i;

	for (j = 1, p = 1; p < n; j*=2, m = p){
		for (p = 0, i = n-1; i < n; ++i)
			y[p++] = i;
		for (i = 0; i < n; ++i)
			if (sa[i] >= j)
				y[p++] = sa[i] - j;
		for (i = 0; i < n; ++i)
			wv[i] = x[y[i]];
		for (i = 0; i < m; ++i)
			ws[i] = 0;
		for (i = 0; i < n; ++i)
			ws[wv[i]]++;
		for (i = 1; i < m; ++i)
			ws[i] += ws[i-1];
		for (i = n-1; i >= 0; --i)
			sa[--ws[wv[i]]] = y[i];
		for (t = x, x = y, y = t, p = 1, x[sa[0]]=0, i = 1; i < n; ++i)
			x[sa[i]] = cmp(y, sa[i-1], sa[i], j)?p-1:p++;
	}
}

void get_height(int *r,int n)//Get height
{
    int i,j,k=0;
    for(i=1; i<=n; i++) rank[sa[i]]=i; //rank function
    for(i=0; i<n; height[rank[i++]]=k)
        for(k?k--:0,j=sa[rank[i]-1]; r[i+k]==r[j+k]; k++);
}

