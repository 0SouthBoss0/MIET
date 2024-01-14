import base64
import email
import imaplib
import os
import re
import time
from email.header import decode_header
import dotenv

# путь до .env файла
dotenv_path = os.path.join(os.path.dirname(__file__), ".env")
if os.path.exists(dotenv_path):
    dotenv.load_dotenv(dotenv_path)

# данные из .env файла
server = os.getenv("IMAP_HOST")
serverport = int(os.getenv("IMAP_PORT"))
login = os.getenv("EMAIL_LOGIN")
pause_time = int(os.getenv("PERIOD_CHECK"))
password = os.getenv("EMAIL_PASSWORD")

# файлы для логирования
success_file = open("success_request.log", "a", encoding="utf-8")
error_file = open("error_request.log", "a", encoding="utf-8")

while True:
    with imaplib.IMAP4_SSL(server, serverport) as imap:
        # вход и просмотр непрочитанных писем во входящих
        imap.login(login, password)
        imap.select("INBOX")
        res, messages = imap.search(None, "UNSEEN")

        if messages[0]:
            res, msg = imap.fetch(messages[0].decode().split(" ")[0], "(RFC822)")
            msg = email.message_from_bytes(msg[0][1])
            msgSubject = decode_header(msg["Subject"])[0][0]

            # проверка совпадения темы письма с форматом "Ticket #12345 Mailer"
            if re.match(r"Ticket #\d{5} Mailer", str(msgSubject)):
                ID = re.search(r'#(.+?) ', str(msgSubject)).group()[slice(1, 6)]
                for part in msg.walk():
                    if part.get_content_maintype() == 'text' and part.get_content_subtype() == 'plain':
                        text = part.get_payload()
                print("Сообщение с Ticket")
                success_file.write(ID + ": " + text)
                success_file.flush()

            else:
                for part in msg.walk():
                    if part.get_content_maintype() == 'text' and part.get_content_subtype() == 'plain':
                        text = part.get_payload()
                print("Сообщение без Ticket")
                error_file.write("Сообщение без Ticket: " + str(base64.b64decode(text[:-1]).decode()))
                error_file.flush()
    time.sleep(pause_time)
