#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
void main(){
int n =100;
int sum = 0; // global so should use critical while updating
#pragma omp parallel for
for(int i=1;i<=n;i++){
#pragma omp critical
sum+=i;
}
printf("sum is %d\n",sum);
}