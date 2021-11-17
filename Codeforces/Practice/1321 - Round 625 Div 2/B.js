// Input handling

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
    readline();  // N
    const B = readline().split(' ').map((x) => parseInt(x));
    const map = new Map();
    B.forEach((x, i) => {
        if (!map.has(x-i)) map.set(x-i, 0);
        map.set(x-i, map.get(x-i) + x);
    });
    const ans = Math.max(...map.values());
    console.log(ans);
}