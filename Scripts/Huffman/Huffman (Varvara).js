let fs = require("fs");
let text = fs.readFileSync("test.txt", "utf-8");


function countFrequencies(text) {
    let freq = {}; //пустой объект который будет считать количество повторов
    for (let char of text) {//проходимся по всем символам в строке
        freq[char] = (freq[char] || 0) + 1; //сначала получаем текущие симв. если сим встречается впервые то 0 чтобы не вернуло undef. иначе +1
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
    let heap = Object.entries(freq).map(([char, f]) => new treeHAF(char, f)); //сначала преобразуем орбъект частот в массив пар(символ, частота). .map создает для каждой пары новый узел




    heap.sort((a, b) => a.freq - b.freq); //сортируем узлы по возрастанию частот

    while (heap.length > 1) {
        let left = heap.shift(); // shift() удаляет и возвращает первый элемент массива. 
        let right = heap.shift(); // так как наш массив отсортирован это 2 узла с наим частотами
        let newNode = new treeHAF(null, left.freq + right.freq, left, right);
        heap.push(newNode); //добавляет новый узел в кучу.
        heap.sort((a, b) => a.freq - b.freq);
    }

    return heap[0]; // Корень дерева
}

function generateCodes(root, code = "", codes = {}) { //текущий узел дерева(начинаем с корня). накапливаемый двоичный код(пусто пока). объект для хранения резов.
    if (root === null) return;

    if (root.char !== null) {
        codes[root.char] = code; //сохр код символа
        return;
    }

    generateCodes(root.left, code + "0", codes); //при движении добавляем 0 к текущему коду
    generateCodes(root.right, code + "1", codes);
    fs.writeFileSync('codes.json', JSON.stringify(codes, null, 3));// полученные коды запис в файл
//параметры: объект который нужно преобразовать в json; функция замены( тут ноль);количество пробелов                                
    return codes;
}

function hufEncode(text, codes) { //Преобразует исходный текст в бинарную строку, где каждый символ заменяется соответствующим ему кодом Хаффмана.
    return text.split("").map(char => codes[char]).join(""); //сплитом разбиваем текст на симв;преобр каждый сим; склеиваем


}

function hufDecode(encodedText, root) {
    let decodedText = ""; //бин стр
    let currentNode = root;// начинаем с корня 

    for (let bit of encodedText) {// перебираем биты
        if (bit === "0") {// двигаемся по дереву
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
    let bytes = [];// инициал массив байтов
    for (let i = 0; i < binaryString.length; i += 8) {// Цикл с шагом 8 (1 байт = 8 бит)
        let byteString = binaryString.slice(i, i + 8).padEnd(8, '0');// берем подстроку длиной 8 бит, если она меньше 8 то добавл 0 справа
        let byte = parseInt(byteString, 2);// переводит бинарную строку в десятичное число
        bytes.push(byte);//добавляем байт в массив
    }
    return Buffer.from(bytes);// Преобразует массив чисел в бинарный Buffer
}

function bytesToBinaryString(buffer) {
    let binaryString = "";
    for (let byte of buffer) {
        binaryString += byte.toString(2).padStart(8, '0');// конвертирует число в бинарку; дополняет нули в НАЧАЛО; конкатенируем строки. 
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
