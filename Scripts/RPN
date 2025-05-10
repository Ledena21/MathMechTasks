//создаем объект, чтобы соотносить операторы с приоритетами
let priority = {
    "^": 1,
    "*": 2,
    "/": 2,
    "+": 3,
    "-": 3
};

function isOperand(chunk) {
    return chunk.match(/^[a-zA-Z0-9]+$/) !== null; //проверяем, является ли chunk числом или переменной, =! null нужно, потому что, если chunk не число и не переменная, вернется null
}

function isOperator(chunk) {
    return ["^", "*", "/", "+", "-"].includes(chunk); //создаем массив из операторов и смотрим, есть ли там chunk
}

function InToPost(infix) {
    if (/([a-zA-Z]\d|\d[a-zA-Z])/.test(infix.replace(/\s/g, ''))) {
        return "ERROR: Смешаны цифры и буквы";
    }

    let stack = []; //создаем стек
    let out = []; //создаем out
    let chunks = infix.replace(/\s+/g, "").split(/([()^*/+-])/).filter(chunk => chunk !== "");
    // с помощью replace(/\s+/g, "" удаляем из строки все пробелы
    //через .split(/([()^*/+-])/) разбиваем строку на отдельные куски по операторам и скобкам
    //.filter(chunk => chunk !== "" убираем все пустые строки. 
    // С помощью filter проверяем каждый элемент массива и возвращаем новый массив из элементов
    //для которых выполняется условие chunk !== ""

    if (chunks.length === 0) {
        return "ERROR: Пустое выражение";
    }
    if (isOperator(chunks[chunks.length - 1])) {
        return "ERROR: Пропущен операнд";
    }

    let lastSym = null; //здесь будем запоминать тип последнего обработанного символа, чтобы находить ошибки

    for (let i = 0; i < chunks.length; i++) {
        let chunk = chunks[i];

        if ((lastSym === "operand" && chunk === "(") || //если операнд стоит перед открывающей скобкой
            (lastSym === ")" && isOperand(chunk)) ||  //или после закрывающей скобки
            (lastSym === "operand" && isOperand(chunk)) || // или два операнда идут подряд
            (lastSym === ")" && chunk === "(")) { //или сначала закрывающая, потом открывающая скобка
            
            while (stack.length > 0 && stack[stack.length - 1] !== "(" && 
                   priority[stack[stack.length - 1]] <= priority["*"]) {
                //пока стек не пуст и последний элемент стека не открывающая скобка 
                    // и приоритет последнего оператора в стеке меньше или равен приоритету умножения (*).
                    out.push(stack.pop()); //выталкиваем последний элемент стека в out
                }
                stack.push("*"); //кладем в стек умножение
                lastSym = "operator"; //запоминаем, что последний символ - оператор
            }

        if (isOperand(chunk)) { //если кусок операнд
            for (let j = 0; j < chunk.length; j++) {
                out.push(chunk[j]); //добавляем операнд в out
                if (j < chunk.length - 1) { //если в операнде несколько символов
                    while (stack.length > 0 && stack[stack.length - 1] !== "(" && 
                           priority[stack[stack.length - 1]] <= priority["*"]) {
                        //пока стек не пуст и последний элемент стека не открывающая скобка 
                        // и приоритет последнего оператора в стеке меньше или равен приоритету умножения (*).
                        out.push(stack.pop()); //выталкиваем последний элемент стека в out
                    }
                    stack.push("*"); //вставляем умножение между символами
                    lastSym = "operator"; //запоминаем, что последний символ - оператор
                }
            }
            lastSym = "operand"; //запоминаем, что последний символ - операнд
        }

        else if (chunk === "(") { //если встретили открывающую скобку
            stack.push(chunk); //положили ее в стек
            lastSym = "("; //запомнили, что последний символ - открывающая скобка
        } 
        else if (chunk === ")") { //если встретили закрывающую скобку
            let foundOpening = false; //этот флаг указывает, есть ли закрывающая скобка.
            while (stack.length > 0 && stack[stack.length - 1] !== "(") { //пока не нашли открывающую скобку
                out.push(stack.pop()); //выталкиваем операторы
            }
            if (stack.length > 0 && stack[stack.length - 1] === "(") { //если нашли открывающую скобку
                stack.pop(); //убрали ее из стека
                foundOpening = true; //переводим флаг в состояние true
            }
            if (!foundOpening) { //если не нашли открывающую скобку, выводим ошибку
                return "ERROR: Пропущена открывающая скобка (";
            }
            lastSym = ")"; //запомнили, что последний символ - закрывающая скобка
        } 
        else if (isOperator(chunk)) { // если кусок - оператор
            while (stack.length > 0 && stack[stack.length - 1] !== "(" && 
                   priority[stack[stack.length - 1]] <= priority[chunk]) {
                //пока стек не пуст и последний элемент стека не открывающая скобка 
                // и приоритет последнего оператора в стеке меньше или равен приоритету текущего оператора.
                out.push(stack.pop());
            }
            stack.push(chunk); //добавляет оператор в стек
            lastSym = "operator"; //запоминаем, что последний символ - оператор
        }
    }
    //очищаем стек в конце
    while (stack.length > 0) {
        let ch = stack.pop();
        if (ch === "(") {
            return "ERROR: Не закрыта скобка";
        }
        out.push(ch);
    }

    return out.join("");
}
function PostToIn(postfix) {
    let stack = [];
    for (let i = 0; i < postfix.length; i++) {
        let chunk = postfix[i];
        if (isOperand(chunk)) {
            stack.push({ value: chunk, priority: 0 }); //сделаем операндам нулевой приоритет
        } 
        else if (isOperator(chunk)) {
            if (stack.length < 2) { //если длина стека меньше 2, ошибка
                return "ERROR: Пропущен операнд";
            }
            //берем 2 последних элемента стека
            let right = stack.pop();
            let left = stack.pop();
            let currentPriority = priority[chunk]; //приоритет текущего оператора
            let leftExpr = left.value; //левое выражение
            if (left.priority > currentPriority) { //если его приоритет выше текущего оператора
                leftExpr = `(${leftExpr})`; //оно берется в скобки
            }
            let rightExpr = right.value; //правое выражение
            if (right.priority > currentPriority || 
                (right.priority === currentPriority && (chunk === '^' || chunk === '-' || chunk === '/'))) {
                //если приоритет выше текущего оператора или приоритеты равны, но оператор правоассоциативный
                rightExpr = `(${rightExpr})`; //оно берется в скобки
            }

            stack.push({
                value: leftExpr + chunk + rightExpr, //новое выражение
                priority: currentPriority //текущий приоритет
            });
        } 
        else {
            return "ERROR: Недопустимый символ " + chunk;
        }
    }

    if (stack.length !== 1) {
        return "ERROR: Пропущен оператор";
    }

    return stack[0].value;
}

function Calculator(expr) {
    if (expr.includes("ERROR:")) {
        return expr; //просто возвращаем сообщение об ошибке
    }

    let balance = 0; //тут посчитаем количество скобок
    for (let char of expr) {
      if (char === "(") balance++; //если нашли открывающую скобку, увеличиваем счетчик
      if (char === ")") balance--; //если нашли закрывающую скобку, уменьшаем счетчик
    }
    if (balance != 0) { //если их количество не равно, ошибка
        return "ERROR: Неправильно расставлены скобки";
    }
  
    let result = new Function(`return ${expr}`)(); //считаем выражение
    //получается, мы создаем новую функцию, в return которой записываем все выражение, вызываем ее, и она возвращает выражение

    if (isFinite(result)){ //если результат - конечное значение, а не NuN, Unfinity и прочее
        return result; //то возвращаем результат
    } else { //иначе выводим ошибку
        return "ERROR: Расчет не выполнен";
    }
  }

  let args = process.argv.slice(2);

  switch (args[0]) {
      case "-h":
      case "--help":
          console.log("Convert infix to postfix: node rpn.js --in2post \"expression\"");
          console.log("Convert postfix to infix: node rpn.js --post2in \"expression\"");
          break;
      case "--in2post":
          let inf = args[1].replace(/\s/g, "");
          console.log(InToPost(inf));
          if (InToPost(inf).includes("ERROR:")===false && /^[\d()+*\/\-.]*$/.test(inf)==true){
              console.log("Result: "+Calculator(PostToIn(InToPost(inf))));
          }
          break;
      case "--post2in":
          let postf = args[1].replace(/\s/g, "");
          console.log(PostToIn(postf));
          if (PostToIn(postf).includes("ERROR:")===false && /^[\d()+*\/\-.]*$/.test(PostToIn(postf))==true){
              console.log("Result: "+Calculator(PostToIn(postf)));
          }
          break;
      default:
          console.log("Invalid option. Use -h for help.");
  }
