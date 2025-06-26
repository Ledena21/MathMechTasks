let fs = require('fs');

// Функция для чтения содержимого файла
function readFileContent(filePath) {
    try {
        return fs.readFileSync(filePath, 'utf-8');
    } catch (error) {
        return `Ошибка чтения файла ${filePath}: ${error.message}`;
    }
}

// Алгоритм грубой силы
function bruteForceSearch(s, t) {
    let n = s.length;
    let m = t.length;
    let result = [];
    let comparisons = 0;

    for (let i = 0; i <= n - m; i++) {
        let match = true;
        for (let j = 0; j < m; j++) {
            comparisons++;
            if (s[i + j] !== t[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            result.push(i);
        }
    }

    return {
        matching: result.length,
        top10: result.slice(0, 10),
        collisious: null,
        SymbolComparing: comparisons
    };
}

// Алгоритм с использованием хэш-суммы
function hashSumSearch(s, t) {
    let n = s.length;
    let m = t.length;
    let result = [];
    let collisions = 0;
    let comparisons = 0;
    
    if (n < m) {
        return {
            matching: 0,
            top10: [],
            collisious: 0,
            SymbolComparing: 0
        };
    }

    let M = 1000000007;
    let patternHash = 0;
    for (let i = 0; i < m; i++) {
        patternHash = (patternHash + t.charCodeAt(i)) % M;
    }

    let windowHash = 0;
    for (let i = 0; i < m; i++) {
        windowHash = (windowHash + s.charCodeAt(i)) % M;
    }

    for (let i = 0; i <= n - m; i++) {
        if (windowHash === patternHash) {
            let match = true;
            for (let j = 0; j < m; j++) {
                comparisons++;
                if (s[i + j] !== t[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                result.push(i);
            } else {
                collisions++;
            }
        }

        if (i < n - m) {
            windowHash = (windowHash - s.charCodeAt(i) + s.charCodeAt(i + m)) % M;
            if (windowHash < 0) {
                windowHash += M;
            }
        }
    }

    return {
        matching: result.length,
        top10: result.slice(0, 10),
        collisious: collisions,
        SymbolComparing: comparisons
    };
}

// Алгоритм Рабина-Карпа
function rabinKarpSearch(s, t) {
    let n = s.length;
    let m = t.length;
    let result = [];
    let collisions = 0;
    let comparisons = 0;
    
    if (n < m) {
        return {
            matching: 0,
            top10: [],
            collisious: 0,
            SymbolComparing: 0
        };
    }

    let M = 1000000007;
    let d = 256;
    let h = 1;

    for (let i = 0; i < m - 1; i++) {
        h = (h * d) % M;
    }

    let patternHash = 0;
    let windowHash = 0;
    for (let i = 0; i < m; i++) {
        patternHash = (d * patternHash + t.charCodeAt(i)) % M;
        windowHash = (d * windowHash + s.charCodeAt(i)) % M;
    }

    for (let i = 0; i <= n - m; i++) {
        if (windowHash === patternHash) {
            let match = true;
            for (let j = 0; j < m; j++) {
                comparisons++;
                if (s[i + j] !== t[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                result.push(i);
            } else {
                collisions++;
            }
        }

        if (i < n - m) {
            windowHash = (d * (windowHash - s.charCodeAt(i) * h) + s.charCodeAt(i + m));
            windowHash %= M;
            if (windowHash < 0) {
                windowHash += M;
            }
        }
    }

    return {
        matching: result.length,
        top10: result.slice(0, 10),
        collisious: collisions,
        SymbolComparing: comparisons
    };
}

// Алгоритм ДКА (Детерминированный конечный автомат)
function automatonSearch(s, t) {
    let n = s.length;
    let m = t.length;
    let result = [];
    let comparisons = 0;
    let stateTransitions = 0;

    if (n < m || m === 0) {
        return {
            matching: 0,
            top10: [],
            collisious: null,
            SymbolComparing: 0,
            stateTransitions: 0
        };
    }

    // Строим таблицу переходов для ДКА
    function buildTransitionTable(pattern) {
        let alphabet = [...new Set(pattern)];
        let table = [];
        
        for (let q = 0; q <= pattern.length; q++) {
            let row = {};
            let currentPrefix = pattern.slice(0, q);
            
            for (let c of alphabet) {
                let k = Math.min(q + 1, pattern.length);
                while (k > 0) {
                    let prefix = pattern.slice(0, k);
                    let possibleState = currentPrefix + c;
                    if (possibleState.endsWith(prefix)) {
                        break;
                    }
                    k--;
                }
                row[c] = k;
            }
            table.push(row);
        }
        
        return table;
    }

    let transitionTable = buildTransitionTable(t);
    let currentState = 0;

    for (let i = 0; i < n; i++) {
        let c = s[i];
        comparisons++;
        
        if (transitionTable[currentState][c] !== undefined) {
            stateTransitions++;
            currentState = transitionTable[currentState][c];
        } else {
            currentState = 0;
        }

        if (currentState === m) {
            result.push(i - m + 1);
            currentState = transitionTable[currentState][t[m-1]] || 0;
        }
    }

    return {
        matching: result.length,
        top10: result.slice(0, 10),
        collisious: null,
        SymbolComparing: comparisons,
        stateTransitions: stateTransitions
    };
}

// Основная функция поиска
function substringSearch(algorithm, stringFile, templateFile) {
    let s = readFileContent(stringFile).replace(/\s+/g, '');
    let t = readFileContent(templateFile).replace(/\s+/g, '');

    if (typeof s !== 'string' || typeof t !== 'string') {
        return { error: "Ошибка чтения файлов" };
    }

    let startTime = process.hrtime();
    let result;

    switch (algorithm) {
        case '--bf':
        case '--bruteforce':
            result = bruteForceSearch(s, t);
            break;
        case '--hs':
        case '--hashsum':
            result = hashSumSearch(s, t);
            break;
        case '--hrk':
        case '--hashRabinKarp':
            result = rabinKarpSearch(s, t);
            break;
        case '--automaton':
        case '--dka':
            result = automatonSearch(s, t);
            break;
        default:
            return { error: "Неверный алгоритм. Используйте --bf, --hs, --hrk или --automaton" };
    }

    let endTime = process.hrtime(startTime);
    let executionTime = (endTime[0] * 1000 + endTime[1] / 1000000).toFixed(3);

    return {
        time: parseFloat(executionTime),
        ...result
    };
}

// Экспорт функции для использования в другом файле
module.exports = function() {
    let args = process.argv.slice(2);
    
    if (args.length < 3) {
        return { error: "Использование: [--bf|--hs|--hrk|--automaton] строка.txt шаблон.txt" };
    }

    return substringSearch(args[0], args[1], args[2]);
};
