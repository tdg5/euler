#include <stdio.h>
#define MAX_INT_LEN 69000

void big_addition(int[], int[]);
int double_pandigital(int ints[]);
void print_iteration(int, int[]);


void big_addition(int recv_array[], int add_array[]) {
  int i, carry = 0, sum, start_pos;
  for(start_pos = 0; add_array[start_pos] == 0; start_pos++);
  for(i = MAX_INT_LEN - 1; i >= start_pos; i--) {
    sum = recv_array[i] + add_array[i] + carry;
    if(sum >= 10) {
      carry = 1;
      sum %= 10;
    } else {
      carry = 0;
    }
    recv_array[i] = sum;
  }
  recv_array[i] += carry;
}


int double_pandigital(int ints[]) {
  int i, sum = 0, product = 1;
  for(i = MAX_INT_LEN - 9; i < MAX_INT_LEN; i++) {
    sum += ints[i];
    product *= ints[i];
  }
  if(sum != 45 || product != 362880) {
    return 0;
  }
  int j;
  product = 1;
  for(j = 0; ints[j] == 0; j++);
  for(i = j; i < j + 9; i++) {
    sum -= ints[i];
    product *= ints[i];
  }
  if(sum != 0 || product != 362880) {
    return 0;
  }
  return 1;
}


int main() {
  printf("Processing with MAX_INT_LEN=%d\n", MAX_INT_LEN);
  int n1[MAX_INT_LEN],
    n2[MAX_INT_LEN],
    iteration = 2,
    i;
  int *iter_ptr,
    *other_ptr;

  for(i = 0; i < MAX_INT_LEN; i++) {
    n1[i] = n2[i] = 0;
  }
  n1[MAX_INT_LEN - 1] = n2[MAX_INT_LEN - 1] = 1;
  iter_ptr = n2;
  other_ptr = n1;

  while(!double_pandigital(iter_ptr)) {
    iteration++;
    if(iter_ptr == n2) {
      iter_ptr = n1;
      other_ptr = n2;
    } else {
      iter_ptr = n2;
      other_ptr = n1;
    }
    big_addition(iter_ptr, other_ptr);
    /*if(iteration == 541 || iteration == 2749) {*/
      /*print_iteration(iteration, iter_ptr);*/
    /*}*/
    if(iter_ptr[1] != 0) {
      printf("No precision remaining, exiting.\n");
      return 1;
    }
  }
  print_iteration(iteration, iter_ptr);
  return 0;
}


void print_iteration(int iteration, int ints[]) {
  int i, j;
  for(j = 0; ints[j] == 0; j++);
  printf("\nIteration %d: ", iteration);
  for(i = j; i < MAX_INT_LEN; i++) {
    printf("%d", ints[i]);
  }
  printf("\n");
}
