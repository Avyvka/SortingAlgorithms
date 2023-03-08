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

        // ������ ��� ������������
        if (min == max)
        {
            return;
        }

        // ������������� ������
        Array<T> aux = Array<T>(std::round(array.size() * FACTOR));
        aux.fill(NULL);

        // ������� ��� ����������� ���������� �������� ��������� �����
        // ������� ���������� ����� � �������� ������� �
        // ���������� �� ����� � ������ ����� � ����� ����������
        std::size_t zeroCounter = 0;
        std::size_t negativeCount = 0;

        for (std::size_t index = 0; index < array.size(); index++)
        {
            // ��� ��� �� ��������� NULL = 0 = "������ �����" � �������,
            // �� ��� ������ ���������� 0 � ������������� ������
            if (array[index] == 0)
            {
                zeroCounter++;
                continue;
            }

            // ������� ���������� ������������� �����,
            // ��� ���������� ������� ���������� �����
            if (array[index] < 0)
            {
                negativeCount++;
            }

            // ������������ hash-index'� 
            std::size_t hashIndex = (array[index] - min) * (aux.size() - 1) / (max - min);

            // ���� ������������ ��������
            if (aux[hashIndex] != NULL)
            {
                int step = 0;
                int sign = 0;

                if (aux[hashIndex] > array[index])
                {
                    while (hashIndex > 0 && aux[hashIndex - 1] > array[index])
                    {
                        hashIndex--;
                    }
                    sign = -1;
                }
                else
                {
                    while (hashIndex < aux.size() - 1 && aux[hashIndex + 1] < array[index] && aux[hashIndex + 1] != NULL)
                    {
                        hashIndex++;
                    }
                    sign = 1;
                }

                while (step + hashIndex < 0 || step + hashIndex >= aux.size() || aux[step + hashIndex] != NULL)
                {
                    step = (step > 0) ? -step : 1 - step;
                }

                std::size_t resultIndex = hashIndex + step;

                step = (step > 0) ? 1 : -1;

                hashIndex += (std::size_t)div((sign + step), 2).quot;

                while (resultIndex != hashIndex)
                {
                    aux[resultIndex] = aux[resultIndex - step];
                    resultIndex = resultIndex - step;
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

