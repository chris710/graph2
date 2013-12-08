#include "main.h"

int main()
{
	int x;
	Graph<string> g;
	Node<string> n1 = g.addNode(), n2 = g.addNode(), n3 = g.addNode(), n4 = g.addNode();

	*n1 = "Poznañ";
	*n2 = "Berlin";
	*n3 = "Pary¿";
	*n4 = "Mozambik";

	g.addArc(n2,n1);
    g.addArc(n3,n2);
	//g.addArc(n3,n4);		//ten ³uk tworzy cykl
	g.printMatrix();
	
	/*for (int i = 0; i< g.wektor.size(); i++)
	{
		cout<<(**g.wektor[i])<<endl;
	}*/

	Graph<string>::Iterator it = g.begin();
	for (it = g.begin(); 
		it != g.end(); 
		it++)
	{
		cout<<*it<<endl;
	}
	
	/*Node<int> ror = g.addNode();
	*ror = 33;
	cout<<*ror<<endl;*/

	cout<<g.currentId<<endl;
	cin>>x;
	return 1;
}

