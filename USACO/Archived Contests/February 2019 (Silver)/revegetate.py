"""
USACO 2019 February Contest (Silver)
Problem 3: The Great Revegetation
By Giantpizzahead
"""

pastures = []
links = []
linked = {}
current_link = 1
impossible = False


def opp(num):
    if num == 1:
        return 2
    return 1


def join_links(type, p1, p2):
    link1 = links[p1]
    link2 = links[p2]
    links2 = linked[link2]
    past1 = pastures[p1]
    past2 = pastures[p2]
    set_opp = False
    if (type == 'S' and past1 != past2) or (type == 'D' and past1 == past2):
        set_opp = True
    for p in links2:
        links[p] = link1
        if set_opp:
            val = pastures[p]
            if val == 1:
                pastures[p] = 2
            else:
                pastures[p] = 1
    linked[link1] += links2
    # del(linked[link2])


def check_conflicts(type, p1, p2):
    if type == 'S' and pastures[p1] == pastures[p2]:
        return False
    elif type == 'D' and pastures[p1] != pastures[p2]:
        return False
    else:
        return True


def handle_cow(type, p1, p2):
    global current_link, impossible
    link1 = links[p1]
    link2 = links[p2]
    if link1 != 0 and link2 != 0:
        if link1 != link2:
            join_links(type, p1, p2)
        else:
            # Check if setup is impossible here
            if check_conflicts(type, p1, p2):
                impossible = True
        return
    elif link1 != 0:
        links[p2] = link1
        linked[link1].append(p2)
    elif link2 != 0:
        links[p1] = link2
        linked[link2].append(p1)
    else:
        links[p1] = current_link
        links[p2] = current_link
        linked[current_link] = [p1, p2]
        current_link += 1
    past1 = pastures[p1]
    past2 = pastures[p2]
    if type == "S":
        if past1 != 0:
            pastures[p2] = past1
        elif past2 != 0:
            pastures[p1] = past2
        else:
            pastures[p1] = 1
            pastures[p2] = 1
    else:
        if past1 != 0:
            pastures[p2] = opp(past1)
        elif past2 != 0:
            pastures[p1] = opp(past2)
        else:
            pastures[p1] = 1
            pastures[p2] = 2


def find_answer():
    if impossible:
        return 0
    answer = 1
    seen_links = []
    for i, pasture in enumerate(pastures):
        if pasture == 0:
            answer *= 10
        elif links[i] not in seen_links:
            seen_links.append(links[i])
            answer *= 10
    return answer


def main():
    # Input parsing
    with open("revegetate.in", 'r') as input:
        num_pastures, num_cows = map(int, input.readline().split())
        for i in range(num_pastures):
            pastures.append(0)
            links.append(0)
        for cow in range(num_cows):
            type, p1, p2 = input.readline().split()
            p1 = int(p1) - 1
            p2 = int(p2) - 1
            handle_cow(type, p1, p2)
            if impossible:
                break
    # print(pastures)
    answer = find_answer()
    with open("revegetate.out", 'w') as output:
        output.write(str(answer))


main()
