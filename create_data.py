from random import randint
import csv

data = [['index', 'nums...'],]
for i in range(500):
    row_list = [i]
    num_nums = randint(1, 2501)
    for j in range(num_nums):
        row_list.append(randint(0, 1000))

    data.append(row_list)


# Open with newline='' to prevent blank lines between rows
with open('output.csv', 'w', newline='') as file:
    writer = csv.writer(file)
    writer.writerows(data)
        