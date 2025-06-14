import sympy as sp
import math


def is_coprime(x: int, y: int) -> bool:
    """
    Проверяет, являются ли два числа взаимно простыми.
    :param x: Первое число.
    :param y: Второе число.
    :return: True, если числа взаимно простые, иначе False.
    """
    return math.gcd(x, y) == 1


def generate_prime() -> int:
    """
    Генерирует случайное простое число в диапазоне от 100 до 5000.
    :return: Случайное простое число.
    """
    return sp.randprime(100, 5000)


def generate_keys() -> tuple[tuple[int, int], tuple[int, int]]:
    """
    Генерирует пару ключей для RSA: открытый и закрытый.
    :return: Кортеж из двух кортежей: (открытый ключ (e, n), закрытый ключ (d, n)).
    """
    # Генерация двух различных простых чисел
    p = generate_prime()
    q = generate_prime()
    while p == q:
        q = generate_prime()

    # Вычисление модуля n и функции Эйлера phi(n)
    n = p * q
    phi = (p - 1) * (q - 1)

    # Выбор открытой экспоненты e (взаимно простой с phi)
    e = 2
    while e < phi:
        if is_coprime(e, phi):
            break
        e += 1

    # Вычисление закрытой экспоненты d (обратной к e по модулю phi)
    k = 1
    while True:
        d = (k * phi + 1) / e
        if d.is_integer():
            break
        k += 1
    d = int(d)

    # Возврат ключей
    public_key = (e, n)
    private_key = (d, n)
    return public_key, private_key


def rsa_encrypt(message: str, public_key: tuple[int, int]) -> list[int]:
    """
    Шифрует сообщение с использованием открытого ключа RSA.
    :param message: Сообщение для шифрования.
    :param public_key: Открытый ключ (e, n).
    :return: Список зашифрованных чисел.
    """
    e, n = public_key
    return [pow(ord(char), e, n) for char in message]


def rsa_decrypt(encrypted_message: list[int], private_key: tuple[int, int]) -> str:
    """
    Расшифровывает сообщение с использованием закрытого ключа RSA.
    :param encrypted_message: Список зашифрованных чисел.
    :param private_key: Закрытый ключ (d, n).
    :return: Расшифрованное сообщение.
    """
    d, n = private_key
    return ''.join([chr(pow(char, d, n)) for char in encrypted_message])


# Пример использования
if __name__ == "__main__":
    # Генерация ключей
    public_key, private_key = generate_keys()
    print("Открытый ключ:", public_key)
    print("Закрытый ключ:", private_key)

    # Шифрование сообщения
    message = "ABCD АБВГД"
    encrypted_message = rsa_encrypt(message, public_key)
    print("Зашифрованное сообщение:", encrypted_message)

    # Расшифровка сообщения
    decrypted_message = rsa_decrypt(encrypted_message, private_key)
    print("Расшифрованное сообщение:", decrypted_message)
