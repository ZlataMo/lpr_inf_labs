import numpy as np
import matplotlib.pyplot as plt
def least_squares(x_arr, y_arr):
    size= x_arr.shape[0]
    print(size)
    b=(np.sum(y_arr)*np.sum(x_arr**2)-np.sum(x_arr)*np.sum(x_arr*y_arr))/(size*np.sum(x_arr**2)-np.sum(x_arr)**2)
    a=(np.sum(y_arr)-size*b)/np.sum(x_arr)
    return a, b

mas = []
with open('max_lin.txt') as file:
    s = file.readline()
    while (s!=''):
        mas.append(list(map(float, s.split())))
        s = file.readline()
mas.sort()
mas_x = []
mas_y = []
for i in range(100):
    mas_x.append(mas[i][0])
    mas_y.append(mas[i][1])
X_coord=np.array(mas_x)
Y_coord=np.array(mas_y)
plt.xlabel("Размер массива")
plt.ylabel("Время работы, мс")
a, b= least_squares(X_coord, Y_coord)
plt.plot(X_coord, Y_coord , '.', color="r", label='эксп')
plt.plot(X_coord,a*X_coord+b , color="b", label=f'{a}x+({b})')
plt.legend()
plt.grid()
plt.show()