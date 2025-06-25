let fs = require('fs');

function CaesarEncode(s, shift) {
    let result = '';
    if (shift < 0){
         shift += 256;
    }
    
    for (let i = 0; i < s.length; i++) {
        let charCode = (s.charCodeAt(i) + shift) % 256;
        result += String.fromCharCode(charCode);
    }
    return result;
}

function CaesarDecode(s, b) {
    let book = fs.readFileSync(b, "utf-8");
    let bookFreq = {};
    
    for (let char of book) {
        bookFreq[char] = (bookFreq[char] || 0) + 1;
    }
    
    for (let char in bookFreq) {
        bookFreq[char] /= book.length;
    }

    let minMSE = Infinity;
    let bestDecoded = '';
    let bestShift = 0;

    for (let shift = 0; shift < 256; shift++) {
        let mse = 0;
        let decoded = '';
        for (let i = 0; i < s.length; i++) {
            let charCode = (s.charCodeAt(i) - shift) % 256;
            if (charCode < 0) charCode += 256;
            decoded += String.fromCharCode(charCode);
        }
        let decodedFreq = {};
        for (let char of decoded) {
            decodedFreq[char] = (decodedFreq[char] || 0) + 1;
        }
        for (let char in decodedFreq) {
            decodedFreq[char] /= decoded.length;
        }
        mse = 0;
        for (let char in decodedFreq) {
            mse += Math.pow(decodedFreq[char] - (bookFreq[char] || 0), 2);
        }
        if (mse < minMSE) {
            minMSE = mse;
            bestDecoded = decoded;
            bestShift = shift;
        }
    }
    console.log("Decoded with shift", bestShift);
    return bestDecoded;
}

let args = process.argv.slice(2);

switch (args[0]) {
    case "-h":
    case "--help":
        console.log("Encode: node caesar.js -e <input> <output> <shift>");
        console.log("Decode: node caesar.js -d <input> <output> <book>");
        break;
    case "-e":
    case "--encode":
        let einput = fs.readFileSync(args[1], "utf-8");
        let shift = parseInt(args[3]);
        let encoded = CaesarEncode(einput, shift);
        fs.writeFileSync(args[2], encoded, "utf-8");
        console.log("Encoded with shift", shift);
        break;
    case "-d":
    case "--decode":
        let dinput = fs.readFileSync(args[1], "utf-8");
        let decoded = CaesarDecode(dinput, args[3]);
        fs.writeFileSync(args[2], decoded, "utf-8");
        break;
    default:
        console.log("Invalid option. Use -h for help.");
}
