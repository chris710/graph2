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
	g.addArc(c,a);
	g.printMatrix();
	Graph<int>::Iterator it = g.begin();
	//for (it = g.begin(); it != g.end(); it++) {
	 x = *it;
	


	cout<<g.currentId<<endl;
	cin>>x;
	return 1;
}

