import os
import threading
import time


# получение числа файлов в директории
def find_amount_files(dic):
    _, _, files = next(os.walk(dic))
    return len(files)


# создание файла с количеством файлов в директории
def create_files():
    folder_iter = list(os.walk(os.getcwd()))
    for current_folder, _, _ in folder_iter:
        amount = str(find_amount_files(current_folder))
        with open(os.path.join(current_folder, "size.txt"), "w") as f:
            f.write(amount)


if __name__ == '__main__':
    # один поток
    t1 = threading.Thread(target=create_files, args=())

    time_start = time.time()
    t1.start()
    t1.join()
    time_end = time.time()

    print("Один поток:", time_end - time_start)

    # два потока
    t2 = threading.Thread(target=create_files, args=())
    t3 = threading.Thread(target=create_files, args=())

    time_start = time.time()
    t2.start()
    t3.start()
    t2.join()
    t3.join()
    time_end = time.time()

    print("Два потока:", time_end - time_start)
