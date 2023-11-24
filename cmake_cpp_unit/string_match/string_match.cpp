#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <time.h>

using namespace std;
char alphabet[63];
int *NEXT(char *P, int m) { // 预处理函数
  int j = 0;
  int *next;
  next = new int[m];
  for (int i = 1; i <= m; i++) {
    next[i] = j;
    while (j > 0 && P[i] != P[j]) {
      j = next[j];
    }
    j = j + 1;
  }
  return next;
}

int KMP(char *T, char *P, int n, int m, int *next) { // 匹配函数
  int j = 1;
  for (int i = 1; i <= n; i++) {
    while (j > 0 && T[i] != P[j]) {
      j = next[j];
    }
    if (j == m)
      return i - m + 1;
    j++;
  }
  return -1;
}

int qs_bc[63], *p, *t;
void prebc(char *P, int m, char *T, int n) { // 预处理过程

  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= 62; j++) {
      if (P[i] == alphabet[j]) {
        p[i] = j;
        break; // 将char *P映射为int *p
      }
    }
    // cout << p[i]<<endl;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= 62; j++) {
      if (T[i] == alphabet[j]) {
        t[i] = j;
        break; // 将char *T映射为int *t
      }
    }
  }
  for (int i = 1; i <= 62; i++)
    qs_bc[i] = m + 1;
  for (int i = 1; i <= m; i++)
    qs_bc[p[i]] = m + 1 - i;
}

int QS(char *P, int m, char *T, int n) { // 匹配过程
  int j = 1;
  while (j <= n - m + 1) {
    if (memcmp(P + 1, T + j, m) == 0)
      return j;
    j = j + qs_bc[t[j + m]];
  }
  return -1;
}

int d, phash, thash;
void prekr(char *P, int m, char *T, int n) { // 预处理过程
  d = 1;
  phash = 0;
  thash = 0;
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= 62; j++) {
      if (P[i] == alphabet[j]) {
        p[i] = j;
        break;
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= 62; j++) {
      if (T[i] == alphabet[j]) {
        t[i] = j;
        break;
      }
    }
  }
  for (int i = 1; i < m; i++)
    d = d << 1;
  for (int i = 1; i <= m; i++) {
    phash = (phash << 1) + p[i];
    thash = (thash << 1) + t[i];
  }
}

int KR(char *P, int m, char *T, int n) { // 匹配过程
  int j = 1;
  while (j <= n - m + 1) {
    if (phash == thash && memcmp(P + 1, T + j, m) == 0)
      return j;
    thash = ((thash - t[j] * d) << 1) + t[j + m];
    j++;
  }
  return -1;
}

int main(int, char**) {
  std::cout << "Hello, from cmake_unit_test!\n"<<endl;
  for (int i = 0; i < 26; i++) { // 初始化alphabet  a~z
    alphabet[i + 1] = i + 97;
  }
  for (int i = 26; i < 52; i++) { // 初始化alphabet A~Z
    alphabet[i + 1] = i - 26 + 65;
  }
  for (int i = 52; i < 62; i++) { // 初始化alphabet 0~9
    alphabet[i + 1] = i - 52 + 48;
  }

  string str, filename1, filename2, filename3;
  int n = 32, m = 4;
  char *P, *T;
  filename1 = "input/input.txt";
  filename2 = "output/output_";
  stringstream stream;
  int group;
  ofstream strout(filename1);
  srand((unsigned)time(NULL));
  for (group = 1; group <= 5; group++) {
    // group = 1;
    T = new char[n + 2];
    P = new char[m + 2];
    //*生成随机字符串
    int k;
    for (int i = 1; i <= n; i++) {
      k = rand() % 62 + 1;
      T[i] = alphabet[k];
    }
    T[0] = ' ';
    T[n + 1] = '\0';
    for (int i = 1; i <= m; i++) {
      k = rand() % 62 + 1;
      P[i] = alphabet[k];
    }
    P[0] = ' ';
    P[m + 1] = '\0';

    /*测试算法正确的例子
    P = " Lczd";
    T = " 2izvB82Lczdgp4RQXBNam7hz8XVHN0vg";  */

    strout << n << "," << m << "," << T + 1 << "," << P + 1 << ";" << endl;
    stream << group;
    stream >> str;
    filename3 = filename2 + str + ".txt";
    stream.clear();
    ofstream out(filename3);
    out << n << "," << m << endl;

    // kmp

    int *next = NEXT(P, m);

    int result = KMP(T, P, n, m, next);

    out << "KMP:" << result << endl;

    // quick search
    p = new int[m + 1];
    t = new int[n + 1];

    prebc(P, m, T, n);

    result = QS(P, m, T, n);

    out << "quick_search:" << result << endl;

    // karp-rabin

    prekr(P, m, T, n);

    result = KR(P, m, T, n);

    out << "Karp_Rabin:" << result << endl;
    n *= 8;
    m *= 2; // next T,P
    out.close();
  }

  strout.close();
  std::cout << "end, from string_match_unit_test!\n";
  return 0;
}
