
**Find “one letter that appears twice” in a string**

------------------

I'm trying to catch if one letter that appears twice in a string using RegEx (or maybe there's some better ways?), for example my string is:

`ugknbfddgicrmopn`

The output would be:

`dd`

**A**

```python
>>> re.search(r'([a-z])\1', 'ugknbfddgicrmopn').group()
'dd'
>>> [i+i for i in re.findall(r'([a-z])\1', 'abbbbcppq')]
['bb', 'bb', 'pp']

>>> [i[0] for i in re.findall(r'(([a-z])\2)', 'abbbbcppq')]
['bb', 'bb', 'pp']
```

As a Pythonic way You can use zip function within a list comprehension:

```python
>>> s = 'abbbcppq'
>>>
>>> [i+j for i,j in zip(s,s[1:]) if i==j]
['bb', 'bb', 'pp']
```

If you are dealing with large string you can use `iter()` function to convert the string to an iterator and use `itertols.tee()` to create two independent iterator, then by calling the next function on second iterator consume the first item and use call the zip class (in Python 2.X use `itertools.izip()` which returns an `iterator`) with this iterators.

```python
>>> from itertools import tee
>>> first = iter(s)
>>> second, first = tee(first)
>>> next(second)
'a'
>>> [i+j for i,j in zip(first,second) if i==j]
['bb', 'bb', 'pp']
```

-----------------------------

**How to match a line does NOT include a word?**

----------

```
Input:

 hoho
 hihi
 haha
 hede

 # grep "Regex for do not contain hede" Input

Output:
 hoho
 hihi
 haha
```

--------------------

`^((?!hede).)*$`

**Explanation 1**

`^`the beginning of the string

`(` group and capture to `\1` (0 or more times (matching the most amount possible))

`(?!` look ahead to see if there is not:

`hede` your string

`)` end of look-ahead

`.` any character except `\n`

`)*` end of `\1` (NOTE: because you are using a quantifier on this capture, only the LAST repetition of the captured pattern will be stored in `\1`)

`$` before an optional `\n`, and the end of the string

**Explanation 2**

A string is just a list of n characters. Before, and after each character, there's an empty string. 
So a list of n characters will have n+1 empty strings. Consider the string "ABhedeCD":

```
    +--+---+--+---+--+---+--+---+--+---+--+---+--+---+--+---+--+
S = |e1| A |e2| B |e3| h |e4| e |e5| d |e6| e |e7| C |e8| D |e9|
    +--+---+--+---+--+---+--+---+--+---+--+---+--+---+--+---+--+

index    0      1      2      3      4      5      6      7
```

where the e's are the empty strings. The regex (?!hede). looks ahead to see if there's no substring "hede" to be seen, 
and if that is the case (so something else is seen), then the . (dot) will match any character except a line break.
Look-arounds are also called zero-width-assertions because they don't consume any characters. 
They only assert/validate something.

So, in my example, every empty string is first validated to see if there's no "hede" up ahead, before a character is consumed
by the . (dot). The regex (?!hede). will do that only once, so it is wrapped in a group, and repeated zero or more times: 
((?!hede).)*. Finally, the start- and end-of-input are anchored to make sure the entire input is consumed: ^((?!hede).)*$

[Ref](http://stackoverflow.com/questions/406230/regular-expression-to-match-line-that-doesnt-contain-a-word)

------------------------------------------------------------

`"f|u|n|n|y||b|o|y||a||c|a|t"`

I would like to replace all "|"s which are not next to another "|" with nothing, to get the result:

`"funny|boy|a|cat"`

**A**

```python
>>> import re
>>> st = "f|u|n|n|y||b|o|y||a||c|a|t" 
>>> re.sub(r'\|(?=[a-z]|$)',r'',st)
'funny|boy|a|cat'
```

```python
>>> import re
>>> s = "f|u|n|n|y||b|o|y||a||c|a|t"
>>> re.sub('\|(?!\|)' , '', s)
'funny|boy|a|cat'
```

```python
>>> s = "f|u|n|n|y||b|o|y||a||c|a|t"
>>> s.replace('||','~').replace('|','').replace('~','|')
'funny|boy|a|cat'
```

------------------------------------------

I would like to find all alternating digits in a string using regular expressions. An alternating digit is defined as two equal digits having a digit in between; for example, `1212` contains `2` alternations (`121` and `212`) and `1111` contains `2` alternations as well (`111` and `111`). I have the following regular expression code:

```python
s = "1212"
re.findall(r'(\d)(?:\d)(\1)+', s)
```

This works for strings like "121656", but not "1212". This is a problem to do with overlapping matches I think. How can I deal with that?

**A**

`(?=((\d)\d\2))`

Use lookahead to get all overlapping matches. Use re.findall and get the first element from the tuple. See the demo:

- (?=((\d)\d\2)) Positive Lookahead - Assert that the regex below can be matched
- 1st Capturing group ((\d)\d\2)
- 2nd Capturing group (\d)
- \d match a digit [0-9]
- \d match a digit [0-9]
- \2 matches the same text as most recently matched by the 2nd capturing group

-------------------------------------------

- 数字：`^[0-9]*$`
- n位的数字：`^\d{n}$`
- 至少n位的数字: `^\d{n,}$`
- m-n位的数字：`^\d{m,n}$`
- 零和非零开头的数字：`^(0|[1-9][0-9]*)$`
- 非零开头的最多带两位小数的数字：`^([1-9][0-9]*)+(.[0-9]{1,2})?$`
- 带1-2位小数的正数或负数：`^(\-)?\d+(\.\d{1,2})?$`
- 正数、负数、和小数：`^(\-|\+)?\d+(\.\d+)?$`
- 有两位小数的正实数：`^[0-9]+(.[0-9]{2})?$`
- 有1~3位小数的正实数：`^[0-9]+(.[0-9]{1,3})?$`
- 非零的正整数：`^[1-9]\d*$` 或 `^([1-9][0-9]*){1,3}$` 或 `^\+?[1-9][0-9]*$`
- 非零的负整数：`^\-[1-9][]0-9"*$` 或 `^-[1-9]\d*$`
- 非负整数：`^\d+$` 或 `^[1-9]\d*|0$`
- 非正整数：`^-[1-9]\d*|0$` 或 `^((-\d+)|(0+))$`
- 非负浮点数：`^\d+(\.\d+)?$` 或 `^[1-9]\d*\.\d*|0\.\d*[1-9]\d*|0?\.0+|0$`
- 非正浮点数：`^((-\d+(\.\d+)?)|(0+(\.0+)?))$` 或 `^(-([1-9]\d*\.\d*|0\.\d*[1-9]\d*))|0?\.0+|0$`
- 正浮点数：`^[1-9]\d*\.\d*|0\.\d*[1-9]\d*$` 或 `^(([0-9]+\.[0-9]*[1-9][0-9]*)|([0-9]*[1-9][0-9]*\.[0-9]+)|([0-9]*[1-9][0-9]*))$`
- 负浮点数：`^-([1-9]\d*\.\d*|0\.\d*[1-9]\d*)$` 或 `^(-(([0-9]+\.[0-9]*[1-9][0-9]*)|([0-9]*[1-9][0-9]*\.[0-9]+)|([0-9]*[1-9][0-9]*)))$`
- 浮点数：`^(-?\d+)(\.\d+)?$` 或 `^-?([1-9]\d*\.\d*|0\.\d*[1-9]\d*|0?\.0+|0)$`

- Email地址：`^\w+([-+.]\w+)*@\w+([-.]\w+)*\.\w+([-.]\w+)*$`
-  域名：`[a-zA-Z0-9][-a-zA-Z0-9]{0,62}(/.[a-zA-Z0-9][-a-zA-Z0-9]{0,62})+/.?`
-  InternetURL：`[a-zA-z]+://[^\s]*` 或 `^http://([\w-]+\.)+[\w-]+(/[\w-./?%&=]*)?$`
-  手机号码：`^(13[0-9]|14[5|7]|15[0|1|2|3|5|6|7|8|9]|18[0|1|2|3|5|6|7|8|9])\d{8}$`
-  电话号码("XXX-XXXXXXX"、"XXXX-XXXXXXXX"、"XXX-XXXXXXX"、"XXX-XXXXXXXX"、"XXXXXXX"和"XXXXXXXX)：`^(\(\d{3,4}-)|\d{3.4}-)?\d{7,8}$`
-  国内电话号码(0511-4405222、021-87888822)：`\d{3}-\d{8}|\d{4}-\d{7}`
-  身份证号(15位、18位数字)：`^\d{15}|\d{18}$`
-  短身份证号码(数字、字母x结尾)：`^([0-9]){7,18}(x|X)?$` 或 `^\d{8,18}|[0-9x]{8,18}|[0-9X]{8,18}?$`
-  帐号是否合法(字母开头，允许5-16字节，允许字母数字下划线)：`^[a-zA-Z][a-zA-Z0-9_]{4,15}$`
-  密码(以字母开头，长度在6~18之间，只能包含字母、数字和下划线)：`^[a-zA-Z]\w{5,17}$`
-  强密码(必须包含大小写字母和数字的组合，不能使用特殊字符，长度在8-10之间)：`^(?=.*\d)(?=.*[a-z])(?=.*[A-Z]).{8,10}$`  
-  日期格式：`^\d{4}-\d{1,2}-\d{1,2}`
-  一年的12个月(01～09和1～12)：`^(0?[1-9]|1[0-2])$`
-  一个月的31天(01～09和1～31)：`^((0?[1-9])|((1|2)[0-9])|30|31)$` 
-  钱的输入格式：
-     1.有四种钱的表示形式我们可以接受:"10000.00" 和 "10,000.00", 和没有 "分" 的 "10000" 和 "10,000"：`^[1-9][0-9]*$` 
-     2.这表示任意一个不以0开头的数字,但是,这也意味着一个字符"0"不通过,所以我们采用下面的形式：`^(0|[1-9][0-9]*)$ `
-     3.一个0或者一个不以0开头的数字.我们还可以允许开头有一个负号：`^(0|-?[1-9][0-9]*)$` 
-     4.这表示一个0或者一个可能为负的开头不为0的数字.让用户以0开头好了.把负号的也去掉,因为钱总不能是负的吧.下面我们要加的是说明可能的- 数部分：`^[0-9]+(.[0-9]+)?$` 
-     5.必须说明的是,小数点后面至少应该有1位数,所以"10."是不通过的,但是 "10" 和 "10.2" 是通过的：`^[0-9]+(.[0-9]{2})?$` 
-     6.这样我们规定小数点后面必须有两位,如果你认为太苛刻了,可以这样：`^[0-9]+(.[0-9]{1,2})?$` 
-     7.这样就允许用户只写一位小数.下面我们该考虑数字中的逗号了,我们可以这样：`^[0-9]{1,3}(,[0-9]{3})*(.[0-9]{1,2})?$` 
-     8.1到3个数字,后面跟着任意个 逗号+3个数字,逗号成为可选,而不是必须：`^([0-9]+|[0-9]{1,3}(,[0-9]{3})*)(.[0-9]{1,2})?$` 
-     备注：这就是最终结果了,别忘了"+"可以用"*"替代如果你觉得空字符串也可以接受的话(奇怪,为什么?)最后,别忘了在用函数时去掉去掉那个反斜- ,一般的错误都在这里
-  xml文件：`^([a-zA-Z]+-?)+[a-zA-Z0-9]+\\.[x|X][m|M][l|L]$`
-  中文字符的正则表达式：`[\u4e00-\u9fa5]`
-  双字节字符：`[^\x00-\xff]`    (包括汉字在内，可以用来计算字符串的长度(一个双字节字符长度计2，ASCII字符计1))
-  空白行的正则表达式：`\n\s*\r`    (可以用来删除空白行)
-  HTML标记的正则表达式：`<(\S*?)[^>]*>.*?</\1>|<.*? />`   
-  首尾空白字符的正则表达式：`^\s*|\s*$或(^\s*)|(\s*$)`    - 可以用来删除行首行尾的空白字符(包括空格、制表符、换页符等等)，非常有用的表达式)
-  腾讯QQ号：`[1-9][0-9]{4,}`    (腾讯QQ号从10000开始)
-  中国邮政编码：`[1-9]\d{5}(?!\d)`    (中国邮政编码为6位数字)
-  IP地址：`\d+\.\d+\.\d+\.\d+`    (提取IP地址时有用)
-  IP地址：`((?:(?:25[0-5]|2[0-4]\\d|[01]?\\d?\\d)\\.){3}(?:25[0-5]|2[0-4]\\d|[01]?\\d?\\d))`  


