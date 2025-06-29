// Только кодирование
// Импорт для работы с файлами и арг. командной строки
const fs = require('fs');
const process = require('process');

function caesarEncrypt(text, shift) {
    // разбиваем строку на массив символов, обраб. каждый символ и собираем обратно в строку
    return text.split('').map(char => {
        // ASCII-код текущего символа
        const charCode = char.charCodeAt(0);
        // сдвиг к ASCII-коду
        const shiftedCode = charCode + shift;
        // Преобразуем новый ASCII-код обратно в символ
        return String.fromCharCode(shiftedCode);
    }).join(''); // собираем массив символов обратно в строку
}

function main() {
 
    const args = process.argv.slice(2);
    
    // Проверка, что передано достаточно аргументов
    if (args.length < 3) {
        console.log('Использование: node caesar.js -e input.txt output.txt shift');
        console.log('Где:');
        console.log('  -e          - флаг шифрования');
        console.log('  input.txt   - входной файл с исходным текстом');
        console.log('  output.txt  - выходной файл для зашифрованного текста');
        console.log('  shift       - величина сдвига для шифрования (целое число)');
        process.exit(1); // Завершаем программу с кодом ошибки
    }
    
    const mode = args[0];          // Режим работы (-e для шифрования)
    const inputFile = args[1];     // Путь к входному файлу
    const outputFile = args[2];    // к выходному файлу
    const shift = parseInt(args[3]); // Величина сдвига (преобразуем в число)
    
    if (mode !== '-e' && mode !== '--encode') {
        console.log('Ошибка: первый аргумент должен быть -e или --encode для шифрования');
        process.exit(1);
    }
    
    // shift является числом?
    if (isNaN(shift)) {
        console.log('Ошибка: shift должен быть целым числом');
        process.exit(1);
    }
    
    try {
        // Читаем содерж. входного файла 
        const text = fs.readFileSync(inputFile, 'utf-8');
        
        // Шифруем
        const encryptedText = caesarEncrypt(text, shift);
        
        // Записываем зашифрованный текст в выходной файл
        fs.writeFileSync(outputFile, encryptedText);
        
        // dыводим сообщение об успешном завершении
        console.log('Текст успешно зашифрован и сохранен в', outputFile);
    } catch (err) {
        // Обр. возможные ошибки (такие как: файл не найден)
        console.error('Ошибка:', err.message);
        process.exit(1);
    }
}

// пуск!
main();
