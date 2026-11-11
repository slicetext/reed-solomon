from itertools import combinations
import statistics
import math
import random


# N is word length
# N = K + P
# Where K is message word length and P is number of parity bits
def encode(data: [int], xvals: [int], n: int):
    # [-1, 0, ... , x-1]
    values = [mult_poly(data, i) for i in xvals]
    return values


def mult_poly(coefficients: [int], x: int) -> int:
    sum: int = 0
    for i in range(len(coefficients)):
        sum += x ** (len(coefficients) - i - 1) * coefficients[i]
    return sum


def mult_two_poly(p1: [float], p2: [float]) -> [float]:
    result = [0] * (len(p1) + len(p2) - 1)
    for i in range(len(p1)):
        for j in range(len(p2)):
            result[i + j] += p1[i] * p2[j]
    return result


def lagrange_interpolation(data: [int], xvals: [int], n: int):
    polynomial: int = [0] * n

    for i in range(n):
        numerator: [float] = [1]
        denominator = 1
        for j in range(n):
            if (i != j):
                num = [1, float(-xvals[j])]
                denom = float(xvals[i] - xvals[j])
                numerator = mult_two_poly(num, numerator)
                denominator *= denom

        for j in range(len(data)):
            polynomial[j] += round((numerator[j] / denominator) * data[i])

    return polynomial


def naive_decode(data: [int], xvals: [int], k: int) -> [int]:
    results: [[int]] = [[]] * math.comb(len(data), k)
    combos = combinations(range(len(data)), k)
    count: int = 0
    for combo in combos:
        results[count] = lagrange_interpolation(
            [data[i] for i in combo],
            [xvals[i] for i in combo], k
        )
        count += 1
    results = [tuple(i) for i in results]
    return list(statistics.mode(results))


def div_two_poly(numerator: [float], denominator: [float]) -> [float]:
    remainder = list(numerator)

    quotient = [0] * (len(numerator) - len(denominator) + 1)

    while (remainder[0] == 0):
        remainder.pop(0)
    while (denominator[0] == 0):
        denominator.pop(0)

    for i in range(len(quotient)):
        first_term_result = remainder[0] / denominator[0]
        quotient[i] = first_term_result
        subtractor = [j * first_term_result for j in denominator]
        remainder = [
            remainder[j] - subtractor[j] for j in range(len(subtractor))
        ] + remainder[len(subtractor):]
        while (remainder[0] == 0 and len(remainder) > 1):
            remainder.pop(0)

    return quotient, remainder


# Gao's algo
def decode(data: [int], xvals: [int], k: int) -> [int]:
    g_0 = lagrange_interpolation(data, xvals, len(data))
    g = [1]
    for i in xvals:
        g = mult_two_poly(g, [1, -i])
    stop_threshold = (len(data) + k) / 2
    r, u, v = eea(g, g_0, stop_threshold)
    return div_two_poly(r, v)


# Extended Euclidean Algorithm
def eea(n: [int], d: [int], stop_threshold):
    q, r = div_two_poly(n, d)
    if len(n) < stop_threshold:
        return q, [1], [0]
    gcd, s, t = eea(d, r, stop_threshold)
    temp = mult_two_poly(q, t)
    return gcd, t, [s[i] - temp[i] for i in range(len(s))]


if __name__ == "__main__":
    k: int = 4
    p: int = 4
    n: int = k + p
    amount: int = 100
    score: int = 0
    for i in range(amount):
        data = [random.randint(-100, 100) for _ in range(k)]
        xvals = [i - 1 for i in range(n)]
        coded: [int] = encode(data, xvals, n)
        corruption_index: int = random.randint(0, n - 1)
        coded[corruption_index] = random.randint(-100, 100)
        decoded = decode(coded, xvals, k)
        print(str(data) + " : " + str(decoded))
        if (data == decoded):
            score += 1

    print(str(score) + "/" + str(amount))
