/*
Given a set T of characters and a string S, find the minimum window in S which will contain all the characters in T in complexity O(n).
eg,
S = “ADOBECODEBANC”
T = “ABC”
Minimum window is “BANC”.
*/
//O(N lg M) time)
bool findMinWindow(const char* str, const char* pattern, int& winBegin, int& winEnd){
	int str_len = strlen(str);
	int pat_len = strlen(pattern);
	int min_window_len = INT_MAX;
	int hmap[256] = {0};

	for (int i = 0; i < pat_len; ++i)
		hmap[pattern[i]]++;

	for (int i = 0; i < 256; ++i)
		if (hmap[i] == 0)
			hmap[i] = -1;

	// array of queues, each corresponds to a unique char in T
	queue<int> q[256];
	
	// maintains a sorted map (maps indices to char), 
	// the first and last element tells us the 
	// starting and ending position of the window
	map<int, char> m;

	for (int i = 0; i < str_len; ++i){
		if (hmap[str[i]] == -1)
			continue;

		if (q[str[i]].size() < hmap[str[i]]){
			q[str[i]].push(i);
			hmap[i] = str[i];
		}else{
			int idx = q[str[i]].front();
			map<int, char>::iterator it = m.find(idx);
			m.erase(it);
			m[i] = str[i];
			q[str[i]].pop();
			q[str[i]].push(i);
		}

		if (m.size() == pat_len){
			int begin = m.rbegin()->first;
			int end = m.begin()->first;
			int len = begin - end + 1;
			if (len < min_window_len){
				min_window_len = len;
				winBegin = begin;
				winEnd = end;
			}
		}
	}

	return (m.size() == pat_len)?true:false;
}
