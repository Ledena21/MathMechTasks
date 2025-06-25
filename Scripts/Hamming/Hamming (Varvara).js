class Hamming {
        let k = 0;
        while (Math.pow(2, k) < n + k + 1) k++;
        return k;
    }

    static isPowerOfTwo(x) { Для степени двойки в битовом представлении есть ровно одна единица!!
        return x > 0 && (x & (x - 1)) === 0; проверяем что х полож И далее сравниваем х с х-1 (когда мы вычитаем 1 все 0 справа от младшей единицы становятся 1 а сама младшая 1 теперь 0)
    }

    static encode(data) {

        if (!data || !/^[01]+$/.test(data)) {//Проверка входных данных (должны быть только 0 и 1) и что data сущ и не пустое 
            throw new Error("Формат входных данных: строка из 0 и 1");
        }

        const n = data.length;  длина исходных данных (бит)
        const k = this.getParityBits(n);  количество контрольных бит (вычисляется методом getParityBits())
        const m = n + k; общая длина кодового слова (n + k)
        const codeword = [];Инициализирует пустой массив codeword для будущего кодового слова
        let dataIndex = 0; Создаёт индекс dataIndex для отслеживания позиции в исходных данных

        for (let i = 1; i <= m; i++) { //здесь отделение битов данных от битов четности происходит неявно
            if (this.isPowerOfTwo(i)) {
                codeword[i-1] = 0; // Позиция для контрольного бита (четности)(пока 0)
      Если позиция i — степень двойки это контрольный бит, инициализируется нулём.     
            } else {
                codeword[i-1] = parseInt(data[dataIndex++]); //бит данных
            }
        }Расчёт контрольных битов (чётность)
        for (let p = 0; p < k; p++) { 
            const parityPos = Math.pow(2, p) - 1; // Позиция контрольного бита (0, 1, 3, ...)
            let parity = 0;
    // Проход по всем битам, которые контролирует этот бит чётности
            for (let i = parityPos; i < m; i += 2 * (parityPos + 1)) {
                for (let j = i; j < Math.min(i + parityPos + 1, m); j++) {
                    parity ^= codeword[j]; // XOR для вычисления чётности
                }
            }

            codeword[parityPos] = parity;// Записываем результат
        }

        return codeword.join(''); Преобразует массив codeword в строку 
    }

    static decode(codeword) {

        if (!codeword || !/^[01]+$/.test(codeword)) {//проверка входных данных в декоде
            throw new Error("Закодированные данные должны быть строкой из 0 и 1");
        }

        const bits = codeword.split('').map(bit => parseInt(bit, 10)); преобразует строку в массив чиселчерез ,
        const m = bits.length;  общая длина кодового слова.
        let syndrome = 0;
    
        let k = 0;
        while (Math.pow(2, k) <= m) k++; Вычисляет, сколько контрольных битов k использовалось при кодировании.

        for (let p = 0; p < k; p++) {
            const parityPos = Math.pow(2, p) - 1; // Позиция контрольного бита (0,1,3...)
            let parity = 0;
// Проверка зоны ответственности контрольного бита
            for (let i = parityPos; i < m; i += 2 * (parityPos + 1)) {
                for (let j = i; j < Math.min(i + parityPos + 1, m); j++) {
                    if (j !== parityPos) { //исключаю контрольный бит
                        parity ^= bits[j]; // Вычисляем чётность
                    }
                }
            }

            if (parity !== bits[parityPos]) {// Сравниваем вычисленную чётность с сохранённым контрольным битом
                syndrome += Math.pow(2, p); // Добавляем позицию ошибочного бита
            }
        }
        const dataBits = [];
        for (let i = 0; i < m; i++) {
            if (!this.isPowerOfTwo(i + 1)) { //если текущ позиция не степень 2 (+1 тк индексы с 0 нач
                dataBits.push(bits[i]); //бит добавляется в массив.мы так собираем только битв данных, пропуская контрольные
        }
        //биты на позициях степени 2 пропускаются, это и есть биты четности
        const data = dataBits.join('');// массив битов в строку
        
        if (syndrome > 0) {
            if (syndrome <= m) {Проверяет, что ошибка находится в пределах кодового слова

                bits[syndrome - 1] ^= 1; Проверяет, что ошибка находится в пределах кодового слова
                ^= 1 - побитовое XOR (инверсия бита)
                const correctedDataBits = [];
                for (let i = 0; i < m; i++) {
                    if (!this.isPowerOfTwo(i + 1)) {
                        correctedDataBits.push(bits[i]);Повторно извлекает информационные биты (аналогично предыдущему шагу)
                    }
                }
                const correctedData = correctedDataBits.join('');Пропускает контрольные биты на позициях степеней двойки
                
                return {
                    error: `Ошибка в ${syndrome} бите`,
                    corrected: bits.join(''),
                    data: correctedData
                };
            } else {
                return {
                    error: "Неисправимая ошибка. Фаталити",
                    data: data
                };
            }
        }

        return {
            error: null,
            data: data
        };
    }
}
const args = process.argv.slice(2);
const option = args[0];
const input = args[1];

if (!option || !input) {
    console.log("Использование:");
    console.log("  Кодирование: node hamming.js -e <data>");
    console.log("  Декодирование: node hamming.js -d <codeword>");
    process.exit(1);
}

try {
    if (option === '-e' || option === '--encode') {
        const encoded = Hamming.encode(input);
        console.log(`Закодированное слово: ${encoded}`);
    } 
    else if (option === '-d' || option === '--decode') {
        const result = Hamming.decode(input);
        
        if (result.error) {
            console.log(`Найдена ошибка: ${result.error}`);
            if (result.corrected) {
                console.log(`Исправленное слово: ${result.corrected}`);
                console.log(`Исходные данные: ${result.data}`);
            }
        } else {
            console.log('Ошибок нема');
            console.log(`Исходные данные: ${result.data}`);
        }
    } 
    else {
        console.log("Неправильная команда!!! Используй -e для кодирования или -d для декодирования");
        process.exit(1);
    }
} 
catch (error) {
    console.error(`Ошибка: ${error.message}`);
    process.exit(1);
}
