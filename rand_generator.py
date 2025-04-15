import random
import struct

with open("liczby_50_000_000.bin", "wb") as f:
    for _ in range(50_000_000):
        f.write(struct.pack("i", random.randint(1, 10_000_000)))
