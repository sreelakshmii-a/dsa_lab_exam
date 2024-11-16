//4.Write a C program to implement two stacks in a single array and performs push and pop operations for both stacks.

#include <stdio.h>
#define MAX 100 

int arr[MAX];

int top1 = -1;       
int top2 = MAX;      

void push1(int value) {
    if (top1 < top2 - 1) { 
        top1++;
        arr[top1] = value;
    } else {
        printf("Stack Overflow for Stack 1\n");
    }
}


void push2(int value) {
    if (top1 < top2 - 1) { 
        top2--;
        arr[top2] = value;
    } else {
        printf("Stack Overflow for Stack 2\n");
    }
}


int pop1() {
    if (top1 >= 0) { 
        int value = arr[top1];
        top1--;
        return value;
    } else {
        printf("Stack Underflow for Stack 1\n");
        return -1;
    }
}


int pop2() {
    if (top2 < MAX) { 
        int value = arr[top2];
        top2++;
        return value;
    } else {
        printf("Stack Underflow for Stack 2\n");
        return -1;
    }
}
void display(int array[]){
  if(top1==-1){
    printf("Stack 1 empty");

  }
  else{
    printf("Stack 1\n");
    for(int i=top1;i>0;i--){
      printf("%d\t",array[i]);
    }
  }
if(top2==MAX){
    printf("Stack 2 empty");

  }
  else{
    printf("Stack 2\n");
    for(int i=top2;i<MAX;i++){
      printf("%d\t",array[i]);
    }
  }
  


}


int main() {
  int choice=0,value;
  while(choice!=6){
    printf("\nCHOOSE FROM BELOW\n1.PUSH-1\n2.POP-2\n3.PUSH-2\n4.POP-2\n5.DISPLAY\n6.EXIT\n");
    printf("CHOICE:");
    scanf("%d",&choice);
    switch(choice){
      case 1:printf("Enter the value:");
      scanf("%d",&value);
      push1(value);
      break;
      case 2:value=pop1();
      printf("Removed value:%d",value);
      break;
      case 3:printf("Enter the value:");
      scanf("%d",&value);
      push2(value);
      break;
      case 4:value=pop2();
      printf("Removed value:%d",value);
      break;
      case 5:display(arr);
      break;
      default:
        printf("Invalid Input");
    }
  }

}
