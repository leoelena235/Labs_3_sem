Реализуйте класс binary_int, который позволяет выполнять операции с целыми числами, используя только
побитовые операции и логические операции для выполнения арифметических задач. Класс должен
работать с числами в диапазоне значений типа int и представлять их только в виде двоичных значений.
Требования к реализации:
● Запрещено использовать стандартные арифметические операторы +, -, *, /, % для выполнения
сложения и вычитания. Все операции реализуются побитовыми манипуляциями с числовыми
значениями;
● Необходимо перегрузить операторы:
○ унарный минус (operator-) для возврата числа с противоположным знаком;
○ префиксного и постфиксного инкремента (operator++) для увеличения значения числа на 1;
○ префиксного и постфиксного декремента (operator--) для уменьшения значения числа на 1;
○ сложения чисел (operator+=) с модификацией вызывающего объекта;
○ сложения чисел (operator+) с возвратом нового объекта;
○ вычитания чисел (operator-=) с модификацией вызывающего объекта;
○ вычитания чисел (operator-) с возвратом нового объекта;
○ умножения чисел (operator*=) с модификацией вызывающего объекта;
○ умножения чисел (operator*) с возвратом нового объекта;
○ побитового сдвига влево (operator<<=) и вправо (operator>>=) с модификацией
вызывающего объекта;
○ побитового сдвига влево (operator<<) и вправо (operator>>) с возвратом нового объекта;
○ вставки в поток (operator<<) для печати в поток вывода битового представления числа;
● Необходимо реализовать метод, возвращающий для объекта пару объектов типа binary_int, где в
первом объекте сохранены только половина старших битов вызывающего объекта, а во втором -
только половина младших битов вызывающего объекта; остальные биты необходимо обнулить.
Продемонстрируйте работу реализованного функционала.