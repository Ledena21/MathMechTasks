<!DOCTYPE html>
<html lang="ru">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Игра "Жизнь"</title>
    <style>
        /* Основные стили страницы */
        body {
            font-family: Arial, sans-serif; /* Шрифт для всей страницы */
            display: flex; /* позволяет использовать флекс элеиента внутри флекс контейнера по основной оси */
            flex-direction: column; /* горизонтальные столбики */
            align-items: center; /* Выравнивание по центру горизонтально */
            background-color: #808080; /* Серый фон */
            margin: 0; /* Убираем внешние отступы */
            padding: 20px; /* Внутренний отступ(между содержимым элемента и его границей) */
        }
        
        /* Стили панели управления */
        .controls {
            margin-bottom: 20px; /* Отступ снизу */
            display: flex; /* Flex-разметка для кнопок */
            gap: 10px; /* Расстояние между элементами */
            flex-wrap: wrap; /* Разрешаем перенос на новую строку */
            justify-content: center; /* Выравнивание по центру */
        }
        
        /* Стили кнопок */
        button {
            padding: 8px 16px; /* Внутренние отступы */
            font-size: 16px; /* Размер шрифта */
            cursor: pointer; /* Курсор в виде указателя */
            background-color: #9c27b0; /* Фиолетовый фон */
            color: white; /* Белый текст */
            border: none; /* Без рамки */
            border-radius: 4px; /* Скругленные углы */
            transition: background-color 0.3s; /* Плавное изменение цвета */
        }
        
        /* Стиль кнопки при наведении */
        button:hover {
            background-color: #7b1fa2; /* Темно-фиолетовый */
        }
        
        /* Блок управления размером поля */
        .size-controls {
            display: flex; /* Flex-разметка */
            gap: 10px; /* Расстояние между элементами */
            align-items: center; /* Выравнивание по центру вертикально */
        }
        
        /* Поля ввода */
        input {
            padding: 8px; /* Внутренние отступы */
            width: 60px; /* Ширина поля */
            text-align: center; /* Текст по центру */
            background-color: #e0e0e0; /* Светло-серый фон */
            border: 1px solid #9c27b0; /* Фиолетовая рамка */
            border-radius: 4px; /* Скругленные углы */
        }
        
        /* Контейнер игрового поля */
        .game-container {
            display: flex; /* Flex-разметка */
            justify-content: center; /* Выравнивание по центру */
            margin-bottom: 20px; /* Отступ снизу */
        }
        
        /* Игровое поле */
        #game-board {
            display: grid; /* сщздаем грид кнтейнер*/
            grid-template-columns: repeat(25, 20px); /* 25 колонок по 20px */
            grid-template-rows: repeat(25, 20px); /* 25 строк по 20px */
            gap: 1px; /* Расстояние между клетками */
            background-color: #333; /* Темно-серый фон */
            border: 2px solid #9c27b0; /* Фиолетовая рамка */
            box-shadow: 0 0 10px rgba(0, 0, 0, 0.5); /* Тень */
        }
        
        /* Клетка игрового поля */
        .cell {
            width: 20px; /* Ширина */
            height: 20px; /* Высота */
            background-color: #222; /* Темный фон */
            cursor: pointer; /* Курсор-указатель */
            border: 1px solid #444; /* Серая граница */
        }
        
        /* Живая клетка */
        .alive {
            background-color: #9c27b0; /* Фиолетовый цвет */
        }
        
        /* Блок статистики */
        .stats {
            margin-top: 10px; /* Отступ сверху */
            font-size: 18px; /* Размер шрифта */
            color: #fff; /* Белый текст */
        }
        
        /* Метки */
        label {
            color: #fff; /* Белый текст */
        }
    </style>
</head>
<body>
    <!-- Заголовок игры -->
    <h1 style="color: #fff;">Игра "Жизнь"</h1>
    
    <!-- Панель управления -->
    <div class="controls">
        <button id="start-stop">Старт</button> <!-- <button> создаёт кликабельную кнопку -->
        <button id="step">Один шаг</button>
        <button id="random">Случайное поле</button>
        <button id="clear">Очистить</button>
        
        <!-- Управление размером поля -->
        <div class="size-controls">
            <label for="rows">Строки:</label>
            <input type="number" id="rows" min="5" max="100" value="25">
            
            <label for="cols">Колонки:</label>
            <input type="number" id="cols" min="5" max="100" value="25">
            
            <button id="resize">Изменить размер</button>
        </div>
    </div>
    
    <!-- Игровое поле -->
    <div class="game-container">
        <div id="game-board"></div>
    </div>
    
    <!-- Статистика -->
    <div class="stats">
        Поколение: <span id="generation">0</span> | <!-- <span> является основным строковым контейнером для фразового контента -->
        Живых клеток: <span id="alive-count">0</span>
    </div>
    
    <script>
        // Ждем загрузки DOM перед выполнением скрипта Код выполнится только после полной загрузки HTML-структуры
        document.addEventListener('DOMContentLoaded', () => {
            // Получаем элементы DOM (- это: Представление веб-страницы в памяти браузера в виде древовидной структуры Программируемый интерфейс, позволяющий JavaScript: Читать содержимое страницы Изменять элементы Управлять стилями Реагировать на события
            let gameBoard = document.getElementById('game-board'); //getElementById - это метод объекта document, который:Ищет элемент на странице по его id Возвращает ссылку на этот элемент (или null, если не найден)
            let startStopBtn = document.getElementById('start-stop');
            let stepBtn = document.getElementById('step');
            let randomBtn = document.getElementById('random');
            let clearBtn = document.getElementById('clear');
            let resizeBtn = document.getElementById('resize');
            let rowsInput = document.getElementById('rows');
            let colsInput = document.getElementById('cols');
            let generationDisplay = document.getElementById('generation');
            let aliveCountDisplay = document.getElementById('alive-count');
            
            // Инициализация переменных игры
            let rows = 25; // Количество строк по умолчанию
            let cols = 25; // Количество колонок по умолчанию
            let grid = createEmptyGrid(rows, cols); // Текущее состояние поля (0 - мертвая, 1 - живая) функция,создаёт и возвращает двумерный массив (матрицу), представляющий пустое игровое поле. 
            let nextGrid = createEmptyGrid(rows, cols); // Буфер для следующего состояния
            let isRunning = false; // Флаг, указывающий работает ли игра
            let generation = 0; // Номер текущего поколения
            let animationId = null; // ID анимационного цикла
            let previousGrid = null; // Предыдущее состояние поля (для проверки стабильности)
            
            /**
             * Инициализирует игровое поле, создавая DOM-элементы для каждой клетки
             */
            function initializeBoard() {
                gameBoard.innerHTML = ''; // Очищаем поле
                
                // Устанавливаем размеры колонок и строк через CSS
                gameBoard.style.gridTemplateColumns = `repeat(${cols}, 20px)`;
                gameBoard.style.gridTemplateRows = `repeat(${rows}, 20px)`;
                
                // Создаем клетки
                for (let i = 0; i < rows; i++) {
                    for (let j = 0; j < cols; j++) {
                        let cell = document.createElement('div'); //createElement('div') создаёт новый HTML-элемент div
                        cell.className = 'cell'; //className = 'cell' присваивает класс для стилизации (из CSS)
                        // Сохраняем координаты в data-атрибутах
                        cell.dataset.row = i;
                        cell.dataset.col = j;
                        
                        // Обработчик клика по клетке
                        cell.addEventListener('click', () => {//addEventListener — метод для подписки на события (клик, наведение и т.д.).
                            if (!isRunning) { // Изменять можно только когда игра остановлена
                                //если 1 (клетка живая) → возвращает 0 (убивает клетку). Если 0 (клетка мёртвая) → возвращает 1 (оживляет клетку)
                                grid[i][j] = grid[i][j] ? 0 : 1;
                                //если класс alive есть удалаяем, если нет добавляем(красим в фиолетовый клктку и наоборот)
                                cell.classList.toggle('alive');
                                updateStats(); // Обновляем счетчик живых клеток
                            }
                        });
                        
                        gameBoard.appendChild(cell); // Добавляем клетку на поле
                    }
                }
                
                updateStats(); // обновление статистики
            }
            
            /**
             * Создает пустую сетку заданного размера
             * @param {number} rows - количество строк
             * @param {number} cols - количество колонок
             * @returns {Array} - двумерный массив, заполненный нулями
             */
            function createEmptyGrid(rows, cols) {
                return Array(rows).fill().map(() => Array(cols).fill(0));//Array(rows) - создаёт массив заданной длины 
                // fill() - заполняет его undefined (чтобы работал map) map(() => Array(cols).fill(0)) - для каждой строки создаёт массив из cols нулей
            }
            
            /**
             * Обновляет статистику (количество поколений и живых клеток)
             */
            function updateStats() {
                // Считаем количество живых клеток
                let aliveCount = grid.flat().filter(cell => cell === 1).length;//grid.flat() — преобразует двумерный массив в одномерный (например, [[0,1], [1,0]] → [0,1,1,0]).
                //filter(cell => cell === 1) — оставляет только 1 (живые клетки) length — возвращает количество живых клеток.
                // Обновляем DOM
                aliveCountDisplay.textContent = aliveCount;//выводит число живых клеток
                generationDisplay.textContent = generation;//выводит номер поколения
            }
            
            /**
             * Вычисляет следующее поколение клеток по правилам игры
             * @returns {boolean} - false если игра окончена, true если продолжается
             */
            function computeNextGeneration() {
                // Сохраняем текущее состояние игры (чтобы потом проверить, изменилось ли что-то).
                previousGrid = JSON.parse(JSON.stringify(grid));//JSON.stringify(grid) → превращает массив в строку
                //JSON.parse(...) → превращает строку обратно в новый массив (чтобы избежать ссылки на исходный grid).
                // Проходим по всем клеткам
                for (let i = 0; i < rows; i++) {
                    for (let j = 0; j < cols; j++) {
                        // Считаем количество живых соседей
                        let neighbors = countLiveNeighbors(i, j);
                        
                        // Применяем правила игры
                        if (grid[i][j] === 1) {
                            // Для живых клеток:
                            // - выживает если 2 или 3 соседа
                            // - умирает в остальных случаях
                            nextGrid[i][j] = (neighbors === 2 || neighbors === 3) ? 1 : 0;
                        } else {
                            // Для мертвых клеток:
                            // - оживает если ровно 3 соседа
                            nextGrid[i][j] = (neighbors === 3) ? 1 : 0;
                        }
                    }
                }
                
                // Проверяем условия окончания игры
                let aliveCount = nextGrid.flat().filter(cell => cell === 1).length;//Эта строка подсчитывает количество живых клеток (1) в следующем поколении (nextGrid)
                let isSameAsPrevious = JSON.stringify(grid) === JSON.stringify(nextGrid);//фигуры которые повторятся подряд
                
                if (aliveCount === 0) {
                    // Все клетки мертвы - игра окончена
                    alert(`Игра окончена! Все клетки мертвы. Поколений: ${generation + 1}`);
                    stopGame();
                    return false;
                } else if (isSameAsPrevious ){
                    // Два поколения одинаковы - игра окончена
                    alert(`Игра окончена! Два соседних поколения одинаковы. Поколений: ${generation + 1}`);
                    stopGame();
                    return false;
                }
                
                return true; // Игра продолжается
            }
            
            /**
             * Считает количество живых соседей для клетки с учетом цилиндрической замкнутости поля
             * @param {number} row - строка клетки
             * @param {number} col - колонка клетки
             * @returns {number} - количество живых соседей (0-8)
             */
            function countLiveNeighbors(row, col) {
                let count = 0;
                
                // Проверяем все 8 соседних клеток
                for (let i = -1; i <= 1; i++) {
                    for (let j = -1; j <= 1; j++) {
                        if (i === 0 && j === 0) continue; // Пропускаем саму клетку
                        
                        // Вычисляем координаты соседа
                        let newRow = row + i;
                        let newCol = col + j;
                        
                        // Обрабатываем цилиндрическую замкнутость по вертикали:
                        if (newRow < 0) newRow = rows - 1; // Выход за верхнюю границу
                        else if (newRow >= rows) newRow = 0; // Выход за нижнюю границу
                        
                        // Обрабатываем цилиндрическую замкнутость по горизонтали:
                        if (newCol < 0) newCol = cols - 1; // Выход за левую границу
                        else if (newCol >= cols) newCol = 0; // Выход за правую границу
                        
                        // Учитываем состояние соседа
                        count += grid[newRow][newCol]; // 1 если живая, 0 если мертвая
                    }
                }
                
                return count;//Функция возвращает количество живых соседей (число от 0 до 8).
            }
            
            /**
             * Обновляет отображение игрового поля на основе nextGrid
             */
            function updateDisplay() {
                let cells = document.querySelectorAll('.cell');//находим все клетоки
                
                // Обновляем все клетки
                for (let i = 0; i < rows; i++) {
                    for (let j = 0; j < cols; j++) {
                        let index = i * cols + j;//Нужно преобразовать двумерные координаты (i, j) в одномерный индекс для доступа к элементу в NodeList
                        let cell = cells[index];//получаем конкретную клетку
                        
                        // Добавляем/удаляем класс 'alive' в зависимости от состояния и они меняют цвет
                        if (nextGrid[i][j] === 1) {
                            cell.classList.add('alive');
                        } else {
                            cell.classList.remove('alive');
                        }
                    }
                }
                
                // Обновляем текущее состояние
                grid = JSON.parse(JSON.stringify(nextGrid));//Копирует nextGrid в grid теперь грид отображает текущее состояние
                generation++; // Увеличиваем счетчик поколений
                updateStats(); // Обновляем статистику
            }
            
            /**
             * Выполняет один шаг игры (одно поколение)
             */
            function makeStep() {
                if (!isRunning) { // Шаг можно сделать только когда игра остановлена
                    if (computeNextGeneration()) { // Если игра не закончилась
                        updateDisplay(); // Обновляем отображение
                    }
                }
            }
            
            /**
             * Главный игровой цикл
             */
            function gameLoop() {
                if (!computeNextGeneration()) return; // вычисляет след поколение клеток и Если игра окончена - выходим
                
                updateDisplay(); // Обновляем отображение
                
                // Если игра еще идет - запрашиваем следующий кадр анимации
                if (isRunning) {
                    animationId = requestAnimationFrame(gameLoop); //requestAnimationFrame(gameLoop):
                    // Рекурсивно запрашивает следующий кадр анимации (создает плавный цикл).
                }
            }
            
            /**
             * Запускает игру (автоматическое обновление поколений)
             */
            function startGame() {
                if (!isRunning) {
                    isRunning = true;
                    startStopBtn.textContent = 'Стоп'; // Меняем текст кнопки
                    gameLoop(); // Запускаем игровой цикл
                }
            }
            
            /**
             * Останавливает игру
             */
            function stopGame() {
                if (isRunning) {
                    isRunning = false;
                    startStopBtn.textContent = 'Старт'; // Меняем текст кнопки
                    if (animationId) {
                        cancelAnimationFrame(animationId); // Останавливаем анимацию
                        animationId = null;
                    }
                }
            }
            
            /**
             * Очищает игровое поле (все клетки становятся мертвыми)
             */
            function clearBoard() {
                stopGame(); // Останавливаем игру
                // Создаем новые пустые сетки
                grid = createEmptyGrid(rows, cols);
                nextGrid = createEmptyGrid(rows, cols);
                generation = 0; // Сбрасываем счетчик поколений
                
                // Удаляем класс 'alive' у всех клеток
                document.querySelectorAll('.cell').forEach(cell => {
                    cell.classList.remove('alive');
                });
                
                updateStats(); // Обновляем статистику
            }
            
            /**
             * Заполняет поле случайными живыми клетками
             */
            function randomizeBoard() {
                stopGame(); // Останавливаем игру
                grid = createEmptyGrid(rows, cols); // Создаем новую пустую сетку
                
                // Заполняем сетку случайными значениями (30% вероятность быть живой)
                for (let i = 0; i < rows; i++) {
                    for (let j = 0; j < cols; j++) {
                        grid[i][j] = Math.random() > 0.7 ? 1 : 0;
                    }
                }
                
                // Обновляем отображение
                let cells = document.querySelectorAll('.cell');
                for (let i = 0; i < rows; i++) {
                    for (let j = 0; j < cols; j++) {
                        let index = i * cols + j;
                        let cell = cells[index];
                        
                        // Добавляем/удаляем класс в зависимости от состояния
                        if (grid[i][j] === 1) {
                            cell.classList.add('alive');
                        } else {
                            cell.classList.remove('alive');
                        }
                    }
                }
                
                generation = 0; // Сбрасываем счетчик поколений
                updateStats(); // Обновляем статистику
            }
            
            /**
             * Изменяет размер игрового поля
             */
            function resizeBoard() {
                // Получаем новые размеры из полей ввода
                let newRows = parseInt(rowsInput.value);
                let newCols = parseInt(colsInput.value);
                
                // Проверяем допустимость размеров (от 5x5 до 100x100)
                if (newRows >= 5 && newRows <= 100 && newCols >= 5 && newCols <= 100) {
                    stopGame(); // Останавливаем игру
                    rows = newRows; // Обновляем количество строк
                    cols = newCols; // Обновляем количество колонок
                    // Создаем новые пустые сетки
                    grid = createEmptyGrid(rows, cols);
                    nextGrid = createEmptyGrid(rows, cols);
                    generation = 0; // Сбрасываем счетчик поколений
                    initializeBoard(); // Пересоздаем поле
                } else {
                    alert('Размеры должны быть от 5 до 100');
                }
            }
            
            // Назначаем обработчики событий на кнопки
            startStopBtn.addEventListener('click', () => {
                if (isRunning) {
                    stopGame();
                } else {
                    startGame();
                }
            });
            
            stepBtn.addEventListener('click', makeStep); // Один шаг
            randomBtn.addEventListener('click', randomizeBoard); // Случайное поле
            clearBtn.addEventListener('click', clearBoard); // Очистка поля
            resizeBtn.addEventListener('click', resizeBoard); // Изменение размера
            
            // при загрузке страницы создается поле
            initializeBoard();
        });
    </script>
</body>
</html>
