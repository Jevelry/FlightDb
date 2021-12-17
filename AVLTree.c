// Assignment 1 21T1 COMP2521: Flight Database
//
// This program was written by Kevin Huang (z5311917)
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "List.h"
#include "Record.h"
#include "AVLTree.h"

typedef struct node *Node;
struct node {
    Record rec;
    Node   left;
    Node   right;
    int    height;
};

struct tree {
    Node    root;
    int     (*compare)(Record, Record);
};

////////////////////////////////////////////////////////////////////////
// Auxiliary functions

static void doTreeFree(Node n, bool freeRecords);
static Node newNode(Record rec);
static Record doTreeSearch(Tree t, Node n, Record rec);
static Node doTreeInsert(Tree t, Node n, Record rec, bool *res);
static void doTreeSearchBetween(Tree t, Node n, Record lower, Record upper, List l);
static void doTreeNext(Tree t, Node n, Record r, Record *res);
Node RightRotate(Node n);
Node LeftRotate(Node n);
int CompareHeight(Node n);
int GetHeight(Node n);
int bigger(int x, int y);
////////////////////////////////////////////////////////////////////////

static Node newNode(Record rec) {
    Node n = malloc(sizeof(*n));
    if (n == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    n->rec = rec;
    n->left = NULL;
    n->right = NULL;
    n->height = 0;
    return n;
}

////////////////////////////////////////////////////////////////////////

Tree TreeNew(int (*compare)(Record, Record)) {
    Tree t = malloc(sizeof(*t));
    if (t == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    t->root = NULL;
    t->compare = compare;
    return t;
}

////////////////////////////////////////////////////////////////////////

void TreeFree(Tree t, bool freeRecords) {
    doTreeFree(t->root, freeRecords);
    free(t);
}

static void doTreeFree(Node n, bool freeRecords) {
    if (n != NULL) {
        doTreeFree(n->left, freeRecords);
        doTreeFree(n->right, freeRecords);
        if (freeRecords) {
            RecordFree(n->rec);
        }
        free(n);
    }
}

////////////////////////////////////////////////////////////////////////

Record TreeSearch(Tree t, Record rec) {
    return doTreeSearch(t, t->root, rec);
}

static Record doTreeSearch(Tree t, Node n, Record rec) {
    if (n == NULL) {
        return NULL;
    }

    int cmp = t->compare(rec, n->rec);
    if (cmp < 0) {
        return doTreeSearch(t, n->left, rec);
    } else if (cmp > 0) {
        return doTreeSearch(t, n->right, rec);
    } else {
        return n->rec;
    }
}


////////////////////////////////////////////////////////////////////////
/* IMPORTANT: 
   Do NOT modify the code above this line. 
   You must not modify the 'node' and 'tree' structures defined above.
   You must not modify the functions defined above.
*/
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////

bool TreeInsert(Tree t, Record rec) {
    //(from lab4 tree.c)    
    bool res = false; // if the record was inserted
    t->root = doTreeInsert(t, t->root, rec, &res);  
    return res;       
}

static Node doTreeInsert(Tree t, Node n, Record rec, bool *res) {
    // Base case (taken from lab4 tree.c)
    if (n == NULL) {
        *res = true;
        return newNode(rec);
    }
    //Insert Node (taken from lab4 tree.c)
    int cmp = t->compare(rec, n->rec);
    if (cmp < 0) {
        n->left = doTreeInsert(t, n->left, rec, res);
    } else if (cmp > 0) {
        n->right = doTreeInsert(t, n->right, rec, res);
    } else {        
        return n;
    }
           
    //Update height
    n->height = 1 + bigger(GetHeight(n->left), GetHeight(n->right));
    
    //Get node balance  
    int balance = CompareHeight(n);
     
    // If unbalanced:
    // Logic from lecture slides
    if (balance > 1) {
        //LR Case
        if (t->compare(rec, n->left->rec) > 0) {
            n->left = LeftRotate(n->left);
        }
        //LL Case
        return RightRotate(n);
    }
    if (balance < -1) {
        //RL Case
        if (t->compare(rec, n->right->rec) < 0) {
            n->right = RightRotate(n->right);
        }
        //RR Case
        return LeftRotate(n);
    }
    return n;
}
////////////////////////////////////////////////////////////////////////
List TreeSearchBetween(Tree t, Record lower, Record upper) {
    //Reused code from lab04 tree.c    
    // l - a list to accumulate results
    List l = ListNew();
    doTreeSearchBetween(t, t->root, lower, upper, l);    
    return l;
}


static void doTreeSearchBetween(Tree t, Node n, Record lower, Record upper, List l) {  
    //Reused code from lab04 tree.c  
    // n - the current node  
    // Base case
    if (n == NULL) {
        return;
    }
    int cmp = t->compare(lower, n->rec);
    int cmp1 = t->compare(upper, n->rec);
    // Record is less than lower bound, search on left side of tree
    if (cmp < 0) {
        doTreeSearchBetween(t, n->left, lower, upper, l);           
    } 
    // Records equal, append to list
    if (cmp <= 0 && cmp1 >= 0) {
        ListAppend(l, n->rec);
    }
    // Record is greater than upper bound, search on right side of tree
    if (cmp1 > 0) {
        doTreeSearchBetween(t, n->right, lower, upper, l);   
    }     
}

////////////////////////////////////////////////////////////////////////
Record TreeNext(Tree t, Record r) {
    Record res = NULL; 
    doTreeNext(t, t->root, r, &res);
    return res;
}

static void doTreeNext(Tree t, Node n, Record r, Record *res) { 
    //used code from lab04 tree.c searchtree 
    // Base case   
    if (n == NULL) {
        return;
    }    
    int cmp = t->compare(r, n->rec);
    // Record is smaller than node value so save it and go left
    if (cmp < 0) {
        *res = n->rec;
        return doTreeNext(t, n->left, r, res);
        // Record is larger node value so go right
    } else if (cmp > 0) {
        return doTreeNext(t, n->right, r, res);
    } else {
        // Records are equal, save and return
        *res = n->rec;
        return;
    }   
}

////////////////////////////////////////////////////////////////////////
// Helper function for right rotation
Node RightRotate(Node n){
    // Logic from lecture slides
    if (n == NULL || n->left == NULL) {
        return n;
    }
    Node n2 = n->left;
    n->left = n2->right;
    n2->right = n;
    // Update heights
    n->height = bigger(GetHeight(n->left), GetHeight(n->right)) + 1;
    n2->height = bigger(GetHeight(n2->left), GetHeight(n2->right)) + 1;
    return n2;
}

// Helper function for left rotation
Node LeftRotate(Node n){
    // Logic from lecture slides
    if (n == NULL || n->right == NULL) {
        return n;
    }
    Node n2 = n->right;
    n->right = n2->left;
    n2->left = n;
    // Update heights
    n->height = bigger(GetHeight(n->left), GetHeight(n->right)) + 1;
    n2->height = bigger(GetHeight(n2->left), GetHeight(n2->right)) + 1;
    return n2;
}

// Helper function to get tree balance
int CompareHeight(Node n) {
    if (n == NULL) {
        return 0;
    }
    return GetHeight(n->left) - GetHeight(n->right);
}

//Helper function to get height
int GetHeight(Node n) {
    if (n == NULL) {
        return -1;
    }
    return n->height;
}

// Helper function to return bigger subtree
int bigger(int x, int y) {
    if (x > y) {
        return x;
    } else {
        return y;
    }
}
