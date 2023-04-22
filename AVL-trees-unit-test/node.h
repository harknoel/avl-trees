#include <cmath>

struct node {
    node* parent;
    node* right;
    node* left;
    int element;

    int height() {
        // TODO find height of this node
         if (!left && !right) {
            return 1;
        }

        if (left && !right) {
            return 1 + left->height();
        }

        if (!left && right) {
            return 1 + right->height();
        }

        return 1 + fmax(left->height(), right->height());
    }
};