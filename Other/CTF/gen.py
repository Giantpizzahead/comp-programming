import random

n = 17200
with open("game.replay", "wb") as fout:
    fout.write((n).to_bytes(16, byteorder='little'))
    for i in range(n):
        on = max(0, i - 250) // 11
        l = (on).to_bytes(7, byteorder='little') + (random.randint(0, 255)).to_bytes(1, byteorder='little')
        fout.write(l)
        print(l)
