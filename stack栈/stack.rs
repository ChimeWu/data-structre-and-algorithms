//实现一个栈，并且实现初始化、进栈、出栈、取栈顶元素、判断栈是否为空、清空栈等操作

use std::ptr::NonNull;

pub struct Stack<T> {
    top: Option<NonNull<Node<T>>>,
    size: usize,
}

struct Node<T> {
    data: T,
    next: Option<NonNull<Node<T>>>,
}

impl<T> Stack<T> {
    pub fn new() -> Self {
        Stack { top: None, size: 0 }
    }

    pub fn push(&mut self, data: T) {
        let mut node = Box::new(Node { data, next: None });
        let node_ptr = Some(unsafe { NonNull::new_unchecked(&mut *node) });
        node.next = self.top;
        self.top = node_ptr;
        self.size += 1;
    }

    pub fn pop(&mut self) -> Option<T> {
        if let Some(mut node) = self.top {
            unsafe {
                let node = node.as_mut();
                self.top = node.next;
                self.size -= 1;
                Some(std::ptr::read(&node.data))
            }
        } else {
            None
        }
    }

    pub fn top(&self) -> Option<&T> {
        unsafe { self.top.as_ref().map(|node| &node.as_ref().data) }
    }

    pub fn is_empty(&self) -> bool {
        self.top.is_none()
    }

    pub fn clear(&mut self) {
        while self.pop().is_some() {}
    }
}

impl<T> Drop for Stack<T> {
    fn drop(&mut self) {
        self.clear();
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_stack() {
        let mut stack = Stack::new();
        assert!(stack.is_empty());
        assert_eq!(stack.size, 0);
        stack.push(1);
        stack.push(2);
        stack.push(3);
        assert_eq!(stack.size, 3);
        assert_eq!(stack.top(), Some(&3));
        assert_eq!(stack.pop(), Some(3));
        assert_eq!(stack.pop(), Some(2));
        assert_eq!(stack.pop(), Some(1));
        assert_eq!(stack.pop(), None);
        assert!(stack.is_empty());
    }
}
