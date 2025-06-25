const fs = require('fs');

class HuffmanNode {
    constructor(char, freq, left = null, right = null) {
        this.char = char;
        this.freq = freq;
        this.left = left;
        this.right = right;
    }
}

function buildFrequencyTable(s) {
    let freq = {};
    for (let char of s) {
        freq[char] = (freq[char] || 0) + 1;
    }
    freq['#'] = 1; // Добавляем специальный флаг конца строки
    return freq;
}

function buildHuffmanTree(freq) {
    let nodes = Object.keys(freq).map(char => new HuffmanNode(char, freq[char]));
    while (nodes.length > 1) {
        nodes.sort((a, b) => a.freq - b.freq);
        let left = nodes.shift();
        let right = nodes.shift();
        let parent = new HuffmanNode(null, left.freq + right.freq, left, right);
        nodes.push(parent);
    }
    return nodes[0];
}

function generateCodes(node, path = '', codes = {}) {
    if (node.char) {
        codes[node.char] = path;
        return;
    }
    generateCodes(node.left, path + '0', codes);
    generateCodes(node.right, path + '1', codes);
    return codes;
}

function encodeString(s, codes) {
    let encoded = '';
    for (let char of s) {
        encoded += codes[char];
    }
    encoded += codes['#']; // Добавляем код для флага конца строки
    return encoded;
}

function padEncodedString(encoded) {
    let padding = 8 - (encoded.length % 8);
    return encoded + '0'.repeat(padding);
}

function binaryStringToBytes(binaryString) {
    let bytes = [];
    for (let i = 0; i < binaryString.length; i += 8) {
        let byte = binaryString.substr(i, 8);
        bytes.push(parseInt(byte, 2)); // Преобразуем двоичную строку в десятичное число
    }
    return bytes;
}

function encode(inputFile, outputFile, codesFile) {
    let s = fs.readFileSync(inputFile, 'utf8').trim();
    let freq = buildFrequencyTable(s);
    let tree = buildHuffmanTree(freq);
    let codes = generateCodes(tree);
    let encoded = encodeString(s, codes);
    let paddedEncoded = padEncodedString(encoded);
    let bytes = binaryStringToBytes(paddedEncoded);

    // Преобразуем байты в символы ASCII с помощью String.fromCharCode
    let asciiString = bytes.map(byte => String.fromCharCode(byte)).join('');
    fs.writeFileSync(outputFile, asciiString); // Записываем строку ASCII в файл

    // Сохраняем коды в файл codes.json
    fs.writeFileSync(codesFile, JSON.stringify(codes, null, 2));
    console.log(`Файл ${codesFile} успешно создан.`);
}

function decode(inputFile, outputFile, codesFile) {
    let codes = JSON.parse(fs.readFileSync(codesFile, 'utf8'));
    let reversedCodes = Object.fromEntries(Object.entries(codes).map(([k, v]) => [v, k]));
    let asciiString = fs.readFileSync(inputFile, 'utf8'); // Читаем строку ASCII из файла

    // Преобразуем символы ASCII обратно в байты
    let bytes = [];
    for (let char of asciiString) {
        bytes.push(char.charCodeAt(0)); // Получаем код ASCII для каждого символа
    }

    // Преобразуем байты в двоичную строку
    let binaryString = '';
    for (let byte of bytes) {
        binaryString += byte.toString(2).padStart(8, '0');
    }

    // Декодируем двоичную строку с использованием кодов Хаффмана
    let decoded = '';
    let temp = '';
    for (let bit of binaryString) {
        temp += bit;
        if (reversedCodes[temp]) {
            if (reversedCodes[temp] === '#') break; // Останавливаемся при достижении флага конца строки
            decoded += reversedCodes[temp];
            temp = '';
        }
    }
    fs.writeFileSync(outputFile, decoded); // Записываем декодированную строку в файл
    console.log(`Файл ${outputFile} успешно создан.`);
}

function showHelp() {
    console.log('Использование:');
    console.log('  node gg.js -e input.txt output.txt codes.json  # Кодирование');
    console.log('  node gg.js -d input.txt output.txt codes.json  # Декодирование');
    console.log('  node gg.js --help                              # Справка');
    console.log('\nОпции:');
    console.log('  -e, --encode  Кодировать строку из input.txt и сохранить результат в output.txt и codes.json');
    console.log('  -d, --decode  Декодировать строку из output.txt с использованием codes.json и сохранить результат в decoded.txt');
    console.log('  --help        Показать справку');
}

function main() {
    let args = process.argv.slice(2);

    if (args.length === 0) {
        console.error('Ошибка: Не указаны аргументы.');
        showHelp();
        return;
    }

    switch (args[0]) {
        case '-e':
        case '--encode':
            if (args.length !== 4) {
                console.error('Ошибка: Для кодирования необходимо указать 3 файла: input.txt, output.txt, codes.json');
                showHelp();
                return;
            }
            encode(args[1], args[2], args[3]);
            break;

        case '-d':
        case '--decode':
            if (args.length !== 4) {
                console.error('Ошибка: Для декодирования необходимо указать 3 файла: input.txt, output.txt, codes.json');
                showHelp();
                return;
            }
            decode(args[1], args[2], args[3]);
            break;

        case '--help':
            showHelp();
            break;

        default:
            console.error(`Ошибка: Неизвестная команда "${args[0]}".`);
            showHelp();
            break;
    }
}

main();
