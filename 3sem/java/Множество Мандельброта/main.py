import numpy as np
from matplotlib import pyplot as plt
import time
from datetime import timedelta

start_time = time.time()

realmin = -2
realmax = 1
imagmin = -1.25
imagmax = 1.25
iters = 50
accuracy = 0.01
pointsize = 3


def isValid(c):
    k = 0
    z = 0j + 0
    while k < iters:
        z = z ** 2 + c
        k += 1
        if abs(z) > 2:
            return 0
    return 1


for re in np.arange(realmin, realmax, accuracy):
    for im in np.arange(imagmin, imagmax, accuracy):
        if isValid(complex(re, im)):
            plt.scatter(re, im, s=pointsize, c="k")
    print(re)

elapsed_time_secs = time.time() - start_time

msg = "Execution took: %s secs (Wall clock time)" % timedelta(seconds=round(elapsed_time_secs))

print(msg)
plt.show()
input()
