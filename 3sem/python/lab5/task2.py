import queue
import threading

q = queue.Queue()


def function():
    while True:
        # получаем текущее число из очереди
        num = q.get()
        # выводим число
        print(threading.current_thread().name, num)
        # завершаем выполнение задачи
        q.task_done()


# создаем два потока
threading.Thread(target=function, daemon=True).start()
threading.Thread(target=function, daemon=True).start()

# добавляем в очередь 30 чисел
for i in range(30):
    q.put(i)

q.join()
print('Все задачи выполнены')
