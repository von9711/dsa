def power(num, x):  # O(log x)
    if x == 0:
        return 1
    temp = power(num, x//2)
    return temp * temp if x % 2 == 0 else temp * temp * num


def powr(num, x):   # O(log x)
    res = 1
    while x > 0:
        if x & 1 == 1:
            res *= num
        x = x >> 1
        num *= num
    return res


print(powr(3, 5))
