import datetime
import sys
import psutil
import platform

def some_function():
    total = 0
    for i in range(1, 1000000):
        total += i
    return total

# Zakładając, że filepath jest zdefiniowane w module 'generowanie'
from generowanie import filepath

# Wczytanie danych z pliku
with open('dane.txt', 'r') as file:
    lines = file.readlines()

# Konwersja danych do float
lines = [float(line.strip()) for line in lines]

# Mierzenie czasu sortowania
start_time = datetime.datetime.now()
posortowane = sorted(lines)
end_time = datetime.datetime.now()

# Czas wykonania sortowania
execution_time = end_time - start_time

# Zapisanie posortowanych danych do pliku
sorted_filepath = "posortowane_dane.txt"
with open(sorted_filepath, 'w') as file:
    for x in posortowane:
        file.write(f"{x}\n")

# Zapisanie informacji o czasie i systemie do oddzielnego pliku
wynik_filepath = "wynik.txt"  # Plik, do którego zapiszemy dodatkowe informacje
with open(wynik_filepath, 'w') as file:
    file.write(f"Czas sortowania: {execution_time}\n")
    file.write(f"Program wykonujący sortowanie: Python {sys.version}\n")

    # Informacje o CPU
    file.write(f"Liczba rdzeni CPU (fizycznych): {psutil.cpu_count(logical=False)}\n")  # Liczba rdzeni fizycznych
    file.write(f"Liczba logicznych rdzeni CPU: {psutil.cpu_count(logical=True)}\n")  # Liczba rdzeni logicznych
    file.write(f"Obciążenie CPU: {psutil.cpu_percent(interval=1)}%\n")  # Obciążenie CPU w procentach

    # Informacje o pamięci RAM
    mem = psutil.virtual_memory()
    file.write(f"Całkowita pamięć RAM: {mem.total} bytes\n")
    file.write(f"Wykorzystana pamięć RAM: {mem.used} bytes\n")
    file.write(f"Wolna pamięć RAM: {mem.free} bytes\n")

    # Informacje o dysku
    disk = psutil.disk_usage('/')
    file.write(f"Całkowita pamięć dysku: {disk.total} bytes\n")
    file.write(f"Wykorzystana pamięć dysku: {disk.used} bytes\n")
    file.write(f"Wolna pamięć dysku: {disk.free} bytes\n")

    # Informacje o systemie
    file.write(f"Wersja systemu: {platform.version()}\n")
    file.write(f"Nazwa systemu operacyjnego: {platform.system()}\n")

print(f"Informacje zostały zapisane do pliku {wynik_filepath}.")
