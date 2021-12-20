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
    console.log(N);
}