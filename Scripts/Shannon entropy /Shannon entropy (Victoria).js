let input = process.argv[2] || "";
let length = input.length;

let freq = {};
for (let char of input) {
  freq[char] = (freq[char] || 0) + 1;
}

let asize = Object.keys(freq).length;

let entropy2 = 0;
let entropyA = 0;

for (let char in freq) {
  let frequency = freq[char] / length;
  entropy2 += frequency * Math.log2(frequency);
  entropyA += frequency * Math.log(frequency) / Math.log(asize);
}

entropy2 = -entropy2;
entropyA = -entropyA;

console.log(`Entropy (base 2): ${entropy2}`);
console.log(`Entropy (base |A|): ${entropyA}`);
