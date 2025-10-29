#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(){
  FILE *fp;
  int saddr,length,addr, new_start, relocation_factor;;
  char name[10],obj[20],record_type;

  fp=fopen("ObjectCode.txt","r");
  if(!fp){
    printf("The input file is invalid");
    return 1;
  }
  fscanf(fp,"%c",&record_type);
  if(record_type=='H'){
    fscanf(fp,"%s\t %X\t %X\n",name,&saddr,&length);
    
        printf("Program Name: %s\n", name);
        printf("Original Starting Address: %04X\n", saddr);
        printf("Program Length: %04X\n\n",length);


    printf("Enter the new start  address");
    scanf("%X",&new_start);
    relocation_factor=new_start-saddr;
    printf("The relocation factor is:%04x\n\n",relocation_factor);



  }
  fscanf(fp,"%c",&record_type);
  while(record_type!='E'){


    if(record_type=='T'){
      fscanf(fp,"%X",&addr);
      printf("\nThe text record starts at %04x",addr);
      addr=addr+relocation_factor;
          while(fscanf(fp,"%s",obj)==1){
            if(obj[0]=='E'||obj[0]=='T'||obj[0]=='M'){
              break;
            }
            printf("%s loaded at relocated address %04x",obj,addr);
            addr+=3;
          }
        record_type=obj[0];
        continue;
      }
    
    if(record_type=='M'){
      int mod_addr,mlength;
      fscanf(fp,"%X%X",&mod_addr,&mlength);
      printf("The modification record is at address %04x of length %04x",mod_addr,mlength);
      printf("After relocation the location is %04x",mod_addr+relocation_factor);
    }
     fscanf(fp, "%c", &record_type);

  }

  if(record_type == 'E'){
    fscanf(fp,"%X",&addr);
    printf("\nExecution starts at relocated address %04x\n",addr+relocation_factor);
  }
  fclose(fp);
  return 0;

}