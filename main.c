
#include<stdio.h>
#include<string.h>
#include "header.h"

int main(int argc, char *argv[])
{
  struct database d = createDatabase(argv);


  printf("\n\nNum values: %d\n", d.database_counter);
  printf("Unused array capacity: %d", d.unused-d.database_counter);

  printf("\nmean: %f\n", getMean(d));
  printf("median: %f\n", getMedian(d));
  printf("stddev: %f\n", getStdev(d));




  return 1;
}
