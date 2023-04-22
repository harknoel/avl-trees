#include "tree.h"
#include <iostream>
using namespace std;
int main() {
    BSTree* tree = new BSTree();

    char op;
    int num;
    do {
        cout << "Operation: ";
        cin >> op;
        node* n;
        switch (op) {
            case 'i':
                cin >> num;
                tree->insert(num);
                break;
            case 's':
                cin >> num;
                tree->search(num);
                break;
            case 'd':
                cin >> num;
                tree->remove(num);
                break;
            case 'p':
                tree->print();
                break;
            case 'h':
                cin >> num;
                cout << tree->search_node(tree->root, num)->height() << endl;
                break;
            case 'Q':
                cin >> num;
                n = tree->search_node(tree->root, num);
                tree->zigleft(n);
                break;
            case 'W':
                cin >> num;
                n = tree->search_node(tree->root, num);
                tree->zigright(n);
                break;
            case 'E':
                cin >> num;
                n = tree->search_node(tree->root, num);
                tree->restructure(n);
                break;
            case 'x':
                cout << "Exiting";
                break;
            default:
                cout << "Invalid operation";
        }
    } while (op != 'x');
};