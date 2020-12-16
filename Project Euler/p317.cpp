#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
using ld = long double;

const int NUM_PARTICLES = 100000;
const ld SHELL_SIZE = 0.001;

const ld INIT_VELOCITY = 20;
const ld INIT_HEIGHT = 100;
const ld GRAVITY = 9.81;

struct Particle {
    ld x, y, vx, vy;

    Particle(ld x, ld y, ld vx, ld vy) : x(x), y(y), vx(vx), vy(vy) {}

    void move(ld SHELL_SIZE) {
        ld t = SHELL_SIZE / vx;
        y += vy * t - 0.5 * GRAVITY * t * t;
        x += SHELL_SIZE;
        vy -= GRAVITY * t;
    }
};

vector<Particle> particles;

int main() {
    cout << fixed;
    for (int i = 0; i < NUM_PARTICLES; i++) {
        ld angle = M_PI_2 * i / NUM_PARTICLES;
        ld vx = cos(angle) * INIT_VELOCITY;
        ld vy = sin(angle) * INIT_VELOCITY;
        particles.emplace_back(0, INIT_HEIGHT, vx, vy);
    }
    // Calculate cylindrical shells while moving
    ld volume = 0, cx = -SHELL_SIZE / 2, maxy;
    while (!particles.empty()) {
        cx += SHELL_SIZE;
        maxy = 0;
        for (int i = 0; i < particles.size(); i++) {
            Particle& p = particles[i];
            p.move(SHELL_SIZE);
            maxy = max(p.y, maxy);
            if (p.y <= 0) {
                // Particle is now useless
                particles.erase(particles.begin()+i);
                i--;
            }
        }
        // cout << cx << " " << maxy << endl;
        ld portion = cx * maxy;
        volume += portion;
    }
    volume *= 2 * M_PI * SHELL_SIZE;
    cout << "Num particles: " << NUM_PARTICLES << endl;
    cout << "Shell size: " << SHELL_SIZE << endl;
    cout << "Volume: " << volume << endl;
    return 0;
}