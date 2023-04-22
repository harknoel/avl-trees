#include "node.h"
#include <iostream>
using namespace std;
class BSTree {
    node* root;
    int size;

    node* create_node(int num, node* parent) {
        node* n = (node*) malloc( sizeof(node) );
        n->element = num;
        n->parent = parent;
        n->right = NULL;
        n->left = NULL;
        return n;
    }

    bool search(node* curr, int num) {
        if (curr == NULL) {
            return false;
        }
        if (num == curr->element) {
            return true;
        }

        if (num < curr->element) {
            return search(curr->left, num);
        }
        return search(curr->right, num);
    }

    node* search_node(node* curr, int num) {
        if (num == curr->element) {
            return curr;
        }

        if (num < curr->element) {
            if (curr->left != NULL) {
                return search_node(curr->left, num);
            }
            return curr;
        }
        if (curr->right != NULL) {
            return search_node(curr->right, num);
        }
        return curr;
    }

    public:
    BSTree() {
        root = NULL;
        size = 0;
    }

    bool search(int num) {
        return search(root, num);
    }

    bool insert(int num) {
        if (root == NULL) {
            root = create_node(num, NULL);
            size++;
            return true;
        } else {
            node* parent = search_node(root, num);
            if (parent->element != num) {
                node* newest = create_node(num, parent);
                if (parent->element < num) {
                    parent->right = newest;
                } else {
                    parent->left = newest;
                }
                size++;
                return true;
            }
        }
        return false;
    }

    bool remove(int num) {
      if (isEmpty()) {
        return false;
      }
      node* rem_node = search_node(root, num);
      if (rem_node->element != num) {
        return false;
      }
      
      // FIND the number of children.
      int children = 0;
      // 0 - no children
      // -1 - left child only
      // 1 - right child only
      // 2 - both children
      if (rem_node->right) {
        children = 1;
      }
      if (rem_node->left) {
        if (children == 1) {
          children = 2;
        } else {
          children = -1;
        }
      }
      
      if (children == 0) { // NO CHILDREN
        node* parent = rem_node->parent;
        if (!parent) {
          root = NULL;
        } else {
          if (rem_node == parent->left) {
            parent->left = NULL;
          } else {
            parent->right = NULL;
          }
        }
        
        free(rem_node);
        size--;
      } else if (children == -1 || children == 1) { // ONE CHILD
        node* parent = rem_node->parent;
        node* child;
        if (children == -1) {
          child = rem_node->left;
        } else {
          child = rem_node->right;
        }
        
        child->parent = parent;
        if (!parent) {
          root = child;
        } else {
          if (parent->left == rem_node) {
            parent->left = child;
          } else {
            parent->right = child;
          }
        }
        
        free(rem_node);
        size--;
      } else { // TWO CHILDREN
        node* right_st = rem_node->right;
        while (right_st->left != NULL) {
          right_st = right_st->left;
        }
        
        int temp = right_st->element;
        remove(temp);
        rem_node->element = temp;
      }
      return true;
    }
    
    // TODO implementation of rotate operation of x where
    //  |
    //  y
    //   \
    //    x <- curr
    void zigleft(node* curr) {
      node *x = curr;
      node *y = x->parent;
      node *grandparent = y ? y->parent : nullptr;
      node *T2 = x->left;

      if(y == root) {
          root = x;
          x->parent = nullptr;
      } else {
          if(grandparent->right == y) {
              grandparent->right = x;
          } else {
              grandparent->left = x;
          }
          x->parent = grandparent;
      }

      y->right = T2;
      if(T2) T2->parent = y;

      x->left = y;
      y->parent = x;  
    }
    
    // TODO implementation of rotate operation of x where
    //   |
    //   y
    //  /
    // x <- curr
    void zigright(node* curr) {
      node *x = curr;
      node *y = x->parent;
      node *grandparent = y ? y->parent : nullptr;
      node *T2 = x->right;

      if(y == root) {
          root = x;
          x->parent = nullptr;
      } else {
          if(grandparent->right == y) {
              grandparent->right = x;
          } else {
              grandparent->left = x;
          }
          x->parent = grandparent;
      }

      y->left = T2;
      if(T2) T2->parent = y;

      x->right = y;
      y->parent = x;  
    }

    // GIVEN the grandparent (or z), find the parent (or y), and the child (or x).
    bool restructure(node* gp) {
        node* par; // parent
        // TODO find parent

        // Identify if the parent is on the left or right of the grandparent
        if(gp->right) {
          par = gp->right;
        } else {
          par = gp->left;
        }

        // This is an indicator of the placement of grandparent to parent (gtop)
        bool gtop_right = false;
        if (gp->right == par) {
            gtop_right = true;
        }
        
        node* child;
        // TODO find child

        // Identify if the child is located at the left or right of the parent  
        if(par->right) {
          child = par->right;
        } else {
          child = par->left;
        }

        // This is an indicator of the placement of parent to child (ptoc)
        bool ptoc_right = false;
        if (par->right == child) {
            ptoc_right = true;
        }

        // FOR THE FOLLOWING: Write in each of the if statements a console output
        // on its corresponding operation (ZIGLEFT, ZIGRIGHT, ZIGZAGLEFT, or ZIGZAGRIGHT)
        
      // z
      //  \
      //   y
      //    \
      //     x
      if (gtop_right && ptoc_right) {
        // TODO call to either zigleft or zigright or both
        cout << "ZIGLEFT" << endl;
        zigleft(par);
      } 
      
      // z
      //   \
      //     y
      //    /
      //   x
      else if (gtop_right && !ptoc_right) {
        // TODO call to either zigleft or zigright or both
        cout << "ZIGZAGLEFT" << endl;
        zigright(child);
        zigleft(child);
      } 
      
      //     z
      //    /
      //   y
      //  /
      // x
      else if (!gtop_right && !ptoc_right) {
        // TODO call to either zigleft or zigright or both
        cout << "ZIGRIGHT" << endl;
        zigright(par);
      } 
      
      //      z
      //    /
      //  y
      //   \
      //    x
      else {
        // TODO call to either zigleft or zigright or both
        cout << "ZIGZAGRIGHT" << endl;
        zigleft(child);
        zigright(child);
      }
      
      return true;
    }

    // WARNING. Do not modify the methods below.
    // Doing so will nullify your score for this activity.
    void print() {
        if (isEmpty()) {
            cout << "EMPTY" << endl;
            return;
        }
        cout << "PRE-ORDER: ";
        print_preorder(root);
        cout << endl << "IN-ORDER: ";
        print_inorder(root);
        cout << endl << "POST-ORDER: ";
        print_postorder(root);
        cout << endl << "STATUS: " << check_health(root, NULL) << endl;
    }

    bool isEmpty() {
        return size == 0;
    }

    void print_preorder(node* curr) {
        cout << curr->element << " ";
        if (curr->left != NULL) {
            print_preorder(curr->left);
        }
        if (curr->right != NULL) {
            print_preorder(curr->right);
        }
    }

    void print_inorder(node* curr) {
        if (curr->left != NULL) {
            print_inorder(curr->left);
        }
        cout << curr->element << " ";
        if (curr->right != NULL) {
            print_inorder(curr->right);
        }
    }

    void print_postorder(node* curr) {
        if (curr->left != NULL) {
            print_postorder(curr->left);
        }
        if (curr->right != NULL) {
            print_postorder(curr->right);
        }
        cout << curr->element << " ";
    }

    bool check_health(node* curr, node* parent) {
        bool health = curr->parent == parent;
        if (curr->left != NULL) {
            health &= check_health(curr->left, curr);
        }
        if (curr->right != NULL) {
            health &= check_health(curr->right, curr);
        }
        return health;
    }
};