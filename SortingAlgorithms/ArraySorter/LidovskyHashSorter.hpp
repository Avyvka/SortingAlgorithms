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
            // то смысла записывать 0 в промежуточный массив нет
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

            std::cout << array[index] << " = " << hashIndex << std::endl;

            // Если образовалась коллизия, то сдвинуть элементы массива
            if (aux[hashIndex] != NULL)
            {
                // Смещение сдвига: влево(-) / вправо(+)
                long long offset = 0;

                // Высчитывание смещения влево
                while (hashIndex + offset > 0 && aux[hashIndex + offset] > array[index])
                {
                    offset--;
                }

                // Ecли сдвинуть элементы влево не получится
                if (offset == 0 || hashIndex + offset == 0)
                {
                    // Высчитать смещение вправо
                    while (hashIndex + offset < aux.size() && aux[hashIndex + offset] != NULL)
                    {
                        offset++;
                    }

                    // Сдвиг элементов массива вправо на 1
                    aux.shift(hashIndex, hashIndex + offset - 1, 1);
                }
                else
                {   
                    // Сдвиг элементов массива влево на 1
                    aux.shift(hashIndex + offset + 1, hashIndex, -1);
                }
            }

            aux[hashIndex] = array[index];
        }

        std::size_t index = 0;
        for (std::size_t auxIndex = 0; auxIndex < aux.size(); auxIndex++)
        {
            while (index > negativeCount && zeroCounter > 0)
            {
                array[index++] = 0;
                zeroCounter--;
            }

            if (aux[auxIndex] != NULL)
            {
                array[index++] = aux[auxIndex];
            }
        }

        aux.print();
	}
};

