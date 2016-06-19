#pragma once
template<typename T>
class gstack_queue
{
public:
	gstack_queue() : q1(new std::queue<T>), q2(new std::queue<T>){};
	~gstack_queue(){ delete q1; delete q2;};

	bool empty() const;
	void push(const T& val);
	void pop();
	T top();

private:
	std::queue<T>* q1;
	std::queue<T>* q2;
};

template<typename T>
void gstack_queue<T>::pop()
{
	while (q1->size() > 1)
	{
		q2->push(q1->front());
		q1->pop();
	}
	q1->pop();
	auto temp = q1;
	q1 = q2;
	q2 = temp;
}

template<typename T>
void gstack_queue<T>::push(const T& val)
{
	q1->push(val);
}

template<typename T>
bool gstack_queue<T>::empty() const
{
	return q1->empty() && q2->empty();
}

template<typename T>
T gstack_queue<T>::top() 
{
	while (q1->size() > 1)
	{
		q2->push(q1->front());
		q1->pop();
	}
	T val = q1->front();
	q2->push(val);
	auto temp = q1;
	q1 = q2;
	q2 = temp;
	return val;
}
