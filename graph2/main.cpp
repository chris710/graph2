#include "main.h"

int main()
{
	int x;
	Graph<string> g;
	Node<string> n1 = g.addNode(), n2 = g.addNode(), n3 = g.addNode(), n4 = g.addNode();

	n1.setLabel("Poznan");
	*g["Poznan"] = "Poznan";
	n2.setLabel("Berlin");
	*g["Berlin"] = "Berlin";
	n3.setLabel("Paryz");
	*g["Paryz"] = "Paryz";
	n4.setLabel("Mozambik");
	*g["Mozambik"] = "Mozambik";

	g.addArc(n2,n1);
    g.addArc(n3,n2);
	g.addArc(n4,n3);
	//g.addArc(n1,n4);	//ten ³uk tworzy cykl
	g.printMatrix();

	Graph<string>::Iterator it = g.begin();
	for (it = g.begin(); it != g.end();	it++)
	{
		cout<<*it<<endl;
	}

	if(g.containsPath(n4,n2))
		cout<<"\nTen graf zawiera sciezke pomiedzy "<<*g["Mozambik"]<<" i "<<*n2<<endl;
	

	//cout<<g.currentId<<endl;
	cin>>x;
	return 1;
}

