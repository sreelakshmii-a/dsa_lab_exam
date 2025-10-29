//15. Write a C program to perform an in-order traversal of a binary tree. Print the elements in sorted order.


#include<stdio.h>
#include<stdlib.h>

int array[100];

struct Node{
  int data;
  struct Node *lc,*rc;

};

struct Node* insert(struct Node *root,int value){
  struct Node *newnode=(struct Node*)malloc(sizeof(struct Node));
  newnode->data=value;
  if(root==NULL){
    root=newnode;
    newnode->lc=newnode->rc=NULL;
    return root;
  }
  else{
    struct Node *temp=root;
    struct Node *parent=temp;
    while(temp!=NULL){
      
      if(temp->data>value){
        temp=temp->lc;
      }
      else{
        temp=temp->rc;
      }

    }
    if(parent->data>temp->data){
      parent->lc=temp;
    }
    else{
      parent->rc=temp;
    }
    return root;
  }

}

int inorder(struct Node *root){
  int i=0;
  if(root!=NULL){
    
    inorder(root->lc);
    printf("%d",root->data);
    inorder(root->rc);
  }
  return array;
}

//main function