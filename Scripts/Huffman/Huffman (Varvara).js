let fs = require("fs");
let text = fs.readFileSync("test.txt", "utf-8");


function countFrequencies(text) {
    let freq = {};
    for (let char of text) {
        freq[char] = (freq[char] || 0) + 1;
    }
    return freq;
}

class treeHAF {
    constructor(char, freq, left = null, right = null) {
        this.char = char; 
        this.freq = freq; 
        this.left = left; 
        this.right = right;
    }
}
function buildtree(freq) {
    let heap = Object.entries(freq).map(([char, f]) => new treeHAF(char, f));




    heap.sort((a, b) => a.freq - b.freq);

    while (heap.length > 1) {
        let left = heap.shift();
        let right = heap.shift();
        let newNode = new treeHAF(null, left.freq + right.freq, left, right);
        heap.push(newNode); //добавляет новый узел в кучу.
        heap.sort((a, b) => a.freq - b.freq);
    }

    return heap[0]; // Корень дерева
}

function generateCodes(root, code = "", codes = {}) {
    if (root === null) return;

    if (root.char !== null) {
        codes[root.char] = code;
        return;
    }

    generateCodes(root.left, code + "0", codes);
    generateCodes(root.right, code + "1", codes);
    fs.writeFileSync('codes.json', JSON.stringify(codes, null, 3));

    return codes;
}

function hufEncode(text, codes) {
    return text.split("").map(char => codes[char]).join("");


}

function hufDecode(encodedText, root) {
    let decodedText = "";
    let currentNode = root;

    for (let bit of encodedText) {
        if (bit === "0") {
            currentNode = currentNode.left;
        } else {
            currentNode = currentNode.right;
        }

        if (currentNode.char !== null) {
            decodedText += currentNode.char;
//Если достигнут лист (узел с символом), добавляем символ к decodedText
            currentNode = root; 
        }
    }

    return decodedText;
}

function binaryStringToBytes(binaryString) {
    let bytes = [];
    for (let i = 0; i < binaryString.length; i += 8) {
        let byteString = binaryString.slice(i, i + 8).padEnd(8, '0');
        let byte = parseInt(byteString, 2);
        bytes.push(byte);//пуш ми энд джаст тач ми
    }
    return Buffer.from(bytes);
}

function bytesToBinaryString(buffer) {
    let binaryString = "";
    for (let byte of buffer) {
        binaryString += byte.toString(2).padStart(8, '0');
    }
    return binaryString;
}

let args = process.argv.slice(2);
let firstarg = args[0];

if (!firstarg) {
    console.log("Error! No arguments provided. Enter: \"h\" for help / \"e\" for encode / \"d\" for decode");
    process.exit(1);
}

switch (firstarg) {
    case "h":
        console.log("This program builds a Huffman tree, encodes, and decodes text using the Huffman method.");
        console.log("Enter: \"h\" for help / \"e\" for encode / \"d\" for decode");
        break;

    case "e":

        let freq = countFrequencies(text);
        let tree = buildtree(freq);
        let codes = generateCodes(tree);

        let encodedText = hufEncode(text, codes);

        let bytes = binaryStringToBytes(encodedText);
        fs.writeFileSync("encode.bin", bytes);
        console.log("Encoding complete! Check encode.bin.");
        break;

    case "d":
        // Чтение байтов из файла
        let buffer = fs.readFileSync("encode.bin");

        let binaryString = bytesToBinaryString(buffer);

        let freqForDec = countFrequencies(text);
        let hufTreeDecode = buildtree(freqForDec);

        let decodedText = hufDecode(binaryString, hufTreeDecode);
        fs.writeFileSync("decode.txt", decodedText, "utf-8");
        console.log("Decoding complete! Check decode.txt.");
        break;

    default:
       console.log("Error! Invalid first argument. Enter: \"h\" for help / \"e\" for encode / \"d\" for decode");
}
