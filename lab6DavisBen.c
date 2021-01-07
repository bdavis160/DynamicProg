#include <stdio.h>
//A program to tabluate the rod cutting problem

double solveRods(int rodLen, double pricePerU)
{
  if(rodLen < 2 || pricePerU < 0)
    return -1;

  double possibleSizes[rodLen];

  possibleSizes[0] = 0;
  possibleSizes[1] = pricePerU;
  int i = 2;

  for(i; i<=rodLen; ++i)
  {
    possibleSizes[i] = i*pricePerU;
  }


  return possibleSizes[i-1]; //since i will be too big
}


int min(int a, int b)
{
  if(a <= b)
    return a;
  else
    return b;
}

//tabular solution to the minimum sum descent of a trialgle of values e.g.
//  1
// 2 4
//7 3 8
//Minimum sum descent would be 6

int minSumDescent(int nums[], int nSize, int depth)
{
  if(nSize < 0)
    return -1;

  int descent[depth];
  descent[0] = nums[0];

  int i = 1;
  int tempMin = 0;
  int k = 1;

  while(i < nSize) 
  {
    int j = i;
    int lineLen;

    if(i==1)
      lineLen = i + 1;
    else
      lineLen = i + i - 1;

    tempMin = min(nums[j],nums[j+1]);

    while(j < nSize && j+1 < nSize &&j < lineLen)
    {
      tempMin = min(tempMin, nums[j+1]);
      j = j+1;
    }

    descent[k] = tempMin + descent[k-1];
    i = lineLen+1;
    k = k+1;
  }

  return descent[k-1];
}

//tabular solution to the n choose k problem with pascals triangle
int nChooseK(int n, int k)
{
  if(n < 0 || k < 0)
    return -1;

  if(n == 1 || k==1)
    return n;

  if(n==k)
    return 1;

  //declare a double array
  int pascals[n][n];

  //initialize the first row to all ones
  //enter nested fors
  for(int i = 0; i < n; ++i)
    for(int j = 0; j < n; ++j)
    {
      if(i == 0)
      {
        pascals[i][j] = 1;
        continue;
      }
      
      if(j==0) //first col is all ones
      {
        pascals[i][j] = 1;
        continue;
      }

      pascals[i][j] = pascals[i][j-1] + pascals[i-1][j];

    }

    return pascals[n-k][k];
}

int main(int argc, char argv[])
{
  int rl = 2;
  double ppu = -1.0;

  printf("Testing rod cutting solution *****************************************************************\n");
  printf("%0.2f\n", solveRods(rl,ppu));

  rl = 0;
  ppu = 1.0;
  printf("%0.2f\n", solveRods(rl,ppu));

  rl = 1;

  ppu = 1.0;
  printf("%0.2f\n", solveRods(rl,ppu));

  rl = 2;
  ppu = 1.5;
  printf("The max total sale price of a rod of length %d at %0.2f a unit is %0.2f\n", rl, ppu,solveRods(rl,ppu));

  rl = 3;
  ppu = 1.5;
  printf("The max total sale price of a rod of length %d at %0.2f a unit is %0.2f\n",rl, ppu, solveRods(rl,ppu));

  printf("Testing smallest sum descent solution *****************************************************************\n");

  int nSz = 10;

  int n[nSz];

  for(int i = 0; i < nSz; ++i)
  {
    n[i] = i+1;

  }

  int dSz = 4;

  printf("The minimum sum descent of a triangle of depth 4 and values 1,2,3,4,5,6,7,8,9,10 is %d\n",minSumDescent(n, 10,4));


  printf("Testing n choose k*****************************************************************\n");
    
  printf("2 choose 1 is %d\n", nChooseK(2,1));
  printf("3 choose 2 is %d\n", nChooseK(3,2));
  printf("5 choose 3 is %d\n", nChooseK(5,3));
  printf("8 choose 4 is %d\n", nChooseK(8,4));
}
