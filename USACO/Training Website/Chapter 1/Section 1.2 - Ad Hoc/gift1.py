"""
ID: sunnyky1
LANG: PYTHON3
TASK: gift1
"""

with open("gift1.in", 'r') as fin:
    num_people = int(fin.readline().strip())
    people = {}
    for i in range(num_people):
        name = fin.readline().strip()
        people[name] = 0
    for i in range(num_people):
        giver = fin.readline().strip()
        money, split_count = [int(n) for n in fin.readline().strip().split()]
        if split_count != 0:
            money_per_person = money // split_count
            left_over = round(money % split_count)
            people[giver] = people[giver] - money + left_over
            for j in range(split_count):
                receiver = fin.readline().strip()
                people[receiver] += money_per_person

with open("gift1.out", 'w') as fout:
    for p in people:
        fout.write("{} {}\n".format(p, people[p]))