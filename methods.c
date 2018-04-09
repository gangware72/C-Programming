#include "header.h"
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdio.h>


/*Creates a file object and opens it. If it doesn't exist it returns a zero. Nothing else will run*/
FILE* openFileRead(char *a[])
{
    FILE *file_pointer = fopen(a[1], "r"); /*fopen("name of file", w==write, r==read, a== append)*/
    if (file_pointer)
    {

        return file_pointer;
    }
    return 0;

}
/*Create a float array using malloc and a pointer*/
void createFloatArray(char *a[], struct database *d)
{
    FILE* file_pointer = openFileRead(a);
    if (file_pointer == NULL)
    {
        printf("\nFile not read.\n");
        return;
    }
    float floatInput;

    int max = 20;

    d->ptr = malloc(sizeof(float)*max + sizeof(struct database)); /*you can't assign to an array only copy, a should have 20 bytes assigned to it */




    while(fscanf(file_pointer,"%f", &floatInput)>0)
    {


        d->ptr[d->database_counter] = floatInput;
        d->database_counter++;
        int i;


        if (d->database_counter == max)
        {
            float temp[max];
            for (i=0; i < max; i++)
            {
              temp[i] = d->ptr[i];
            }

            d->ptr = malloc(sizeof(float)*(max*2) + sizeof(struct database)); /*Call malloc to allocate space for a new array that is twice the size of the new one */

            for (i=0; i < max; i++)
            {
              d->ptr[i] = temp[i];
            }


            d->database_counter=max;
            max = max*2;
        }


    }

    d->unused = max;
}


/*Create a database struct to read float into, then call creat Floatarry*/
struct database createDatabase(char *a[])
{
    struct database d;
    d.database_counter = 0;
    d.unused = 20;

    createFloatArray(a, &d);
    return d;
}
/*prints out all the floats read in to the struct*/
void printFloatData(struct database d)
{
    int counter; //specifies the current array position to print
    for (counter = 0; counter < d.database_counter; counter++)
        printf("%f\n", d.ptr[counter]);
}
/*gets the mean of the float array*/
float getMean(struct database d)
{
    float answer = 0;
    int i;

    for (i =0; i<d.database_counter; i++)
    {
        answer = answer + d.ptr[i];
    }

    answer = answer/(d.database_counter);

    return answer;
}
/*gets the median of the float array*/
float getMedian(struct database d)
{
    sortByFloat(&d);

    if ((d.database_counter-1)%2==0)
    {
        return d.ptr[d.database_counter/2];
    }
    else
    {
        return (d.ptr[d.database_counter/2] + d.ptr[(d.database_counter/2) -1 ]) / 2;
    }

}
/*gets the stdev of the float array*/
float getStdev(struct database d)
{
    float su;
    su = sum(d);
    float number = su/(d.database_counter);
    float answer = sqrtf(number);
    return answer;

}

/*Get the sum as it relates to stdev*/
float sum(struct database d)
{
    float answer = 0;
    float mean = getMean(d);
    int i;
    float xavg;

    for (i=0; i < d.database_counter; i++)
    {
        xavg = d.ptr[i] - mean;
        answer = answer + (xavg * xavg);
    }

    return answer;
}

/*Used for swapping in a series of algorithms, specifically bubble sort here*/
void swap(float *one, float *another)
{
    float temp = *one;
    *one = *another;
    *another = temp;
}

/*Bubble sort the array to use Stand dev on, will change the array in the end*/
void sortByFloat(struct database* d)
{
    int i, j;
    int array_size = d->database_counter;
    for (i =0; i < array_size; i++)
        for (j=0; j < array_size-1-i; j++)
            if (d->ptr[j] > d->ptr[j+1])
                swap(&d->ptr[j], &d->ptr[j+1]);
}
