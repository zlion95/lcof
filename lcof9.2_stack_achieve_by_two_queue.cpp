#include <iostream>
#include <queue>
#include <stdexcept>

template<typename T> class CStack
{
public:
	CStack(void);
	~CStack(void);

	void push(const T& node);
	T pop();

private:
	std::queue<T> q1;
	std::queue<T> q2;
};

template<typename T> CStack<T>::CStack(void)
{
}

template<typename T> CStack<T>::~CStack(void)
{
}

template<typename T> void CStack<T>::push(const T& element)
{
	if (!q1.empty()) {
		q1.push(element);
	} else {
		q2.push(element);
	}
}

template<typename T> T CStack<T>::pop()
{
	T data;
	std::queue<T> *p = &q2, *p2 = &q1;
	if (!q1.empty()) {//选择不为空的queue作为p
		p = &q1;
		p2 = &q2;
	}

	if (p->empty()) throw std::runtime_error("stack is empty.");

	data = p->front();
	p->pop();
	while (!p->empty()) {//将p队列中除了最后一个data，全部移入到p2队列中
		p2->push(data);
		data = p->front();
		p->pop();
	}
	return data;
}

int main(int argc, char **argv)
{
	CStack<int> st;
	int count = 0;
	for (int i = 0; i < 100; i=i+2) {
		st.push(i);
		++count;
	}
	while (count--) {
		std::cout << st.pop() << " ";
	}
	std::cout << std::endl;

	std::cout << "Try to triger exception." << std::endl;
	st.pop();
	return 0;
}
