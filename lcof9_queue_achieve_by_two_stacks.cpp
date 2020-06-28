#include <iostream>
#include <stack>
#include <stdexcept>

template<typename T> class CQueue
{
public:
	CQueue(void);
	~CQueue(void);

	void push(const T& node);
	T pop();

private:
	std::stack<T> stack1;
	std::stack<T> stack2;
};

template<typename T> CQueue<T>::CQueue(void)
{

}

template<typename T> CQueue<T>::~CQueue(void)
{

}

template<typename T> void CQueue<T>::push(const T& element)
{
	stack1.push(element);
}

template<typename T> T CQueue<T>::pop()
{
	if (stack2.empty()) {//当stack2为空时，从stack1中pop出数据放入到stack2中
		while (!stack1.empty()) {
			T& data = stack1.top();
			stack1.pop();
			stack2.push(data);
		}
	}
	if (stack2.empty()) throw std::runtime_error("queue is empty!");//如果从stack1中没移出任何东西，说明队列为空，返回错误

	T head = stack2.top();
	stack2.pop();

	return head;
}

int main(int argc, char **argv)
{
	CQueue<int> q;
	int count = 0;
	for (int i = 0; i < 100; i=i+2) {
		q.push(i);
		++count;
	}
	while (count--) {
		std::cout << q.pop() << " ";
	}
	std::cout << std::endl;

	std::cout << "Try to triger exception." << std::endl;
	q.pop();
	return 0;
}
