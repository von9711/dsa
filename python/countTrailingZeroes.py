def countTrailingZeroes(n):
    count = 0
    i = 5
    while i <= n:
        count += n // i
        i *= 5
    return count


print(countTrailingZeroes(251))