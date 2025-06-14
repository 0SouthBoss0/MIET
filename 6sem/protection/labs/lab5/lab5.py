import random
import time
import math

import sympy as sp


def is_prime_rabin_miller(p, t=5):
    if p <= 1:
        return False
    elif p <= 3:
        return True
    elif p % 2 == 0:
        return False

    # Разложение p-1 в вид 2^b * m
    b = 0
    m = p - 1
    while m % 2 == 0:
        m //= 2
        b += 1

    # Проведение t тестов
    for _ in range(t):
        a = random.randint(2, p - 2)
        z = pow(a, m, p)

        if z == 1 or z == p - 1:
            continue

        for j in range(b - 1):
            z = pow(z, 2, p)
            if z == p - 1:
                break
            if z == 1:
                return False
        else:
            return False
    return True


def generate_large_prime(n_bits, rabin_miller_checks=5):
    if n_bits < 2:
        raise ValueError("Длина числа должна быть не менее 2 бит")

    # Предварительно вычисленные простые числа до 2000 для быстрой проверки
    small_primes = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
                    73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151,
                    157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233,
                    239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317,
                    331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419,
                    421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503,
                    509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607,
                    613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701,
                    709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811,
                    821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911,
                    919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997, 1009, 1013,
                    1019, 1021, 1031, 1033, 1039, 1049, 1051, 1061, 1063, 1069, 1087, 1091, 1093,
                    1097, 1103, 1109, 1117, 1123, 1129, 1151, 1153, 1163, 1171, 1181, 1187, 1193,
                    1201, 1213, 1217, 1223, 1229, 1231, 1237, 1249, 1259, 1277, 1279, 1283, 1289,
                    1291, 1297, 1301, 1303, 1307, 1319, 1321, 1327, 1361, 1367, 1373, 1381, 1399,
                    1409, 1423, 1427, 1429, 1433, 1439, 1447, 1451, 1453, 1459, 1471, 1481, 1483,
                    1487, 1489, 1493, 1499, 1511, 1523, 1531, 1543, 1549, 1553, 1559, 1567, 1571,
                    1579, 1583, 1597, 1601, 1607, 1609, 1613, 1619, 1621, 1627, 1637, 1657, 1663,
                    1667, 1669, 1693, 1697, 1699, 1709, 1721, 1723, 1733, 1741, 1747, 1753, 1759,
                    1777, 1783, 1787, 1789, 1801, 1811, 1823, 1831, 1847, 1861, 1867, 1871, 1873,
                    1877, 1879, 1889, 1901, 1907, 1913, 1931, 1933, 1949, 1951, 1973, 1979, 1987, 1993, 1997, 1999]

    iterations = 0
    start_time = time.time()

    while True:
        iterations += 1

        # Шаг 1: Генерация случайного n-битного числа
        p = random.getrandbits(n_bits)

        # Шаг 2: Установка старшего и младшего битов в 1
        p |= (1 << (n_bits - 1)) | 1

        # Шаг 3: Проверка на делимость на малые простые числа
        for prime in small_primes:
            if p % prime == 0 and p != prime:
                break
        else:
            # Шаг 4: Проверка тестом Рабина-Миллера
            if is_prime_rabin_miller(p, t=rabin_miller_checks):
                end_time = time.time()
                return p, iterations, end_time - start_time


def find_primes_in_range(start, end):
    start_time = time.time()
    primes = []

    # Проверяем четность начала диапазона
    if start <= 2:
        primes.append(2)
        current = 3
    else:
        current = start if start % 2 != 0 else start + 1

    # Проверяем только нечетные числа
    while current <= end:
        if is_prime_rabin_miller(current):
            primes.append(current)
        current += 2
        if current > end:
            break

    end_time = time.time()
    return primes, end_time - start_time


def find_primitive_roots(n, count=100):
    start_time = time.time()

    if not sp.isprime(n):
        return [], 0.0  # Первообразные корни существуют только для простых чисел или степеней простых (кроме 2* p^k)

    phi = n - 1
    factors = sp.primefactors(phi)
    primitive_roots = []

    for g in range(1, n):
        if math.gcd(g, n) != 1:
            continue

        is_primitive = True
        for p in factors:
            if pow(g, phi // p, n) == 1:
                is_primitive = False
                break

        if is_primitive:
            primitive_roots.append(g)
            if len(primitive_roots) >= count:
                break

    elapsed_time = time.time() - start_time
    return primitive_roots, elapsed_time


def diffie_hellman_key_exchange(p, Xa=None, Xb=None):
    if not is_prime_rabin_miller(p):
        print("Ошибка: введенное число не является простым!")
        return

    # Находим первообразный корень
    roots, _ = find_primitive_roots(p, count=1)
    if not roots:
        print("Не удалось найти первообразный корень для данного p!")
        return
    g = roots[0]
    print(f"Первообразный корень g: {g}")

    if not Xa or not Xb:
        Xa = random.randint(2, p - 2)
        Xb = random.randint(2, p - 2)
    print(f"Секретный ключ абонента A (Xa): {Xa}")
    print(f"Секретный ключ абонента B (Xb): {Xb}")

    # Вычисление открытых ключей
    Ya = pow(g, Xa, p)
    Yb = pow(g, Xb, p)

    print(f"\nОткрытый ключ абонента A (Ya = g^Xa mod p): {Ya}")
    print(f"Открытый ключ абонента B (Yb = g^Xb mod p): {Yb}")

    # Обмен открытыми ключами и вычисление общего секретного ключа
    Ka = pow(Yb, Xa, p)  # Секретный ключ, вычисленный абонентом A
    Kb = pow(Ya, Xb, p)  # Секретный ключ, вычисленный абонентом B

    print(f"\nОбщий секретный ключ, вычисленный абонентом A: {Ka}")
    print(f"Общий секретный ключ, вычисленный абонентом B: {Kb}")

    if Ka == Kb:
        print("\nОбмен ключами прошел успешно! Ключи совпадают.")
    else:
        print("\nОшибка! Ключи не совпадают.")


print("\n---Генерация простого n-битного числа---")
prime, iterations, time_taken = generate_large_prime(n_bits=1000, rabin_miller_checks=5)
print("Результат:")
print(f"Сгенерированное простое число: {prime}")
print(f"Количество бит: {prime.bit_length()}")
print(f"Количество итераций генерации: {iterations}")
print(f"Затраченное время: {time_taken:.4f} секунд")
print("--------------------------------------")

print("\n---Все простые числа из диапазона---")
primes, time_taken = find_primes_in_range(start=10000, end=20000)
print("Результат:")
print(f"Найдено простых чисел: {len(primes)}")
print(f"Затраченное время: {time_taken:.4f} секунд")
print("Простые числа:")
print(primes)
print("--------------------------------------")

print("\n---Первые 100 первообразных корней-_-")
roots, time_taken = find_primitive_roots(19997)
print(f"Первые {len(roots)} первообразных корней по модулю {19997}:")
print(roots)
print(f"\nВремя выполнения: {time_taken:.4f} секунд")
print("--------------------------------------")

print("\n---Обмен ключами между абонентами по схеме Диффи-Хеллмана---")
prime, _, _ = generate_large_prime(n_bits=256, rabin_miller_checks=5)
diffie_hellman_key_exchange(prime)
print("--------------------------------------")
