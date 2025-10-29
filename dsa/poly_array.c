#include<stdio.h>
//pakka self made!!!
//17/Nove/2024
struct Term{
  int coeff;
  int pow;
};
struct Term poly1[100],poly2[100];
struct Term sum[100];

int insert(struct Term poly[]){
  int n;
  printf("Enter the number of terms\n");
  scanf("%d",&n);
  for(int i=0;i<n;i++){
    printf("Coeff,Pow:");
    scanf("%d%d", &poly[i].coeff, &poly[i].pow);
  }
  return n;
}

void display(struct Term poly[],int n){
  for(int i=0;i<n;i++){
    printf("%dx^%d ",poly[i].coeff,poly[i].pow);
    if(i<n-1){
    if(poly[i+1].coeff>0){
      printf("+");
    }
    else{
      printf("");
    }
    }
  
    
  }
}

int add(struct Term poly1[],int n1,struct Term poly2[],int n2){
  
  int i=0,j=0,k=0;
  while(i!=n1 && j!=n2){
    if(poly1[i].pow>poly2[j].pow){
      sum[k].pow=poly1[i].pow;
      sum[k++].coeff=poly1[i++].coeff;
    }
    else if(poly1[i].pow<poly2[j].pow){
      sum[k].pow=poly2[j].pow;
      sum[k++].coeff=poly1[j++].coeff;
  }
  else{
    sum[k].pow=poly1[i].pow;
    sum[k++].coeff=poly1[i++].coeff+poly2[j++].coeff;
  }
  while(i!=n1){
    sum[k].pow=poly1[i].pow;
    sum[k++].coeff=poly1[i++].coeff;
    
  }
  while(j!=n2){
    sum[k].pow=poly2[j].pow;
    sum[k++].coeff=poly2[j++].coeff;
    
  }
}
return k;
}
void main(){
  int n1=insert(poly1);
  printf("1st POLYNOMIAL:");
  display(poly1,n1);
  int n2=insert(poly2);
  printf("2nd POLYNOMIAL:");
  display(poly2,n2);
  int n3=add(poly1,n1,poly2,n2);
  printf("\nSUM:");
  display(sum,n3);
}