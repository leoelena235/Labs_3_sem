#include <iostream>
#include <string>
#include <stdexcept>
#include <bitset>
#include <climits>

class logical_values_array final
{
private:
    unsigned int _value; // 32 бита

public:
    logical_values_array(unsigned int num = 0) : _value(num) {}

    unsigned int get_value() const
    {
        return _value;
    }

    // инверсия
    logical_values_array invert() const
    {
        return logical_values_array(~_value);
    }
    // конъюнкция A ∧ B = ¬(¬A ∨ ¬B)
    logical_values_array conjunction(const logical_values_array &other) const
    {

        return this->invert().disjunction(other.invert()).invert();
    }

    // дизъюнкция
    logical_values_array disjunction(const logical_values_array &other) const
    {
        return logical_values_array(_value | other._value);
    }
    // импликация - ¬A∨B
    logical_values_array implication(const logical_values_array &other) const
    {
        return this->invert().disjunction(other);
    }
    // коимпликация - двойная импликация
    logical_values_array coimplication(const logical_values_array &other) const
    {
        return implication(other).conjunction(other.implication(*this));
    }
    // сложение по модулю2 A⊕B=(A∨B)∧¬(A∧B)
    logical_values_array xor_op(const logical_values_array &other) const
    {
        return this->disjunction(other).conjunction(this->conjunction(other).invert());
    }

    // эквив  - когда биты совпад
    logical_values_array equivalence(const logical_values_array &other) const
    {
        return xor_op(other).invert();
    }
    // стрелка пирса NOR
    logical_values_array pierce_arrow(const logical_values_array &other) const
    {
        return this->disjunction(other).invert();
    }
    // штрих шеффера NAND
    logical_values_array sheffer_stroke(const logical_values_array &other) const
    {
        return this->conjunction(other).invert();
    }

    static bool equals(const logical_values_array &a, const logical_values_array &b)
    {
        return a._value == b._value;
    }
    bool get_bit(size_t pos) const
    {
        if (pos >= sizeof(unsigned int) * 8)
        {
            throw std::out_of_range("Bit position out of range");
        }
        return (_value >> pos) & 1;
    }

    void to_binary_string(char *string) const
    {
        if (!string)
        {
            throw std::invalid_argument("String pointer is null");
        }

        // constexpr
        const size_t bit_count = sizeof(unsigned int) * 8;

        for (int i = 0; i < bit_count; ++i)
        {
            unsigned int bit = (1 << i) & _value;

            if (bit)
            {
                string[bit_count - 1 - i] = '1';
            }
            else
            {
                string[bit_count - 1 - i] = '0';
            }
        }

        string[bit_count] = '\0';
    }
};
void print_operation(const std::string &op_name, const logical_values_array &result)
{
    char binary[33]; // std::unique_ptr<T>
    result.to_binary_string(binary);
    std::cout << op_name << ": " << result.get_value() << " (Binary: " << binary << ")\n";
}

int main()
{
    logical_values_array val1(5); // 0101
    logical_values_array val2(3); // 0011

    std::cout << "Initial Values:\n";
    print_operation("Value 1", val1);
    print_operation("Value 2", val2);

    // AND
    print_operation("AND", val1.conjunction(val2));

    // OR
    print_operation("OR", val1.disjunction(val2));

    // XOR
    print_operation("XOR", val1.xor_op(val2));

    print_operation("Equivalence", val1.equivalence(val2));

    // NOT for val1
    print_operation("NOT Value 1", val1.invert());

    print_operation("Implication (Value 1 ⇒ Value 2)", val1.implication(val2));

    print_operation("Coimplication", val1.coimplication(val2));

    // Pierce Arrow (NOR)
    print_operation("Pierce Arrow (NOR)", val1.pierce_arrow(val2));

    print_operation("Sheffer Stroke (NAND)", val1.sheffer_stroke(val2));

    std::cout << "Bit 2 of Value 1: " << val1.get_bit(2) << "\n";

    std::cout << "Values equal: " << std::boolalpha << logical_values_array::equals(val1, val2) << "\n";

    return 0;
}