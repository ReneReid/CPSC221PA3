#include "qtcount.h"

bool qtcount::prunable(Node * root, int tol) {
    RGBAPixel avg = root->avg;
    int area = pow(pow(2, root->dim), 2);
    int count = helper(root, tol, avg);
    return count == area;
}

int qtcount::helper(Node * root, int tol, RGBAPixel avg) {
    if (root->NE == NULL) {
        int sqDist = pow(root->avg.r - avg.r, 2) + pow(root->avg.g - avg.g, 2) + pow(root->avg.b - avg.b, 2);
        if (sqDist <= tol) {
            return 1;
        } else {
            return 0;
        }
    } else {
        int rsf = 0;
        rsf += helper(root->NE, tol, avg);
        rsf += helper(root->NW, tol, avg);
        rsf += helper(root->SE, tol, avg);
        rsf += helper(root->SW, tol, avg);
        return rsf;
    }
}
