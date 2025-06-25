console.log("hell(o) this is a results ;) ");
let args = process.argv.slice(2);
let box = args[0];

let freq = {};// хранит частоты символов

function countFrequency(box) {
    for (let char of box) {
        freq[char] = (freq[char] || 0) + 1; //если этот символ был, то к его частоте+1 если нет то пишем 0 и +1
    }
    return freq;
}


countFrequency(box);// вызов функции для нашей строки

let mass = Object.entries(freq).map(([char, freqq]) => [char, freqq / box.length]); //entries Преобразует объект частот в массив пар [ключ, значение].
//далее мы преобразуем это в новый массив где аргум будут символ, относит частота

let entrop = 0;
let entrop_alph = 0;

for (let [char, p] of mass) {
    entrop -= (p > 0 ? (p * Math.log2(p)) : 0); 
//деление ниже это смена основания логарифма
    entrop_alph -= (p > 0 ? (p * Math.log(p) / Math.log(mass.length)) : 0);
}

console.log("Entropy with base 2:", entrop);
console.log("Entropy with the basis of the alphabet power:", entrop_alph);
