#include <iostream>
#include <bitset>

class binary_int final
{
private:
    int value;
    static void sum(int &a, int &b)
    {
        int carry;
        while (b != 0)
        {
            carry = (a & b) << 1;
            a ^= b;
            b = carry;
        }
    }

    static void multiplication(int &a, int &b)
    {
        int res = 0;
        int addend;
        int temp = a;

        while (b != 0)
        {
            if (b & 1)
            {
                addend = temp;
                sum(res, addend);
            }
            temp <<= 1;
            b >>= 1;
        }
        a = res;
    }

public:
    explicit binary_int(int num = 0) : value(num) {}
    // геттер
    int get_value() const
    {
        return value;
    }

    // Унарный минус-преобр в доп код(~n+1)
    binary_int &operator-()
    {
        int one = 1;
        int inverted = value;
        inverted = ~inverted;
        sum(inverted, one);
        value = inverted;
        return *this;
    }

    // Префиксный ++
    binary_int &operator++()
    {
        int one = 1;
        sum(value, one);
        return *this;
    }

    // Постфиксный ++
    binary_int operator++(int)
    {
        binary_int temp = *this;
        int one = 1;
        sum(value, one);
        return temp;
    }

    //  преф декр
    binary_int &operator--()
    {
        int one = 1;
        int neg_one = ~one + 1;
        sum(value, neg_one);
        return *this;
    }

    // пост декр
    binary_int operator--(int)
    {
        binary_int temp = *this;
        int one = 1;
        int neg_one = ~one + 1;
        sum(value, neg_one);
        return temp;
    }

    // Оператор +=
    binary_int &operator+=(int num)
    {
        sum(value, num);
        return *this;
    }

    // Оператор +
    binary_int operator+(int num) const
    {
        return binary_int(*this) += num;

        // binary_int result = *this;
        // sum(result.value, num);
        // return result;
    }

    // Оператор -=
    binary_int &operator-=(int num)
    {
        int one = 1;
        num = ~num;
        sum(num, one);
        sum(value, num);
        return *this;
    }

    // Оператор -
    binary_int operator-(int num) const
    {
        binary_int result = *this;
        int one = 1;
        num = ~num;
        sum(num, one);
        sum(result.value, num);
        return result;
    }

    // Оператор *=
    binary_int &operator*=(int num)
    {
        multiplication(value, num);
        return *this;
    }

    //  Оператор *
    binary_int operator*(int num) const
    {
        binary_int result = *this;
        multiplication(result.value, num);
        return result;
    }

    // Оператор <<
    binary_int operator<<(int keep) const
    {
        return binary_int(value << keep);
    }

    // Оператор >>
    binary_int operator>>(int keep) const
    {
        return binary_int(value >> keep);
    }

    // Оператор <<=  Изм тек об
    binary_int &operator<<=(int keep)
    {
        value <<= keep;
        return *this;
    }

    binary_int &operator>>=(int keep)
    {
        value >>= keep;
        return *this;
    }

    // friend-доступ к приватным членам класса
    friend std::ostream &operator<<(std::ostream &os, const binary_int &bin)
    {
        os << std::bitset<sizeof(int) * 8>(bin.value);
        return os;
    }

    // Получение старших и младших битов
    static std::pair<binary_int, binary_int> get_bites(const binary_int &bin)
    {
        int num = bin.value;

        size_t total_bits = sizeof(int) * 8;
        size_t half_bits = total_bits / 2;

        int high_bits = num >> half_bits;
        int low_bits = num & ((1 << half_bits) - 1);

        return std::make_pair(binary_int(high_bits), binary_int(low_bits));
    }
};

int main()
{
    binary_int a(3), b(7), c;

    // Исходные значения
    std::cout << "Initial values:\n";
    std::cout << "a: " << a << " (" << a.get_value() << ")\n";
    std::cout << "b: " << b << " (" << b.get_value() << ")\n";

    // Унарный минус
    c = a;
    -c;
    std::cout << "\nUnary minus:\n";
    std::cout << "c: " << c << " (" << c.get_value() << ")\n";

    // Префиксный и постфиксный инкремент
    c = a;
    std::cout << "\nPrefix increment:\n";
    std::cout << "++c: " << ++c << " (" << c.get_value() << ")\n";

    c = a;
    binary_int temp = c++;
    std::cout << "\nPostfix increment:\n";
    std::cout << "c++: " << temp << " (" << temp.get_value() << ")\n";
    std::cout << "After c++: " << c << " (" << c.get_value() << ")\n";
    // Префиксный и постфиксный декремент
    c = a;
    std::cout << "\nPrefix decrement:\n";
    std::cout << "--c: " << --c << " (" << c.get_value() << ")\n";

    c = a;
    binary_int tmp = c--;
    std::cout << "\nPostfix decrement:\n";
    std::cout << "c--: " << tmp << " (" << tmp.get_value() << ")\n";
    std::cout << "After c--: " << c << " (" << c.get_value() << ")\n";

    // Сложение и вычитание
    c = a + b.get_value();
    std::cout << "\nAddition:\n";
    std::cout << "a + b: " << c << " (" << c.get_value() << ")\n";

    c = a - b.get_value();
    std::cout << "\nSubtraction:\n";
    std::cout << "a - b: " << c << " (" << c.get_value() << ")\n";

    // Умножение
    c = a * b.get_value();
    std::cout << "\nMultiplication:\n";
    std::cout << "a * b: " << c << " (" << c.get_value() << ")\n";

    // Побитовые сдвиги
    c = a << 2;
    std::cout << "\nLeft shift:\n";
    std::cout << "a << 2: " << c << " (" << c.get_value() << ")\n";

    c = a >> 2;
    std::cout << "\nRight shift:\n";
    std::cout << "a >> 2: " << c << " (" << c.get_value() << ")\n";

    // Старшие и младшие биты
    auto bits = binary_int::get_bites(a);
    std::cout << "\nHigh and low bits:\n";
    std::cout << "High bits: " << bits.first << " (" << bits.first.get_value() << ")\n";
    std::cout << "Low bits: " << bits.second << " (" << bits.second.get_value() << ")\n";

    // Операторы с присваиванием
    c = a;
    c += b.get_value();
    std::cout << "\nOperator +=:\n";
    std::cout << "c += b: " << c << " (" << c.get_value() << ")\n";

    c = a;
    c -= b.get_value();
    std::cout << "\nOperator -=:\n";
    std::cout << "c -= b: " << c << " (" << c.get_value() << ")\n";

    c = a;
    c *= b.get_value();
    std::cout << "\nOperator *=:\n";
    std::cout << "c *= b: " << c << " (" << c.get_value() << ")\n";

    c = a;
    c <<= 2;
    std::cout << "\nOperator <<=:\n";
    std::cout << "c <<= 2: " << c << " (" << c.get_value() << ")\n";

    c = a;
    c >>= 2;
    std::cout << "\nOperator >>=:\n";
    std::cout << "c >>= 2: " << c << " (" << c.get_value() << ")\n";

    return 0;
}