/*Implement inorder threaded binary tree and traverse it in inorder and preorder*/


#include<bits/stdc++.h>  
using namespace std; 
  
struct Node 
{ 
    struct Node *left, *right; 
    int data; 
    bool thread_left; 
 	bool thread_right; 
}; 
Node *insert(struct Node *root, int data_to_insert) 
{ 
    
    Node *temp = root; 
    Node *parent = NULL; 
    while (temp != NULL) 
    { 
        
        if (data_to_insert == (temp->data))  
        { 
           cout<<"Duplicate Key !\n";
 
            return root; 
        } 
  
        parent = temp; 
  
    
        if (data_to_insert < temp->data)  
        { 
            if (temp -> thread_left == false) 
                temp = temp -> left; 
            else
                break; 
        } 
  
       
        else
        { 
            if (temp->thread_right == false) 
                temp = temp -> right; 
            else
                break; 
        } 
    } 
    Node *new_node = new Node; 
    new_node -> data = data_to_insert; 
    new_node -> thread_left = true; 
    new_node -> thread_right = true; 
  
    if (parent == NULL) 
    { 
        root = new_node; 
        new_node -> left = NULL; 
        new_node -> right = NULL; 
    } 
    else if (data_to_insert < (parent -> data)) 
    { 
        new_node -> left = parent -> left;   
        new_node -> right = parent;  
        parent -> thread_left = false;
        parent -> left = new_node;
    } 
    else
    { 
        new_node -> left = parent;        
        new_node -> right = parent -> right; 
        parent -> thread_right = false;   
        parent -> right = new_node; 
    } 
  
    return root; 
} 
 void preorder(struct Node *root )  
{  
        struct Node *ptr;  
        if(root==NULL)  
        {  
                cout << "Tree is empty" << endl;  
                return;  
        }  
        ptr=root;  
        while(ptr!=NULL)  
        {  
                cout<<ptr->data<<" ";  
                if(ptr->thread_left==false)  
                        ptr=ptr->left;  
                else if(ptr->thread_right==false)  
                        ptr=ptr->right;  
                else 
                {  
                        while(ptr!=NULL && ptr->thread_right==true)  
                                ptr=ptr->right;  
                        if(ptr!=NULL)  
                                ptr=ptr->right;  
                }  
        }  
}   
struct Node *inorderSuccessor(struct Node *temp) 
{  
    
    if (temp -> thread_right == true) 
        return temp->right; 
  
   
    temp = temp -> right; 
    while (temp -> thread_left == false)  
                temp = temp -> left; 
    return temp; 
} 
void inorder(struct Node *root) 
{ 
    if (root == NULL) 
        cout<<"Tree is empty"; 
  
    
    Node *temp = root; 
    while (temp -> thread_left == false)  
        temp = temp -> left;
    while (temp != NULL) 
    { 
        cout<<temp -> data<<" ";  
        temp = inorderSuccessor(temp); 
    } 
} 
  int main() 
{ 
    Node *root = NULL; int ch,n,size;
    
    
    do{
       cout<<"\n1. Insert";
    cout<<"\n2. Display Inorder Threaded binary tree";
    cout<<"\n3. Display Preorder Threaded binary tree ";
    cout<<"\n4. Exit\nEnter Choice :";
    cin>>ch;
   switch(ch){
      case 1:cout<<"How many nodes you want to enter :";
      cin>>size;
      for(int i=1;i<=size;i++){
         cout<<"#"<<i<<" Insert node value  : ";
                cin>>n;
                root=insert(root,n);
                }
             break;
     case 2:
     cout<<"Inorder binary threaded tree: ";
     inorder(root);   ;
     cout<<endl;
             break;
       case 3:
     cout<<"Preorder binary threaded tree: ";
     preorder(root);   ;
     cout<<endl;
             break;
   }}while(ch!=4);
  
    return 0; 
} 
