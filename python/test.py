def stairs(n: int, k: int, status: list) -> int:
    dp = [0 for i in range(k)]
    dp[0] = 1
    for i in range(1, n+1):
        if not status[i]:
            dp[i % k] = 0
            continue
        for j in range(1, k):
            if i-j >= 0:
                dp[i % k] += dp[(i-j) % k]

    return dp[n % k]

n, k = 7, 3
status = [True, False, True, False, False, True, True, True]
print(stairs(n, k, status))
