import random

filepath = "dane.txt"

with open(filepath, 'w') as file:
    for i in range(100000):
        x = random.uniform(0, 100)
        file.write(f"{x}\n")

print("Dane zostały zapisane do pliku.")
