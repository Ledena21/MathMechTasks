//10 баллов

module.exports = function() {
    function main() {
        let args = process.argv.slice(2);
        let fs = require("fs");

        let algorithm = undefined;
        let action = undefined;
        let inputFileName = undefined;
        let outputFileName = undefined;

        switch (args[0]) {
            case "-h":
            case "--help":
                console.log("This program encodes or decodes files using jump or escape encoding.");
                console.log("To use, write node func.js [encoding type] [encoding or decoding] [input file name] [output file name]");
                break;
            case "-e":
            case "--escape":
                algorithm = "escape";
                switch (args[1]){
                    case "-e":
                    case "--encode":
                        action = "encode";
                        inputFileName = args[2];
                        outputFileName = args[3];
                        fs.writeFileSync(outputFileName, EscapeEncode(fs.readFileSync(inputFileName, "utf-8")), "utf-8");
                        break;
                    case "-d":
                    case "--decode":
                        action = "decode";
                        inputFileName = args[2];
                        outputFileName = args[3];
                        fs.writeFileSync(outputFileName, EscapeDecode(fs.readFileSync(inputFileName, "utf-8")), "utf-8");
                        break;
                    default:
                        console.log("Ошибка: неизвестная опция для --escape");
                        break;
                }
                break;
            case "-j":
            case "--jump":
                algorithm = "jump";
                switch (args[1]){
                    case "-e":
                    case "--encode":
                        action = "encode";
                        inputFileName = args[2];
                        outputFileName = args[3];
                        fs.writeFileSync(outputFileName, JumpEncode(fs.readFileSync(inputFileName, "utf-8")), "utf-8");
                        break;
                    case "-d":
                    case "--decode":
                        action = "decode";
                        inputFileName = args[2];
                        outputFileName = args[3];
                        fs.writeFileSync(outputFileName, JumpDecode(fs.readFileSync(inputFileName, "utf-8")), "utf-8");
                        break;
                    default:
                        console.log("Ошибка: неизвестная опция для --jump");
                        break;
                }
                break;
            default:
                console.log("Ошибка: неизвестная опция");
                break;
        }

        return {
            "algorithm": algorithm,
            "action": action,
            "inputFileName": inputFileName,
            "outputFileName": outputFileName
        };
    }
    
    return main();
}

function EscapeEncode(str) {
    let str2 = "";
    let sym = "";
    for (let i = 0; i < str.length; i++) {
        sym = str[i];
        let count = 1;
        while (i < str.length - 1 && str[i] === str[i + 1]) {
            count++;
            i++;
        }
		if (sym != "#"){
			while (count>259){
				str2+= "#"+String.fromCharCode(255)+sym;
				count-=259;
			}
			if (count>=4){
				str2+="#"+String.fromCharCode(count-4)+sym;
			} else {
                str2+=sym.repeat(count)
			}
		} else {
			while (count>256){
                str2+=String.fromCharCode(255)+sym;
                count-=256;
            }
            str2+="#"+String.fromCharCode(count-1)+sym;
		}
	}
    return str2;
}

function EscapeDecode(str) {
    let str2 = "";
    let i = 0;
    while (i < str.length) {
        if (str[i] === "#") {
            let count = str.charCodeAt(i + 1);
            let sym = str[i + 2];
            if (sym !== "#") {
                str2 += sym.repeat(count + 4);
            } else {
                str2 += sym.repeat(count + 1);
            }
            i += 3;
        } else {
            str2 += str[i];
            i++;
        }
    }
    return str2;
}

function JumpEncode(str) {
    let str2 = "";
    let i = 0;
    let uniq = "";
    while (i < str.length) {
        let sym = str[i];
        let count = 1;
        while (i + count < str.length && str[i + count] === sym) {
            count++;
        }
        if (count >= 3) {
            if (uniq.length > 0) {
                str2 +=  String.fromCharCode(uniq.length + 127) + uniq;
                uniq = "";
            }
            while (count > 0) {
                const chunk = Math.min(count, 130);
                str2 += String.fromCharCode(chunk - 3) + sym;
                count -= chunk;
                i += chunk;
            }
        } else {
            uniq += sym;
            i++;
            if (uniq.length >= 128) {
                str2 += String.fromCharCode(255) + uniq.slice(0, 128);
                uniq = uniq.slice(128);
            }
        }
    }
    if (uniq.length > 0) {
        str2 += String.fromCharCode(uniq.length + 127) + uniq;
    }
    return str2;
}

function JumpDecode(str) {
    let str2 = "";
    let i = 0;
    while (i < str.length) {
        let count = str.charCodeAt(i);
        if (count > 127) {
            let length = count - 127;
            let sequence = str.substring(i + 1, i + 1 + length);
            str2 += sequence;
            i += 1 + length;
        } else {
            let sym = str[i + 1];
            str2 += sym.repeat(count + 3);
            i += 2;
        }
    }
    return str2;
}
