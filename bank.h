#ifndef BANK_H_INCLUDED
#define BANK_H_INCLUDED
#include<string.h>
#include<stdio.h>

int M=4;//the number of process
int N=3;//the number of resource;

int all_resource[3]={9,3,6};
int max[4][3]={{3,2,2},{6,1,3},{3,1,4},{4,2,2}};
int available[20];
int allocation[4][3]={{1,0,0},{6,1,2},{2,1,1},{0,0,2}};
int need[10][20];
int request[20];

void showdata();
void bank();
void changedata(int k);
void rstordata(int k);
int chkerr(int k);

#endif // BANK_H_INCLUDED
