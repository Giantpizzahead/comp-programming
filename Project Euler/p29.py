print(len(set().union(*[set(a ** b for a in range(2, 101)) for b in range(2, 101)])))
print(len(set((x%99+2)**(x//99+2) for x in range(99*99))))