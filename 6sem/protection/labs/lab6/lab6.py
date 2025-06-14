import hashlib
import random
from math import gcd

from sympy import randprime


def generate_keys(bit_length=512):
    # 1. Выбираем большое простое p
    p = randprime(2 ** (bit_length - 1), 2 ** bit_length)

    # 2. Находим генератор g (простой способ: берём любое число и возводим в степень)
    def find_generator(p):
        # Факторизуем p-1 (упрощённо)
        factors = []
        temp = p - 1
        for i in [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31]:
            if temp % i == 0:
                factors.append(i)
                while temp % i == 0:
                    temp = temp // i
        # Ищем генератор
        for g in range(2, p):
            if all(pow(g, (p - 1) // f, p) != 1 for f in factors):
                return g
        return None

    g = find_generator(p)
    if g is None:
        raise ValueError("Не удалось найти генератор для p")

    # 3. Секретный ключ x
    x = random.randint(2, p - 2)
    # 4. Открытый ключ y
    y = pow(g, x, p)

    return p, g, x, y


def sign_message(message, p, g, x):
    h = int(hashlib.sha256(message.encode()).hexdigest(), 16) % p
    # Выбираем случайное k (взаимно простое с p-1)
    while True:
        k = random.randint(2, p - 2)
        if gcd(k, p - 1) == 1:
            break

    a = pow(g, k, p)
    # Вычисляем b = (h - x*r) * k^(-1) mod (p-1)
    k_inv = pow(k, -1, p - 1)
    b = (h - x * a) * k_inv % (p - 1)
    return a, b


def verify_signature(message, signature, p, g, y):
    a, b = signature
    if not (0 < a < p and 0 < b < p - 1):
        return False

    h = int(hashlib.sha256(message.encode()).hexdigest(), 16) % p
    left = pow(g, h, p)
    right = (pow(y, a, p) * pow(a, b, p)) % p
    return left == right


p, g, x, y = generate_keys(bit_length=32)
message = "Hello, World!"
print(f"Сообщение: {message}")
signature = sign_message(message, p, g, x)
print(f"Подпись (r, s): {signature}")

is_valid = verify_signature(message, signature, p, g, y)
print(f"Подпись {'валидна' if is_valid else 'невалидна'}!")

# Попытка подменить сообщение
fake_message = "Fake message"
is_valid_fake = verify_signature(fake_message, signature, p, g, y)
print(f"Подпись для '{fake_message}' {'валидна' if is_valid_fake else 'невалидна'}!")
