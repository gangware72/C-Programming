#include <stdio.h>
#include <math.h>
#include<string.h>

#define Array_Size 20

struct database
{

  int database_counter;
  int unused;

  float *ptr; /*has to be last member of struct*/

};

float readFloat();
FILE* openFileRead(char *a[]);
void createFloatArray(char *a[], struct database *d);
struct database createDatabase(char *a[]);
void printFloatData(struct database d);
float getMean(struct database d);
void swap(float *one, float *another);
void sortByFloat(struct database* d);
float getMedian(struct database d);
float getMean(struct database d);
float sum(struct database d);
float getStdev(struct database d);
void copyArray(float *f[], struct database *d);
