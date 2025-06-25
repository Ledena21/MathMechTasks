let fs = require('fs');

function BruteForce(text, pattern) {
    let start = process.hrtime.bigint(); //начинаем отсчет времени
    let n = text.length;
    let m = pattern.length;
    let matching = [];  //массив, куда мы будем класть индексы начала совпадений
    let comp = 0;
    
    for (let i = 0; i <= n - m; i++) {//идем по тексту
        let j;
        for (j = 0; j < m; j++) { //идем по шаблону
            comp++; //считаем сравнение символов
            if (text[i + j] !== pattern[j]){ //если не совпадают
                break; //прерываем проверку
            } 
        }
        if (j === m){ //если дошли до конца -> совпадает
            matching.push(i);//положим индекс начала совпадения в массив
        } 
    }
    return {
        time: (Number(process.hrtime.bigint() - start) / 1000000).toFixed(4) + " ms",
        matching: matching.length,
        top10: matching.slice(0, 10),
        collisious: null,
        SymbolComparing: comp
    };
}

function HashSum(text, pattern) {
    let start = process.hrtime.bigint(); //начинаем отсчет времени
    let M = 997;
    let n = text.length;
    let m = pattern.length;
    let matching = []; //массив, куда мы будем класть индексы начала совпадений
    let collisions = 0;
    let comp = 0;

    let patternHash = 0;
    for (let i = 0; i < m; i++) { //находим хэш для шаблона
        patternHash = (patternHash + pattern.charCodeAt(i)) % M;
    }

    let windowHash = 0;
    for (let i = 0; i < m; i++) { //находим хэш для первого куска
        windowHash = (windowHash + text.charCodeAt(i)) % M;
    }

    for (let i = 0; i <= n - m; i++) { //идем по строке
        if (windowHash === patternHash) { //если хэш совпал
            let match = true;
            for (let j = 0; j < m; j++) { //проверяем посимвольно
                comp++; //считаем сравнения символов
                if (text[i + j] !== pattern[j]) { //если символы не совпадают
                    match = false; // совпадения нет
                    collisions++; // и это коллизия
                    break;
                }
            }
            if (match) {
                matching.push(i); //положим индекс начала совпадения в массив
            }
        }
        if (i < n - m) {
            windowHash = (windowHash - text.charCodeAt(i) + text.charCodeAt(i + m)) % M; //пересчитываем хэш для следующего куска
            if (windowHash < 0){
                windowHash += M;
            }
        }
    }

    return {
        time:(Number(process.hrtime.bigint() - start) / 1000000).toFixed(4) + " ms",
        //из текущего момента вычитаем старт, преобразуем разность в обычное число, делим наносекунды на 1000000,
        //чтобы перевести в милисекунды, через .toFixed возвращаем 4 знака после запятой и пишем единицы измерения
        matching: matching.length,
        top10: matching.slice(0, 10),
        collisious: collisions || null,
        SymbolComparing: comp
    };
}

function hashRabinKarp(text, pattern) {
    const start = process.hrtime.bigint();
    const M = 997;
    const n = text.length;
    const m = pattern.length;
    const matches = []; //массив, куда мы будем класть индексы начала совпадений
    let collisions = 0;
    let comp = 0;
    let patternHash = 0;

    for (let i = 0; i < m; i++) { //посчитаем хэш для шаблона
        patternHash = (patternHash * 2 + pattern.charCodeAt(i)) % M;
    }

    let windowHash = 0;
    for (let i = 0; i < m; i++) { //посчитаем хэш для первого куска
        windowHash = (windowHash * 2 + text.charCodeAt(i)) % M;
    }

    for (let i = 0; i <= n - m; i++) { //идем по строке
        if (windowHash === patternHash) { //если хэш совпадает
            let isMatch = true;
            for (let j = 0; j < m; j++) { //идем сравнивать символы
                comp++; //считаем сравнения
                if (text[i + j] !== pattern[j]) { //если символы не совпадают
                    isMatch = false; //нет совпадения
                    collisions++; //это коллизия
                    break;
                }
            }
            if (isMatch) matches.push(i); //положим индекс начала совпадения в массив
        }
        if (i < n - m) {
            windowHash = (windowHash * 2 - text.charCodeAt(i) * ((2**(m-1))%M) * 2 + text.charCodeAt(i + m)) % M;
            if (windowHash < 0){ //если хэш ушел в минус
                windowHash += M; //прибавим М
            }
        }
    }

    return {
        time: (Number(process.hrtime.bigint() - start) / 1000000).toFixed(4) + " ms",
        matching: matches.length,
        top10: matches.slice(0, 10),
        collisious: collisions || null,
        comp: comp
    };
}

let args = process.argv.slice(2);

switch (args[0]) {
    case "-h":
    case "--help":
        console.log("Algorithm for finding a substring in a string");
        console.log("To start, enter subringsearch [method of finding] [text] [pattern]");
        break;
    case "--bf":
    case "--bruteforce":
        text = fs.readFileSync(args[1], "utf-8");
        pattern = fs.readFileSync(args[2], "utf-8");
        BruteForce(text, pattern);
        break;
    case "--hs":
    case "--hashsum":
        text = fs.readFileSync(args[1], "utf-8");
        pattern = fs.readFileSync(args[2], "utf-8");
        HashSum(text, pattern);
        break;
    case "--hrk":
    case "--hashRabinKarp":
        text = fs.readFileSync(args[1], "utf-8");
        pattern = fs.readFileSync(args[2], "utf-8");
        hashRabinKarp(text, pattern);
        break;
    default:
        console.log("Invalid option. Use -h for help.");
}
