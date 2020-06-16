#include "qtvar.h"

bool qtvar::prunable(Node * root, int tol) {

    if (root->var >= (double) tol) {
        
        return false;

    } else {

        return true;
    }
    /* Your code here! */
}
