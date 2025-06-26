const fs = require("fs");
const path = require("path");

function EscapeEncoding(input) {
    let result = "";

    if (input.length === 0) {
        console.log("Входные данные пусты.");
        return result;
    }

    let len = 1;
    for (let i = 0; i < input.length; i++) {
        if (i + 1 < input.length && input[i] === input[i + 1]) {
            len += 1;
        } else {
            while (len > 0) {
                if (input[i] === "#") {
                    if (len > 256) {
                        result += '#' + String.fromCharCode(255) + input[i];
                        len -= 256;
                    } else {
                        result += '#' + String.fromCharCode(len - 1) + input[i];
                        len = 0;
                    }
                } else {
                    if (len > 259) {
                        result += '#' + String.fromCharCode(255) + input[i];
                        len -= 259;
                    } else if (len >= 4) {
                        result += '#' + String.fromCharCode(len - 4) + input[i];
                        len = 0;
                    } else {
                        while (len > 0) {
                            result += input[i];
                            len--;
                        }
                        len = 0;
                    }
                }
            }
            len = 1;
        }
    }
    return result;
}

function EscapeDecoding(input) {
    let result = "";
    let i = 0;

    if (input.length === 0) {
        console.log("Входные данные пусты.");
        return result;
    }

    while (i < input.length) {
        if (input[i] === '#') {
            const asciiCode = input.charCodeAt(i + 1);
            const char = input[i + 2];

            if (char === '#') {
                result += '#'.repeat(asciiCode + 1);
            } else {
                result += char.repeat(asciiCode + 4);
            }
            i += 3;
        } else {
            result += input[i];
            i++;
        }
    }

    return result;
}

function jumpEncode(input) {
    let result = "";
    let i = 0;
    const length = input.length;

    while (i < length) {
        let currentChar = input[i];
        let count = 1;
        while (i + count < length && input[i + count] === currentChar) {
            count++;
        }

        if (count >= 3) {
            while (count > 0) {
                const chunkSize = Math.min(count, 130);
                const encodedCount = chunkSize - 3;
                const asciiChar = String.fromCharCode(encodedCount);
                result += `${asciiChar}${currentChar}`;
                count -= chunkSize;
                i += chunkSize;
            }
        } else {
            let nonRepeatingChars = currentChar;
            i++;

            while (i < length) {
                let nextCount = 1;
                while (i + nextCount < length && input[i + nextCount] === input[i]) {
                    nextCount++;
                }

                if (nextCount >= 3) {
                    break;
                }
                nonRepeatingChars += input[i];
                i++;

                if (nonRepeatingChars.length >= 128) {
                    break;
                }
            }

            const m = nonRepeatingChars.length;
            if (m > 0) {
                const encodedCount = m + 127;
                const asciiChar = String.fromCharCode(encodedCount);
                result += `${asciiChar}${nonRepeatingChars}`;
            }
        }
    }

    return result;
}

function jumpDecode(encodedString) {
    let result = "";
    let i = 0;
    const length = encodedString.length;

    while (i < length) {
        const count = encodedString[i].charCodeAt(0);

        if (count < 128) {
            const charToRepeat = encodedString[i + 1];
            const repeatCount = count + 3;
            result += charToRepeat.repeat(repeatCount);
            i += 2;
        } else {
            const sequenceLength = count - 127;
            const sequence = encodedString.slice(i + 1, i + 1 + sequenceLength);
            result += sequence;
            i += 1 + sequenceLength;
        }
    }

    return result;
}

function main() {
    let args = process.argv.slice(2);

    if (args.length === 0) {
        console.log("Используйте -h или --help для получения справки.");
        return;
    }

    let algorithm = undefined;
    let action = undefined;
    let inputFileName = undefined;
    let outputFileName = "out.txt";

    switch (args[0]) {
        case "-h":
        case "--help":
            console.log("Эта программа кодирует файлы с помощью методов jump и escape");
            console.log("Запуск: node func.js [кодирование] [кодирование или декодирование] [входной файл] [выходной файл]");
            break;
        case "-e":
        case "--escape":
            algorithm = "escape";
            if (args.length < 3) {
                console.log("Ошибка: недостаточно аргументов для --escape.");
                return;
            }
            switch (args[1]) {
                case "-e":
                case "--encode":
                    action = "encode";
                    inputFileName = args[2];
                    if (!fs.existsSync(inputFileName)) {
                        console.log(`Ошибка: файл ${inputFileName} не существует.`);
                        return;
                    }
                    const inputDataEscapeEncode = fs.readFileSync(inputFileName, "utf-8");
                    fs.writeFileSync(outputFileName, EscapeEncoding(inputDataEscapeEncode), "utf-8");
                    console.log(`Файл успешно закодирован и записан в ${outputFileName}`);
                    break;
                case "-d":
                case "--decode":
                    action = "decode";
                    inputFileName = args[2];
                    if (!fs.existsSync(inputFileName)) {
                        console.log(`Ошибка: файл ${inputFileName} не существует.`);
                        return;
                    }
                    const inputDataEscapeDecode = fs.readFileSync(inputFileName, "utf-8");
                    fs.writeFileSync(outputFileName, EscapeDecoding(inputDataEscapeDecode), "utf-8");
                    console.log(`Файл успешно декодирован и записан в ${outputFileName}`);
                    break;
                default:
                    console.log("Ошибка: неизвестная опция для --escape.");
                    break;
            }
            break;
        case "-j":
        case "--jump":
            algorithm = "jump";
            if (args.length < 3) {
                console.log("Ошибка: недостаточно аргументов для --jump.");
                return;
            }
            switch (args[1]) {
                case "-e":
                case "--encode":
                    action = "encode";
                    inputFileName = args[2];
                    if (!fs.existsSync(inputFileName)) {
                        console.log(`Ошибка: файл ${inputFileName} не существует.`);
                        return;
                    }
                    const inputDataJumpEncode = fs.readFileSync(inputFileName, "utf-8");
                    fs.writeFileSync(outputFileName, jumpEncode(inputDataJumpEncode), "utf-8");
                    console.log(`Файл успешно закодирован и записан в ${outputFileName}`);
                    break;
                case "-d":
                case "--decode":
                    action = "decode";
                    inputFileName = args[2];
                    if (!fs.existsSync(inputFileName)) {
                        console.log(`Ошибка: файл ${inputFileName} не существует.`);
                        return;
                    }
                    const inputDataJumpDecode = fs.readFileSync(inputFileName, "utf-8");
                    fs.writeFileSync(outputFileName, jumpDecode(inputDataJumpDecode), "utf-8");
                    console.log(`Файл успешно декодирован и записан в ${outputFileName}`);
                    break;
                default:
                    console.log("Ошибка: неизвестная опция для --jump.");
                    break;
            }
            break;
        default:
            console.log("Ошибка: неизвестная опция.");
            break;
    }
}

main();
