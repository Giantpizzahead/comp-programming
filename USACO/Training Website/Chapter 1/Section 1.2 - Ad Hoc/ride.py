'''
ID: sunnyky1
LANG: PYTHON3
TASK: ride
'''

file_in = open("ride.in", mode='r')
comet_name = file_in.readline()
group_name = file_in.readline()
comet_total = 1
for char in comet_name[:-1]:
    comet_total *= (ord(char) - 64)
group_total = 1
for char in group_name[:-1]:
    group_total *= (ord(char) - 64)
if comet_total % 47 == group_total % 47:
    output = "GO"
else:
    output = "STAY"
file_out = open("ride.out", mode='w')
file_out.write(output + "\n")
file_out.close()
