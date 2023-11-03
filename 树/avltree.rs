//定义一个平衡二叉树，实现插入、删除、查找、遍历等操作

use std::cmp::Ordering;
use std::fmt::Debug;
use std::fmt::Display;
use std::fmt::Formatter;
use std::fmt::Result;
use std::mem::replace;
use std::ptr::NonNull;
use std::ptr::null_mut;

#[derive(Debug)]
pub struct AVLTree<T: Ord + Debug> {
    root: Option<NonNull<AVLNode<T>>>,
}

#[derive(Debug)]
struct AVLNode<T: Ord + Debug> {
    data: T,
    height: i32,
    left: Option<NonNull<AVLNode<T>>>,
    right: Option<NonNull<AVLNode<T>>>,
}

impl<T: Ord + Debug> AVLTree<T> {
    pub fn new() -> Self {
        AVLTree { root: None }
    }

    pub fn insert(&mut self, data: T) {
        let mut node = AVLNode::new(data);
        let mut parent = None;
        let mut cur = self.root;
        while let Some(mut cur_node) = cur {
            let cur_ref = unsafe { cur_node.as_mut() };
            parent = cur;
            if node.data < cur_ref.data {
                cur = cur_ref.left;
            } else {
                cur = cur_ref.right;
            }
        }
        if let Some(mut parent_node) = parent {
            let parent_ref = unsafe { parent_node.as_mut() };
            if node.data < parent_ref.data {
                parent_ref.left = Some(NonNull::new(&mut node as *mut _));
            } else {
                parent_ref.right = Some(NonNull::new(&mut node as *mut _));
            }
        } else {
            self.root = Some(NonNull::new(&mut node as *mut _));
        }
        self.rebalance();
    }

    pub fn remove(&mut self, data: T) {
        let mut parent = None;
        let mut cur = self.root;
        while let Some(mut cur_node) = cur {
            let cur_ref = unsafe { cur_node.as_mut() };
            if data < cur_ref.data {
                parent = cur;
                cur = cur_ref.left;
            } else if data > cur_ref.data {
                parent = cur;
                cur = cur_ref.right;
            } else {
                if cur_ref.left.is_some() && cur_ref.right.is_some() {
                    let mut min_parent = cur;
                    let mut min = cur_ref.right;
                    while let Some(mut min_node) = min {
                        let min_ref = unsafe { min_node.as_mut() };
                        if min_ref.left.is_some() {
                            min_parent = min;
                            min = min_ref.left;
                        } else {
                            cur_ref.data = replace(&mut min_ref.data, data);
                            cur = min;
                            parent = min_parent;
                            break;
                        }
                    }
                } else {
                    let mut child = cur_ref.left.or(cur_ref.right);
                    if let Some(mut parent_node) = parent {
                        let parent_ref = unsafe { parent_node.as_mut() };
                        if cur_ref.data < parent_ref.data {
                            parent_ref.left = child;
                        } else {
                            parent_ref.right = child;
                        }
                    } else {
                        self.root = child;
                    }
                    break;
                }
            }
        }
        self.rebalance();
    }

    pub fn find(&self, data: T) -> Option<&T> {
        let mut cur = self.root;
        while let Some(mut cur_node) = cur {
            let cur_ref = unsafe { cur_node.as_mut() };
            if data < cur_ref.data {
                cur = cur_ref.left;
            } else if data > cur_ref.data {
                cur = cur_ref.right;
            } else {
                return Some(&cur_ref.data);
            }
        }
        None
    }

    pub fn preorder_traverse<F>(&self, mut f: F)
    where
        F: FnMut(&T),
    {
        let mut stack = Vec::new();
        let mut cur = self.root;
        while cur.is_some() || !stack.is_empty() {
            while let Some(mut cur_node) = cur {
                let cur_ref = unsafe { cur_node.as_mut() };
                f(&cur_ref.data);
                stack.push(cur);
                cur = cur_ref.left;
            }
            if let Some(mut cur_node) = stack.pop() {
                let cur_ref = unsafe { cur_node.as_mut() };
                cur = cur_ref.right;
            }
        }
    }

    pub fn inorder_traverse<F>(&self, mut f: F)
    where
        F: FnMut(&T),
    {
        let mut stack = Vec::new();
        let mut cur = self.root;
        while cur.is_some() || !stack.is_empty() {
            while let Some(mut cur_node) = cur {
                let cur_ref = unsafe { cur_node.as_mut() };
                stack.push(cur);
                cur = cur_ref.left;
            }
            if let Some(mut cur_node) = stack.pop() {
                let cur_ref = unsafe { cur_node.as_mut() };
                f(&cur_ref.data);
                cur = cur_ref.right;
            }
        }
    }

    pub fn postorder_traverse<F>(&self, mut f: F)
    where
        F: FnMut(&T),
    {
        let mut stack = Vec::new();
        let mut cur = self.root;
        let mut last = None;
        while cur.is_some() || !stack.is_empty() {
            while let Some(mut cur_node) = cur {
                let cur_ref = unsafe { cur_node.as_mut() };
                stack.push(cur);
                cur = cur_ref.left;
            }
            if let Some(mut cur_node) = stack.last() {
                let cur_ref = unsafe { cur_node.as_mut() };
                if cur_ref.right.is_none() || cur_ref.right == last {
                    f(&cur_ref.data);
                    last = stack.pop();
                } else {
                    cur = cur_ref.right;
                }
            }
        }
    }

    fn rebalance(&mut self) {
        let mut stack = Vec::new();
        let mut cur = self.root;
        while cur.is_some() || !stack.is_empty() {
            while let Some(mut cur_node) = cur {
                let cur_ref = unsafe { cur_node.as_mut() };
                stack.push(cur);
                cur = cur_ref.left;
            }
            if let Some(mut cur_node) = stack.pop() {
                let cur_ref = unsafe { cur_node.as_mut() };
                let left_height = cur_ref.left.as_ref().map_or(-1, |node| unsafe {
                    let node_ref = node.as_ref();
                    node_ref.height
                });
                let right_height = cur_ref.right.as_ref().map_or(-1, |node| unsafe {
                    let node_ref = node.as_ref();
                    node_ref.height
                });
                cur_ref.height = left_height.max(right_height) + 1;
                if left_height - right_height > 1 {
                    let left = cur_ref.left.unwrap();
                    let left_ref = unsafe { left.as_ref() };
                    let left_left_height = left_ref.left.as_ref().map_or(-1, |node| unsafe {
                        let node_ref = node.as_ref();
                        node_ref.height
                    });
                    let left_right_height = left_ref.right.as_ref().map_or(-1, |node| unsafe {
                        let node_ref = node.as_ref();
                        node_ref.height
                    });
                    if left_left_height >= left_right_height {
                        self.rotate_right(&mut cur_node);
                    } else {
                        self.rotate_left(&mut left);
                        self.rotate_right(&mut cur_node);
                    }
                } else if right_height - left_height > 1 {
                    let right = cur_ref.right.unwrap();
                    let right_ref = unsafe { right.as_ref() };
                    let right_left_height = right_ref.left.as_ref().map_or(-1, |node| unsafe {
                        let node_ref = node.as_ref();
                        node_ref.height
                    });
                    let right_right_height = right_ref.right.as_ref().map_or(-1, |node| unsafe {
                        let node_ref = node.as_ref();
                        node_ref.height
                    });
                    if right_right_height >= right_left_height {
                        self.rotate_left(&mut cur_node);
                    } else {
                        self.rotate_right(&mut right);
                        self.rotate_left(&mut cur_node);
                    }
                }
                cur = cur_ref.right;
            }
        }
    }
    
    fn rotate_left(&mut self, node: &mut NonNull<AVLNode<T>>) {
        let mut node_ref = unsafe { node.as_mut() };
        let mut right = node_ref.right.unwrap();
        let mut right_ref = unsafe { right.as_mut() };
        node_ref.right = right_ref.left;
        right_ref.left = Some(NonNull::new(node as *mut _));
        node_ref.height = node_ref
            .left
            .as_ref()
            .map_or(-1, |node| unsafe { node.as_ref().height })
            .max(node_ref.right.as_ref().map_or(-1, |node| unsafe { node.as_ref().height }))
            + 1;
        right_ref.height = right_ref
            .left
            .as_ref()
            .map_or(-1, |node| unsafe { node.as_ref().height })
            .max(right_ref.right.as_ref().map_or(-1, |node| unsafe { node.as_ref().height }))
            + 1;
        if let Some(mut parent) = node_ref.right {
            let mut parent_ref = unsafe { parent.as_mut() };
            parent_ref.left = Some(NonNull::new(&mut node_ref as *mut _));
        } else {
            self.root = Some(NonNull::new(&mut node_ref as *mut _));
        }
        *node = right;
    }

    fn rotate_right(&mut self, node: &mut NonNull<AVLNode<T>>) {
        let mut node_ref = unsafe { node.as_mut() };
        let mut left = node_ref.left.unwrap();
        let mut left_ref = unsafe { left.as_mut() };
        node_ref.left = left_ref.right;
        left_ref.right = Some(NonNull::new(node as *mut _));
        node_ref.height = node_ref
            .left
            .as_ref()
            .map_or(-1, |node| unsafe { node.as_ref().height })
            .max(node_ref.right.as_ref().map_or(-1, |node| unsafe { node.as_ref().height }))
            + 1;
        left_ref.height = left_ref
            .left
            .as_ref()
            .map_or(-1, |node| unsafe { node.as_ref().height })
            .max(left_ref.right.as_ref().map_or(-1, |node| unsafe { node.as_ref().height }))
            + 1;
        if let Some(mut parent) = node_ref.left {
            let mut parent_ref = unsafe { parent.as_mut() };
            parent_ref.right = Some(NonNull::new(&mut node_ref as *mut _));
        } else {
            self.root = Some(NonNull::new(&mut node_ref as *mut _));
        }
        *node = left;
    }

    pub fn is_empty(&self) -> bool {
        self.root.is_none()
    }

    pub fn clear(&mut self) {
        self.root = None;
    }

    pub fn height(&self) -> i32 {
        self.root
            .as_ref()
            .map_or(-1, |node| unsafe { node.as_ref().height })
    }

    pub fn size(&self) -> usize {
        let mut size = 0;
        let mut stack = Vec::new();
        let mut cur = self.root;
        while cur.is_some() || !stack.is_empty() {
            while let Some(mut cur_node) = cur {
                let cur_ref = unsafe { cur_node.as_mut() };
                stack.push(cur);
                cur = cur_ref.left;
            }
            if let Some(mut cur_node) = stack.pop() {
                let cur_ref = unsafe { cur_node.as_mut() };
                size += 1;
                cur = cur_ref.right;
            }
        }
        size
    }

    pub fn is_balanced(&self) -> bool {
        let mut stack = Vec::new();
        let mut cur = self.root;
        while cur.is_some() || !stack.is_empty() {
            while let Some(mut cur_node) = cur {
                let cur_ref = unsafe { cur_node.as_mut() };
                stack.push(cur);
                cur = cur_ref.left;
            }
            if let Some(mut cur_node) = stack.pop() {
                let cur_ref = unsafe { cur_node.as_mut() };
                let left_height = cur_ref.left.as_ref().map_or(-1, |node| unsafe {
                    let node_ref = node.as_ref();
                    node_ref.height
                });
                let right_height = cur_ref.right.as_ref().map_or(-1, |node| unsafe {
                    let node_ref = node.as_ref();
                    node_ref.height
                });
                if (left_height - right_height).abs() > 1 {
                    return false;
                }
                cur = cur_ref.right;
            }
        }
        true
    }

    pub fn is_bst(&self) -> bool {
        let mut stack = Vec::new();
        let mut cur = self.root;
        let mut last = None;
        while cur.is_some() || !stack.is_empty() {
            while let Some(mut cur_node) = cur {
                let cur_ref = unsafe { cur_node.as_mut() };
                stack.push(cur);
                cur = cur_ref.left;
            }
            if let Some(mut cur_node) = stack.pop() {
                let cur_ref = unsafe { cur_node.as_mut() };
                if let Some(last_node) = last {
                    let last_ref = unsafe { last_node.as_ref() };
                    if cur_ref.data <= last_ref.data {
                        return false;
                    }
                }
                last = Some(cur_node);
                cur = cur_ref.right;
            }
        }
        true
    }

    pub fn is_avl(&self) -> bool {
        self.is_balanced() && self.is_bst()
    }

    pub fn to_vec(&self) -> Vec<&T> {
        let mut vec = Vec::new();
        self.inorder_traverse(|data| vec.push(data));
        vec
    }

    pub fn to_sorted_vec(&self) -> Vec<&T> {
        let mut vec = Vec::new();
        self.inorder_traverse(|data| vec.push(data));
        vec.sort();
        vec
    }

    pub fn to_string(&self) -> String
    where
        T: Display,
    {
        let mut string = String::new();
        self.inorder_traverse(|data| {
            string.push_str(&format!("{} ", data));
        });
        string
    }

    pub fn to_sorted_string(&self) -> String
    where
        T: Display,
    {
        let mut string = String::new();
        self.inorder_traverse(|data| {
            string.push_str(&format!("{} ", data));
        });
        string.pop();
        string
    }

    pub fn to_dot(&self) -> String
    where
        T: Display,
    {
        let mut string = String::new();
        string.push_str("digraph {\n");
        if let Some(mut root) = self.root {
            let root_ref = unsafe { root.as_mut() };
            string.push_str(&format!("  {};\n", root_ref.data));
            let mut stack = Vec::new();
            stack.push(root);
            while let Some(mut cur) = stack.pop() {
                let cur_ref = unsafe { cur.as_mut() };
                if let Some(left) = cur_ref.left {
                    let left_ref = unsafe { left.as_mut() };
                    string.push_str(&format!("  {} -> {};\n", cur_ref.data, left_ref.data));
                    stack.push(left);
                }
                if let Some(right) = cur_ref.right {
                    let right_ref = unsafe { right.as_mut() };
                    string.push_str(&format!("  {} -> {};\n", cur_ref.data, right_ref.data));
                    stack.push(right);
                }
            }
        }
        string.push_str("}");
        string
    }

    pub fn to_sorted_dot(&self) -> String
    where
        T: Display,
    {
        let mut string = String::new();
        string.push_str("digraph {\n");
        if let Some(mut root) = self.root {
            let root_ref = unsafe { root.as_mut() };
            string.push_str(&format!("  {};\n", root_ref.data));
            let mut stack = Vec::new();
            stack.push(root);
            while let Some(mut cur) = stack.pop() {
                let cur_ref = unsafe { cur.as_mut() };
                if let Some(left) = cur_ref.left {
                    let left_ref = unsafe { left.as_mut() };
                    string.push_str(&format!("  {} -> {};\n", cur_ref.data, left_ref.data));
                    stack.push(left);
                }
                if let Some(right) = cur_ref.right {
                    let right_ref = unsafe { right.as_mut() };
                    string.push_str(&format!("  {} -> {};\n", cur_ref.data, right_ref.data));
                    stack.push(right);
                }
            }
        }
        string.push_str("}");
        string
    }

    pub fn to_graphviz(&self, path: &str) -> std::io::Result<()> {
        use std::fs::File;
        use std::io::Write;
        let mut file = File::create(path)?;
        file.write_all(self.to_dot().as_bytes())?;
        Ok(())
    }

    pub fn to_sorted_graphviz(&self, path: &str) -> std::io::Result<()> {
        use std::fs::File;
        use std::io::Write;
        let mut file = File::create(path)?;
        file.write_all(self.to_sorted_dot().as_bytes())?;
        Ok(())
    }

    pub fn from_vec(vec: Vec<T>) -> Self {
        let mut tree = AVLTree::new();
        for data in vec {
            tree.insert(data);
        }
        tree
    }

    pub fn from_sorted_vec(vec: Vec<T>) -> Self {
        let mut tree = AVLTree::new();
        tree.root = AVLNode::from_sorted_vec(vec);
        tree
    }

    pub fn from_string(string: &str) -> Self
    where
        T: std::str::FromStr,
    {
        let mut tree = AVLTree::new();
        for data in string.split_whitespace() {
            tree.insert(data.parse().unwrap());
        }
        tree
    }

    pub fn from_sorted_string(string: &str) -> Self
    where
        T: std::str::FromStr,
    {
        let mut tree = AVLTree::new();
        tree.root = AVLNode::from_sorted_string(string);
        tree
    }

    pub fn from_graphviz(path: &str) -> std::io::Result<Self>
    where
        T: std::str::FromStr,
    {
        use std::fs::File;
        use std::io::Read;
        let mut file = File::open(path)?;
        let mut string = String::new();
        file.read_to_string(&mut string)?;
        Ok(AVLTree::from_dot(&string))
    }

    pub fn from_sorted_graphviz(path: &str) -> std::io::Result<Self>
    where
        T: std::str::FromStr,
    {
        use std::fs::File;
        use std::io::Read;
        let mut file = File::open(path)?;
        let mut string = String::new();
        file.read_to_string(&mut string)?;
        Ok(AVLTree::from_sorted_dot(&string))
    }

    pub fn from_dot(string: &str) -> Self
    where
        T: std::str::FromStr,
    {
        let mut tree = AVLTree::new();
        let mut lines = string.lines();
        lines.next();
        for line in lines {
            let mut iter = line.split_whitespace();
            let from = iter.next().unwrap();
            let to = iter.next().unwrap();
            tree.insert(from.parse().unwrap());
            tree.insert(to.parse().unwrap());
        }
        tree
    }

    pub fn from_sorted_dot(string: &str) -> Self
    where
        T: std::str::FromStr,
    {
        let mut tree = AVLTree::new();
        let mut lines = string.lines();
        lines.next();
        for line in lines {
            let mut iter = line.split_whitespace();
            let from = iter.next().unwrap();
            let to = iter.next().unwrap();
            tree.insert(from.parse().unwrap());
            tree.insert(to.parse().unwrap());
        }
        tree
    }

    pub fn from_preorder_vec(vec: Vec<T>) -> Self {
        let mut tree = AVLTree::new();
        tree.root = AVLNode::from_preorder_vec(vec);
        tree
    }

    pub fn from_preorder_string(string: &str) -> Self
    where
        T: std::str::FromStr,
    {
        let mut tree = AVLTree::new();
        for data in string.split_whitespace() {
            tree.insert(data.parse().unwrap());
        }
        tree
    }