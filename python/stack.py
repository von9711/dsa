top = -1
stack = [0]*10


def push(data):
    global top
    if top == 10:
        print('stack overflow')
        return
    top += 1
    stack[top] = data


def peek():
    if top == -1:
        print('stack empty')
        return
    return stack[top]

push(10)
push(20)
print(peek())
