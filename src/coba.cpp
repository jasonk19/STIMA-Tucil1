#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int main() {
  string greeting = "HELLO";

  reverse(greeting.begin(), greeting.end());

  cout << greeting << endl;
}

// GUDANG

  // Diagonal Matching
  // locRow = 0;
  // locCol = 0;
  // while (locRow <= row - m && locCol <= col - m && !found) {
  //   iter = 0;
  //   while (iter < m && P[iter] == Elem(T, locRow + iter, locCol + iter)) {
  //     iter++;
  //   }

  //   if (iter == m) {
  //     found = true;
  //     for (int i = 0; i < row; i++) {
  //       for (int j = 0; j < col; j++) {
  //         if (i != j) {
  //           Elem(T,i,j) = '-';
  //         }
  //         if (i < locRow && j < locCol) {
  //           Elem(T,i,j) = '-';
  //         }
  //         if (i >= locRow + m && j >= locCol + m) {
  //           Elem(T,i,j) = '-';
  //         }
  //       }
  //     }
  //   } else {
  //     locRow++;
  //     locCol++;
  //   }
  // }