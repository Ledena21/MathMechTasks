function buildMatrix(l) {
    let m = 1;
    while (Math.pow(2, m) < m + l + 1) { //находим количество контрольных битов по формуле
        m++;
    }
    let allbits = m + l; //получаем общее количество битов, исходные складываем с контрольными
    let matrix = [];
    for (let i = 0; i < m; i++) { //идем по каждому биту четности и создаем для него массив
        let row = [];
        for (let j = 1; j <= allbits; j++) { //теперь идем по каждому номеру позиции в слове
            let binary = j.toString(2).padStart(m, '0'); //преобразуем номер в двоичный вид с нулями спереди
            row.push(Number(binary[m - 1 - i])); //кладем
        }
        matrix.push(row); //кладем в матрицу очередной ряд чисел
    }
    return matrix;
}

function HammingEncode(s) {
    let bits = s.split('').map(bit => parseInt(bit));
    let matrix = buildMatrix(bits.length); //строим матрицу
    let m = matrix.length; //находим количество битов четности
    let allbits = m + bits.length + 1; //общее количество битов, +1 для p0
    
    let ks = [0]; //начинаем с p0, он временно 0
    
    let ind = 0;
    for (let i = 1; i < allbits; i++) {
        if (Number.isInteger(Math.log2(i))) { //если это место для бита четности
            ks.push(0); //пока что кладем ноль
        } else {
            ks.push(bits[ind++]); //кладем биты данных
        }
    }
    
    // Вычисляем обычные биты четности
    for (let i = 0; i < m; i++) { 
        let p = Math.pow(2, i); //место текущего бита четности
        let sum = 0;
        for (let j = 1; j < allbits; j++) {
            if (matrix[i][j-1] == 1) { //если в матрице 1
                sum += ks[j]; //собираем сумму
            }
        }
        ks[p] = sum % 2; //на это место вычисляем бит четности, остаток суммы от деления на 2
    }
    let p0 = 0;
    for (bit of ks){ //идем по всем битам сообщения
        p0 += bit; //собираем их сумму
    }
    p0 = p0 % 2; //делим сумму на 2 и получаем p0
    ks[0] = p0;
    return ks.join('');
}

function HammingDecode(s) {
    let ksBits = s.split('').map(bit => parseInt(bit));//делаем из строки массив символов
    
    let m = 1;
    while (Math.pow(2, m) < ksBits.length) { //находим количество контрольных битов
        m++;
    }
    
    let matrix = buildMatrix(ksBits.length - m - 1); //строим матрицу для длины сообщения без битов четности и нулевого бита
    
    let p0 = 0;
    for (let i = 0; i < ksBits.length; i++) {
        p0 = p0 + ksBits[i];
    }
    p0 = p0 % 2;
    
    let mist = [];
    for (let i = 0; i < m; i++) {
        let sum = 0;
        for (let j = 1; j < ksBits.length; j++) {
            sum += ksBits[j] * matrix[i][j-1]; //умножаем закодированное на матрицу
        }
        mist.push(sum % 2); //возвращаем остаток от деления на 2
    }

    mist = mist.reverse(); //переворачиваем то, что получилось
    let error = parseInt(mist.join(''), 2); //переводим в десятичную систему
    
    if (mist.includes(1)) { //если нашли ошибки
        if (p0 === 1) { //ели p0 не 0
            console.log("1 error detected in position " + error); 
            ksBits[error] = Number(!ksBits[error]); //инвертируем бит с ошибкой
        } else {
            console.log("2 errors detected");
            return ks;
        }
    } else if (p0 === 1) {
        console.log("Error in p0");
        ksBits[0] = Number(!ksBits[0]); //инвертируем нулевой бит
    }
    
    let decoded = [];
    for (let i = 1; i < ksBits.length; i++) {
        if (!Number.isInteger(Math.log2(i))) {
            decoded.push(ksBits[i]); //переписываем биты данных, пропуская биты четности
        }
    }
    return decoded.join('');
}

let args = process.argv.slice(2);
let s = args[1];

switch (args[0]) {
    case "-h":
    case "--help":
        console.log("This program encodes or decodes files using Hamming encoding with extended parity bit.");
        console.log("To use, write node humming.js [encoding or decoding] [string]");
        break;
    case "-e":
    case "--encode":
        console.log(HammingEncode(s));
        break;
    case "-d":
    case "--decode":
        console.log(HammingDecode(s));
        break;
    default:
        console.log("Error: undefined option");
        break;
}
