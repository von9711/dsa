def printAllDivisor(num):  # O(n^1/2)
    last = []
    i = 1
    while i*i < num:
        if num % i == 0:
            print(i, end=" ")
        i += 1
    while i > 0:
        if num % i == 0:
            print(num // i, end=" ")
        i -= 1


printAllDivisor(25)
