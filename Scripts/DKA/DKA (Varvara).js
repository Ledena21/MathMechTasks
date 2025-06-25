Сложность: O(n*m), где n - длина текста, m - длина шаблона

let fs = require('fs');

function readFile(filename) {
    return fs.readFileSync(filename, 'utf-8').trim();//читаем файл, трим убирает лишние пробелы.дальше работаем со строкой
}
function brutForce(s, t) {//алгоритм брут форса
    let n = s.length;
    let m = t.length;
    let result = []; // массив для найденных позиций
    let comparisons = 0;//счетчик сравнений

    for (let i = 0; i <= n - m; i++) {// перебор всевозможных позиций
        let match = true;
        for (let j = 0; j < m; j++) {// сравнение символов
            comparisons++;
            if (s[i + j] !== t[j]) {// если символы не совпали
                match = false;
                break;
            }
        }
        if (match) {// если найдено совпадение, сораняем позицию
            result.push(i);
            if (result.length === 10) break;//берем первые 10 совпадений
        }
    }

    return {// возвращаем результаты
        matching: result.length,
        top10: result.slice(0, 10),
        collisious: null,
        SymbolComparing: comparisons
    };
}
function hashS(s, t, M = 1000000007) {//алг. хэш-суммы, М рандомное число большое
    let n = s.length;
    let m = t.length;
    let result = [];
    let collisions = 0;
    let comparisons = 0;
    let hashT = 0;//вычисляем хэш шаблона
    for (let i = 0; i < m; i++) {
        hashT = (hashT + t.charCodeAt(i)) % M;// сумма кодов символов взятием аски кода каждого символа и суммирования их
    } //модуль чтобы не выйти за грань
    let hashS = 0;//вычисляем хэш первой подстр
    for (let i = 0; i < m; i++) {
        hashS = (hashS + s.charCodeAt(i)) % M;
    }
    for (let i = 0; i <= n - m; i++) { //перебираем все начальные позиции подстроки в строке
//i - текущая начальная позиция подстроки в тексте s; n - длина текста s, m - длина шаблона t;
//Условие гарантирует, что подстрока длины m полностью помещается в оставшейся части текста          
        if (hashS === hashT) { //если хэши совпали
            let match = true;//проверяем на коллизии
            for (let j = 0; j < m; j++) {// перебор символов
                comparisons++;
                if (s[i + j] !== t[j])// {s[i + j] - символ в тексте на позиции i+j; t[j] - символ в шаблоне на позиции j
                    match = false;
                    break;
                }
            }
            if (match) {
                result.push(i);//запоминаем позиции совпадения
                if (result.length === 10) break;
            } else {
                collisions++;
            }
        }
        if (i < n - m) {//вычисляем хэш для следующей подстроки
            hashS = (hashS - s.charCodeAt(i) + s.charCodeAt(i + m)) % M; //вычитаем код прошлого символа и добавляем код следующего
            if (hashS < 0) hashS += M;//в джс модуль может дать отрицательное число поэтому мы проверяем и исправляем если надо
        }
    }

    return {
        matching: result.length,
        top10: result.slice(0, 10),
        collisious: collisions,
        SymbolComparing: comparisons
    };
}

function rabinK(s, t, M = 1000000007) {
    let n = s.length;
    let m = t.length;
    let result = [];
    let collisions = 0;
    let comparisons = 0;
    let power = 1;//
    for (let i = 0; i < m; i++) {// вычисляем 2^m mod M
        power = (power * 2) % M;
    }
    let hashT = 0;
    for (let i = 0; i < m; i++) { //вычисляем хэш шаблона
        hashT = (hashT * 2 + t.charCodeAt(i)) % M;
    }
    let hashS = 0;
    for (let i = 0; i < m; i++) {//вычисляем хэш первой подстрки в строке
        hashS = (hashS * 2 + s.charCodeAt(i)) % M;
    }

    for (let i = 0; i <= n - m; i++) {
        if (hashS === hashT) {// если хеши совпали
            let match = true;//проверяем на коллизии
            for (let j = 0; j < m; j++) {
                comparisons++;
                if (s[i + j] !== t[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                result.push(i);
                if (result.length === 10) break;
            } else {
                collisions++;
            }
        }

        if (i < n - m) {//вычисляем хэш для следующей подстрки
            hashS = (hashS * 2 - s.charCodeAt(i) * power + s.charCodeAt(i + m)) % M;// умножаем старый хэш на 2, вычитаем прошлый симв, добавляем новый, берем модуль
            if (hashS < 0) hashS += M; //коррект отриц хэш
        }
    }

    return {
        matching: result.length,
        top10: result.slice(0, 10),
        collisious: collisions,
        SymbolComparing: comparisons
    };
}
class DFA {
    constructor(pattern) {
        this.pattern = pattern;
        this.alphabet = this.unique(pattern);// получаем уникальные символы шаблона
        this.states = this.statesT();//строим таблицу состояний
    }

    unique(str) {
        return [...new Set(str)];//создаем множество из симв стр и преобразуем его в массив перед этим удаляя дублекаты
    }

    statesT() { //строим таблицу состояний
        let states = {};
        let pattern = this.pattern;
        
        for (let i = 0; i <= pattern.length; i++) {
            let prefix = pattern.slice(0, i);//префикс шаблона
            states[i] = { name: prefix };//состояние соответств префиксу
            
            for (let char of this.alphabet) {// опред переход для каждого символа
                let newPrefix = prefix + char;// добавляем символ к префиксу
                
                while (newPrefix.length > 0 && !pattern.startsWith(newPrefix)) {// находим макс суффикс который и явл префиксом шаблона
                    //сокращаем префикс пока не найдем совпадение
                    newPrefix = newPrefix.slice(1);
                }
                
                states[i][char] = newPrefix.length;// сохр переход в состояние с длиной префикса
            }
            
            states[i]['*'] = 0;//если симв не из алфавита то переход в состояние 0
        }
        
        return states;
    }

    search(text) {
        let currentState = 0;
        let result = [];
        let patternLength = this.pattern.length; // Длина искомого шаблона
        let comparisons = 0; // Счетчик сравнений символов
        
        for (let i = 0; i < text.length; i++) {
            let char = text[i];// выбираем симв для переода
            let transitionChar = this.alphabet.includes(char) ? char : '*';//если символ не из алфавита то юзаем *
            
            currentState = this.states[currentState][transitionChar];// переодим между состояниями
            
            if (currentState === patternLength) {//если дошли до конечного состояния то нашли вхождение
                let startIndex = i - patternLength + 1;//считаем начало вхождения
                result.push(startIndex);// сейвим позицию
                currentState = this.states[currentState]['*'];//Сбрасывает текущее состояние автомата в состояние по умолчанию ('*')
                if (result.length === 10) break;//так как нам нужны первые 10
            }
            
            comparisons++;
        }
        
        return {
            matching: result.length,
            top10: result.slice(0, 10),
            collisious: null,
            SymbolComparing: comparisons
        };
    }
}

function dfaSearch(s, t) {//функция обертка чтобы совместить с другими алгоритмами 
    let dfa = new DFA(t);//автомат для шаблона т
    return dfa.search(s);//текст с
}

function main() {
    let args = process.argv.slice(2);
    if (args.length < 3) {
        return("Usage: node substringsearch.js [--bf|--hs|--hrk|--dka] string.txt template.txt");
        process.exit(1);
    }
// парсим аргументы
    let algoritm = args[0];//выбранный алгоритм
    let stringf = args[1];// файл с текстом
    let tempf = args[2];// файл с шаблоном

    let s = readFile(stringf);//читаем начальную строку и шаблон
    let t = readFile(tempf);

    let result;
    let start = process.hrtime();// замеряем время начала работы

    switch (algoritm) {
        case '--bf':
        case '--bruteforce':
            result = brutForce(s, t);
            break;
        case '--hs':
        case '--hashsum':
            result = hashS(s, t);
            break;
        case '--hrk':
        case '--hashRabinKarp':
            result = rabinK(s, t);
            break;
        case '--dka':
        case '--automathon':
            result = dfaSearch(s, t);
            break;
        default:
            return("Unknown algorithm:", algoritm);
            process.exit(1);
    }

    let end = process.hrtime(start);// замеряем время выполнения программы
    let executionTime = (end[0] * 1000 + end[1] / 1000000).toFixed(3);//преобр в милисекунды с округлением до 3 знаков
    let output = { 
        time: parseFloat(executionTime),//преобр в число с плавающей запятой
        ...result// хранит все свойства объекта результ внутри нового объекта аутпут
    };

    return(JSON.stringify(output, null, 2));//возвращаем json
}

main();
