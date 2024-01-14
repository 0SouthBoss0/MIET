import os
import socket
import dotenv

# путь до .env файла
dotenv_path = os.path.join(os.path.dirname(__file__), ".env")
if os.path.exists(dotenv_path):
    dotenv.load_dotenv(dotenv_path)

# хост и порт сервера
HOST = "127.0.0.1"
PORT = 50006

while True:
    address = input("Введите адрес:")
    text = input("Введите сообщение:")
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST, PORT))
        s.sendall((address + "~" + text).encode('utf-8'))

        data = s.recv(1024).decode()
        if data == "OK":
            print("Отправлено успешно!")
            s.close()
            break
        else:
            print(data)
