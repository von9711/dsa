class Node:
    def __init__(self, data):
        self.data = data
        self.next = None;
        self.prev = None;

class Doubly_List:
    def __init__(self):
        self.start = None;

    def Insert_First(self, value):
        newNode = Node(value)
        newNode.next = self.start
        newNode.prev = None
        self.start = newNode

    def Insert_Last(self, value):
        newNode = Node(value)
        temp = self.start
        while(temp.next != None):
            temp = temp.next
        newNode.next = None;
        temp.next = newNode

    def Insert_Pos(self, x, value):
        temp = self.start
        while(temp != None):
            if(temp.data == x):
                break
            temp = temp.next
        if(temp == None):
            print("pos is not valid")
        elif(temp.next == None):
            newNode = Node(value)

            temp.next = newNode
            newNode.prev = temp
            newNode.next = None;

        else:
            newNode = Node(value)
            temp.next.prev = newNode
            newNode.next = temp.next
            newNode.prev = temp
            temp.next = newNode

    def delete_First(self):
        temp = self.start
        if(self.start == None):
            print("List is empty")
        else:
            self.start = temp.next

    def delete_Last(self):
        temp = self.start
        if(self.start == None):
            print("List is empty")
        else:
            while(temp.next.next != None):
                temp = temp.next
            temp.next = None;

    def delete_mid(self, index):
        temp = self.start
        while temp.next is not None and index != 0:
            temp = temp.next
            index -= 1
        print(temp.prev.next.data)
        temp.next.prev = temp.prev
        temp.prev.next = temp.next


    def view_List(self):
        if (self.start == None):
            print("No any node exist")
        else :
            temp = self.start
            while(temp != None):
                print(temp.data, end= ' ')
                temp = temp.next

    def count_Node(self):
        temp = self.start
        count = 0
        while(temp != None):
            count+=1
            temp = temp.next
        return(count)


mylist = Doubly_List()
mylist.Insert_First(10)
mylist.Insert_First(20)
mylist.Insert_First(40)
mylist.Insert_First(110)

mylist.Insert_Last(300)

mylist.Insert_Last(200)

mylist.Insert_Pos(200, 100)
mylist.view_List()
print(mylist.count_Node())
print()
mylist.delete_First()
mylist.view_List()

print()
mylist.delete_First()
mylist.view_List()
print()
mylist.delete_Last()
mylist.view_List()
print()
mylist.delete_mid(2)
mylist.view_List()
