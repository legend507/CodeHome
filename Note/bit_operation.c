计算n+1
 -~n
计算n-1
~-n

取相反数
~n + 1;

另一种写法

(n ^ -1) + 1;

if(x == a) x = b; if(x == b) x = a;
x = a ^ b ^ x;

sign函数，参数为n，当n>0时候返回1，n<0时返回-1，n=0时返回0
return !!n – (((unsigned)n >> 31) << 1);
