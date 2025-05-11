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
    let bits = s.split('').map(bit => parseInt(bit)); //разбиваем матрицу на массив чисел
    let matrix = buildMatrix(bits.length); //строим матрицу
    let m = matrix.length; //количество битов четности
    let allbits = m + bits.length; //длина итогового сообщения
    
    let ks = [];
    let ind = 0;
    
    for (let i = 1; i <= allbits; i++) {
        if (Number.isInteger(Math.log2(i))) { //если i степень двойки
            ks.push(0); //кладем ноль, потому что это бит четности, который мы еще не посчитали
        } else {
            ks.push(bits[ind++]); //иначе кладем туда бит данных
        }
    }
    
    for (let i = 0; i < m; i++) { //идем по битам четности
        let p = Math.pow(2, i) - 1; //найдем позицию текущего контрольного бита
        let sum = 0; //здесь считаем единицы
        for (let j = 0; j < allbits; j++) { //проходим по позициям закодированного слова
            if (matrix[i][j] == 1) { //если в матрице 1
                sum += ks[j]; //считаем тот бит, который стоит в слове
            }
        }
        ks[p] = sum % 2; //на позицию контрольного бита ставим сотаток суммы от деления на 2
    }
    return ks.join('');
}

function HammingDecode(s) {
    let ksBits = s.split('').map(bit => parseInt(bit)); //преобразуем строку
    
    let m = 1;
    while (Math.pow(2, m) < ksBits.length + 1) { //считаем количество битов четности
        m++; 
    }
    
    let matrix = buildMatrix(ksBits.length - m); //строим матрицу
    
    let mist = [];
    for (let i = 0; i < m; i++) { //идем по матрице
        let sum = 0;
        for (let j = 0; j < ksBits.length; j++) {
            sum += ksBits[j] * matrix[i][j]; //умножаем строки матрицы на поступившую строку
        }
        mist.push(sum % 2); //кладем в массив остаток от деления на два этой суммы
    }

    mist = mist.reverse(); //переворачиваем получившееся число
    let error = parseInt(mist.join(''), 2); //переводим его в десятичную систему

    if (error-1 >=0){
        console.log("Error in "+error+" position");
        ksBits[error-1]=Number(!ksBits[error-1]); //инвертируем нужный нам бит
    }

    let dec = [];
    for (let i = 0; i < ksBits.length; i++) {
        if (!Number.isInteger(Math.log2(i + 1))) { //если позиция не степень двойки
            dec.push(ksBits[i]); //добавляем
        }
    }
    return dec.join('');
}

let args = process.argv.slice(2);
let s = args[1];

switch (args[0]) {
    case "-h":
    case "--help":
        console.log("This program encodes or decodes files using Hamming encoding.");
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
