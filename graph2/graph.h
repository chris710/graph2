// Graph.h
#ifndef Graph_H
#define Graph_H

#include<iostream>
#include<map>
#include<string>
#include<vector>
#include "node.h"
#include "exception.h"

using namespace std;


template<class T> class Graph 
{
public:
	int currentId;
	map<string,Node<T> > mapa;		//mapa grafu
	vector<vector<bool> > graf;		//macierz s¹siedztwa
	vector<Node<T>* > wektor;		//wektor ze wskaŸnikami do wierzcho³ków w kolejnoœci dodawania
	vector<Node<T>* > sorted;		//wektor z posortowanymi topologicznie wierzcho³kami (do iteratora)


	//konstruktor
	Graph()
	{
		currentId = 0;
	}



		class Iterator									//KLASA ITERATORA	
		{
		public:
			Graph<T>* parent;
			Node<T>* pointer;				//wskaŸnik na obecny wierzcho³ek (do dereferencji)
			int id;							//numer w wektorze
			vector<bool> visited;			//tablica odwiedzonych wierzcho³ków
			bool cycle;						//flaga cyklu

			Iterator(Graph<T>* g)		//konstruktor
			{
				parent = g;
				cycle = false;
			}


			bool operator!=(Iterator it)
			{
				if(pointer->id == it.pointer->id)
					return false;
				return true;
			}

			void operator++()
			{
				this->id++;
				this->pointer = (sorted[id]);
			}

			void operator++(int)
			{
				this->id++;
				this->pointer = (sorted[id]);
			}

			void unvisit()
			{
				if(visited.size() == 0)
				{
					for(int i = 0; i< parent->graf.size(); ++i)
						visited.push_back(false);
				}
				else 
					for(vector<bool>::iterator it = visited.begin(); it != visited.end(); ++it)
					{
						*it = false;
					}
			}

			void detectCycle()
			{
				unvisit();
				for(int i = 0; i < parent->graf.size(); ++i)
				{
					//visited[i] = true;
					detectCycle(i,i);
				}
			}

			void detectCycle(int n, int origin)
			{
				for(int i = 0; i < parent->graf.size(); ++i)
				{
					if(i!=n && parent->graf[n][i])
					{
						if(i == origin)
							cycle = true;
						else if( !visited[i] )
						{
							visited[i] = true;
							detectCycle(i, n);
							visited[i] = false;
						}
					}
				}
			}

			void sortDFS()
			{
				unvisit();
				for(int i = 0; i < parent->graf.size(); ++i)
				{
					if(!visited[i])
						sortDFS(i);
				}
			}

			void sortDFS(int n)
			{
				visited[n] = true;
				parent->sorted.push_back(parent->wektor[n]);
				for(int i = 0; i < parent->graf.size(); ++i)
				{
					if(!visited[i] && parent->graf[n][i])
						sortDFS(i);
				}
			}


			T& operator*()
			{
				return *(*pointer);
			}
		};


	Iterator begin()
	{
		Iterator Result(this);
		Result.detectCycle();
		Cyclicgraphexception cyclicgraphexception;
		try
		{
			if(Result.cycle)
				throw cyclicgraphexception;
			Result.sortDFS();
			Result.pointer = sorted[0];
			Result.id = 0;
			return Result;
		}
		catch(exception& e)
		{
			cout<<e.what()<<endl;
		}
	}

	Iterator end()
	{
		Iterator Result(this);
		Result.detectCycle();
		Cyclicgraphexception cyclicgraphexception;
		try
		{
			if(Result.cycle)
				throw cyclicgraphexception;
			Result.sortDFS();
			Result.pointer = sorted.end();
			Result.id = sorted.size();
			return Result;
		}
		catch(exception& e)
		{
			cout<<e.what()<<endl;
		}
	}


	Node< T> addNode()						//dodawanie nowego wierzcho³ka
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
		wektor.push_back(++Result);
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