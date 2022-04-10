import sys

sys.stdin = open('input', 'r')


class Node:
    def __init__(self, data):
        self.data = data
        self.next = None


class LinkedList:
    def __init__(self):
        self.head = None

    def insert(self, data):
        if self.head is None:
            self.head = Node(data)
        else:
            #insert at end
            '''temp = self.head
            while temp.next is not None:
                temp = temp.next
            temp.next = Node(data)'''

            #insert at beg
            new = Node(data)
            new.next = self.head
            self.head = new

    def delete(self):
        if self.head is None:
            return
        temp = self.head
        '''self.head = self.head.next
        del temp'''
        while temp.next is not None:
            temp = temp.next
        del temp.next
        temp.next = None

    def __repr__(self):
        temp = self.head
        text = 'head -> '
        while temp is not None:
            text += str(temp.data) + ' -> '
            temp = temp.next
        text += 'NULL'
        return text

    '''def reverse(self):
        curr = self.head
        prev = temp = None
        while curr is not None:
            temp = curr.next
            curr.next = prev
            prev = curr
            curr = temp
        self.head = prev'''

    def reverse(self, cur, prev):
        if cur.next is None:
            cur.next = prev
            return cur
        temp = self.reverse(cur.next, cur)
        cur.next = prev
        return temp

    def midElement(self):
        slow = fast = self.head
        while fast is not None and fast.next is not None:
            slow = slow.next
            fast = fast.next.next
        return slow.data

ll = LinkedList()
ll.insert(5)
ll.insert(6)
ll.insert(8)
ll.insert(9)
ll.insert(15)
print(ll)
'''ll.head = ll.reverse(ll.head, None)
print(ll)'''
print(ll.midElement())
