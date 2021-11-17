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

function readSplitLine(mapFunc = (x => x)) {
    return readline().split(' ').map(mapFunc);
}

// Main function

function parseGraph() {
    const [N, M] = readSplitLine((x) => parseInt(x));
    const graph = {
        N,
        M,
        adj: Array.from(new Array(N), () => []),
        revAdj: Array.from(new Array(N), () => []),
        dist: Array.from(new Array(N), () => null)
    };
    for (let i = 0; i < M; i++) {
        const [u, v] = readSplitLine((n) => parseInt(n)-1);
        graph.adj[u].push(v);
        graph.revAdj[v].push(u);
    }
    return graph;
}

class Queue {
    constructor(N) {
        this.N = N;
        this.arr = new Array(N);
        this.currL = 0;
        this.currR = 0;
    }

    push(n) {
        if (this.currR == this.N) throw "Queue is out of space";
        this.arr[this.currR++] = n;
    }

    poll() {
        if (this.currL === this.currR) throw "poll() called on an empty queue";
        return this.arr[this.currL++];
    }

    empty() {
        return this.currL === this.currR;
    }
}

function bfs(graph, dest) {
    const queue = new Queue(graph.N);
    graph.dist[dest] = 0;
    queue.push(dest);
    while (!queue.empty()) {
        const n = queue.poll();
        for (let e of graph.revAdj[n]) {
            if (graph.dist[e] !== null) continue;
            graph.dist[e] = graph.dist[n] + 1;
            queue.push(e);
        }
    }
}

function parsePath() {
    const K = parseInt(readline());
    const path = readSplitLine((n) => parseInt(n)-1);
    return path;
}

function getAnswer(graph, path) {
    let minAns = 0;
    let maxAns = 0;
    path.reduce((prevN, currN) => {
        if (graph.dist[currN] !== graph.dist[prevN]-1) {
            minAns++;
            maxAns++;
        } else for (let e of graph.adj[prevN]) {
            if (e !== currN && graph.dist[e] === graph.dist[currN]) {
                maxAns++;
                break;
            }
        }
        return currN;
    });
    return {minAns, maxAns};
}

function main() {
    const graph = parseGraph();
    const path = parsePath();
    bfs(graph, path[path.length-1]);
    let {minAns, maxAns} = getAnswer(graph, path);
    // console.log(graph);
    // console.log(path);
    console.log(minAns, maxAns);
}