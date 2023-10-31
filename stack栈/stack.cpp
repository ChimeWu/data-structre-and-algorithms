//实现一个泛型栈，并且实现初始化、进栈、出栈、取栈顶元素、判断栈是否为空、清空栈等操作
#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

template <typename T>
class Stack
{
public:
    Stack(int size);
    ~Stack();
    bool stackEmpty(); //判断栈是否为空
    bool stackFull();  //判断栈是否为满
    void clearStack(); //清空栈
    int stackLength(); //栈的长度
    bool push(T elem); //入栈
    bool pop(T &elem); //出栈
    void stackTraverse(bool isFromBottom); //遍历栈
    void printStack(); //打印栈
private:
    T *m_pBuffer; //栈空间指针
    int m_iSize;  //栈容量
    int m_iTop;   //栈顶
};

template <typename T>
Stack<T>::Stack(int size)
{
    m_iSize = size;
    m_pBuffer = new T[size];
    m_iTop = 0;
}

template <typename T>
Stack<T>::~Stack()
{
    delete[] m_pBuffer;
    m_pBuffer = NULL;
}

template <typename T>
bool Stack<T>::stackEmpty()
{
    if (m_iTop == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <typename T>
bool Stack<T>::stackFull()
{
    if (m_iTop == m_iSize)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <typename T>
void Stack<T>::clearStack()
{
    m_iTop = 0;
}

template <typename T>
int Stack<T>::stackLength()
{
    return m_iTop;
}

template <typename T>
bool Stack<T>::push(T elem)
{
    if (stackFull())
    {
        return false;
    }
    m_pBuffer[m_iTop] = elem;
    m_iTop++;
    return true;
}

template <typename T>
bool Stack<T>::pop(T &elem)
{
    if (stackEmpty())
    {
        return false;
    }
    m_iTop--;
    elem = m_pBuffer[m_iTop];
    return true;
}

template <typename T>
void Stack<T>::stackTraverse(bool isFromBottom)
{
    if (isFromBottom)
    {
        for (int i = 0; i < m_iTop; i++)
        {
            cout << m_pBuffer[i] << endl;
        }
    }
    else
    {
        for (int i = m_iTop - 1; i >= 0; i--)
        {
            cout << m_pBuffer[i] << endl;
        }
    }
}

template <typename T>
void Stack<T>::printStack()
{
    for (int i = 0; i < m_iTop; i++)
    {
        cout << m_pBuffer[i] << endl;
    }
}

int main()
{
    Stack<string> *pStack = new Stack<string>(5);
    pStack->push("aaa");
    pStack->push("bbb");
    pStack->push("ccc");
    pStack->push("ddd");
    pStack->push("eee");
    pStack->printStack();
    cout << "-----------------" << endl;
    string elem;
    pStack->pop(elem);
    cout << "elem = " << elem << endl;
    pStack->printStack();
    cout << "-----------------" << endl;
    pStack->stackTraverse(true);
    cout << "-----------------" << endl;
    pStack->stackTraverse(false);
    delete pStack;
    pStack = NULL;
    return 0;
}
