function calculateControlBits(dataBits) {
    let r = 0; 
    // Вычисляем минимальное r - такое что 2^r >= dataBits + r + 1
    while (Math.pow(2, r) < dataBits + r + 1) {
      r++; 
    }
    return r;
  }
  
  function encodeHamming(data) {
    // gроверка на то что входные данные состоят только из 0 и 1
    if (!/^[01]+$/.test(data)) {
      throw new Error('Входные данные должны быть битовой строкой (0 или 1)');
    }
  
    let k = data.length; // Кол информационных битов
    let r = calculateControlBits(k); // Кол-во контрольных битов
    let n = k + r; // длина закодированного слова
    
    // массив для закодированного слова, заполненный нулями
    let encoded = new Array(n).fill(0);
    let dataIndex = 0; // Индекс для перемещения по входным данным
  
    // Заполняем биты данных (позиции, которые не степени двойки)
    for (let i = 1; i <= n; i++) {
      // Проверяем, является ли позиция степенью двойки
      if ((i & (i - 1)) !== 0) { // eсли i не степень двойки
        if (dataIndex < k) { // eсли еще есть данные для вставки
          // Вставляем бит данных в текущую позицию
          encoded[i - 1] = parseInt(data[dataIndex]);
          dataIndex++; 
        }
      }
    }
  
    // Вычиc. контрольные биты
    for (let p = 0; p < r; p++) {
      let pos = Math.pow(2, p); // это позиция контрольного бита (1, 2, 4, 8...)
      let xor = 0; 
      
      // идем по всем битам, которые включают этот контрольный бит
      for (let i = pos; i <= n; i++) {
        if ((i & pos) === pos) { // Если бит pos установлен в числе i
          xor ^= encoded[i - 1]; // Вычисляем XOR с текущим битом
        }
      }
      
      // Устанавливаем вычисленное значение контрольного бита
      encoded[pos - 1] = xor;
    }
// XOR - это битовая операция, которая: Возвращает 0, если оба бита одинаковые (0^0 = 0, 1^1 = 0) Возвращает 1, если биты разные (0^1 = 1, 1^0 = 1)
  
    return encoded.join('');// Преобразуем массив в строку и возвращаем результат
  }
  
  function decodeHamming(encoded) {
    if (!/^[01]+$/.test(encoded)) {
      throw new Error('Закодированные данные должны быть битовой строкой (0 или 1)');
    }
  
    let n = encoded.length; // Длина закод. слова
    let bits = encoded.split('').map(bit => parseInt(bit));
    let errorPos = 0; // это позиция ошибки (0 если нет ошибки)
    
    // Находим количество контрольных битов
    let r = 0;
    while (Math.pow(2, r) < n + 1) r++;
  
    // Вычисление позиции ошибки
    for (let p = 0; p < r; p++) {
      let pos = Math.pow(2, p); // Позиция текущего контрольного бита
      let xor = 0; // Переменная для хранения XOR
      
      // Проверяем все биты, которые включают этот контрольный бит
      for (let i = pos; i <= n; i++) {
        if ((i & pos) === pos) { // Если бит pos установлен в числе i
          xor ^= bits[i - 1]; // Вычисляем XOR с текущим битом
        }
      }
      
      // Если XOR не равен 0, добавляем позицию контрольного бита к errorPos
      if (xor !== 0) {
        errorPos += pos;
      }
    }
  
    // Исправляем ошибку, если она есть
    if (errorPos !== 0 && errorPos <= n) {
      // Инвертируем бит в ошибочной позиции (XOR с 1)
      bits[errorPos - 1] ^= 1;
      console.log(`Обнаружена и исправлена ошибка в бите ${errorPos}`);
    } else if (errorPos > n) {
      console.log('Обнаружены множественные ошибки - исправление невозможно');
    }
  
    // Извлекаем исходные данные
    let decoded = '';
    let k = n - r; // Количество информационных битов
    let dataIndex = 0;
    
    for (let i = 1; i <= n && dataIndex < k; i++) {
      // Если позиция не является степенью двойки (не контрольный бит)
      if ((i & (i - 1)) !== 0) {
        // Добавляем бит данных к результату
        decoded += bits[i - 1];
        dataIndex++;
      }
    }
  
    // dозвращаем объект с результатами
    return {
      corrected: bits.join(''), // исправленное кодовое слово
      decoded: decoded,         // Декодированные данные
      errorPosition: errorPos <= n ? errorPos : null // Позиция ошибки
    };
  }
  
  let args = process.argv.slice(2);
  let mode = args[0]; 
  let input = args[1];
  
  if (mode === '-e' || mode === '--encode') {
    // Кодируем введенные данные, ура
    try {
      let encoded = encodeHamming(input);
      console.log(`Закодированное слово: ${encoded}`);
      console.log(`Параметры кода: (${encoded.length}, ${input.length})`);
    }
    catch (e) {
      // Обрабатываем ошибки
      console.error(e.message);
    }
  }
  else if (mode === '-d' || mode === '--decode') {
    try {
      // Декодируем введенные данные, урааа
      let result = decodeHamming(input);
      console.log(`Исправленное слово: ${result.corrected}`);
      console.log(`Декодированное слово: ${result.decoded}`);
    }
    catch (e) {
      console.error(e.message);
    }
  } 
  else {
    // Если аргументы не распознаны, выводим справку
    console.log('Использование:');
    console.log('  Для кодирования: node hamming.js -e (expr)');
    console.log('  Для декодирования: node hamming.js -d (expr)');
  }
