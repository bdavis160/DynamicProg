/*
author:           Ben Davis
date:             2020-08-05
description:      solves the dynamic programming problems of rod-cutting,
                  minimum sum descent, and n choose k
*/
#include <stdio.h>

int BOARD[100][100];
int OUTS[100][100];

/*initialize given arrays to -1*/
void init(int size)
{
  for(int i = 0; i < size; ++i)
    for(int j = 0; j < size; ++j)
      OUTS[i][j] = -1;
}

/*initializes to given set of values*/
void init_board(int size)
{
  int triangle_cols = 1;

  for(int i = 0; i < size; ++i)
  {
      for(int j = 0; j < triangle_cols; ++j)
      {
        scanf("%d", &(BOARD[i][j]));
      }
      
      triangle_cols = triangle_cols + 1;
  }
}

/*helper to return the minimum of two integers*/
int min(int a, int b)
{
  if(a >= b)
    return b;
  else
    return a;
}

double max(double a, double b)
{
  if(a >= b)
    return a;
   else
     return b;
}

/*returns the minimum value from an array*/
int min_val(int arr[], int size)
{
  if(size < 1)
    return -1;

  int min = arr[0];

  for(int i = 1; i < size; ++i)
  {
    if(arr[i] < min)
      min = arr[i];
  }

  return min;
    
}

double max_val(double arr[], int size)
{

  if(size < 1)
    return -1;

  double max = arr[1];

  for(int i = 2; i < size; ++i)
  {
    if(arr[i] > max)
      max = arr[i];
  }

  return max;
}

/*initializes the prices for up to the given rod size*/
void init_prices(int rod_len)
{

}

/* a tabular solution to the rod-cutting problem */
double solve_rod(int rod_len, double prices[], int size)
{
  if(size < rod_len)
    return -1;

  double price_per_size[rod_len+1]; //we are going to start at index 1

  price_per_size[0] = 0;
  price_per_size[1] = rod_len * prices[1];

  for(int i = 2; i < rod_len+1; ++i)
  {
    //calculate 
    price_per_size[i] = ((rod_len/i)*prices[i]);
    
    if(rod_len % i == 1)
      price_per_size[i] = price_per_size[i] + (prices[1]*(rod_len%i));

    if(rod_len%i > 1) //we need to choose the most valuable way to split the remainder of the rod
    {
      price_per_size[i] = price_per_size[i] + solve_rod(rod_len%i, prices, size);
    }
  }

  return max_val(price_per_size, rod_len); 
}

/* a tabular solution to the minimum sum descent problem */
int solve_sum_descent(int size)
{
  if(size < 1)
    return -1;
  
  if(size < 2)
    return BOARD[0][0];
  
  //Generate initial output values
  OUTS[0][0] = BOARD[0][0];
  OUTS[1][0] = OUTS[0][0] + BOARD[1][0];
  OUTS[1][1] = OUTS[0][0] + BOARD[1][1];
  
  //we already know the answer don't go further
  if(size == 2)
    return min(OUTS[1][0], OUTS[1][1]);

  int num_cols = 3;
  for(int i = 2; i < size; ++i)
  {
    for(int j = 0; j < num_cols; ++j)
    {
      if(j == 0)
      {
        OUTS[i][j] = OUTS[i-1][j] + BOARD[i][j];
      }
      else if(j == num_cols-1)
      {
        OUTS[i][j] = OUTS[i-1][j-1] + BOARD[i][j];
      }
      else
      {
        OUTS[i][j] = min((OUTS[i-1][j-1]+BOARD[i][j]), (OUTS[i-1][j] + BOARD[i][j]));
      } 
    }

    num_cols = num_cols + 1;
  }

  return min_val(OUTS[size-1], size-1);
}

/* a tabular solution to the n choose k problem */
int solve_n_choose_k(int n, int k)
{
  if(k > n)
    return -1;

  if(n == k || n-k == 1)
    return 1;

  //initialize the top of pascals triangle 
  BOARD[0][0] = 1;
  BOARD[1][0] = 1;
  BOARD[1][1] = 1;

  int triangle_cols = 3;

  for(int i = 2; i < n+1; ++i)
  {
      for(int j = 0; j < triangle_cols; ++j)
      {
        if(j == 0 || j == triangle_cols-1) //the first and last numbers in a row are 1 in pascals triangle
          BOARD[i][j] = 1;
        
        else
          BOARD[i][j] = BOARD[i-1][j] + BOARD[i-1][j-1];
      } 
      triangle_cols = triangle_cols + 1;
  }

  return BOARD[n][k];
}



int main(int argc, char argv[])
{
/*  int size;
  scanf("%d", &size);
  init(size);
  init_board(size);
  int s = solve_sum_descent(size);
  double prices[5] = {0, 3.5, 4.0, 2.7, 12};
  double p = solve_rod(4, prices, 4);
  double prices1[6] = {0, 1, 2, 3, 4, 5};
  double p1 = solve_rod(5, prices1, 5);
  double prices2[7] = {0, 6, 5, 4, 3, 2, 1};
  double p2 = solve_rod(6, prices2, 6);
  double prices3 [8] = {0,1,1,1,1,1,1,1};
  double p3 = solve_rod(7, prices3, 7);
  double prices4 [10] = {0,2,4,6,8,10,12,14,16,18};
  double p4 = solve_rod(10, prices4, 10);*/
  int t = solve_n_choose_k(4, 2);
  return 0;
}
