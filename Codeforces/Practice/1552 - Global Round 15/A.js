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
    const T = parseInt(readline());
    for (let i = 0; i < T; i++) {
        const N = parseInt(readline());
        const str = readline().split('');
        const sortedStr = str.slice();
        sortedStr.sort();
        let ans = 0;
        for (let j = 0; j < N; j++) {
            if (str[j] !== sortedStr[j]) ans++;
        }
        console.log(ans);
    }
}