#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
void vector_addn_parallel(int n,int *res_vector,int *vector_a, int *vector_b){
#pragma omp parallel for
for(int i=0; i<n;i++)
{
    int t = omp_get_thread_num();
    res_vector[i] = vector_a[i]+vector_b[i];
    printf("\nThread: %d sum : %d",t,res_vector[i]);
}
}

void main(){
int n = 5;
int vector_a[100000],vector_b[100000], res_vector[100000];
for(int i=0;i<n;i++)
{
vector_a[i] = rand()%10;
printf(" vector a: %d",vector_a[i]);
vector_b[i] = rand()%10;
printf(" vector b: %d",vector_b[i]);
}
double start = omp_get_wtime();
vector_addn_parallel(n,res_vector,vector_a,vector_b);
double end = omp_get_wtime();
printf("\nParallel Time %f\n",end-start);
}
