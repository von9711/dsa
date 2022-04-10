from math import ceil, floor, sqrt
from prime import isPrime


def primeFactors(num):
    i = 2
    while i*i <= num:
        while num % i == 0:
            print(i, end=" ")
            num //= i
        i += 1
    if i > 1:
        print(num, end="")
    print()


primeFactors(84)
