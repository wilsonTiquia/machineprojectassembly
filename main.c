#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>

// For asm
extern double daxpy_asm(long long int n, double X[], double Y[], double Z[], double A);
clock_t start, end;

void randomizer(long long int n, double X[], double Y[] ) {
   
    for (int i = 0; i < n; i++) {
        X[i] = ((double)rand());
        Y[i] = ((double)rand());
    }
  
}
void c_function(long long int n, double X[], double Y[], double Z[], double A) {
   
    for (int i = 0; i < n; i++) {
        Z[i] = (A * X[i]) + Y[i];
    }
    
}
void display_asm(long long int n) {
    printf("\n-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n");
    printf("-_-_-_-_-_-_-_DAXPY Using Assembly Kernel # %d_-_-_-_-_-_-_-\n", n);
    printf("-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n");
}

void display_c(long long int n) {
    printf("\n-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n");
    printf("-_-_-_-_-_-_-_-_-_DAXPY Using C Kernel # %d_-_-_-_-_-_-_-_-_-\n", n);
    printf("-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n");
}
int main() {
    // Initialize the time

    // Initialize Sanity Check
    double sanity_check = 0.0;


    // LENGTH OF THE ARRAY 
    // N IS RANDOM MINIMUM 30 
    // long long int n = rand() % (RAND_MAX - 30 + 1) + 30;
    long long int n = 1000000;
    // Initializing The VALUE OF A 
    double A = ((double)rand());
    
    // Initialize arrays
    double* X = (double*)malloc(n * sizeof(double));
    double* Y = (double*)malloc(n * sizeof(double));
    double* Z = (double*)malloc(n * sizeof(double));
    
    

    // DISPLAY RESULT OF DAXPY USING C 
 
    double* res = (double*)malloc(n * sizeof(double));

    // DISPLAY THE RESULT

    
    display_c(n);
    double total_time_c = 0.0;
    
    for (int i = 0; i < 30; i++) {
        randomizer(n, X, Y);
        start = clock();
        c_function(n, X, Y, res, A);
        end = clock();
        double total_time = ((double)end - start) / CLOCKS_PER_SEC;
        total_time_c += total_time;
        printf("\nTIME IT TOOK IS: %f\n", total_time);
        printf("\n\n");
        printf("Z--> ");
        for (int j = 0; j < 10; j++) {
            printf("%f, ", res[j]);

        }
      
    
    }
    double average_time_c = total_time_c / 30;
    double total_time_asm = 0.0;
    display_asm(n);
    for (int i = 0; i < 30; i++) {
        randomizer(n, X, Y);
        start = clock();
        daxpy_asm(n, X, Y, Z, A);
        end = clock();
        double total_time = ((double)(end - start)) / CLOCKS_PER_SEC;
        total_time_asm += total_time;
        printf("\nTIME IT TOOK INSIDE ASM: %f\n", total_time);
        printf("\n\n");
        printf("Z--> ");
        for (int j = 0; j < 10; j++) {
            printf("%f, ", Z[j]);

        }


    }
    double average_time_asm = total_time_asm / 30;


    printf("\n\nTOTAL TIME IN C: %f\n", total_time_c);
    printf("AVERAGE TIME IN C: %f\n\n", average_time_c);

    printf("TOTAL TIME IN ASM: %f\n", total_time_asm);
    printf("AVERAGE TIME IN ASM: %f\n", average_time_asm);
    

    free(X);
    free(Y);
    free(Z);


 
    

    
   

 //   free(A);
  // free(B);

    return 0;
}
