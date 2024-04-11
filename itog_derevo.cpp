// derevo

#include<iostream>
#include <fstream>

long long K = 0;				// значение ключа
long long dl;					// длина пути
long long mn_dl = LLONG_MAX;	//миним длина пути
long long mx_h = 0;				// макс высота
long long ves = 0;				// миним вес пути
long long mn_ves = LLONG_MAX;	// минм вес

std::ofstream out("output.txt");
std::ifstream in("input.txt");

class Node {
public:
	int key;
	Node* left;
	Node* right;
	long long h;					//высота
	long long velichina;			//масса? мин пути
	long long ne_h;					//расстояние миним до листа
	Node(long long x) :
		key(x),
		left(0),
		right(0), h(0), velichina(0), ne_h(0) {
	}
};

class Tree {
public:	Node* root;

	  Tree() : root(0) {};
	  ~Tree() {
		  DestroyNode(root);
	  }
	  static void DestroyNode(Node* node) {
		  if (node) {
			  DestroyNode(node->left);
			  DestroyNode(node->right);
			  delete node;
		  }
	  }

	  Node* delete_key(Node* v, long long x) {
		  if (v == NULL) {
			  return NULL;
		  }
		  if (x < v->key) {
			  v->left = delete_key(v->left, x);
			  return v;
		  }
		  else if (x > v->key) {
			  v->right = delete_key(v->right, x);
			  return v;
		  }

		  if (v->left == NULL) {
			  return v->right;
		  }
		  else if (v->right == NULL) {
			  return v->left;
		  }
		  else {
			  long long min_key = find_min(v->right)->key;
			  v->key = min_key;
			  v->right = delete_key(v->right, min_key);
			  return v;
		  }
	  }

	  Node* find_min(Node* v) {
		  if (v->left != NULL) {
			  return find_min(v->left);
		  }
		  else {
			  return v;
		  }
	  }


	  void insert(long long x) {
		  Node** cur = &root;
		  while (*cur) {
			  Node& node = **cur;
			  if (x < node.key) {
				  cur = &node.left;
			  }
			  else if (x > node.key) {
				  cur = &node.right;
			  }
			  else {
				  return;
			  }
		  }
		  *cur = new Node(x);
	  }
	  void print(Node* node) {
		  if (node != NULL) {
			  out << node->key << std::endl;
			  print(node->left);
			  print(node->right);
		  }
	  }

	  void function(Node* node) {
		  if (node != NULL) {
			  function(node->left);
			  function(node->right);
			  if (node->left == NULL && node->right == NULL) {     // list
				  node->velichina = node->key;
				  node->ne_h = 0;
				  node->h = 0;
			  }
			  else if ((node->left != NULL && node->right == NULL) || (node->left == NULL && node->right != NULL)) {
				  if (node->left != NULL) {
					  node->velichina = node->key + node->left->velichina;
					  node->ne_h = node->left->ne_h + 1;
					  node->h = node->left->h + 1;
				  }
				  else if (node->right != NULL) {
					  node->velichina = node->key + node->right->velichina;
					  node->ne_h = node->right->ne_h + 1;
					  node->h = node->right->h + 1;
				  }
			  }
			  else {
				  Node* nd;
				  if (node->left->ne_h > node->right->ne_h) {
					  nd = node->right;
				  }
				  else if (node->left->ne_h < node->right->ne_h) {
					  nd = node->left;
				  }
				  else if (node->left->ne_h == node->right->ne_h && node->left->velichina >= node->right->velichina) {
					  nd = node->right;
				  }
				  else {
					  nd = node->left;
				  }
				  node->ne_h = nd->ne_h + 1;
				  node->velichina = node->key + nd->velichina;
				  node->h = std::max(node->left->ne_h, node->right->ne_h) + 1;

				  dl = node->left->ne_h + node->right->ne_h + 3;
				  ves = node->left->velichina + node->right->velichina + node->velichina;			//вес всего пути

				  if (mn_dl > dl) {
					  mn_dl = dl;
					  mn_ves = ves;
					  K = node->key;
					  Node* a = node;
					  if (dl % 2 == 1) {
						  long long v_do = node->left->ne_h + 1;
						  long long v_po = dl - v_do - 1;
						  while (v_do != v_po) {
							  if (v_do < v_po) {
								  v_do++;
								  v_po--;
								  node = node->right;
								  K = node->key;
							  }
							  else if (v_do > v_po) {
								  v_do--;
								  v_po++;
								  node = node->left;
								  K = node->key;
							  }
						  }
						  node = a;
					  }
				  }

				  else if (mn_dl == dl) {
					  if (mn_ves >= ves) {
						  mn_ves = ves;
						  mx_h = node->h;
						  K = node->key;
						  Node* a = node;
						  if (dl % 2 == 1) {
							  long long v_do = node->left->ne_h + 1;
							  long long v_po = dl - v_do - 1;
							  while (v_do != v_po) {
								  if (v_do < v_po) {
									  v_do++;
									  v_po--;
									  node = node->right;
									  K = node->key;
								  }
								  else if (v_do > v_po) {
									  v_do--;
									  v_po++;
									  node = node->left;
									  K = node->key;
								  }
							  }
							  node = a;
						  }

					  }
				  }
			  }
			  //out << "key: " << node->key << ", vel: " << node->velichina << ", h:" << node->h << std::endl;
		  }
	  }

};
int main() {
	long long x;
	Tree a;
	in >> x;
	Node* node = new Node(x);
	a.root = node;
	Node* root = node;
	while (in.is_open() && !in.eof()) {
		in >> x;
		node = new Node(x);
		a.insert(x);
	}

	a.function(a.root);
	out << "K: " << K << std::endl;

	if (mn_dl % 2 == 0) {
		a.print(a.root);
	}
	else {
		a.root = a.delete_key(a.root, K);
		a.print(a.root);
	}
	in.close();
	out.close();
}