#pragma once
#include "AbstractArraySorter.h"
#include <utility>
#include <math.h>

template <class T>
class LidovskyHashSorter : public AbstractArraySorter<T>
{
private:
    const double FACTOR = 1.4;

    std::pair<T, T> minmax(Array<T>& array)
    {
        T min = array.first();
        T max = array.first();

        for (std::size_t index = 0; index < array.size(); index++)
        {
            if (array[index] < min) {
                min = array[index];
            }

            if (array[index] > max) {
                max = array[index];
            }
        }

        return { min, max };
    }

public:
    std::string name()
    {
        return "LidovskyHash";
    }

    void sort(Array<T>& array) override
    {
        const std::pair<T, T> pair = minmax(array);
        const T min = pair.first;
        const T max = pair.second;

        // Массив уже отсортирован
        if (min == max)
        {
            return;
        }

        // Промежуточный массив
        Array<T> aux = Array<T>(std::round(array.size() * FACTOR));
        aux.fill(NULL);

        // Костыль для возможности сортировки большего диапазона чисел
        // Считаем количество нулей в исходном массиве и
        // возвращаем их назад в нужное место в конце сортировки
        std::size_t zeroCounter = 0;
        std::size_t negativeCount = 0;

        for (std::size_t index = 0; index < array.size(); index++)
        {
            // Так как по умолчанию NULL = 0 = "пустое место" в массиве,
            // то нет смысла записывать 0 в промежуточный массив
            if (array[index] == 0)
            {
                zeroCounter++;
                continue;
            }

            // Считаем количество отрицательных чисел,
            // для определния позиции добавления нулей
            if (array[index] < 0)
            {
                negativeCount++;
            }

            // Высчитывание hash-index'а 
            std::size_t hashIndex = (array[index] - min) * (aux.size() - 1) / (max - min);

            // Если образовалась коллизия
            if (aux[hashIndex] != NULL)
            {
                int direction = (aux[hashIndex] > array[index]) ? -1 : 1;

                // Поиск "окна"
                if (aux[hashIndex] > array[index])
                {
                    //                 <- hashIndex
                    //                        v
                    // [ .., 2, x, x, 5, {collision}, .. ]
                    //             ^
                    while (hashIndex > 0 && aux[hashIndex - 1] > array[index])
                    {
                        hashIndex--;
                    }
                }
                else
                {   
                    //        hashIndex ->
                    //            v
                    // [ .., {collision}, 7, x, x, 12, .. ]
                    //                       ^
                    while (hashIndex < aux.size() - 1 && aux[hashIndex + 1] < array[index] && aux[hashIndex + 1] != NULL)
                    {
                        hashIndex++;
                    }
                }

                int numberSteps = 0;

                // Если "окно" найти не удалось, то начинается поиск ближайшего
                // свободного места относительно неудачно найденного элемента
                while (numberSteps + hashIndex < 0 || numberSteps + hashIndex >= aux.size() || aux[numberSteps + hashIndex] != NULL)
                {
                    numberSteps = (numberSteps > 0) ? -numberSteps : 1 - numberSteps;
                }

                std::size_t resultIndex = hashIndex + numberSteps;

                numberSteps = (numberSteps > 0) ? 1 : -1;

                // Сдвиг влево/вправо, если не удалось найти "окно" и
                // направление не совпало с изначальным
                hashIndex += (std::size_t)div((direction + numberSteps), 2).quot;

                // Сдвиг элементов массива - создание "окна"
                while (resultIndex != hashIndex)
                {
                    aux[resultIndex] = aux[resultIndex - numberSteps];
                    resultIndex = resultIndex - numberSteps;
                }
            }

            aux[hashIndex] = array[index];
        }

        std::size_t index = 0;
        for (std::size_t auxIndex = 0; auxIndex < aux.size(); auxIndex++)
        {
            while (index >= negativeCount && zeroCounter > 0)
            {
                array[index++] = 0;
                zeroCounter--;
            }

            if (aux[auxIndex] != NULL)
            {
                array[index++] = aux[auxIndex];
            }
        }
	}
};

