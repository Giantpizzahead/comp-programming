import pygame, sys
from pygame.locals import *

# Setup Pygame
pygame.init()
BACKGROUND = (0, 0, 0)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)
YELLOW = (255, 255, 0)
FPS = 60
fpsClock = pygame.time.Clock()
WINDOW_WIDTH = 800
WINDOW_HEIGHT = 800
WINDOW = pygame.display.set_mode((WINDOW_WIDTH, WINDOW_HEIGHT))
pygame.display.set_caption("osu! Visualizer")

def main_loop():
    looping = True
    frame = 0
    # The main game loop
    while looping:
        # Get inputs
        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                sys.exit()
        # Render elements of the game
        WINDOW.fill(BACKGROUND)
        render(frame)
        pygame.display.update()
        fpsClock.tick(FPS)
        frame += 1

# Load notes
with open("notes.txt", 'r') as fin:
    notes = []
    for line in fin.readlines():
        t, x, y, c = line.strip().split()
        notes.append({"t": int(t), "x": int(x), "y": int(y), "c": c})

# Load conditions
with open("conditions.txt", 'r') as fin:
    conditions = []
    for line in fin.readlines():
        values = list(map(int, line.strip().split()))
        conditions.append({
            "id": values[0],
            "values": values[1:]
        })

def get_note_color(n):
    c_to_color = {
        "r": RED,
        "b": BLUE,
        "g": GREEN
    }
    return c_to_color[notes[n]["c"]]

def get_note_pos(n):
    return (notes[n]["x"]*(WINDOW_WIDTH-100)//9+50, notes[n]["y"]*(WINDOW_HEIGHT-100)//9+50)

def render_note(n, color=None):
    if color:
        pygame.draw.circle(WINDOW, color, get_note_pos(n), 35)
    else:
        pygame.draw.circle(WINDOW, get_note_color(n), get_note_pos(n), 15)

def render_condition(n):
    color = RED if conditions[n]["id"] == 4 else BLUE
    pygame.draw.polygon(WINDOW, color, [get_note_pos(i) for i in conditions[n]["values"]])
    # for x in conditions[n]["values"]:
    #     render_note(x)

# Main render method
locs = set()
order = []
for i in range(len(conditions)):
    for j in conditions[i]["values"]:
        if get_note_pos(j) not in locs:
            locs.add(get_note_pos(j))
            order.append(j)
            print(i)
print(sorted(order))
def render(frame):
    # global conditions
    # only_3 = []
    # for i in range(len(conditions)):
    #     if conditions[i]["id"] < 4:
    #         only_3.append(conditions[i])
    # n = frame // 30
    # conditions = only_3
    # render_condition(n)
    for i in range(len(notes)):
        if 0 <= notes[i]["t"]-frame <= 180:
            if i in order:
                render_note(i, YELLOW)
            else:
                render_note(i)
    
main_loop()
