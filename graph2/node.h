#ifndef NODE_H
#define NODE_H


template<class T> class Node
{
public:
	T *pointer;
	int id;

	Node(int i)
	{
		id = i;
		T* tmp = new T;
		this->pointer = tmp;
	}

	T& operator*()
	{
		return *pointer;
	}
};

#endif	//NODE_H