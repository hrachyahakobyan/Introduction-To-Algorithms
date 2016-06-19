#pragma once
template<typename T>
class gqueue_stack
{
public:
	gqueue_stack(){};
	~gqueue_stack(){};

	bool empty() const;
	void enqueue(const T& val);
	T dequeue();

private:
	std::stack<T> in;
	std::stack<T> out;
};

template<typename T>
T gqueue_stack<T>::dequeue() 
{
	if (out.empty())
	{
		while (!in.empty())
		{
			out.push(in.top());
			in.pop();
		}
		T val = out.top();
		out.pop();
		return val;
	}
	else
	{
		T val = out.top();
		out.pop();
		return val;
	}
}

template<typename T>
void gqueue_stack<T>::enqueue(const T& val)
{
	in.push(val);
}

template<typename T>
bool gqueue_stack<T>::empty() const
{
	return in.empty() && out.empty();
}
