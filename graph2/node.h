#ifndef NODE_H
#define NODE_H
#include<map>
#include<vector>
#include<list>
#include<string>

using namespace std;

template<class T> class Node;

template<class T> class Graph;




template<class T> class Node
{
public:
	T *pointer;
	int id;
	Graph<T>* parent;

	Node(int i, Graph<T> *g)
	{
		parent = g;
		id = i;
		pointer = new T;
	}

	Node(int i, T tmp, Graph<T> *g)
	{
		id = i;
		parent = g;
		//pointer = new T;
		pointer = &tmp;
	}

	T& operator*()
	{
		return *pointer;
	}

	Node<T>* operator++()
	{
		return this;
	}

	T* operator->() const 
	{
		return pointer;
	}

	
	/*Node<T>* operator() const {
		return &**this;
	}*/

	const list<Node<T> > nexts()
	{
		list<Node<T> > result;
		for(int i = 0; i< parent->graf.size(); ++i)
		{
			if(parent->graf[id][i])
			{
				result.push_back(parent->wektor[i]);
			}
		}
	}

	const list<Node<T> > prevs()
	{
		list<Node<T> > result;
		for(int i = 0; i< parent->graf.size(); ++i)
		{
			if(parent->graf[i][id])
			{
				result.push_back(parent->wektor[i]);
			}
		}
	}

	void setLabel(string s)
	{
		parent->mapa.insert(pair<string,Node<T>* >(s,this));		// do dodawania do mapy
	}

};

#endif	//NODE_H