// Graph.h
#ifndef Graph_H
#define Graph_H

#include<iostream>
#include<map>
#include<string>
#include<vector>
#include<list>
#include "node.h"
#include "exception.h"

using namespace std;


template<class T> class Graph 
{
public:
	int currentId;
	map<string,Node<T>* > mapa;		//mapa grafu
	vector<vector<bool> > graf;		//macierz s¹siedztwa
	vector<Node<T>* > wektor;		//wektor ze wskaŸnikami do wierzcho³ków w kolejnoœci dodawania
	vector<Node<T>* > sorted;		//wektor z posortowanymi topologicznie wierzcho³kami (do iteratora)
	vector<bool> visited;			//tablica odwiedzonych wierzcho³ków do szukania œcie¿ki
	bool cycle;						//flaga cyklu


	//konstruktor
	Graph()
	{
		currentId = 0;
		cycle = false;
	}


	Node<T>& operator[](string s)
	{
		return *mapa[s];
	}



		class Iterator									//KLASA ITERATORA	
		{
		public:
			Graph<T>* parent;
			Node<T>* pointer;				//wskaŸnik na obecny wierzcho³ek (do dereferencji)
			int id;							//numer w wektorze
			

			Iterator(Graph<T>* g)		//konstruktor
			{
				parent = g;
			}


			bool operator!=(Iterator it)
			{
				if(id == it.id)
					return false;
				return true;
			}

			void operator++()
			{
				this->id++;
				if(this->id != parent->sorted.size())
					this->pointer = (parent->sorted[id]);
			}

			void operator++(int)
			{
				this->id++;
				if(this->id != parent->sorted.size())
					this->pointer = (parent->sorted[id]);
			}


			void sortDFS()
			{
				parent->unvisit();
				parent->sorted.clear();
				for(int i = 0; i < parent->graf.size(); ++i)
				{
					if(!parent->visited[i])
						sortDFS(i);
				}
			}

			void sortDFS(int n)
			{
				parent->visited[n] = true;
				parent->sorted.push_back(parent->wektor[n]);
				for(int i = 0; i < parent->graf.size(); ++i)
				{
					if(!parent->visited[i] && parent->graf[n][i])
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
		detectCycle();
		Cyclicgraphexception cyclicgraphexception;
		try
		{
			if(cycle)
				throw cyclicgraphexception;
			Result.sortDFS();
			Result.pointer = sorted[0];
			Result.id = 0;
			return Result;
		}
		catch(Cyclicgraphexception& e)
		{
			cout<<e.what()<<endl;
			e.kill();
		}
	}

	Iterator end()
	{
		Iterator Result(this);
		Result.id = sorted.size();
		return Result;
	}


	Node< T> addNode()						//dodawanie nowego wierzcho³ka
	{
		Node<T>* Result = new Node<T>(currentId,this);
		wektor.push_back(Result);

		currentId ++;

		vector<bool> nowy;
		for(int i = 0; i < currentId; ++i)
			nowy.push_back(false);
		graf.push_back(nowy);
		for(int i = 0; i < graf.size()-1; ++i)
		{
			graf[i].push_back(false);
		}
		
		return *Result;
	}

	Node< T> addNode(T x)
	{				//	ACHTUNG dubluje siê z powy¿szym
		
		Node<T>* Result = new Node<T>(currentId, x ,this);
		wektor.push_back(Result);

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
		
		return *Result;
	}


	void addArc(Node<T> a,Node<T> b)
	{
		graf[a.id][b.id] = true;
	}


	void unvisit()
	{
		if(visited.size() == 0)
		{
			for(int i = 0; i< graf.size(); ++i)
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
			if(i!=n && graf[n][i])
			{
				if(i == origin)
				{
					cycle = true;
				}
				else if( !visited[i] )
				{
					visited[i] = true;
					detectCycle(i, origin);
					visited[i] = false;
				}
			}
		}
	}


	bool detectPath(int n, int origin)
	{
		bool result = false;
		for(int i = 0; i < graf.size(); ++i)
		{
			if(i!=n && graf[n][i])
			{
				if(i == origin)
				{
					result = true;
				}
				else if( !visited[i] )
				{
					visited[i] = true;
					result = detectPath(i, origin);
					visited[i] = false;
				}
			}
		}
		return result;
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
		cout<<endl;
	}
	
	bool containsPath(Node<T> a, Node<T> b)
	{
		unvisit();
		return detectPath(a.id, b.id);
	}

};


#endif	//Graph_H