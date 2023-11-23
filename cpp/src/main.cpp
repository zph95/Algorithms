#include <fstream>
#include <iostream>
#include <string.h>
#include <time.h>

#define N 729  // 数据规模3^2
#define MAX 16 // 字符串最大长度
using namespace std;

char alphabet[26];

struct str {
  int length;          // 存放字符串长度
  int string[MAX + 1]; // 字符串数组
} A[N], B[N]; // A为随机生成的字符串数据，B为排序后的字符串数据

void output(str b[]) { // 输出字符串数据
  long i;
  int j;
  for (i = 0; i < N; i++) {
    for (j = 0; j < b[i].length; j++) {
      cout << alphabet[b[i].string[j]];
    }
    cout << ' ';
  }
}

void stringcopy(str a[], str b[]) { // 将A的数据拷贝给B
  long i;
  int j;
  for (i = 0; i < N; i++) {
    b[i].length = a[i].length;
    for (j = 0; j < a[i].length; j++) {
      b[i].string[j] = a[i].string[j];
    }
  }
}

void copy(str &a, str &b) { // 将元素b赋值给a
  a.length = b.length;
  for (long i = 0; i < a.length; i++) {
    a.string[i] = b.string[i];
  }
}

int compare(str a, str b) { // 比较str a,b；a<b 返回1，否则返回0；
  if (a.length < b.length)
    return 1;
  else if (a.length > b.length)
    return 0;
  else
    for (int i = 0; i < a.length; i++) {
      if (a.string[i] < b.string[i])
        return 1;
      else if (a.string[i] > b.string[i])
        return 0;
    }
  return 0;
}

void sort1();
void sort2();
void sort3();
void sort4();
void sort5();

int main(int argc, char *argv[]) {
  std::cout << "Hello world!" << std::endl;

  int i;
  long j;
  for (i = 0; i < 26; i++) { // 初始化alphabet
    alphabet[i] = toascii(i + 97);
  }
  /*	ofstream strout("input_strings.txt");
  srand((unsigned)time(NULL));
  for (j = 0; j < N; j++) {
          int length = rand() % MAX + 1;
          A[j].length = length;
          for (i = 0; i < length; i++) {
                  A[j].string[i] = rand() % 26;
                  strout << alphabet[A[j].string[i]];
          }
          strout << endl;
  }
  cout << "string ok" << endl;
  */
  char temp[17];
  ifstream in("input_strings.txt");
  for (j = 0; j < N; j++) {
    in >> temp;
    A[j].length = strlen(temp); // cout << A[j].length;
    for (i = 0; i < A[j].length; i++) {
      A[j].string[i] = temp[i] - 'a';
    }
  }
  in.close();

  for (i = 1; i <= 5; i++) {

    stringcopy(A, B);
    switch (i) {
    case 1: {
      sort1(); // output(B); cout << endl;

      ofstream out("直接插入排序result.txt");
      for (j = 0; j < N; j++) {
        for (int k = 0; k < B[j].length; k++) {
          out << alphabet[B[j].string[k]];
        }
        out << endl;
      }
      out.close();
      break;
    }
    case 2: {
      sort2(); // output(B); cout << endl;

      ofstream out("归并排序result.txt");
      for (j = 0; j < N; j++) {
        for (int k = 0; k < B[j].length; k++) {
          out << alphabet[B[j].string[k]];
        }
        out << endl;
      }
      out.close();
      break;
    }
    case 3: {
      sort3(); // output(B); cout << endl;

      ofstream out("快速排序result.txt");
      for (j = 0; j < N; j++) {
        for (int k = 0; k < B[j].length; k++) {
          out << alphabet[B[j].string[k]];
        }
        out << endl;
      }
      out.close();
      break;
    }
    case 4: {
      sort4(); // output(B); cout << endl;

      ofstream out("堆排序result.txt");
      for (j = 0; j < N; j++) {
        for (int k = 0; k < B[j].length; k++) {
          out << alphabet[B[j].string[k]];
        }
        out << endl;
      }
      out.close();
      break;
    }
    case 5: {
      sort5(); // output(B); cout << endl;

      ofstream out("SHELL排序result.txt");
      for (j = 0; j < N; j++) {
        for (int k = 0; k < B[j].length; k++) {
          out << alphabet[B[j].string[k]];
        }
        out << endl;
      }
      out.close();
      break;
    }
    default:
      break;
    }
  }
  return 0;
}

void sort1() { // 直接插入排序
  long i, j;
  str temp;
  temp.length = 1;
  temp.string[0] = 0;
  for (j = 1; j < N; j++) {
    copy(temp, B[j]);
    i = j - 1;
    while (i >= 0 && compare(temp, B[i])) {
      copy(B[i + 1], B[i]);
      i--;
    }
    copy(B[i + 1], temp);
  }
}

void merge(long p, long q, long r) {
  str *temp;
  temp = new str[N];
  long i = p, j = q + 1;
  long m = q, n = r;
  long k = 0;
  while (i <= m && j <= n) {
    if (compare(B[i], B[j]))
      copy(temp[k++], B[i++]);
    else
      copy(temp[k++], B[j++]);
  }
  while (i <= m)
    copy(temp[k++], B[i++]);

  while (j <= n)
    copy(temp[k++], B[j++]);

  for (i = 0; i < k; i++)
    copy(B[p + i], temp[i]);
  free(temp);
}

void mergesort(long p, long r) {
  if (p < r) {
    long q = (p + r) / 2;
    mergesort(p, q);
    mergesort(q + 1, r);
    merge(p, q, r);
    // cout << q << endl;
  }
}

void sort2() { // 归并排序
  mergesort(0, N - 1);
}

long partition(long p, long r) {
  str x;
  copy(x, B[r]);
  str temp;
  long i = p - 1;
  for (long j = p; j < r; j++) {
    if (compare(B[j], x)) {
      i = i + 1;
      copy(temp, B[i]);
      copy(B[i], B[j]);
      copy(B[j], temp);
    }
  }
  copy(temp, B[i + 1]);
  copy(B[i + 1], B[r]);
  copy(B[r], temp);
  return i + 1;
}
void quicksort(long p, long r) {
  if (p < r) {
    long q = partition(p, r);
    quicksort(p, q - 1);
    quicksort(q + 1, r);
  }
}

void sort3() { // 快速排序
  quicksort(0, N - 1);
}

int PARENT(int i) { return (i - 1) / 2; }
int LEFT(int i) { return 2 * i + 1; }
int RIGHT(int i) { return 2 * i + 2; }

long heap_size = N;
void MAX_HEAPIFY(long i) {
  long largest = 0;
  long L = LEFT(i);
  long R = RIGHT(i);
  str temp;

  if (L < heap_size && compare(B[i], B[L])) {
    largest = L;
  } else
    largest = i;
  if (R < heap_size && compare(B[largest], B[R])) {
    largest = R;
  }
  if (largest != i) {
    copy(temp, B[largest]);
    copy(B[largest], B[i]);
    copy(B[i], temp);
    MAX_HEAPIFY(largest);
  }
}

void sort4() { // 堆排序
  long i;
  str temp;
  for (i = N / 2; i >= 0; i--) // 建堆
  {
    MAX_HEAPIFY(i);
  }
  for (int i = N - 1; i >= 0; i--) {
    copy(temp, B[i]);
    copy(B[i], B[0]);
    copy(B[0], temp);
    heap_size--;
    MAX_HEAPIFY(0);
  }
}

void sort5() { // 希尔排序
  long i, j, gap;
  int k;
  for (k = 5; k > 0; k--)
    switch (k) { // 希尔增量
    case 1: {
      gap = 1;
      break;
    }
    case 2: {
      gap = 3;
      break;
    }
    case 3: {
      gap = 7;
      break;
    }
    case 4: {
      gap = 15;
      break;
    }
    case 5: {
      gap = 21;
      break;
    }
    }
  for (i = 0; i < gap; i++) // 直接插入排序
  {
    for (j = i + gap; j < N; j += gap)
      if (compare(B[j], B[j - gap])) {
        str temp;
        copy(temp, B[j]);
        long k = j - gap;
        while (k >= 0 && compare(temp, B[k])) {
          copy(B[k + gap], B[k]);
          k -= gap;
        }
        copy(B[k + gap], temp);
      }
  }
}
