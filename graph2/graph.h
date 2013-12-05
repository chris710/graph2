// Graph.h
#ifndef Graph_H
#define Graph_H

#include<iostream>
#include<map>
#include<string>
#include<vector>
#include "node.h"

using namespace std;


template<class T> class Graph 
{
public:
	int currentId;
	map<string,Node<T> > mapa;		//mapa grafu
	vector<vector<bool> > graf;		//macierz s¹siedztwa
	vector<Node<T> > wektor;		//wektor ze wskaŸnikami do wierzcho³ków


	//konstruktor
	Graph()
	{
		currentId = 0;
	}



	class Iterator
	{
		Node<T>* pointer;
		vector<bool> visited;
		bool cycle;

		Iterator()		//konstruktor
		{
			cycle = false;
		}


		bool operator!=(Iterator it)
		{

		}

		Node<T>& operator++()
		{
			//przechodzenie po wektorze
		}

		void unvisit()
		{
			for(vector<bool>::iterator it = visited.begin(); it != visited.end(); ++it)
			{
				*it = false;
			}
		}

		void detectCycle()
		{
			unvisit();
			for(int i = 0; i < graf.size(); ++i)
			{
				//visited[i] = true;
				detectCycle(i,i);
			}
		}

		void detectCycle(int n, int origin)
		{
			for(int i = 0; i < graf.size(); ++i)
			{
				if(i == n)
					cycle = true;
				else if( !visited[i] )
				{
					visited[i] = true;
					detectCycle(i, n);
					visited[i] = false;
				}
			}
		}

	};

	Iterator begin()
	{
		Iterator Result;
		Result.detectCycle();
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		try
		{
			if(Result.cycle)
				throw cyclicgraphexception;
		}
		catch(exception& e)
	}

	Iterator end()
	{

	}



	Node< T> addNode()
	{
		Node<T> Result(currentId);
		//mapa.insert(Result);		// do dodawania do mapy

		currentId ++;
		vector<bool> nowy;
		for(int i = 0; i < currentId; ++i)
			nowy.push_back(false);
		graf.push_back(nowy);
		for(int i = 0; i < graf.size()-1; ++i)
		{
			graf[i].push_back(false);
		}
		wektor.push_back(Result);
		return Result;
	}

	Node< T> addNode(int x)
	{
		Node<T > tmp = addNode();
		*tmp = x;
		return tmp;
	}

	void addArc(Node<T> a,Node<T> b)
	{
		graf[a.id][b.id] = true;
	}

	void printMatrix()
	{
		for(int i = 0; i<graf.size(); ++i)
		{
			for(int j = 0; j<graf.size(); ++j)
			{
				cout<<graf[i][j]<<" ";
			}
			cout<<endl;
		}
	}
	
};


#endif	//Graph_H