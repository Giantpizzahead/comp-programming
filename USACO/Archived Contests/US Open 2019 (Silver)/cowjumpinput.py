with open("cowjump.in", 'w') as fout:
    fout.write("1000\n")
    for i in range(1000-1):
        fout.write("0 " + str(i*1000) + " 5 " + str(i*1000) + "\n")
    fout.write("2 -5 3 9999999")
