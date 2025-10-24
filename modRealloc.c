#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
    char record_type,obje[20],name[10];
    int saddr,proglength,addr;
    FILE*f1;
    f1=fopen("object_program.txt","r");
    if(!f1)
    {
        printf("error in reading files\n");
        return 1;
    }
    fscanf(f1,"%c",&record_type);
    if(record_type=='H')
    {
        fscanf(f1,"%s\t%X\t%X\n",name,&saddr,&proglength);
        printf("programs name=%s\n",name);
        printf("programs starting address=%04x\n",saddr);
        printf("programs length=%04x\n",proglength);
    }
    fscanf(f1,"%c",&record_type);
    while(record_type!='E')
    {
        if(record_type=='T')
        {
            fscanf(f1,"%X",&addr);
            printf("Text record stars at %04x\n",addr);
            while(fscanf(f1,"%s",obje)==1)
            {
                if(obje[0]=='E' ||obje[0]=='T')
                {
                    break;
                }
                printf("%s loading at address %04x\n",obje,addr);
                addr+=3;
            }
            record_type=obje[0];
            continue;
        }
        fscanf(f1,"%c",&record_type);
    }
    if(record_type=='E')
    {
        fscanf(f1,"%X",&addr);
        printf("jump to location %04x for program execution",addr);
    }
}