
/**
 *
 * quadtree (pa3)
 * quadtree.cpp
 * This file will be used for grading.
 *
 */

#include "quadtree.h"
#include <math.h>
using namespace std;


// Node constructor, given.
quadtree::Node::Node(pair<int,int> ul, int d,RGBAPixel a, double v)
	:upLeft(ul),dim(d),avg(a),var(v),NW(NULL),NE(NULL),SE(NULL),SW(NULL)
	{}

// quadtree destructor, given.
quadtree::~quadtree() {
	clear();
}
// quadtree copy constructor, given.
quadtree::quadtree(const quadtree & other) {
	copy(other);
}
// quadtree assignment operator, given.
quadtree & quadtree::operator=(const quadtree & rhs) {
	if (this != &rhs) {
		clear();
		copy(rhs);
	}
	return *this;
}


quadtree::quadtree(PNG & imIn) {

	// STEP 1: determine the largest 2^k by 2^k square that can be extracted
	// from the PNG
	int dimD = floor(log2(std::min(imIn.width(), imIn.height()))); 
	edge = pow(2, dimD); 

	// STEP 2: initialize stats using imIn as the argument (i.e. stats(imIn)); 
	stats s = stats(imIn);

	// STEP 3: initialize upper left 
	pair<int, int> ul = make_pair(0, 0); 

	// STEP 4: build quadtree (recursively) using buildTree helper function
	buildTree(s, ul, dimD); 

}


quadtree::Node * quadtree::buildTree(stats & s, pair<int,int> & ul, int dim) {
        // base case. node == leaf == pixel. 
		if (dim == 0) {

			// step1: make current node using the node constructor. 
			// return current node;

			Node *currentNode = new Node(ul, dim, s.getAvg(ul, dim), s.getVar(ul, dim));
			return currentNode;
		}
		
		else { 

	// step1: make current node using the node constructor. 
	// if root is NULL (i.e. nothing yet created), root assigned to the node. 		
				Node *currentNode = new Node(ul, dim, s.getAvg(ul, dim), s.getVar(ul, dim));

				if (root == NULL) {
					root = currentNode; 
				}

	// step2 I: determine ul (upper left) value for each of current node's children;
 
				pair<int, int> ulNW = make_pair(ul.first, ul.second);
				pair<int, int> ulNE = make_pair(ul.first + ((pow(2, dim))/2), ul.second); 
				pair<int, int> ulSW = make_pair(ul.first, ul.second + ((pow(2, dim))/2)); 
				pair<int, int> ulSE = make_pair(ul.first + ((pow(2, dim))/2), ul.second + ((pow(2, dim))/2)); 

	// step 2 II: decrement dimension, and pass the new value as children's dimension 

				dim--; 

	// step 2 III: buildTree for each of the children.

				Node* subTreeNW = buildTree( s, ulNW, dim);
				Node* subTreeNE = buildTree( s, ulNE, dim);
				Node* subTreeSW = buildTree( s, ulSW, dim);
				Node* subTreeSE = buildTree( s, ulSE, dim); 

	// step 2 IV: point current node to its children, populate the default fields. 

				currentNode -> NW = subTreeNW;
				currentNode -> NE = subTreeNE;
				currentNode -> SW = subTreeSW;
				currentNode -> SE = subTreeSE; 

				return currentNode; 

		}
		/* Your code here! */

}


PNG quadtree::render() {
        /* Your code here! */
	// Created a recursive helper function, that takes type node as its argument.
	// this helper will go through the tree, and pull pixel from those nodes that are = leaf
	// and continue drilling for those nodes that have children. 
	// PNG is the return type for buildTreeImage. 

	return buildTreeImage(root); 
}




	// this function will populate the initially blank PNG with pixels found from those
	// nodes that constitute leaves, while recursively calling those nodes with children. 
	// referred PA1 for guidance re render (specifically PNG files, block).
	// created new PNG files within this assignment folder

PNG quadtree::buildTreeImage(Node* currentNode) {

	// step 1: create new square shaped PNG (blank canvas), of length and width edge == 2^dim.
	// "edge" represents the maximum square can be extracted from the image. 
	// made quadPNG a static object so that it doesn't "disappear" after the function ends. 

	static PNG* quadPNG = new PNG(edge, edge); 

	// base case: the current node has no children;
	// this means that we are at a leaf
	// PNG pixels will be rendered from parameter (average pixel) contained within leaf node 

	if (currentNode -> NW == NULL) {
		pair<int, int> ul = currentNode->upLeft;
		int dim = currentNode->dim; 
		int length = pow(2, dim); 

		int startX = ul.first;
		int startY = ul.second;

		int endX = startX + length; 
		int endY = startY + length;

		for (int y = startY; y < endY; y++) {
			for (int x = startX; x < endX; x++) {

				RGBAPixel *pixel = quadPNG->getPixel(x, y); 
				*pixel = currentNode->avg;
			}
		}
		return *quadPNG;
	}

	// recursive case: current node has children; call renderTree on each child. 
	// function will keep drilling down. 
	// note that if a node has children, it has four of them.  
	// i.e. either a node has no children or it has four. 

	
	buildTreeImage(currentNode -> NW);
	buildTreeImage(currentNode -> NE); 
	buildTreeImage(currentNode -> SW); 
	buildTreeImage(currentNode -> SE); 
	
	return *quadPNG;

}


int quadtree::idealPrune(int leaves){
        int rsf = INT_MAX;
		//rsf = idealHelper(leaves, rsf);
		// prune size & binary search
		// give sample tolerance -> 1, change it with binary search
		return rsf;
}

int quadtree::countPrune(Node* node, int tol) {
	if (node == NULL || !prunable(node, tol)) return 0;
	// refactor
	int rsf = 1;
	rsf += countPrune(node->NE, tol);
	rsf += countPrune(node->NE, tol);
	rsf += countPrune(node->NE, tol);
	rsf += countPrune(node->NE, tol);

	return rsf;
}

int quadtree::pruneSize(int tol){
        /* Your code here! */
		if (root != NULL && prunable(root, tol)) {
			return countPrune(root, tol);

		}
		return 0;
}

// this function uses a recursive helper function pruneTree. 
void quadtree::prune(int tol){
        /* Your code here! */

		// base case: variability  > tolerance. Keep node. 
		// recursive case: variability < tolerance. clear descendants of node. 

		return pruneTree(tol, root); 

}

// utilizes two helper functions: clear() and prunable 
// prunable helper function needs to be implemented; require some TA direction as 
// specifications are not clear to me. Made a piazza post on the topic. 
void quadtree::pruneTree(int tol, Node* node) {

	// determine whether the node even has children.... if it
	// has no children (i.e. is a leaf), there is nothing that can be pruned.
	// note that a node either has no children or has four children.  

	if (node -> NW == NULL) {

		return;
	}

	// base case is where node's variance <= tolerance. 
	// in this case, prune the children off the node. No further drilling. 
	// note: use prunable helper function for the conditional. 

	if (prunable(node, tol)) {

		clearNode(node -> NW);
		clearNode(node -> NE);
		clearNode(node -> SW);
		clearNode(node -> SE);

		node -> NW = NULL;
		node -> NE = NULL;
		node -> SW = NULL;
		node -> SE = NULL;
	}


	// recursive case is where node's variance > tolerance
	// in this case, call on pruneTree on each of the node's children.
	// note: use prunable helper function for the conditional. 

	else {

		pruneTree(tol, node -> NW); 
		pruneTree(tol, node -> NE); 
		pruneTree(tol, node -> SW); 
		pruneTree(tol, node -> SE);

	}

}

// this one will either be modified or unused. Note:
// needed a recursive clear function; made clearNode to fulfill that requirement
// not sure what to do with this one (as it takes no arguments, cannot use it recursively).
// query whether it can be modified to take arguments. assuming it cannot, made clearNode
// as an argument accepting alternative. Will speak to TA. 
void quadtree::clear() {

	clearNode(root); 	
/* your code here */
}


// Originally made as a helper function, it became the main 
// clear function. this is because clear needs to be recursive, and needs to be able to call 
// on a specific node indicated in pruneTree. 
void quadtree::clearNode(Node* node) {

	if (node == NULL) {

		return;
	}

	else {

		clearNode(node -> NW);
		clearNode(node -> NE);
		clearNode(node -> SW);
		clearNode(node -> SE);
		node -> NW = NULL;
		node -> NE = NULL;
		node -> SW = NULL;
		node -> SE = NULL;
		delete node;
	}

}

// Does a deep copy of the nodes
quadtree::Node * quadtree::copyHelper(Node * node) {
	if (node == NULL) return NULL;

	Node* newNode = new Node(node->upLeft, node->dim, node->avg, node->var);
	newNode->NW = copyHelper(node->NW);
	newNode->NE = copyHelper(node->NE);
	newNode->SE = copyHelper(node->SE);
	newNode->SW = copyHelper(node->SW);
	return newNode;

}

void quadtree::copy(const quadtree & orig){
	root = new Node(orig.root->upLeft, orig.root->dim, orig.root->avg, orig.root->var);
	root->NW = copyHelper(orig.root->NW);
	root->NE = copyHelper(orig.root->NE);
	root->SE = copyHelper(orig.root->SE);
	root->SW = copyHelper(orig.root->SW);
	edge = orig.edge;
}


