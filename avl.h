#ifndef AVL_H
#define AVL_H

#include <string>

using namespace std;

/**********************************************************************
 *
 *You can add things to this file, if necessary.
 *
 * ********************************************************************/

struct student{
  int id;//student ID
  string name;//student name
  float gpa;//student GPA

  student(int i, string n, float g)
  {id = i; name = n; gpa = g;}
};

struct node{
  student* s;//student record
  
  int height;//height of current node
  int bf;//balance factor of current node

  node *left_child;//a pointer to the left child
  node *right_child;//a pointer to the right child

  node(student* st,int h, int factor, node *l, node *r)
  {s = st;height = h; bf = factor; left_child = l; right_child = r;}
 
};

class AVL{
 private:
  node *root;//the root node of the tree
  float maxgpa;//holds the max gpa of the tree
 public:
  AVL();

  void insert(student* s);
  //insert a student record into the tree

  void deleteID(int id);
  //delete a student record from the tree based on ID

  void showHeight();
  //print the height of the current AVL tree

  void printAll();
  //print all records, sorted by student ID. This is essentially an in-order traversal of the tree.
  
  float GPA(int id);
  //return a student's GPA based on his/her ID

  float maxGPA();
  //return the max GPA of all the students

};

#endif
