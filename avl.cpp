#include "avl.h"
#include<iostream>
#include<cstddef>
#include<string>

using namespace std;

//AVL constructor
AVL::AVL(){
  root = NULL;
  maxgpa = 0;
}

//returns the height of the current tree
int height(node *n){
  if(n == NULL)
    return -1;
  else
    return n->height;
}

//computes the balance factor of the input node
void computeBF(node *r){
  r->height = max(height(r->left_child), height(r->right_child)) + 1;
  r->bf = height(r->left_child) - height(r->right_child);
}

//left rotate function
node* leftRotate(node *x){
  node *y = x->right_child;
  node *beta = y->left_child;

  y->left_child = x;
  x->right_child = beta;

  computeBF(x);
  computeBF(y);

  return y;
}

//right rotate function
node* rightRotate(node* y){
  node* x = y->left_child;
  node* beta = x->right_child;
  x->right_child = y;
  y->left_child = beta;

  computeBF(y);
  computeBF(x);

  return x;
}

//balances the input ndoe
node* balance(node* r){
  computeBF(r);
  
  if(r->bf == 2 && r->left_child->bf >= 0){
    //leftleft case
    return rightRotate(r);
  }
  else if(r->bf == 2 && r->left_child->bf == -1){
    //leftright case
    r->left_child = leftRotate(r->left_child);
    return rightRotate(r);
  }
  if(r->bf == -2 && r->right_child->bf <= 0){
    //rightright case
    return leftRotate(r);
  }
  else if(r->bf == 2 && r->right_child->bf == 1){
    //leftright case
    r->right_child = rightRotate(r->right_child);
    return leftRotate(r);
  }
  
  return r;
}

//function to insert a new node
node* insert_helper(node* r, student* s){
  if(r == NULL){
    return new node(s, 0, 0, NULL, NULL);
  }
  if(s->id == r->s->id){
    return r;
  }
  else if(s->id > r->s->id)
    r->right_child = insert_helper(r->right_child, s);
  else
    r->left_child = insert_helper(r->left_child, s);
  
  return balance(r);
}

//inserts a new student into the tree
void AVL::insert(student* s){
  if(s->gpa > maxgpa)
    maxgpa = s->gpa;//marks max gpa as they are input into the tree
  root = insert_helper(root, s);
}

//inorder tansversal used to print the tree
void inorder_helper(node *r){
  if(r == NULL)
    return;
  
  inorder_helper(r->left_child);
  cout << r->s->name << " " << r->s->id << " " << r->s->gpa << " ";
  if(r->s->id % 5 == 0){
    cout<<endl;//new line every 5 students to make the print easier to read
  }
  inorder_helper(r->right_child);
}

void AVL::printAll(){
  inorder_helper(root);
  cout<<endl;
}

int findMin(node *r){
  //Find the min node in the subtree rooted by r.
  if(r->left_child == NULL)
    return r->s->id;
  else
    return findMin(r->left_child);
}

//function to remove the student with given id
node* remove_helper(node *r, int item){
  if(r == NULL)
    return NULL;
  else if(item > r->s->id){
    r->right_child = remove_helper(r->right_child, item);
    
    return r;
  }
  else if(item < r->s->id){
    r->left_child = remove_helper(r->left_child, item);
    
    return r;
  }
  else{
    if(r->left_child == NULL && r->right_child == NULL){
      //r is a leaf node.
      delete r;
      return NULL;
    }
    else if(r->left_child == NULL){
      node *n = r->right_child;
      delete r;
      return n;
    }
    else if(r->right_child == NULL){
      node *n = r->left_child;
      delete r;
      return n;
    }
    else{
      r->s->id = findMin(r->right_child);
      r->right_child = remove_helper(r->right_child, r->s->id);
      
      return r;
    }
  }
}

void AVL::deleteID(int id){
  root = remove_helper(root, id);
}

//prints height
void AVL::showHeight(){
  cout << height(root) << endl;;
}


//inorder traversal to find and output student gpa based on id
node* GPA_helper(node* r, int id){
  if(r == NULL){
    return NULL;
  }else if(r->s->id == id){
    return r;
  }
  
  if(id > r->s->id){
    GPA_helper(r->right_child, id);
  }
  else{
    GPA_helper(r->left_child, id);
  }
}

float AVL::GPA(int id){
  node* n = GPA_helper(root, id);

  return n->s->gpa;
}

//returns the maxgpa of the tree
float AVL::maxGPA(){
  return maxgpa;
}
