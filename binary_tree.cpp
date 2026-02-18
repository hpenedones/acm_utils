#include <iostream>
#include <list>

using namespace std;


class BinaryTreeNode{

	public:
		BinaryTreeNode(int d): data(d), left(NULL), right(NULL) 
	{
	}
                void insert(int d)
		{
                 if (d < data)
		 {
                  if (!left)
			  left = new BinaryTreeNode(d);
		  else
			  left->insert(d);
		 }
		 else
		 {
                  if(!right)
			  right = new BinaryTreeNode(d);
		  else
			  right->insert(d);
		 }
		}

                void visit_in_order(list<int> & visited)
		{
                     	if(left)
				left->visit_in_order(visited);
			visited.push_back(data);
			if(right)
				right->visit_in_order(visited);
		}

                BinaryTreeNode* search(int n)
		{
                 
			if (data == n)
				return this;

			if (n < data && left)
				return left->search(n);
			if (n > data && right)
				return right->search(n);

			return NULL;

		}

		bool contains(int n)
		{
                 	return (search(n) != NULL);
		}

		// Must be called on the root node so the full tree is searched.
		void remove(int n)
		{
			BinaryTreeNode * parent = NULL;
			BinaryTreeNode * node = this;
			bool isLeft = false;

			while (node && node->data != n) {
				parent = node;
				if (n < node->data) {
					node = node->left;
					isLeft = true;
				} else {
					node = node->right;
					isLeft = false;
				}
			}

			if (!node) return;

			if (!node->left && !node->right) {
				if (parent) {
					if (isLeft) parent->left = NULL;
					else parent->right = NULL;
				}
				delete node;
			}
			else if (!node->left) {
				if (parent) {
					if (isLeft) parent->left = node->right;
					else parent->right = node->right;
				}
				delete node;
			}
			else if (!node->right) {
				if (parent) {
					if (isLeft) parent->left = node->left;
					else parent->right = node->left;
				}
				delete node;
			}
			else {
				// two children: replace with in-order successor
				BinaryTreeNode * successorParent = node;
				BinaryTreeNode * successor = node->right;
				while (successor->left) {
					successorParent = successor;
					successor = successor->left;
				}
				node->data = successor->data;
				if (successorParent == node)
					successorParent->right = successor->right;
				else
					successorParent->left = successor->right;
				delete successor;
			}
		}

                BinaryTreeNode * min()
		{
                        if (!left)
				return this;
			return left->min();


		}


		void print()
		{
  		      list<int> visited;                                                         
		      visit_in_order(visited); 
		
		      for( list<int>::iterator it = visited.begin(); it!= visited.end(); it++)
			      cout << *it << endl;                                               
		}
                                                                                    
                private:

		BinaryTreeNode *left, *right;
		int data;
};





int main(int argc, const char *argv[])
{
	BinaryTreeNode tree(4);
	tree.insert(3);
	tree.insert(33);
	tree.insert(2);
	tree.insert(-9);
	tree.insert(23);
	tree.insert(9);

        tree.print();



	int a;

	while(cin >> a)
	{
		cout << ".................................." << endl;
        	tree.remove(a);
		
          	tree.print();

	}

	return 0;
}
