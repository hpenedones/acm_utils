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
			removeNode(n);
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

		BinaryTreeNode* removeNode(int n)
		{
			if (n < data) {
				if (left) left = left->removeNode(n);
			} else if (n > data) {
				if (right) right = right->removeNode(n);
			} else {
				if (!left && !right) { delete this; return NULL; }
				if (!left) { BinaryTreeNode* r = right; delete this; return r; }
				if (!right) { BinaryTreeNode* l = left; delete this; return l; }
				// two children: replace with in-order successor
				BinaryTreeNode* s = right->min();
				data = s->data;
				right = right->removeNode(s->data);
			}
			return this;
		}

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
