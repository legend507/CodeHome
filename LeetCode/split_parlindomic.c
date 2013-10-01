/*
对一个字符串按照回文进行分割，例如aba|b|bbabb|a|b|aba就是字符串ababbbabbababa的一个回文分割，每一个字串都是一个回文。
请找到可以分割的最少的字串数。例如：
ababbbabbababa最少4个字符串，分割三次：a|babbbab|b|ababa
如果字符串整体是回文，则需要0次分割，最少1个字符串
*/

/*
我们可以从字符串的第一个字符开始，找满足回文的字 串。假设str[0..k]是一个回文字串（包括0和k），问题可以分解为子问题了：
假设count[i]表示从i开始、包括i的字符串的回文切割数（当 然是有很多可能的），如果str[0..k]是一个回文字符串，
则count[i]=count[k+1] + 1。找到递归表达式，这里要注意，从0开始，可能会有多个回文子串，也正是因为如此，才有最少分割一说。
上面的算法中，每次要遍历一遍字符串，同时要判断子串是否是回文，这里显然是存在重复计算的。这给我们改进提供了可能。
那么该如何更好的判断回文呢？我们设定P[i][j]：
为true时，表示str[i..j]为回文
为false时，表示str[i..j]不是回文
则，当：
i==j时，P[i][j]=true
j==i+1时，P[i][j]=str[i]==str[i]
其他，P[i][j]=P[i+1][j-1]&&(str[i]==str[j])
这个P该如何构建呢？根据其状态转移的方程，P[i][j]所代表的字符串，长度从1开始变化，逐渐到整个字符串，是这样的一个构建的过程
，所以外层循环应该是所要判断的字串的长度。
*/



/*
回文字串判断完毕之后，改如何计算最少分割呢？我们可以根据P构建一棵树，然后宽度有限遍历，找到树的最小深度。
上面判断回文的时间复杂度为 O(n^2)，构建树的时间复杂度为遍历一次P，时间复杂度也是O(n^2)，最后树的遍历，
时间复杂度要小于O(n^2)，这样，整体的时间复杂度为 O(n^2)。
也可以不这样考虑，如同我们上面说的，我们用C[i]表示str[0..j]的最小分割数，然后变量k从1开始到n遍历，找到最少的分割。
时间复杂度O(n^2)。
*/
