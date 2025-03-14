#include <iostream>
#include <fstream>
#include <cassert>

using namespace std;

//Node for tree
struct Node {
	int label;
	Node* left = nullptr;
	Node* right = nullptr;
};

//free Node
void free(Node* node) {
	if (node == nullptr)
		return;
	free(node->left);
	free(node->right);
	delete node;
}

//read from a file or from a cin
Node* read(istream& in) {
	Node* node = new Node{};
	in >> node->label;

	char c1 = in.peek();
	if (c1 != '(')
		return node;
	in >> c1;
	node->left = read(in);
	in >> c1;
	assert(c1 == ')');

	char c2 = in.peek();
	if (c2 != '(')
		return node;
	in >> c2;
	node->right = read(in);
	in >> c2;
	assert(c2 == ')');
	return node;
}

//print Node
void print(Node* node, int steps_to_root = 0) {
	if (node == nullptr)
		return;
	cout << '\n';
	for (int i = 0; i < steps_to_root; i++)
		cout << ' ';
	cout << node->label;
	print(node->left, steps_to_root + 1);
	print(node->right, steps_to_root + 1);
}

//check for a leaf
bool check(Node* node, int min_steps_to_leaves, int max_steps_to_leaves) {
	if (node == nullptr)
		return false;
	if (node->left == nullptr && node->right == nullptr)
		return min_steps_to_leaves <= 0 && 0 <= max_steps_to_leaves;
	return check(node->left, min_steps_to_leaves - 1, max_steps_to_leaves - 1) or
		check(node->right, min_steps_to_leaves - 1, max_steps_to_leaves - 1);
}

//final print with min_steps_to_leaves and max_steps_to_leaves
void print_if(Node* node, int min_steps_to_leaves, int max_steps_to_leaves) {
	if (node == nullptr)
		return;
	if (check(node, min_steps_to_leaves, max_steps_to_leaves))
		cout << node->label << " ";
	print_if(node->left, min_steps_to_leaves, max_steps_to_leaves);
	print_if(node->right, min_steps_to_leaves, max_steps_to_leaves);
}


int main() {
	int ask;
	cout << "Insert 0: keyboard; 1: file\n";
	cin >> ask;



	if (cin.fail()) {	//catch an error
		cout << "Input error\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return 0;
	}

	Node* root = nullptr;

	if (ask) {
		//ifstream in("C:\\Users\\79648\\Downloads\\lab2_newsubject\\mat.txt");
		ifstream in("tree.txt");
		root = read(in);
	}
	else
		root = read(cin);

	print(root);
	cout << "\n";

	int min_steps_to_leaves;
	cout << "Insert min_steps_to_leaves\n";
	cin >> min_steps_to_leaves;
	int max_steps_to_leaves;
	cout << "Insert max_steps_to_leaves\n";
	cin >> max_steps_to_leaves;
	print_if(root, min_steps_to_leaves, max_steps_to_leaves);


	free(root);

}