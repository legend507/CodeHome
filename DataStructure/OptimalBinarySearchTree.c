// A naive recursive implementation of optimal binary search tree problem
#include <stdio.h>
#include <limits.h>
 
// A utility function to get sum of array elements freq[i] to freq[j]
int sum(int freq[], int i, int j);
 
// A recursive function to calculate cost of optimal binary search tree
int optCost(int freq[], int i, int j)
{
   // Base cases
   if (j < i)      // If there are no elements in this subarray
     return 0;
   if (j == i)     // If there is one element in this subarray
     return freq[i];
 
   // Get sum of freq[i], freq[i+1], ... freq[j]
   int fsum = sum(freq, i, j);
 
   // Initialize minimum value
   int min = INT_MAX;
 
   // One by one consider all elements as root and recursively find cost
   // of the BST, compare the cost with min and update min if needed
   for (int r = i; r <= j; ++r)
   {
       int cost = optCost(freq, i, r-1) + optCost(freq, r+1, j);
       if (cost < min)
          min = cost;
   }
 
   // Return minimum value
   return min + fsum;
}
 
// The main function that calculates minimum cost of a Binary Search Tree.
// It mainly uses optCost() to find the optimal cost.
int optimalSearchTree(int keys[], int freq[], int n)
{
     // Here array keys[] is assumed to be sorted in increasing order.
     // If keys[] is not sorted, then add code to sort keys, and rearrange
     // freq[] accordingly.
     return optCost(freq, 0, n-1);
}
 
/*
和 Matrix Chain Multiplication 相同，窮舉所有可以當作 root 的鍵值，並以 root 將原來的樹分作左右兩棵子樹，便縮小了問題。
所有的子問題共有 O(N^2) 個，每個子問題需要窮舉 O(N) 種分割點，故時間複雜度為 O(N^3) 。
C[i,j]=P[i,j]+min(C[i,r-1]+C[r+1,j]), i<=r<=j
下面是計算 Optimal Binary Search Tree 權重的程式碼，至於印出一棵 Optimal Binary Search Tree 的程式碼就不提供了。
*/
 // 將陣列邊界左右各加一格，如此可省去一些判斷陣列邊界的麻煩。
// 鍵值排序後，各自對應的出現頻率。最左邊和最右邊是額外加上的空格子。
int freq[5+2] = {0, 4, 6, 12, 2, 5, 0};
 
int sum[5+2][5+2];      // 連續區間和
int c[5+2][5+2];        // 實行DP所用的陣列。初始化為零。
int path[5+2][5+2];     // 用來紀錄左右子樹的分割點
 
void OptimalBinarySearchTree()
	{
	    /* 先計算連續區間和。之後就會輕鬆多了。 */
	    for (int i=0; i<5; ++i)         // 區間的寬度
	        for (int j=1; j+i<=5; ++j)  // 區間的起點
	            sum[j][j+i] = freq[j] + sum[j+1][j+i];
	 
	    /* 計算最佳的二元搜尋樹。 */
	    for (int i=0; i<5; ++i)         // 區間的寬度
	        for (int j=1; j+i<=5; ++j)  // 區間的起點
	        {
	            int c[j][j+i] = 1e9;
	            for (int k=j; k<=j+i; ++k)  // 分割點
	                if (c[j][k-1] + c[k+1][j+i] + sum[j][j+i] < c[j][j+i])
	                {
	                    c[j][j+i] = c[j][k-1] + c[k+1][j+i] + sum[j][j+i];
	                    path[j][j+i] = k;
	                }
	        }
	 
	    cout << "最佳的二元搜尋樹的平均搜尋成本為" << c[1][5];
	}
//由於第二層迴圈實行時， sum[j][j+i] 都維持定值，也不影響最大值的判斷，故可將之移到迴圈外面去。加法次數減少，會稍微快一點。
        for (int j=1; j+i<=5; ++j)
        {
            int c[j][j+i] = 1e9;
            for (int k=j; k<=j+i; ++k)
                if (c[j][k-1] + c[k+1][j+i] < c[j][j+i])
                {
                    c[j][j+i] = c[j][k-1] + c[k+1][j+i];    // 移走
                    path[j][j+i] = k;
                }
	            c[j][j+i] += sum[j][j+i];   // 移到這裡來
	        }
//迴圈判斷式中，關於區間起點的範圍，與其用減法計算區點起點的界限，不如簡單想成區間終點不超過陣列邊界。 
	    for (int i=0; i<5; ++i)         // 區間的寬度
	        for (int j=1; j<=5-i; ++j)  // 用減法計算區間起點的界限
	            // 不確定j+i會不會超過邊界
	            sum[j][j+i] = freq[j] + sum[j+1][j+i];

	    for (int i=0; i<5; ++i)
	        for (int j=1; j+i<=5; ++j)  // 區間終點不超過陣列邊界
	            // 對應到此處的index，可確定j+i不會超過陣列邊界。
	            sum[j][j+i] = freq[j] + sum[j+1][j+i];
/*
細心的觀察者們，可以發現每次計算一個子問題時，總是要窮舉所有的分割點。然而有些分割點很明顯地是錯誤的，
尤其是靠近區間邊界的那些分割點，實在不太可能將兩顆子樹分的夠均勻、令總和最小。
另外這個問題還有一個特性。相近的子問題，其分割點的位置也很相近。例如子問題 [a,b] 的分割點，
應該會與子問題 [a-1,b] 、 [a+1,b] 的分割點差不多，因為分割出來的左右子樹頂多也只差了一個鍵值，考量到左右子樹要均勻才行，
可推論總成本、子樹的形狀、分割點的位置應該都是差不多的。
子問題 [a,b] 的分割點，必定位於更小的子問題 [a+1,b] 和 [a,b-1] 的分割點之間。如此一來，每次計算一個子問題時，
就不必窮舉所有的分割點，只要找更小的子問題 [a+1,b] 和 [a,b-1] 的分割點之間的分割點即可，為常數個（請各位自行觀察一下）。
由於檢查分割點的次數變成常數次，所以時間複雜度為 O(1) 。計算 O(N^2) 個子問題時，時間複雜度就是 O(N^2) 了。*/
            for (int k=path[j+1][j+i]; k<=path[j][j+i-1]; ++k)  // 分割點
