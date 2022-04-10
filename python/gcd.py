def gcd(num1, num2):    # O(log(min(a,b))
    while num1 % num2 != 0:
        num1, num2 = num2, num1 % num2
    return num2


def lcm(num1, num2):    # O(log(min(a,b))
    hcf = gcd(num1, num2)
    return num1 * num2 // hcf


print(lcm(4, 6))
