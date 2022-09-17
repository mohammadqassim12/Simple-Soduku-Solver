/**
 * Exercise 11 - Simple Sudoku Solver
 *
 * Please read the comments below carefully, they describe your task in detail.
 * Any clarifications and corrections will be posted to Piazza so please keep
 * an eye on the forum!
 *
 * Starter code: Mustafa Quraish, 2020
 */

#include <stdio.h>

#ifndef __testing__
/**
 * Prints out the sudoku in an easy-to-view format. Feel free to change
 * this function if you need to help you debug.
 */
void print_sudoku(int sudoku[9][9])
{
  printf("The Sudoku contains:\n");
  printf("+-------+-------+-------+\n");
  for (int j = 0; j < 9; j++)
  {
    printf("| ");
    for (int i = 0; i < 9; i++)
    {
      printf("%d ", sudoku[j][i]);
      if (i % 3 == 2)
        printf("| ");
    }
    printf("\n");
    if (j % 3 == 2)
      printf("+-------+-------+-------+\n");
  }
}
#endif

/*****************************************************************************/
int v_row(int sudoku[9][9], int row, int num){
    int counter =0;
    for (int j=0; j<9; j++){
        if (sudoku[row][j]==num){
            counter++;
        }
    }

    return counter;
  }
int v_col(int sudoku[9][9], int col, int num){
    int counter =0;
    for (int i=0; i<9; i++){
        if (sudoku[i][col]==num){
            counter++;
        }
    }

    return counter;
}
int v_square(int sudoku[9][9], int startrow, int startcol, int num){
  int row=0;
  int col=0;
  if ((startrow>=0) && (startrow<=2))
  {
    row = 0;
  }
  else if ((startrow>=3) && (startrow<=5))
  {
    row = 3;
  }
  else if ((startrow>=6) && (startrow<=8))
  {
    row = 6;
  }
  if ((startcol>=0) && (startcol<=2))
  {
    col = 0;
  }
  else if ((startcol>=3) && (startcol<=5))
  {
    col = 3;
  }
  else if ((startcol>=6) && (startcol<=8))
  {
    col = 6;
  }
  int counter=0;
  for (int i=row; i<row+3; i++)
  {
    for (int j=col; j<col+3; j++)
    {
        if (sudoku[i][j]==num)
        {
            counter++;
        }
      }
  
}
  return counter;
}

/**
 * This function checks if the current sudoku grid (not necessarily
 * complete) is valid. This means that (ignoring the 0s), each row, column
 * and 3x3 subgrid should not repeat any digits 1-9.
 *
 * Returns 1 if the sudoku is valid, or 0 if it's not.
 */
int is_valid_sudoku(int sudoku[9][9])
{
    for (int i=0; i<9;i++){
         for (int j=0; j<9; j++){
             if (sudoku[i][j] !=0) {
                 if ((v_square(sudoku, i, j, sudoku[i][j]) > 1) || (v_col(sudoku, j, sudoku[i][j])>1) || (v_row(sudoku, i, sudoku[i][j])>1)){
                     return 0;
         }
         }
      }
    }
  return 1; // Fix this to return the correct value!
}

/**
 * Given a (possibly partially) completed sudoku grid, try and solve the
 * sudoku. The `sudoku` array should be changed to contain the solution if
 * one exists. None of digits in the input grid should be changed.
 * 
 * NOTE: The empty spots are denoted with 0s in them.
 *
 * Refer to the handout for more discussion on how to implement this.
 *
 * Return 1 if the sudoku was solved, and update the `sudoku` parameter.
 * Return 0 if it's not possible to solve the sudoku, and leave the input
 *    `sudoku` array unchanged in this case.
 */
/// helper
int solved(int sudoku[9][9])
{
    for (int i=0; i<9; i++){
        for (int j=0; j<9; j++){
            if (sudoku[i][j]==0 || (v_square(sudoku, i, j, sudoku[i][j]) != 1) || (v_col(sudoku, j, sudoku[i][j])!=1) || (v_row(sudoku, i, sudoku[i][j])!=1)){
                return 0;
            }
        }
    }
    return 1;
}

int emp_col(int sudoku[9][9]){
    for (int i=0; i<9; i++){
        for (int j=0; j<9; j++){
            if (sudoku[i][j]==0){
                return j;
            }
        }
    }
    return -1;
}

int emp_row(int sudoku[9][9]){
    for (int i=0; i<9; i++){
        for (int j=0; j<9; j++){
            if (sudoku[i][j]==0){
                return i;
            }
        }
    }
    return -1;
}

int solve_sudoku(int sudoku[9][9])
{
    if (solved(sudoku) ==1)
    {
        return 1;
    }
    int a_row = emp_row(sudoku);
    int a_col = emp_col(sudoku);
    
    
    for (int n = 1; n <= 9; n++)
    {
        if ((v_col(sudoku, a_col, n) == 0) && (v_row(sudoku, a_row, n) == 0) && (v_square(sudoku, a_row, a_col, n) == 0))
        {
            sudoku[a_row][a_col] = n;
            int next_row = emp_row(sudoku);
            int next_col = emp_col(sudoku);
            solve_sudoku(sudoku);
            if (solved(sudoku) == 1)
            {
                return 1;
            }
            sudoku[next_row][next_col] = 0;
        }
    }
    if (sudoku[a_row][a_col] == 0)
    {
        return 0;
    }
    return 0;
}

#ifndef __testing__

int main()
{
  /**
   * This example is the one from the Wiki, but your solution should be able
   * to handle any solvable sudoku. The time to solve different puzzles may
   * vary, but ideally it should not take more than a second for this one.
   */

  int sudoku_grid[9][9] = {
      {5, 3, 0, 0, 7, 0, 0, 0, 0},
      {6, 0, 0, 1, 9, 5, 0, 0, 0},
      {0, 9, 8, 0, 0, 0, 0, 6, 0},
      {8, 0, 0, 0, 6, 0, 0, 0, 3},
      {4, 0, 0, 8, 0, 3, 0, 0, 1},
      {7, 0, 0, 0, 2, 0, 0, 0, 6},
      {0, 6, 0, 0, 0, 0, 2, 8, 0},
      {0, 0, 0, 4, 1, 9, 0, 0, 5},
      {0, 0, 0, 0, 8, 0, 0, 7, 9}};

  print_sudoku(sudoku_grid);

  int solved = solve_sudoku(sudoku_grid);

  printf("\nsolve_sudoku() return value: %d\n\n", solved);

  /* Look at the handout to see the solution for this! */
  print_sudoku(sudoku_grid);

  return 0;
}

#endif
