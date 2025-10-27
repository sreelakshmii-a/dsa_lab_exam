#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(){
  FILE *f1,*f2,*f3;
  char label[20],operand[20],opcode[20];
  char line[50];
  int locctr,start_addr;

  f1 = fopen("input.asm","r");
  f2 = fopen("symtab","w");
  f3 = fopen("intermediate2.txt","w");

  if(f1==NULL){
    printf("Input file doesn't exist");
    exit(1);
  }

  fscanf(f1,"%s %s %s",label,opcode,operand);
  if(strcmp(opcode,"START")==0){
    start_addr=atoi(operand);
    locctr=start_addr;
    fprintf(f3,"%d %s %s %s\n",locctr,label,opcode,operand);
    fscanf(f1,"%s %s %s",label,opcode,operand);
  }
  
  while(strcmp(opcode,"END")!=0){
    fprintf(f3,"%d %s %s %s\n",locctr,label,opcode,operand);
    if(strcmp(label,"**")!=0){
      fprintf(f2,"%s %d",label,locctr);
    }

    if(strcmp(opcode,"WORD")==0){
      locctr+=3;
    }
    else if(strcmp(opcode,"RESW")==0){
      locctr+=3*atoi(operand);
    }
    else if(strcmp(opcode,"RESB")==0){
      locctr+=atoi(operand);
    }
    else if(strcmp(opcode,"BYTE")==0){
      locctr+=strlen(operand)-3;
    }
    else{
      locctr+=3;
    }

    fscanf(f1,"%s %s %s",label,opcode,operand);


  }
  
  fprintf(f3,"%d %s %s %s\n",locctr,label,opcode,operand);
  fclose(f1);
  fclose(f2);
  fclose(f3);
  printf("The length of the program is %d ",locctr-start_addr);
  return 0;


}