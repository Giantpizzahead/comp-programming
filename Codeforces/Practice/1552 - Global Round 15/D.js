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

function checkArr(arr, i, v, used) {
    if (i == arr.length) return used && v === 0;
    const res1 = checkArr(arr, i+1, v, used);
    const res2 = checkArr(arr, i+1, v+arr[i], true);
    const res3 = checkArr(arr, i+1, v-arr[i], true);
    return res1 || res2 || res3;
}

function main() {
    const T = parseInt(readline());
    for (let i = 0; i < T; i++) {
        const N = parseInt(readline());
        const arr = readline().split(' ').map((x) => parseInt(x));
        console.log(checkArr(arr, 0, 0, false) ? "YES" : "NO");
    }
}