let args = process.argv.slice(2);
let s = args[0];

let freqs = {};
for (let char of s) {
    freqs[char] = (freqs[char] || 0) + 1;
}

let freq = [];
for (let [char, count] of Object.entries(freqs)) {
    freq.push(count / s.length);
}

let entropy2 = 0;
let entropyA = 0;
for (let p of freq) {
    if (p > 0) {
        entropy2 -= p * Math.log2(p);
        entropyA -= (p * Math.log(p) / Math.log(freq.length))||0;
    }
}

console.log("Энтропия по основанию 2:", entropy2);
console.log("Энтропия по основанию |A|:", entropyA);
