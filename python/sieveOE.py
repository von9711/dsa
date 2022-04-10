# sieve of eratosthenes


def soe(num):  # O(log log n)
    prime = [True] * (num + 1)
    prime[0] = prime[1] = False

    i = 2
    while i <= num:
        if prime[i]:
            print(i, end=" ")
            for j in range(i*i, num + 1, i):
                prime[j] = False
        i += 1


soe(100)
