#ifndef SPARSEMTX_HEADER_FILE_INCLUDED
#define SPARSEMTX_HEADER_FILE_INCLUDED
#include <stdio.h>
#include <string>
using namespace std;

#ifndef EPSILON
#define EPSILON 0.00000000001
#endif
namespace Sparse {

class ELEM
{
public:
  int row;
  int col;
  double val;
  ELEM()
  {
    row = 0;
    col = 0;
    val = 0;
  }
  ELEM(int i, int j, double d)
  {
    row = i;
    col = j;
    val = d;
  }
  void operator=(ELEM t)
  {
    row = t.row;
    col = t.col;
    val = t.val;
  }
  bool operator<(ELEM t)
  {
    if (row < t.row)
      return true;
    else if (row == t.row && col < t.col) {
      return true;
    } else
      return false;
  }

  bool operator>(ELEM t)
  {
    if (row > t.row)
      return true;
    else if (row == t.row && col > t.col) {
      return true;
    } else
      return false;
  }

  bool operator==(ELEM t)
  {
    if (row == t.row && col == t.col) {
      return true;
    } else {
      return false;
    }
  }

  bool operator!=(ELEM t) { return !(*this == t); }

  bool operator>=(ELEM t) { return (*this > t || *this == t); }

  bool operator<=(ELEM t) { return (*this < t || *this == t); }
};

class Vector
{
public:
  int iNum;
  double* pdData;
  // 构造函数
  Vector(int iDimen)
  {
    iNum = iDimen;
    pdData = new double[iNum];
  }

  // 析构函数
  ~Vector() { delete[] pdData; }
  void Initilize() { memset(pdData, 0, iNum * sizeof(double)); }

  void Initilize(double dVal)
  {
    int i;
    for (i = 0; i < iNum; i++) {
      pdData[i] = dVal;
    }
  }

  double Sum()
  {
    double d = 0.0;
    for (int i = 0; i < iNum; i++) {
      d += pdData[i];
    }
    return d;
  }

  void ShowVector()
  {
    int i;
    for (i = 0; i < iNum; i++) {
      printf("%f ", pdData[i]);
    }
  }
  int SaveVector(char* pchFileName)
  {
    FILE* fp;
    if (NULL == (fp = fopen(pchFileName, "wb"))) {
      printf("Fail to open writen file\n");
      return (-1);
    }

    if (iNum != fwrite(pdData, sizeof(double), iNum, fp)) {
      printf("Error data size\n ");
      return (-1);
    }
    return 0;
  }
};

class SparseMtx
{
  // private:
public:
  int n_rows;
  int n_cols;
  int n_max_ELEM;
  int n_actual_ELEM;
  ELEM* items;

public:
  // 构造函数
  SparseMtx(int rows, int cols, int n_max);

  // 析构函数
  ~SparseMtx() { free(items); }
  // 稀疏矩阵初始化
  void Empty();

  // 矩阵转置
  void Transpose();

  // 添加元素，添加了处理溢出的机制
  bool AddElment(ELEM e);

  // 对元素按行进行一次排序
  void ElemRowSort();

  // 缩减稀疏矩阵存储空间到最低值
  void CutSparMtxMem();

  // 显示函数 for debugging
  void ShowElements();

  // 元素交换
  void MySwap(ELEM& s1, ELEM& s2);

  // 递归快速排序，注意递归算法处理大的数据容易栈溢出
  void QuickSort(ELEM* vec, int low, int high);
  // 保存到文件
  void SaveToFile(char* pchFileName);
};

}
#endif