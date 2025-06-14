import os
import random


def get_file_size(file_path):
    """
    Возвращает размер файла в байтах.

    :param file_path: Путь к файлу.
    :return: Размер файла в байтах или сообщение об ошибке.
    """
    try:
        size = os.path.getsize(file_path)
        return size
    except FileNotFoundError:
        return f"File {file_path} not found!"
    except Exception as e:
        return f"Unexpected error - {e}!"


def count_byte_frequency(file_path):
    """
    Подсчитывает частоту появления каждого байта в файле.

    :param file_path: Путь к файлу.
    :return: Словарь с частотой появления байтов или сообщение об ошибке.
    """
    try:
        byte_frequency = {}
        with open(file_path, 'rb') as file:
            for byte in file.read():
                byte_frequency[byte] = byte_frequency.get(byte, 0) + 1
        return dict(sorted(byte_frequency.items(), key=lambda item: item[1], reverse=True))
    except FileNotFoundError:
        return "Файл не найден"
    except Exception as e:
        return f"Произошла ошибка: {e}"


def encrypt_file(input_file, output_file, key):
    """
    Шифрует файл с использованием заданного ключа.

    :param input_file: Путь к исходному файлу.
    :param output_file: Путь к зашифрованному файлу.
    :param key: Ключ для шифрования.
    """
    with open(input_file, 'rb') as f_in, open(output_file, 'wb') as f_out:
        for byte in f_in.read():
            f_out.write(bytes([key[byte]]))


def generate_encryption_key(key_file='key.txt'):
    """
    Генерирует случайный ключ из 256 уникальных байтов и сохраняет его в файл.

    :param key_file: Имя файла для сохранения ключа (по умолчанию 'key.txt').
    """
    key = list(range(256))
    random.shuffle(key)
    key_bytes = bytes(key)
    with open(key_file, 'wb') as f:
        f.write(key_bytes)
    print(f"Ключ успешно сгенерирован и сохранен в файл {key_file}.")


def create_decryption_key(key):
    """
    Создает ключ для расшифрования на основе ключа шифрования.

    :param key: Ключ шифрования.
    :return: Ключ для расшифрования.
    """
    decryption_key = bytearray(256)
    for i, byte in enumerate(key):
        decryption_key[byte] = i
    return decryption_key


def load_key(key_file):
    """
    Загружает ключ из файла.

    :param key_file: Путь к файлу с ключом.
    :return: Ключ.
    :raises ValueError: Если ключ не содержит 256 уникальных байтов.
    """
    with open(key_file, 'rb') as f:
        key = f.read()
    if len(key) != 256 or len(set(key)) != 256:
        raise ValueError("Ключ должен содержать 256 уникальных байтов.")
    return key


# Демонстрация работы функций

# Пример работы с размером файла
file_path = 'docfile.doc'
file_size = get_file_size(file_path)

if isinstance(file_size, int):
    print(f"Размер файла '{file_path}' составляет {file_size} байт.")
else:
    print(file_size)

# Пример работы с частотой байтов
frequency = count_byte_frequency(file_path)

if isinstance(frequency, dict):
    print("Частота появления байтов в файле:")
    for byte_value, count in frequency.items():
        print(f"Байт {hex(byte_value)} встречается {count} раз")
else:
    print(frequency)

# Генерация ключа и шифрование файла
generate_encryption_key()
key = load_key("key.txt")

# Шифрование файла
encrypt_file("docfile.doc", "doccrypted.xxx", key)

# Расшифрование файла
encrypt_file("doccrypted.xxx", "docfile_NEW.doc", create_decryption_key(key))
