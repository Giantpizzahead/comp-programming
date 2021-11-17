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
    let arr = readline().split(' ').map((x) => parseInt(x));
    arr.sort((a, b) => a-b);
    let ans = 0;
    for (let i = 0; i < N; i++) {
        let x = arr[i];
        let found = false;
        for (let p2 = 1; p2 <= 3e9; p2 *= 2) {
            let y = p2 - x;
            let low = 0;
            let high = N-1;
            while (low <= high) {
                let mid = Math.floor((low + high) / 2);
                if (arr[mid] < y) low = mid+1;
                else if (arr[mid] > y) high = mid-1;
                else {
                    if (i === mid) {
                        if (i != 0 && arr[i-1] === arr[i]) found = true;
                        else if (i != N-1 && arr[i+1] === arr[i]) found = true;
                    } else found = true;
                    break;
                }
            }
            if (found) break;
        }
        // console.log(i, found);
        if (!found) ans++;
    }
    console.log(ans);
}