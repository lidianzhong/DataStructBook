#include<iostream>
#include <cstring>
using namespace std;

#define MAX_LEN 100

// �ǵݹ����next����
void Get_Next1(char P[], int next[]) {
	// next[i]����ⷽ���ǣ��ҵ���t[0]~t[i-1]�Ĺ����ƥ��ǰ׺�ͺ�׺�ĳ���

	next[0] = -1;
	next[1] = 0;

	// ����ѭ����������ж�Ӧ��next[i]ֵ
	for (int i = 2; P[i] != '\0'; i++) {

		// ÿ��Ӧһ��i������������ֵ����

		int max_len = i - 1, len;
		
		// ���������ǰ��׺������len���Դ���ĳ���max_len(i - 1) ��ʼ��һֱ�����Ϊ1
		for (len = max_len; len >= 1; len--) {

			int j;

			// ÿ��Ӧһ�������ǰ��׺len���ж��Ƿ���������
			for (j = 0; j < len; j++)
				if(P[j] != P[i - len + j]) break;

			// �����˳�forѭ��������ƥ��ɹ�����ʱjӦ�õ���len
			if (j == len) {
				next[i] = len;
				break;
			}

		}

		if (len < 1) next[i] = 0; // ���len = 1�����������������ônext[i]�϶���0��

	}

}

// �ݹ����next����
void Get_Next2(char P[], int next[]) {

	next[0] = -1;
	next[1] = 0;

	// �˲�������������iֵ
	for (int i = 2; P[i] != '\0'; i++) {

		int k = next[i - 1]; // ȡ��iǰһ��λ�õ�next����ֵ

		if (k == -1) { // ���ǰһ��next����ֵΪ-1����ôi��Ӧ��next����һ����0
			next[i] = 0;
			continue;
		}
		else {
			// ǰһ��next���鲻Ϊ-1
			while (P[i - 1] != P[k] && k != -1) k = next[k];
			if (P[i - 1] == P[k]) next[i] = k + 1; // �ߵ�����˵��ƥ��ɹ�
			else next[i] = 0;
		}

	}
}


// KMPƥ�����
int KMP_match(char S[], char P[]) {

	// ����next����
	int next[MAX_LEN];
	Get_Next2(P, next);

	// KMPƥ�����
	int i = 0, j = 0;
	while (S[i] != '\0' && P[j] != '\0') { // ƥ�䲻������ѭ������ͣ

		if (S[i] == P[j]) { i++; j++; } // �����ǰ�ַ�ƥ��ɹ���i��j����ǰ��
		else {
			// ʧ���ˣ��ͳ���Ѱ��next����
			j = next[j];
			if (-1 == j) { i++; j++; } // �����ͷ�ˣ���ѡ�����ƥ�䴮����һ��λ�ã�ͬʱj = 0
		}
	}

	if (P[j] == '\0') return i - strlen(P); // ��ͷ�ˣ�ƥ��ɹ�
	else return -1;

}

int main() {
	char* s = (char*)"cabadba";
	char* t = (char*)"dba";
	cout << KMP_match(s, t);
	return 0;
}