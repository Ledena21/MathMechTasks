class RPNConverter {
    constructor() {
        // Таблица операторов с их приоритетами и ассоциативностью
        this.operators = {
            '^': { prioritet: 1, assoc: 'right' },  // степень наивысший приоритет
            '*': { prioritet: 2, assoc: 'left' },   
            '/': { prioritet: 2, assoc: 'left' },   
            '+': { prioritet: 3, assoc: 'left' },  
            '-': { prioritet: 3, assoc: 'left' }   
        };
    }

    // проверка символ это оператор? 
    isOperator(znak) {
        return znak in this.operators;
    }

    // Проверяет, является ли символ операндом (буква или цифра)
    isOperand(znak) {
        return /^[a-zA-Z0-9]$/.test(znak);
    }

    // Нормализуем выражение (добавляем * где это требуется)
    normalizeExpression(expression) {
        let znaks = this.znakize(expression);
        let normalized = [];
        
        for (let i = 0; i < znaks.length; i++) {
            normalized.push(znaks[i]);
            
            // проверяем необходимость вставки *
            if (i < znaks.length - 1) {
                let current = znaks[i];
                let next = znaks[i+1];
                
                // когда добавляем *:
                if ((this.isOperand(current) && this.isOperand(next)) ||      // между двумя операндами
                    (this.isOperand(current) && next === '(') ||             // между операндом и открывающей скобкой
                    (current === ')' && this.isOperand(next)) ||             // между закрывающей скобкой и операндом
                    (current === ')' && next === '(')) {                    // между двумя скобками
                    normalized.push('*');
                }
            }
        }
        
        return normalized.join('');
    }

    // infix to postfix
    infixToPostfix(expression) {
        let normalized = this.normalizeExpression(expression);
        let output = [];
        let stack = [];  
        let znaks = this.znakize(normalized);
        let lastznakType = null;

        // Проверка на пустое выражение
        if (znaks.length === 0) {
            throw new Error("Empty expression");
        }

        for (let znak of znaks) {
            if (this.isOperand(znak)) {
                output.push(znak);
                lastznakType = 'operand';
            } 
            else if (znak === '(') {
                stack.push(znak);
                lastznakType = 'paren';
            } 
            else if (znak === ')') {
                let foundOpening = false;
                while (stack.length > 0) {
                    let top = stack.pop();
                    if (top === '(') {
                        foundOpening = true;
                        break;
                    }
                    output.push(top);
                }
                if (!foundOpening) {
                    throw new Error("Mismatched parentheses: missing opening parenthesis");
                }
                lastznakType = 'paren';
            } 
            else if (this.isOperator(znak)) {
                // Проверка на два оператора подряд или оператор в начале
                if (lastznakType === 'operator' || lastznakType === null) {
                    throw new Error("Missing operand");
                }

                while (stack.length > 0 && stack[stack.length - 1] !== '(' && 
                      (this.operators[stack[stack.length - 1]].prioritet <= this.operators[znak].prioritet)) {
                    output.push(stack.pop());
                }
                stack.push(znak);
                lastznakType = 'operator';
            }
            else {
                throw new Error(`Invalid character: ${znak}`);
            }
        }

        // Проверка на оператор в конце
        if (lastznakType === 'operator') {
            throw new Error("Missing operand");
        }

        while (stack.length > 0) {
            let top = stack.pop();
            if (top === '(') {
                throw new Error("Mismatched parentheses: missing closing parenthesis");
            }
            output.push(top);
        }

        return output.join('');
    }

    // postfix to infix
    postfixToInfix(expression) {
        let stack = []; 
        let znaks = this.znakize(expression);

        if (znaks.length === 0) {
            throw new Error("Empty expression");
        }

        for (let znak of znaks) {
            if (this.isOperand(znak)) {
                stack.push(znak);
            } 
            else if (this.isOperator(znak)) {
                if (stack.length < 2) {
                    throw new Error("Not enough operands for operator");
                }
                
                let right = stack.pop();
                let left = stack.pop();
                
                let needLeft = this.needsParentheses(left, znak);
                let needRight = this.needsParentheses(right, znak);
                
                if (znak === '-' && this.containsOperator(right)) {
                    needRight = true;
                }
                
                let leftExpr = needLeft ? `(${left})` : left;
                let rightExpr = needRight ? `(${right})` : right;
                
                stack.push(`${leftExpr}${znak}${rightExpr}`);
            }
            else {
                throw new Error(`Invalid character: ${znak}`);
            }
        }

        if (stack.length !== 1) {
            throw new Error("Too many operands");
        }

        return stack[0];
    }

    containsOperator(expr) {
        for (let char of expr) {
            if (this.isOperator(char)) return true;
        }
        return false;
    }

    needsParentheses(expr, parentOp) {
        if (!this.containsOperator(expr)) return false;
        if (expr.startsWith('(') && expr.endsWith(')')) return false;
        
        let mainOp = this.findMainOperator(expr);
        if (!mainOp) return false;
        
        return this.operators[mainOp].prioritet >= this.operators[parentOp].prioritet;
    }

    findMainOperator(expr) {
        let depth = 0;
        let minprioritet = Infinity;
        let mainOp = null;
        
        for (let i = 0; i < expr.length; i++) {
            let char = expr[i];
            if (char === '(') depth++;
            else if (char === ')') depth--;
            else if (depth === 0 && this.isOperator(char)) {
                let prec = this.operators[char].prioritet;
                if (prec < minprioritet) {
                    minprioritet = prec;
                    mainOp = char;
                }
            }
        }
        
        return mainOp;
    }

    znakize(expr) {
        if (typeof expr !== 'string') {
            throw new Error("Expression must be a string");
        }
        return expr.replace(/\s+/g, '').split('').filter(ch => ch !== '');
    }
}

function main() {
    let args = process.argv.slice(2);
    
    if (args.length < 2) {
        console.error("Usage: node qq.js --in2post|--post2in \"expression\"");
        console.error("Note: Expressions with parentheses must be quoted");
        console.error("Example without quotes: node qq.js --in2post a+b");
        console.error("Example with quotes: node qq.js --in2post \"(a+b)*c\"");
        process.exit(1);
    }
    
    let mode = args[0];
    let expr = args.slice(1).join(' ');
    let converter = new RPNConverter();
    
    try {
        if (mode === '--in2post') {
            console.log(converter.infixToPostfix(expr));
        } else if (mode === '--post2in') {
            console.log(converter.postfixToInfix(expr));
        } else {
            console.error("Invalid mode. Use --in2post or --post2in");
            process.exit(1);
        }
    } catch (error) {
        console.error("Error:", error.message);
        process.exit(1);
    }
}

main();
