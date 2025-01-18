#include<stdio.h>
int A[100][100],S[100][100];
int rows,cols;
void getMatrix(){
  
  
  printf("Enter the number of rows and coloumns");
  scanf("%d%d",&rows,&cols);
  for(int i=0;i<rows;i++){
    for(int j=0;j<cols;j++){
      scanf("%d",&A[i][j]);
    }
  }
}
void display(int A[100][100],int rows,int cols){
  printf("\n");
  for(int i=0;i<rows;i++){
    for(int j=0;j<cols;j++){
      printf("%d\t",A[i][j]);
    }
    printf("\n");
  }
}

void Sparse(int A[100][100],int rows,int cols){
  int count=0;
  for(int i=0;i<rows;i++){
    for(int j=0;j<cols;j++){
      if(A[i][j]!=0){
        count++;
      }
    }
  }

  for(int i=0;i<count;i++){
    for(int j=0;j<3;j++){
      
    }
  }
  

}

void main(){
  getMatrix();
  display(A,rows,cols);

}