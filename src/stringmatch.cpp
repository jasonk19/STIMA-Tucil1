#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <bits/stdc++.h>
#include <chrono>
using namespace std;

#define MAX 100

typedef struct
{
  char contents[MAX][MAX];
  int rowEff;
  int colEff;
} Matrix;

typedef struct
{
  string patterns[MAX];
  int length;
} List;

#define LENGTH(L) (L).length
#define ListElem(L, i) (L).patterns[i]

#define ROWS(M) (M).rowEff
#define COLS(M) (M).colEff
#define Elem(M, i, j) (M).contents[(i)][(j)]


/*** KONSTRUKTOR ***/
void createMat(Matrix *m)
{
  for (int i = 0; i < MAX; i++)
  {
    for (int j = 0; j < MAX; j++)
    {
      Elem(*m, i, j) = '#';
    }
  }
}

void createList(List *l)
{
  for (int i = 0; i < MAX; i++)
  {
    ListElem(*l, i) = "*";
  }
}

/*** FUNGSI/PROSEDUR PENDUKUNG ***/
int getLength(List l)
{
  int count = 0;
  for (int i = 0; i < MAX; i++)
  {
    if (ListElem(l, i) != "*")
    {
      count++;
    }
  }
  return count;
}

void displayList(List l)
{
  for (int i = 0; i < getLength(l); i++)
  {
    cout << ListElem(l, i) << endl;
  }
}

int getRow(Matrix m)
{
  int count = 0;
  for (int i = 0; i < MAX; i++)
  {
    if (Elem(m, i, 0) == '#')
    {
      break; 
    }
    count++;
  }
  return count;
}

int getCol(Matrix m)
{
  int count = 0;
  for (int j = 0; j < MAX; j++)
  {
    if (Elem(m, 0, j) != '#')
    {
      count++;
    }
  }
  return count;
}

void displayMat(Matrix m)
{
  for (int i = 0; i < getRow(m); i++)
  {
    for (int j = 0; j < getCol(m); j++)
    {
      cout << Elem(m, i, j) << " ";
    }
    cout << endl;
  }
}

void readFileBox(string filename, Matrix *m) {
  vector<vector<char> > text;
  ifstream myfile;
  myfile.open(filename.c_str());
  string line;

  while (getline(myfile, line))
  {
    vector<char> textData;
    stringstream lineStream(line);

    char value;
    while (lineStream >> value)
    {
      textData.push_back(value);
    }

    text.push_back(textData);
  }
  int index;
  for (int i = 0; i < text.size(); i++)
  {
    for (int j = 0; j < text[i].size(); j++)
    {
      Elem(*m, i, j) = text[i][j];
    }
  }

}

void readFile(string filename, List *l)
{
  vector<vector<string> > text;
  ifstream myfile;
  myfile.open(filename.c_str());
  string line;

  while (getline(myfile, line))
  {
    vector<string> textData;
    stringstream lineStream(line);

    string value;
    while (lineStream >> value)
    {
      textData.push_back(value);
    }

    text.push_back(textData);
  }
  int index;
  for (int i = 0; i < text.size(); i++)
  {
    for (int j = 0; j < text[i].size(); j++)
    {
      ListElem(*l, i) = text[i][0];
    }
  }

}

List fixList(List l) {
  List lf;
  createList(&lf);
  int idx;
  for (int i = 0; i < getLength(l); i++) {
    if (ListElem(l,i) == "*") {
      idx = i;
    }
  }

  idx = idx + 1;
  int k = 0;
  for (int i = idx; i < getLength(l) + 1; i++) {
    ListElem(lf,k) = ListElem(l, i);
    k++;
  }

  return lf;
}

/*** PROSEDUR/FUNGSI STRING MATCHING ***/
void PencocokanString(Matrix T, string P)
{
  int col = getCol(T);
  int row = getRow(T);
  int m = P.length();

  int locRow, locCol;
  int iter;
  bool found;
  int countLetter; // Variabel untuk menghitung jumlah perbandingan huruf

  found = false;
  // Horizontal Matching
  if (!found) {
    countLetter = 0;
    for (int i = 0; i < row; i++) {
      locCol = 0;
      while (locCol <= col - m && !found) {
        iter = 0;
        while (iter < m && P[iter] == Elem(T, i, locCol + iter)) {
          iter++;
          countLetter++;
        }

        if (iter == m) {
          found = true;
          locRow = i;
          for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
              if (i != locRow) {
                Elem(T,i,j) = '-';
              }
              if (i == locRow) {
                if (j < locCol) {
                  Elem(T,i,j) = '-';
                }
                if (j >= m + locCol) {
                  Elem(T, i, j) = '-';
                }
              }
            }
          }
        } else {
          locCol++;
          countLetter++;
        }
      }
    }

  }

  // Vertical Matching
  if(!found) {
    locCol = 0;
    countLetter = 0;
    while (locCol < col) {
      locRow = 0;
      while (locRow <= row - m && !found) {
        iter = 0;
        while (iter < m && P[iter] == Elem(T, locRow + iter, locCol)) {
          iter++;
          countLetter++;

        }

        if (iter == m) {
          found = true;
          for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
              if (j != locCol) {
                Elem(T,i,j) = '-';
              }
              if (j == locCol) {
                if (i < locRow) {
                  Elem(T,i,j) = '-';
                }
                if (i >= m + locRow) {
                  Elem(T,i,j) = '-';
                }
              }
            }
          }
        } else {
          locRow++;
          countLetter++;

        }
      }
      locCol++;
    }

  }

  // Row Major Diagonal Matching
  if (!found) {
    locRow = 0;
    locCol = 0;
    countLetter = 0;
    while (locRow <= row - m) {
      locCol = 0;
      while (locCol <= col - m && !found) {
        iter = 0;
        while (iter <= m && P[iter] == Elem(T, locRow + iter, locCol + iter)) {
          iter++;
          countLetter++;

        }
        if (iter == m) {
          found = true;
          for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
              if (i < locRow) {
                Elem(T,i,j) = '-';
              }
              if (j < locCol) {
                Elem(T,i,j) = '-';
              }
              if (i >= locRow + m) {
                Elem(T,i,j) = '-';
              }
              if (j >= locCol + m) {
                Elem(T,i,j) = '-';
              }
              for (int k = 0; k < m; k++) {
                if (i > locRow + k && j <= locCol + k) {
                  Elem(T,i,j) = '-';
                }
                if (i <= locRow + k && j > locCol + k) {
                  Elem(T,i,j) = '-';
                }
              }
            }
          }
        } else {
          locCol++;
          countLetter++;

        }
      }
      locRow++;
    }

  }


  // Alternate Row Major Diagonal Matching
  if (!found) {
    countLetter = 0;
    locRow = 0;
    locCol = col - 1;
    while (locRow <= row - m) {
      locCol = col - 1;
      while (locCol >= col - m && !found) {
        iter = 0;
        while (iter <= m && P[iter] == Elem(T, locRow + iter, locCol - iter)) {
          iter++;
          countLetter++;

        }

        if (iter == m) {
          found = true;
          for (int i = 0; i < row; i++) {
            for (int j = col - 1; j >= 0; j--) {
              if (i < locRow) {
                Elem(T,i,j) = '-';
              }
              if (j > locCol) {
                Elem(T,i,j) = '-';
              }
              if (j <= locCol - m) {
                Elem(T,i,j) = '-';
              }
              if (i >= locRow + m) {
                Elem(T,i,j) = '-';
              }
              for (int k = 0; k < m; k++) {
                if (i > locRow + k && j == locCol - k) {
                  Elem(T,i,j) = '-';
                }
                if (i == locRow + k && j < locCol - k) {
                  Elem(T,i,j) = '-';
                }
              }
            }
          }
        } else {
          locCol--;
          countLetter++;

        }
      }
      locRow++;
    }
  }

  // Karena Pencarian Diagonal berdasarkan row major dan column major dan diagonal utama hasilnya sama jadi cukup berdasarkan row major saja.

  if (found) {
    displayMat(T);
    cout << endl;
    cout << "Total Perbandingan Huruf : " << countLetter << endl << endl;
    cout << "-----------------------ENDLINE-----------------------" << endl << endl;

  }
}

/*** MAIN FUNCTION ***/

int main()
{

  time_t start, end; // Inisiasi Waktu Eksekusi

  Matrix m;
  List l;

  createList(&l);

  createMat(&m);

  string namaFile;

  cout << "Masukkan nama file (*.txt) : ";
  cin >> namaFile;

  readFile("../test/" + namaFile + ".txt", &l);
  readFileBox("../test/" + namaFile + ".txt", &m);

  l = fixList(l);

  cout << "-----------------------WORD BOX-----------------------" << endl;
  displayMat(m);
  cout << "-----------------------WORD CHOICES-----------------------" << endl;
  displayList(l);

  cout << "-----------------------RESULT-----------------------" << endl;

  for (int i = 0; i < getLength(l); i++) {
    PencocokanString(m, ListElem(l,i));
  }

  for (int i = 0; i < getLength(l); i++) {
    string reversedString = ListElem(l,i);
    reverse(reversedString.begin(), reversedString.end());
    PencocokanString(m, reversedString);
  }

  cout << "-----------------------EXECUTION TIME-----------------------" << endl;


  return 0;
}