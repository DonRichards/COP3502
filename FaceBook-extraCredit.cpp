/**
Donald Richards
Facebook Hacker Cup 2014 Challenge
Basketball Game
11/22/2013

You want to write an image detection system that is able to recognize different geometric shapes. In the first version of the system you settled with just being able to detect filled squares on a grid.

You are given a grid of N×N square cells. Each cell is either white or black. Your task is to detect whether all the black cells form a square shape.

Input:
The first line of the input consists of a single number T, the number of test cases.

Each test case starts with a line containing a single integer N. Each of the subsequent N lines contain N characters. Each character is either "." symbolizing a white cell, or "#" symbolizing a black cell. Every test case contains at least one black cell.

Output:
For each test case i numbered from 1 to T, output "Case #i: ", followed by YES or NO depending on whether or not all the black cells form a completely filled square with edges parallel to the grid of cells.

Constraints
1 ≤ T ≤ 20
1 ≤ N ≤ 20

*/

#include <iostream>
#include <cstdio>

using namespace std;
typedef long long int ll;

int main() {
    int t;
    scanf("%d", &t);

    for (int c = 1; c <= t; c++) {
        int x0, y0, x1, y1, n;
        bool found = false;
        bool valid = true;

        scanf("%d", &n);

        char board[n][n];

        for (int i = 0; i < n; i++) {
            scanf(" %s", board[i]);
        }//END OF SCANF n

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == '#') {
                    if (!found) {
                        found = true;
                        x0 = i;
                        y0 = j;
                        }// END IF NOT FOUND
                x1 = i;
                y1 = j;
                }//END OF BOARD EXIST
            }// END OF NESTED FOR J
        }// END OF FOR i < n

        valid = x1 - x0 == y1 - y0;

        for (int i = x0; i <= x1 && valid; i++) {
            for (int j = y0; j <= y1 && valid; j++) {
                valid = board[i][j] == '#';
                }
            }// END OF i <= x1 && VALID

        printf("Case #%d: %s\n", c, valid ? "YES" : "NO");
        }// END OF FOR c

    return 0;
}// END OF MAIN
