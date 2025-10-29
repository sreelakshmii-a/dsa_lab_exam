#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
    int progaddr,startaddr,length,code,opcode,address;
    char text,mask[13],input[50],objectcode[20];
    printf("enter the address to load the program(PROGADDR):");
    scanf("%x",&progaddr);
    FILE *fp=fopen("object_program.txt","r");
    if(fp==NULL)
    {
        printf("error:cannot open file");
        return 1;
    }
    while(fscanf(fp,"%s",input)!=EOF)
    {
        text=input[0];
        if(text=='E')
        {
            break;
        }
        if(text=='T')
        {
            fscanf(fp,"%x %x %s",&startaddr,&length,mask);
            startaddr+=progaddr;
            int maskbit[12],maskvalue;
            sscanf(mask,"%x",&maskvalue);
            for(int i=11;i>=0;i--)
            {
                maskbit[i]=maskvalue%2;
                maskvalue/=2;
            }
            int index=0;
            while(index<12 && fscanf(fp,"%s",objectcode)==1)
            {
                if (objectcode[0] == 'E' || objectcode[0] == 'T') {
                    fseek(fp, -strlen(objectcode), SEEK_CUR);
                    break;
                }
                sscanf(objectcode,"%x",&code);
                opcode=code/0x10000;
                address=code%0x10000;
                if(maskbit[index]==1)
                {
                    address+=progaddr;
                    printf("Address %04x:%02x%04x(Relocated)\n",startaddr,opcode,address);
                }
                else
                {
                    printf("Address %04x:%04x\n",startaddr,code);
                }
                startaddr+=3;
                index++;
            }
        }
    }
    fclose(fp);
    return 0;
}