// Input handling (Ctrl-D for EOF)

const readlineModule = require("readline");
const rl = readlineModule.createInterface({
    input: process.stdin,
    output: process.stdout
});

const input = [];
let currLine = 0;

rl.on("line", line => {
    input.push(line);
});

rl.on("close", () => {
    main();
})

function readline() {
    return input[currLine++];
}

// Main function

function main() {
    const N = parseInt(readline());
    const arr = readline().split(' ').map((x) => parseInt(x));
    let ans = 0;
    for (let i = 0; i < N; i++) {
        let found = false;
        for (let j = 0; j < N; j++) {
            if (i == j) continue;
            let res = arr[i] + arr[j];
            let k = 1;
            while (k <= res) {
                if (res === k) {
                    found = true;
                    break;
                } else k *= 2;
            }
            if (found) break;
        }
        if (!found) ans++;
    }
    console.log(ans);
}