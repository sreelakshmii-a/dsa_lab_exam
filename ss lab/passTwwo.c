#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
  FILE *fin,*fsym,*fopt,*fout;
  char label[20],opcode[20],operand[20],symb[20],mnem[20],code[20];
  int addr;

  fin=fopen("intermedite.txt","r");
  fsym=fopen("symtab.txt","r");
  fopt=fopen("optab.txt","r");
  fout=fopen("ojectcode.txt","w");


  
  if(!fin||!fsym||!fopt||!fout){
    printf("Error in opening one of the files");
  }

  fscanf(fin,"%s %s %s",label,opcode,operand);
  if(strcmp(opcode,"START")==0){
    fprintf(fout,"H^%s^00%s",opcode,operand);
    fscanf(fin,"%s %s %s",label,opcode,operand);
  }

  fprintf(fout,"T^");

  while(strcmp(opcode,"END")!=0){
    int flag=0;

    rewind(fopt);
    while(fscanf(fopt,"%s %s",mnem,code)!=EOF){
      if(strcmp(mnem,opcode)==0){
        flag=1;
        break;
      }
    }

    if(flag==1){
      rewind(fsym);
      while(fscanf(fsym,"%s %d",symb,&addr)!=EOF){
        if(strcmp(symb,operand)==0){
          fprintf(fout,"%s^%04d",code,addr);
          break;
        }
      }
    }

    else if(strcmp(operand,"WORD")==0){
      
    }

  }


}