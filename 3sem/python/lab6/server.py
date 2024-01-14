import os
import re
import smtplib
import socket
import random

import dotenv

# путь до .env файла
dotenv_path = os.path.join(os.path.dirname(__file__), ".env")
if os.path.exists(dotenv_path):
    dotenv.load_dotenv(dotenv_path)

# данные из .env файла
admin_email = os.getenv("EMAIL_LOGIN")
admin_password = os.getenv("EMAIL_PASSWORD")
smptaddr = str(os.getenv("SMTP_HOST")) + ":" + str(os.getenv("SMTP_PORT"))

# хост и порт сервера
HOST = "127.0.0.1"
PORT = 50006


# проверка корректности адреса
def validate(email):
    regex = r'\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Z|a-z]{2,7}\b'
    if re.fullmatch(regex, email):
        return True
    return False


while True:
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST, PORT))
        s.listen()
        connection, address = s.accept()

        with connection:
            print("Connected by", address)
            # получение адреса и сообщения
            data = connection.recv(1024).decode("utf-8")

            # проверка на пустые данные
            try:
                email, message = data.split("~")
                if not validate(email) or not message:
                    raise Exception
            except Exception:
                connection.sendall("Неверные данные".encode())

            else:
                # установка темы письма
                message = ("Subject:" + "Ticket #" + str(
                    random.randint(10000, 99999)) + " Mailer" + "\n\n" + message).encode('utf-8')

                # отправка письма
                try:
                    server = smtplib.SMTP_SSL(smptaddr)
                    server.login(admin_email, admin_password)
                    server.sendmail(admin_email, [admin_email, email], message)
                except Exception:
                    connection.sendall("Ошибка отправления".encode())
                else:
                    connection.sendall("OK".encode())
            connection.close()
