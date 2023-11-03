#实现一个泛型栈，并且实现初始化、进栈、出栈、取栈顶元素、判断栈是否为空、清空栈等操作
class Stack:
    def __init__(self):
        self.__list = []

    def push(self, item):
        self.__list.append(item)

    def pop(self):
        if self.__list:
            return self.__list.pop()
        else:
            return None

    def peek(self):
        if self.__list:
            return self.__list[-1]
        else:
            return None

    def is_empty(self):
        return self.__list == []

    def size(self):
        return len(self.__list)

    def clear(self):
        self.__list.clear()

if __name__ == '__main__':
    stack = Stack()
    stack.push(1)
    stack.push(2)
    stack.push(3)
    print(stack.pop())
    print(stack.peek())
    print(stack.size())
    print(stack.is_empty())
    stack.clear()
    print(stack.is_empty())
    