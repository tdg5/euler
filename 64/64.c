#include <stdio.h>
#define UPPER_LIMIT 10000
#define UPPER_LIMIT_ROOT 101
#define MIN_SEQ_OCCURS 10
#define SEQUENCE_LIMIT 2500

int squares[UPPER_LIMIT_ROOT];

int whole_component(int);
int next_fractional(int, int, int*, int*);
int sequence_length(int*, int);
int matching_sequences(int*, int*, int);


void build_squares(void) {
  int i;
  for(i = 0; i <= UPPER_LIMIT_ROOT; i++) {
    squares[i] = i * i;
  }
}


int sqrt_period(int num) {
  int i;
  int sequence[SEQUENCE_LIMIT];
  int iteration_numerator, iteration_denominator, seq_len;
  for(i = 2; i < UPPER_LIMIT_ROOT; i++) {
    if(squares[i] == num) {
      return 0;
    }
  }
  sequence[0] = whole_component(num);
  iteration_numerator = -sequence[0];
  iteration_denominator = i = 1;
  while((seq_len = sequence_length(sequence, i)) == -1 && i <= SEQUENCE_LIMIT) {
    sequence[i] = next_fractional(num, sequence[0], &iteration_numerator, &iteration_denominator);
    i++;
  }
  return seq_len;
}


int sequence_length(int *sequence, int seq_len) {
  int *seq_last = &sequence[seq_len - 1];
  int patt_len = 1, occurs = 0;
  while(patt_len * MIN_SEQ_OCCURS <= seq_len && occurs != MIN_SEQ_OCCURS) {
    if(matching_sequences(seq_last - patt_len, seq_last - ((occurs + 1) * patt_len), patt_len)) {
      occurs += 1;
    } else {
      patt_len++;
      occurs = 0;
    }
  }
  return occurs == MIN_SEQ_OCCURS ? patt_len : -1;
}


int matching_sequences(int *sequence1, int *sequence2, int seq_len) {
  int i = seq_len;
  while(i) {
    if(*sequence1++ != *sequence2++) {
      return 0;
    }
    i--;
  }
  return 1;
}


int whole_component(int num) {
  int i = 0;
  while(squares[i] <= num) { i++; }
  return i - 1;
}


int next_fractional(int base, int base_root, int * iteration_numerator, int * iteration_denominator) {
  int original_numerator = *iteration_numerator;
  int original_denominator = *iteration_denominator;
  int retval;
  int common;
  int multiplier;
  int i;
  *iteration_denominator = base - (original_numerator * original_numerator);
  for(i = 2; i <= *iteration_denominator; i++) {
    if(*iteration_denominator % i == 0 && original_denominator % i == 0) {
      do { // reduce by divsor as many times as possible
        *iteration_denominator /= i;
        original_denominator /= i;
      } while(*iteration_denominator % i == 0 && original_denominator % i == 0);
    }
  }
  common = (original_denominator * (base_root - original_numerator));
  *iteration_numerator = (common  % *iteration_denominator) - (original_denominator * base_root);
  retval =  common / *iteration_denominator;
  return retval;
}


int main() {
  build_squares();
  int i, count, period, val;
  for(i = 2; i <= UPPER_LIMIT; i++) {
    val = sqrt_period(i);
    if(val % 2 != 0) {
      count++;
    }
  }
  printf("There are %d square roots with odd periods that are less than %d.\n", count, UPPER_LIMIT);
  return 0;
}
