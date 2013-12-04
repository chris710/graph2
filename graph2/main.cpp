#include "main.h"

int main()
{
	int x;
	Graph<int> g;
	Node<int> a = g.addNode();
	*a = 33;
	Node<int> b = g.addNode(55);
	Node<int> c = g.addNode(44);
	g.addArc(a,b);
	g.addArc(b,c);
	g.printMatrix();

	cout<<*a<<endl;
	cin>>x;
	return 1;
}

