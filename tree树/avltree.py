#定义一个AVL树，实现了AVL树的自平衡功能，即在插入和删除节点时，自动调整树的结构，使其保持平衡

class AVLTreeNode(object):
    def __init__(self, value):
        self.value = value
        self.height = 0
        self.left = None
        self.right = None


class AVLTree(object):
    def __init__(self):
        self._root = None

    def _insert(self, node, value):
        if node is None:
            node = AVLTreeNode(value)
        elif value < node.value:
            node.left = self._insert(node.left, value)
            if (self.height(node.left) - self.height(node.right)) == 2:
                if value < node.left.value:
                    node = self._left_left_rotation(node)
                else:
                    node = self._left_right_rotation(node)
        elif value > node.value:
            node.right = self._insert(node.right, value)
            if (self.height(node.right) - self.height(node.left)) == 2:
                if value > node.right.value:
                    node = self._right_right_rotation(node)
                else:
                    node = self._right_left_rotation(node)
        node.height = max(self.height(node.left), self.height(node.right)) + 1
        return node

    def insert(self, value):
        self._root = self._insert(self._root, value)

    def _delete(self, node, value):
        if node is None:
            raise ValueError('value not found in the tree')
        elif value < node.value:
            node.left = self._delete(node.left, value)
            if (self.height(node.right) - self.height(node.left)) == 2:
                if node.right.left is not None and (self.height(node.right.left) > self.height(node.right.right)):
                    node = self._right_left_rotation(node)
                else:
                    node = self._right_right_rotation(node)
        elif value > node.value:
            node.right = self._delete(node.right, value)
            if (self.height(node.left) - self.height(node.right)) == 2:
                if node.left.right is not None and (self.height(node.left.right) > self.height(node.left.left)):
                    node = self._left_right_rotation(node)
                else:
                    node = self._left_left_rotation(node)
        elif node.left and node.right:
            if node.left.height <= node.right.height:
                min_node = self._find_min(node.right)
                node.value = min_node.value
                node.right = self._delete(node.right, min_node.value)
            else:
                max_node = self._find_max(node.left)
                node.value = max_node.value
                node.left = self._delete(node.left, max_node.value)
        else:
            if node.left:
                node = node.left
            else:
                node = node.right
        return node
    
    def delete(self, value):
        self._root = self._delete(self._root, value)

    def _find_min(self, node):
        if node.left is None:
            return node
        else:
            return self._find_min(node.left)
        
    def find_min(self):
        return self._find_min(self._root).value
    
    def _find_max(self, node):
        if node.right is None:
            return node
        else:
            return self._find_max(node.right)
        
    def find_max(self):
        return self._find_max(self._root).value
    
    def _left_left_rotation(self, node):
        k = node.left
        node.left = k.right
        k.right = node
        node.height = max(self.height(node.left), self.height(node.right)) + 1
        k.height = max(self.height(k.left), node.height) + 1
        return k
    
    def _right_right_rotation(self, node):
        k = node.right
        node.right = k.left
        k.left = node
        node.height = max(self.height(node.left), self.height(node.right)) + 1
        k.height = max(self.height(k.right), node.height) + 1
        return k
    
    def _left_right_rotation(self, node):
        node.left = self._right_right_rotation(node.left)
        return self._left_left_rotation(node)
    
    def _right_left_rotation(self, node):

        node.right = self._left_left_rotation(node.right)
        return self._right_right_rotation(node)
    
    def height(self, node):
        if node is None:
            return -1
        else:
            return node.height
        
    def _pre_order(self, node):
        if node is not None:
            print(node.value)
            self._pre_order(node.left)
            self._pre_order(node.right)

    def pre_order(self):
        self._pre_order(self._root)

    def _in_order(self, node):
        if node is not None:
            self._in_order(node.left)
            print(node.value)
            self._in_order(node.right)

    def in_order(self):
        self._in_order(self._root)

    def _post_order(self, node):
        if node is not None:
            self._post_order(node.left)
            self._post_order(node.right)
            print(node.value)

    def post_order(self):
        self._post_order(self._root)

    def _level_order(self, node):
        if node is None:
            return
        queue = []
        queue.append(node)
        while len(queue) > 0:
            node = queue.pop(0)
            print(node.value)
            if node.left is not None:
                queue.append(node.left)
            if node.right is not None:
                queue.append(node.right)

    def level_order(self):
        self._level_order(self._root)

    def _get(self, node, value):
        if node is None:
            return None
        if value < node.value:
            return self._get(node.left, value)
        elif value > node.value:
            return self._get(node.right, value)
        else:
            return node
        
    def get(self, value):
        return self._get(self._root, value)
    
    def _get_parent(self, node, value):
        if node is None:
            return None
        if value < node.value:
            if node.left.value == value:
                return node
            else:
                return self._get_parent(node.left, value)
        elif value > node.value:
            if node.right.value == value:
                return node
            else:
                return self._get_parent(node.right, value)
        else:
            return None
        
    def get_parent(self, value):
        return self._get_parent(self._root, value)
    
    def _get_min(self, node):
        if node.left is None:
            return node
        else:
            return self._get_min(node.left)
        
    def get_min(self):
        return self._get_min(self._root).value
    
    def _get_max(self, node):
        if node.right is None:
            return node
        else:
            return self._get_max(node.right)
        
    def get_max(self):
        return self._get_max(self._root).value
    