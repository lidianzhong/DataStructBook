#include<iostream>
#include <cstring>
using namespace std;

#define MAX_LEN 100

// 非递归求解next数组
void Get_Next1(char P[], int next[]) {
	// next[i]的求解方法是，找到从t[0]~t[i-1]的公共最长匹配前缀和后缀的长度

	next[0] = -1;
	next[1] = 0;

	// 本层循环是求出所有对应的next[i]值
	for (int i = 2; P[i] != '\0'; i++) {

		// 每对应一个i，进行如下求值过程

		int max_len = i - 1, len;
		
		// 遍历最长公共前后缀，长度len尝试从最长的长度max_len(i - 1) 开始，一直到最短为1
		for (len = max_len; len >= 1; len--) {

			int j;

			// 每对应一个最长公共前后缀len，判断是否满足条件
			for (j = 0; j < len; j++)
				if(P[j] != P[i - len + j]) break;

			// 正常退出for循环，代表匹配成功，这时j应该等于len
			if (j == len) {
				next[i] = len;
				break;
			}

		}

		if (len < 1) next[i] = 0; // 如果len = 1的情况都不成立，那么next[i]肯定是0了

	}

}

// 递归求解next数组
void Get_Next2(char P[], int next[]) {

	next[0] = -1;
	next[1] = 0;

	// 此层遍历所有满足的i值
	for (int i = 2; P[i] != '\0'; i++) {

		int k = next[i - 1]; // 取出i前一个位置的next数组值

		if (k == -1) { // 如果前一个next数组值为-1，那么i对应的next数组一定是0
			next[i] = 0;
			continue;
		}
		else {
			// 前一个next数组不为-1
			while (P[i - 1] != P[k] && k != -1) k = next[k];
			if (P[i - 1] == P[k]) next[i] = k + 1; // 走到这里说明匹配成功
			else next[i] = 0;
		}

	}
}


// KMP匹配过程
int KMP_match(char S[], char P[]) {

	// 先求next数组
	int next[MAX_LEN];
	Get_Next2(P, next);

	// KMP匹配过程
	int i = 0, j = 0;
	while (S[i] != '\0' && P[j] != '\0') { // 匹配不结束，循环不会停

		if (S[i] == P[j]) { i++; j++; } // 如果当前字符匹配成功，i和j都往前走
		else {
			// 失败了，就尝试寻找next数组
			j = next[j];
			if (-1 == j) { i++; j++; } // 如果到头了，就选择查找匹配串的下一个位置，同时j = 0
		}
	}

	if (P[j] == '\0') return i - strlen(P); // 到头了，匹配成功
	else return -1;

}

int main() {
	char* s = (char*)"cabadba";
	char* t = (char*)"dba";
	cout << KMP_match(s, t);
	return 0;
}