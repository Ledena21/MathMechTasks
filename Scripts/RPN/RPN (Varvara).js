let args = process.argv.slice(2);//извлекаем аргументы ком.строки
let mode = args.find(arg => arg === '--in2post' || arg === '--post2in');
let expression = args.find(arg => arg !== mode)?.replace(/\s+/g, '') || ''; //1 эл не флаг, защита от оштбок и безопасный вызов реплейс. игнорируем пробелы во всей строке
//если слева ноль или undef. то пустая строка будет аргументом 
if (!mode || !expression) {//проверка аргументов
    console.log('Use: node rpn.js --in2post/--post2in "expression" :)) ');
    process.exit(1);
}

let priority = {//расставляем приоритеты операций
    '^': 1,
    '*': 2,
    '/': 2,
    '+': 3,
    '-': 3
};

function operator(token) {//проверка является ли переданный симв. алгебраическим оператором
    return ['+', '-', '*', '/', '^'].includes(token);
}

function operand(token) {//проверкаа операндов
    return /^[a-zA-Z0-9]+$/.test(token);// ^ - начало строки, латинница, + - один и более символов, $ - конец строки
}

function in2post(infix) {//инфиксное выражение в постфиксную форму
    let output = [];//массивдля выодной строки
    let stack = [];//стек для операторов и скобок
    let bracket = 0;//считает скобки
    let lastsimvol = null;//последний сивол
    let infixtemp = '';//с ее помощью будем модифицировать стр

    for (let i = 0; i < infix.length; i++) {
        const token = infix[i];
        if (lastsimvol && (//проверяем нужно ли вставлять *
            (operand(lastsimvol) && (operand(token) || token === '(')) ||//есл предыдущий симв операнд и текущ симв тоже или скобка (
            (lastsimvol === ')' && (operand(token) || token === '('))// пред ) и текущ операнд или (
        )) {
            infixtemp += '*';//доб *
        }
        infixtemp += token;//добавляем к временной стр текущий символ
        lastsimvol = token;//последний символ записываем
    }

    if (infixtemp.length > 0 && operator(infixtemp[infixtemp.length - 1])) {//не заканчивается ли выражение оператором (как раз тот случай с а+)
        throw new Error('Missing operand after operator');
    }

    for (let i = 0; i < infixtemp.length; i++) {
        let token = infixtemp[i];
        if (operand(token)) {
            output.push(token);//если симв- операнд, то он доб в выодную очередь
        } else if (token === '(') {
            stack.push(token);//доб скобку в стек
            bracket++;
        } else if (token === ')') {
            if (bracket <= 0) throw new Error('Missing opening parenthesis');//если счетчик скобок <= 0 то ошибка
            bracket--;
            while (stack.length && stack[stack.length - 1] !== '(') {//стек не пуст и верний эл-нт не ( 
                output.push(stack.pop());//доб верний эл в выодную часть стека
            }
            stack.pop(); // Удаляем '('
        } else if (operator(token)) {
            if (i === 0 || operator(infixtemp[i - 1]) || infixtemp[i - 1] === '(') {//если оператор  1й сим / 2 оператора подряд / оператор после (
                throw new Error('Missing operand before operator');
            }

            while (stack.length && stack[stack.length - 1] !== '(' &&//верний эл не (
                   priority[token] >= priority[stack[stack.length - 1]]) {//сравниваем приоритеты оператора
                output.push(stack.pop());//выталкиваем из стека которые >= по приоритетам
            }
            stack.push(token);//добавляем оператор в стек
        } else {
            throw new Error(`Invalid character: ${token}`);
        }
    }

    if (bracket !== 0) throw new Error('Missing closing parenthesis');//проверяем что все скобки закрыты
    while (stack.length) {
        const op = stack.pop();//убираем операторы из стека
        if (op === '(') throw new Error('Unmatched parenthesis');//если скобки ( остались еще
        output.push(op);//доб операторы в выход
    }

    return output.join('');//склеиваем в стр элементы массива
}
function post2in(postfix) {
    let stack = [];

    for (let i = 0; i < postfix.length; i++) {
        const token = postfix[i];

        if (operand(token)) {
            stack.push(token);//помещаем операнды в стек
        } else if (operator(token)) {
            if (stack.length < 2) { //так как нам надо 2 операнда
                throw new Error('operand is omitte!');
            }
            let right = stack.pop();
            let left = stack.pop();//извлекаем правый и левый
        
            let rightStr = (right.match(/[+\-*/^]/)) ? `(${right})` : right;
            let leftStr = (left.match(/[+\-*/^]/)) ? `(${left})` : left;//ставим () вокруг операндов
            
            stack.push(`${leftStr}${token}${rightStr}`); // строим выражение и в стек
        } else {
            throw new Error(`invalid character: ${token}`);
        }
    }

    if (stack.length !== 1) {//проверяем что в стеке 1 элемент тк оно должно свернуться в 1 выражение
        throw new Error('missing operator...');
    }

    return stack[0];//возвращаем инфиксное выражение
}

try {
    let result; //проверяем режим работы
    if (mode === '--in2post') {
        result = in2post(expression);
    } else {
        result = post2in(expression);
    }
    console.log(result);
} catch (error) { //обрабатываем все ошибке в прошлом блоке 
    console.error('And nothing is that fact that error? ', error.message);
    process.exit(1);
}
