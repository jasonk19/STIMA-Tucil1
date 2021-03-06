#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <bits/stdc++.h>
#include <time.h>
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
void PencocokanString(Matrix T, string P, int *perbandinganHuruf)
{
  int col = getCol(T);
  int row = getRow(T);
  int m = P.length();

  int locRow, locCol;
  int iter;
  bool found;

  found = false;
  // Horizontal Matching
  if (!found) {
    locRow = 0;
    locCol = 0;
    for (int i = 0; i < row; i++) {
      locCol = 0;
      while (locCol <= col - m && !found) {
        iter = 0;
        while (iter < m && P[iter] == Elem(T, i, locCol + iter)) {
          iter++;
          *perbandinganHuruf += 1;
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
          *perbandinganHuruf += 1;
        }
      }
    }

  }

  // Alternate Horizonal Matching
  if (!found) {
    locRow = 0;
    locCol = col - 1;
    for (int i = 0; i < row; i++) {
      locCol = col - 1;
      while (locCol >= m - 1 && !found) {
        iter = 0;
        while (iter < m && P[iter] == Elem(T, i, locCol - iter)) {
          iter++;
          *perbandinganHuruf += 1;
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
                if (j > locCol) {
                  Elem(T,i,j) = '-';
                }
                if (j <= locCol - m) {
                  Elem(T,i,j) = '-';
                }
              }
            }
          }
        } else {
          locCol--;
          *perbandinganHuruf += 1;
        }
      }
    }

  }

  // Vertical Matching
  if (!found) {
    locCol = 0;
    while (locCol < col) {
      locRow = 0;
      while (locRow <= row - m && !found) {
        iter = 0;
        while (iter < m && P[iter] == Elem(T, locRow + iter, locCol)) {
          iter++;
          *perbandinganHuruf += 1;

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
          *perbandinganHuruf += 1;

        }
      }
      locCol++;
    }

  }

  // Alternate Vertical Matching
  if (!found) {
    locCol = 0;
    locRow = row - 1;
    while (locCol < col) {
      locRow = row - 1;
      while (locRow >= m - 1 && !found) {
        iter = 0;
        while (iter < m && P[iter] == Elem(T, locRow - iter, locCol)) {
          iter++;
          *perbandinganHuruf += 1;

        }

        if (iter == m) {
          found = true;
          for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
              if (j != locCol) {
                Elem(T,i,j) = '-';
              }
              if (j == locCol) {
                if (i > locRow) {
                  Elem(T,i,j) = '-';
                }
                if (i <= locRow - m) {
                  Elem(T,i,j) = '-';
                }
              }
            }
          }
        } else {
          locRow--;
          *perbandinganHuruf += 1;

        }
      }
      locCol++;
    }

  }

  // Row Major Diagonal Matching
  if (!found) {
    locRow = 0;
    locCol = 0;
    while (locRow < row) {
      locCol = 0;
      while (locCol <= col - m && !found) {
        iter = 0;
        while (iter < m && P[iter] == Elem(T, locRow + iter, locCol + iter)) {
          iter++;
          *perbandinganHuruf += 1;

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
          *perbandinganHuruf += 1;

        }
      }
      locRow++;
    }

  }


  // Alternate Row Major Diagonal Matching
  if (!found) {
    locRow = 0;
    locCol = col - 1;
    while (locRow < row) {
      locCol = col - 1;
      while (locCol >= m - 1 && !found) {
        iter = 0;
        while (iter < m && P[iter] == Elem(T, locRow + iter, locCol - iter)) {
          iter++;
          *perbandinganHuruf += 1;

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
          *perbandinganHuruf += 1;

        }
      }
      locRow++;
    }
  }

  // Column Major Diagonal Matching
  if (!found) {
    locRow = 0;
    locCol = 0;
    while (locCol < col) {
      locRow = 0;
      while (locRow <= row - m && !found) {
        iter = 0;
        while (iter < m && P[iter] == Elem(T, locRow + iter, locCol + iter)) {
          iter++;
          *perbandinganHuruf += 1;
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
          locRow++;
          *perbandinganHuruf += 1;
        }
      }
      locCol++;
    }
  }

  // Alternate Column Major Diagonal Matching
  if (!found) {
    locRow = row - 1;
    locCol = 0;
    while (locCol < col) {
      locRow = row - 1;
      while (locRow >= m - 1 && !found) {
        iter = 0;
        while (iter < m && P[iter] == Elem(T, locRow - iter, locCol + iter)) {
          iter++;
          *perbandinganHuruf += 1;
        }
        if (iter == m) {
          found = true;
          for (int i = 0; i < row; i++) {
            for (int j = col - 1; j >= 0; j--) {
              if (j < locCol) {
                Elem(T,i,j) = '-';
              }
              if (i > locRow) {
                Elem(T,i,j) = '-';
              }
              if (j >= locCol + m) {
                Elem(T,i,j) = '-';
              }
              if (i <= locRow - m) {
                Elem(T,i,j) = '-';
              }
              for (int k = 0; k < m; k++) {
                if (i < locRow - k && j <= locCol + k) {
                  Elem(T,i,j) = '-';
                }
                if (i == locRow - k && j > locCol + k) {
                  Elem(T,i,j) = '-';
                }
              }
            }
          }
        } else {
          locRow--;
          *perbandinganHuruf += 1;
        }
      }
      locCol++;
    }
  }

  // Diagonal checking from bottom right
  if (!found) {
    locRow = row - 1;
    locCol = col - 1;
    while (locCol >= 0) {
      locRow = row - 1;
      while (locRow >= m - 1 && !found) {
        iter = 0;
        while (iter < m && P[iter] == Elem(T, locRow - iter, locCol - iter)) {
          iter++;
          *perbandinganHuruf += 1;
        }

        if (iter == m) {
          found = true;
          for (int i = 0; i < row; i++) {
            for (int j = col - 1; j >= 0; j--) {
              if (j > locCol) {
                Elem(T,i,j) = '-';
              }
              if (i > locRow) {
                Elem(T,i,j) = '-';
              }
              if (j <= locCol - m) {
                Elem(T,i,j) = '-';
              }
              if (i <= locRow - m) {
                Elem(T,i,j) = '-';
              }
              for (int k = 0; k < m; k++) {
                if (i < locRow - k && j == locCol - k) {
                  Elem(T,i,j) = '-';
                }
                if (i == locRow - k && j < locCol - k) {
                  Elem(T,i,j) = '-';
                }
              }
            }
          }
        } else {
          locRow--;
          *perbandinganHuruf += 1;
        }
      }
      locCol--;
    }
  }

  if (found) {
    displayMat(T);
    cout << endl;
    cout << "-----------------------ENDLINE-----------------------" << endl << endl;
  }
}

/*** MAIN FUNCTION ***/

int main()
{

  Matrix m;
  List l;
  int perbandinganHuruf = 0;

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

  cout << "-----------------------RESULT-----------------------" << endl << endl;

  clock_t start = clock();

  for (int i = 0; i < getLength(l); i++) {
    PencocokanString(m, ListElem(l,i), &perbandinganHuruf);
  }

  cout << "-----------------------CONCLUSION-----------------------" << endl << endl;

  cout << "Total number of letter comparison: " << perbandinganHuruf << " times" << endl;
  cout << "Execution Time of the program with Result Printing : ";
  cout.precision(10);
  cout << fixed << float(clock() - start) / CLOCKS_PER_SEC << "s" << endl;

  return 0;
}