#include <stdio.h>
#define MAX_INT_LEN 69000

void big_addition(short[], short[], int*);
int double_pandigital(short ints[], int*);
void print_iteration(int, short[]);


void big_addition(short recv_array[], short add_array[], int *active_length) {
  int i,
    carry = 0,
    upper = MAX_INT_LEN - 1,
    lower = MAX_INT_LEN - *active_length;
  for(i = upper; i >= lower; i--) {
    recv_array[i] += add_array[i] + carry;
    if(recv_array[i] > 9) {
      carry = 1;
      recv_array[i] -= 10;
    } else {
      carry = 0;
    }
  }
  if(carry) {
    recv_array[i]++;
    (*active_length)++;
  }
}


int double_pandigital(short ints[], int *active_length) {
  int i,
    product = 1,
    sum = 0;
  for(i = MAX_INT_LEN - 9; i < MAX_INT_LEN; i++) {
    sum += ints[i];
    product *= ints[i];
  }
  if(sum != 45 || product != 362880) {
    return 0;
  }
  product = 1;
  int lower = MAX_INT_LEN -*active_length,
    upper = lower + 9;
  for(i = lower; i < upper; i++) {
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
  short n1[MAX_INT_LEN],
    n2[MAX_INT_LEN],
    *pair[] = {n2, n1};

  int i,
    active_length = 1,
    iter_flag = 0,
    iteration = 2;

  // Initialize
  for(i = 0; i < MAX_INT_LEN - 1; i++) {
    n1[i] = n2[i] = 0;
  }
  n1[MAX_INT_LEN - 1] = n2[MAX_INT_LEN - 1] = 1;

  while(!double_pandigital(pair[iter_flag], &active_length)) {
    iteration++;
    iter_flag = !iter_flag;
    big_addition(pair[iter_flag], pair[!iter_flag], &active_length);
    /*if(iteration == 541 || iteration == 2749) {*/
      /*print_iteration(iteration, pair[iter_flag]);*/
    /*}*/
    /*if(pair[iter_flag][1] != 0) {*/
      /*printf("No precision remaining, exiting.\n");*/
      /*return 1;*/
    /*}*/
  }

  /*print_iteration(iteration, pair[iter_flag]);*/
  printf("Iteration of first double pandigitial fib: %d\n", iteration);
  return 0;
}


void print_iteration(int iteration, short ints[]) {
  int i, j;
  for(j = 0; ints[j] == 0; j++);
  printf("\nIteration %d: ", iteration);
  for(i = j; i < MAX_INT_LEN; i++) {
    printf("%d", ints[i]);
  }
  printf("\n");
}
