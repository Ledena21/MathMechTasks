#!/bin/bash

fibonacci() {
    local n=$1
    if [ $n -eq 0 ]; then
        echo 0
    elif [ $n -eq 1 ]; then
        echo 1
    else
        local a=0
        local b=1
        local fib=0
        for (( i=2; i<=n; i++ ))
        do
            fib=$((a + b))
            a=$b
            b=$fib
        done
        echo $fib
    fi
}

read -p "Введите число n: " n

if [[ ! $n =~ ^[0-9]+$ ]]; then
    echo "Ошибка: введите неотрицательное целое число!" >&2
    exit 1
fi

result=$(fibonacci $n)
echo "Число Фибоначчи под номером $n: $result"
