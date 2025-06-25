class Hamming {
    static getParityBits(n) {
        let k = 0;
        while (Math.pow(2, k) < n + k + 1) k++;
        return k;
    }

    static isPowerOfTwo(x) {
        return x > 0 && (x & (x - 1)) === 0;
    }

    static encode(data) {

        if (!data || !/^[01]+$/.test(data)) {//исправила проверку входных данных в енкоде
            throw new Error("Формат входных данных: строка из 0 и 1");
        }

        const n = data.length;
        const k = this.getParityBits(n);
        const m = n + k;
        const codeword = [];
        let dataIndex = 0;

        for (let i = 1; i <= m; i++) { //здесь отделение битов данных от битов четности происходит неявно
            if (this.isPowerOfTwo(i)) {
                codeword[i-1] = 0; //тут бит четности и пока он 0
            } else {
                codeword[i-1] = parseInt(data[dataIndex++]); //бит данных
            }
        }
        for (let p = 0; p < k; p++) { 
            const parityPos = Math.pow(2, p) - 1;
            let parity = 0;

            for (let i = parityPos; i < m; i += 2 * (parityPos + 1)) {
                for (let j = i; j < Math.min(i + parityPos + 1, m); j++) {
                    parity ^= codeword[j];
                }
            }

            codeword[parityPos] = parity;
        }

        return codeword.join('');
    }

    static decode(codeword) {

        if (!codeword || !/^[01]+$/.test(codeword)) {//исправила проверку входных данных в декоде
            throw new Error("Закодированные данные должны быть строкой из 0 и 1");
        }

        const bits = codeword.split('').map(bit => parseInt(bit, 10));
        const m = bits.length;
        let syndrome = 0;
    
        let k = 0;
        while (Math.pow(2, k) <= m) k++;

        for (let p = 0; p < k; p++) {
            const parityPos = Math.pow(2, p) - 1;
            let parity = 0;

            for (let i = parityPos; i < m; i += 2 * (parityPos + 1)) {
                for (let j = i; j < Math.min(i + parityPos + 1, m); j++) {
                    if (j !== parityPos) { //исключаю контрольный бит
                        parity ^= bits[j];
                    }
                }
            }

            if (parity !== bits[parityPos]) {
                syndrome += Math.pow(2, p);
            }
        }
        const dataBits = [];
        for (let i = 0; i < m; i++) {
            if (!this.isPowerOfTwo(i + 1)) { //если текущ позиция не степень 2
                dataBits.push(bits[i]); //бит данных
            }
        }
        //биты на позициях степени 2 пропускаются, это и есть биты четности
        const data = dataBits.join('');
        
        if (syndrome > 0) {
            if (syndrome <= m) {

                bits[syndrome - 1] ^= 1;
                
                const correctedDataBits = [];
                for (let i = 0; i < m; i++) {
                    if (!this.isPowerOfTwo(i + 1)) {
                        correctedDataBits.push(bits[i]);
                    }
                }
                const correctedData = correctedDataBits.join('');
                
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
