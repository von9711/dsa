import math


def isPrime(num):
    if num <= 1:
        return False

    if num == 2 or num == 3:
        return True

    if num % 2 == 0 or num % 3 == 0:
        return False

    for i in range(5, math.ceil(math.sqrt(num))+1, 6):
        if num % i == 0 or num % (i + 2) == 0:
            return False

    return True


if __name__ == '__main__':
    print(isPrime(2))
