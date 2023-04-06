import ctypes
import matplotlib.pyplot as plt

def read_data():
    with open("game.beatmap", "rb") as fin:
        data = fin.read()
    return data

data = read_data()
loc = 0

def read(size):
    global loc
    result = data[loc:loc+size]
    loc += size
    return result

def read_int(size):
    global loc
    res = 0
    for i in reversed(range(loc, loc+size)):
        res <<= 8
        res += data[i]
    loc += size
    return res

def read_float(size):
    global loc
    res = 0
    for i in reversed(range(loc, loc+size)):
        res <<= 8
        res += data[i]
    loc += size
    return ctypes.c_float.from_buffer(ctypes.c_uint32(res)).value

print(data[:50])

out_notes = open("notes.txt", "w")
num_notes = read_int(2)
print(f"{num_notes=}")  # num_notes = 1722
read(14)
for i in range(num_notes):
    x = read_float(4)
    y = read_float(4)
    x = round(x * 10 + 9) // 2
    y = round(y * 10 + 9) // 2
    y = 9 - y
    t = read_int(2)
    u3 = read_int(6)
    color = read_int(3)
    u4 = read_int(5)
    if color == 255:
        c = 'r'
    elif color == 16711680:
        c = 'b'
    else:
        c = 'g'
    # print(f"{t=:05} {x=:6.3f} {y=:6.3f} {c=}")
    out_notes.write(f"{t} {x} {y} {c}\n")
out_notes.close()

out_cond = open("conditions.txt", "w")
# 51056 lines
cnt = {}
max_a = -1
min_a = 1733
for i in range(51056):
    a = read_int(8)
    min_a = min(a, min_a)
    max_a = max(a, max_a)
    b = read_int(8)
    c = read_int(8)
    d = read_int(8)
    x = read(32)
    y = ''
    for v in x:
        y += hex(v // 16)[2:]
        y += hex(v % 16)[2:]
    if y ==   '8786afa6d7c6a0e6d886f6f8e6e7f6c47e6e8080808080808080808080808080':
        id = 0
    elif y == '8786afa6d7c6a0e6d886f6e7f6c47e6e80808080808080808080808080808080':
        id = 1
    elif y == '8786afa6d7c6a0e6d886f6f8e69ff6c47e6e8080808080808080808080808080':
        id = 2
    elif y == '8786afa6d7c6a0e6d886f69ff6c47e6e80808080808080808080808080808080':
        id = 3
    elif y == '6effe5f6afd587c47ed7d5afc47e6e8080808080808080808080808080808080':
        id = 4
    elif y == 'f687edafddd7cd81c47ea7dccfcc81c47e6e8080808080808080808080808080':
        id = 5
    else:
        id = -1
    cnt.setdefault(id, 0)
    cnt[id] += 1
    # print('X' if id == 3 else ' ', end='')
    # e = read_int(8)
    # f = read_float(4)
    # g = read_float(4)
    # read(16)
    # # print(i)
    if id == 4:
        print(f"{a=} {b=} {c=} {d=} {id=}")
    if id < 4:
        out_cond.write(f"{id} {a} {b} {c} {d}\n")
    else:
        out_cond.write(f"{id} {a} {b} {c}\n")
out_cond.close()

print("Done")
print(min_a, max_a)
