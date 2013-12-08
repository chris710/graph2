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
};

#endif	//NODE_H