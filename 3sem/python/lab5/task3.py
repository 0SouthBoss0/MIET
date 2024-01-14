import concurrent.futures
import math
import time

N = 500

# матрицы под заполнение
resultmatrix1 = [[0 for _ in range(N)] for _ in range(N)]
resultmatrix2 = [[0 for _ in range(N)] for _ in range(N)]


# функция, производящая вычисление
def calculate(q, p):
    return q, p, math.sqrt(abs(q - p))


# последовательное вычисление
def withoutconcurrent():
    time_start = time.time()

    for i in range(1, N + 1):
        for j in range(1, N + 1):
            result = calculate(i, j)[2]
            resultmatrix1[i - 1][j - 1] = result

    time_end = time.time()
    return time_end - time_start


# параллельное вычисление
def withconcurrent():
    time_start = time.time()

    with concurrent.futures.ThreadPoolExecutor() as executor:
        futures = [executor.submit(calculate, i, j) for i in range(1, N + 1) for j in range(1, N + 1)]
        for _, future in enumerate(concurrent.futures.as_completed(futures)):
            i, j, result = future.result()
            resultmatrix2[i - 1][j - 1] = result

    time_end = time.time()
    return time_end - time_start


if __name__ == '__main__':
    print("withoutconcurrent:", withoutconcurrent())
    print("withconcurrent:", withconcurrent())
