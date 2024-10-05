#include<stdio.h>
#include<stdlib.h>
void main()
{
int np,r,flag=0,count=0,k=0;
printf("Enter the no of process:");
scanf("%d",&np);
printf("Enter the no of resources:");
scanf("%d",&r);
int allocation[np][r],need[np][r],max[np][r],available[r],safesequence[np],visited[np];
printf("Enter the allocation of each process:\n");
for(int i=0;i<np;i++){
for(int j=0;j<r;j++){
scanf("%d",&allocation[i][j]);
}
}
printf("Enter the max allocation of each process:\n");
for(int i=0;i<np;i++){
visited[i]=0;
for(int j=0;j<r;j++){
scanf("%d",&max[i][j]);
}
}
for(int i=0;i<np;i++){
for(int j=0;j<r;j++){
need[i][j]=max[i][j]-allocation[i][j];
}
}
printf("Enter the available space for each allocation:");
for(int i=0;i<r;i++){
scanf("%d",&available[i]);
}
printf("ALLOCATION   MAX    AVAILABLE     NEED\n");
for(int i=0;i<np;i++){
for(int j=0;j<r;j++){
printf(" %d ",allocation[i][j]);
}
for(int j=0;j<r;j++){
printf("  %d",max[i][j]);
}
printf(" ");
for(int j=0;j<r;j++){
printf("  %d",available[j]);
}
printf("   ");
for(int j=0;j<r;j++){
printf(" %d ",need[i][j]);
}
printf("\n");
}
while(count<np){
flag=0;
for(int i=0;i<np;i++){
int executed=0;
for(int j=0;j<r;j++){
if(need[i][j]<=available[j]){
executed++;
}
}
if(executed==r && visited[i]==0){
for(int j=0;j<r;j++){
available[j]=available[j]+allocation[i][j];
}
flag=1;
visited[i]=1;
count++;
safesequence[k++]=i;
}
}
if(flag==0){
printf("\nThere is no Safe Sequence");
exit(0);
}
}
printf("\nSafe Sequence = <");
for(int i=0;i<k;i++){
printf("P%d ",safesequence[i]);
}
printf(">");
printf("\n");
}

