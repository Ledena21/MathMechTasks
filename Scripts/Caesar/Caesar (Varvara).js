const fs = require('fs');
const path = require('path');// для работы с путями файлов

// функция шифрования
function Encrypt(buffer, shift) {
    shift = shift % 256; // сдвиг от 0 до 255
    const result = Buffer.alloc(buffer.length);// создаем буфер для результата с указанным размером 
    for (let i = 0; i < buffer.length; i++) {
        result[i] = (buffer[i] + shift) % 256;// Применяем сдвиг по модулю 256
    }
    return result;
}

// функция декода
function Decrypt(buffer, shift) {
    shift = shift % 256; //проверяем правильность сдвига. что он будет в нужном диапазоне 0-255
    const result = Buffer.alloc(buffer.length);// буфер для результата
    for (let i = 0; i < buffer.length; i++) { проходисмя по каждому байту
        result[i] = (buffer[i] - shift + 256) % 256;// обратный сдвиг с защитой от отрицательных значений
    }
    return result;
}

// построение таблицы частот (0-255)
function FrequencyTable(buffer) {
    const freq = new Array(256).fill(0); //масссив частот. 256 эл так как это макс возможное знач байта. И каждый эл инициал 0 так как они не встречаются еще
    const total = buffer.length || 1;  // защита от деления на ноль. считаем общ количество байтов
    
    for (let i = 0; i < buffer.length; i++) {
        const byte = buffer[i];
        freq[byte]++;
    }// подсчет частот каждого байта (buffer[i] = 0x41 (символ 'A'), то freq[65]++ ((так как 0x41 = 65 в десятичной системе))    
    return freq.map(count => count / total); //приводим частоты к 0 или 1
}

function loadRefFreq(bookPath) {
    const bookBuffer = fs.readFileSync(bookPath); //сохр текст в буфер
    return FrequencyTable(bookBuffer);//строим таблицу частот
}

// вычисление MSE между частотами
function calculateMSE(textFreq, referfreq) {
    let mse = 0; //сумма квадр разности
    let count = 0; количесвто учтенных символов
    
    for (let i = 32; i < 127; i++) { //анализ только печатных аскии символов
        if (referfreq[i] > 0.0001) { //пропуск редковстречающися симв
            mse += Math.pow(textFreq[i] - referfreq[i], 2); //вычисляем mse
            count++;
        }
    }
    
    return count > 0 ? mse / count : Infinity;// возвращаем среднее значение или бесконечность, если нет совпадений
}


function bshift(encryptedBuffer, referfreq) {// автоматическое определение сдвига
    let bshift = 0;// лучший найденный сдвиг
    let bestMSE = Infinity;// минимальная мсе
    
    for (let shift = 0; shift < 256; shift++) {// перебираем все возможные сдвиги
        // пробуем дешифровать с текущим сдвигом
        const decrypbuf = Decrypt(encryptedBuffer, shift);
        const textFreq = FrequencyTable(decrypbuf);
        const mse = calculateMSE(textFreq, referfreq);
        
        // если нашли лучший вариант сменьшим мсе, сохраняем
        if (mse < bestMSE) {
            bestMSE = mse;
            bestShift = shift;
        }
    }
    
    return bshift;
}


function main() {
    const args = process.argv.slice(2);//обработка аргументов
    
    if (args.length < 3 || args[0] === '-h' || args[0] === '--help') {//справка
        console.log('Использование:');
        console.log('Шифрование: node caesar.js -e input.txt output.txt shift');
        console.log('Дешифрование: node caesar.js -d input.txt output.txt book.txt');
        console.log('Пример: node caesar.js -d encrypted.txt decrypted.txt book.txt');
        return;
    }

    const mode = args[0]; //вид работы программы
    const inputFile = path.resolve(args[1]);// входной файл
    const outputFile = path.resolve(args[2]);// выходной файл
    
    try {
        
        const inputbuf = fs.readFileSync(inputFile);// читаем входной файл как бинарные данные
        let resultBuffer, shift;

        if (mode === '-e') {//режим кодинга
            shift = parseInt(args[3]);
            if (isNaN(shift)) throw new Error('Сдвиг должен быть числом');
            
            resbuf = Encrypt(inputbuf, shift);
            console.log(`Файл зашифрован со сдвигом ${shift}`);
        } 
        else if (mode === '-d') {//режим декодинга
            const bookFile = path.resolve(args[3]);
            const referfreq = loadRefFreq(bookFile);
            
            // используем указанный сдвиг или автоматически определяем
            shift = args[4] ? parseInt(args[4]) : bshift(inputbuf, referfreq);
            if (isNaN(shift)) throw new Error('Сдвиг должен быть числом');
            
            resbuf = Decrypt(inputbuf, shift);
            console.log(`Файл дешифрован. Использован сдвиг: ${shift}`);
            
            // выводим начало расшифрованного текста для проверки
            console.log('Первые 50 байт:', resbuf.slice(0, 50).toString());
        }
        else {
            throw new Error('Неизвестный режим. Используйте -e или -d');
        }

        // сораняем результат
        fs.writeFileSync(outputFile, resbuf);
    } catch (err) {
        console.error('Ошибка:', err.message);// Обработка ошибок
        process.exit(1);
    }
}

main();
