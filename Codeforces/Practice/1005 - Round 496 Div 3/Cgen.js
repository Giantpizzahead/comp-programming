const N = Math.floor(Math.random() * 10);
const arr = [];
for (let i = 0; i < N; i++) {
    arr.push(Math.floor(Math.random() * 10));
}
console.log(N);
console.log(arr.join(' '));