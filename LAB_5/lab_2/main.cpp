#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>

std::ostream &operator<<(std::ostream &os, std::byte b)
{
    return os << char(std::to_integer<int>(b));
}

class Encoder final
{
private:
    std::vector<std::byte> S, key;
    int x, y;

    int to_int(std::byte b) const // преобр объект в целое число
    {
        return std::to_integer<int>(b);
    }

    void initialize_state() // S
    {
        S.resize(256);                // созд вектор с 256 эл-ми
        for (int i = 0; i < 256; ++i) // заполняем знач-и->каждый эл-т имеет свой инд
        {
            S[i] = std::byte(i);
        }
        // перемешиваем s с помощью ключа шифр-ия
        int j = 0;
        for (int i = 0; i < 256; ++i)
        {
            j = (j + to_int(S[i]) + to_int(key[i % key.size()])) % 256;
            std::swap(S[i], S[j]);
        }
        x = 0;
        y = 0;
    }

    std::byte get_next_byte() // след байт потока
    {
        x = (x + 1) % 256;
        // увел индекс x, чтобы перейти к следующему элементу массива S.
        y = (y + to_int(S[x])) % 256; // обновляем индекс y на основе текущего значения в массиве
        std::swap(S[x], S[y]);
        return S[(to_int(S[x]) + to_int(S[y])) % 256]; // генерируем псевдосл байт потока
    }

    void validate_files(const std::string &input_name, const std::string &output_name) const
    {
        if (input_name.empty() || output_name.empty())
        {
            throw std::invalid_argument("File paths cannot be empty.");
        }
        if (std::filesystem::equivalent(input_name, output_name))
        {
            throw std::runtime_error("Input and output files cannot be the same.");
        }
    }

public:
    explicit Encoder(const std::vector<std::byte> &encryption_key)
        : key(encryption_key), x(0), y(0)
    {
        if (encryption_key.empty())
        {
            throw std::invalid_argument("Key cannot be empty.");
        }
    }
    // принимает новый ключ в виде байтов
    void set_key(const std::vector<std::byte> &new_key)
    {
        if (new_key.empty())
        {
            throw std::invalid_argument("Key cannot be empty.");
        }
        key = new_key;
    }
    void encode(const std::string &input_name, const std::string &output_name, bool encrypt = true)
    {
        validate_files(input_name, output_name);

        std::ifstream input_file(input_name, std::ios::binary);
        if (!input_file.is_open())
        {
            throw std::runtime_error("Failed to open input file: " + input_name);
        }
        std::ofstream output_file(output_name, std::ios::binary);
        if (!output_file.is_open())
        {
            input_file.close();
            throw std::runtime_error("Failed to open output file: " + output_name);
        }

        initialize_state();

        char ch;
        while (input_file.get(ch))
        { // симв преобр в целое, затем в байт
            std::byte input_byte = std::byte(static_cast<unsigned char>(ch));
            std::byte cipher_byte = input_byte ^ get_next_byte();
            output_file.put(static_cast<char>(to_int(cipher_byte)));
        }

        input_file.close();
        output_file.close();
    }
    static std::vector<std::byte> generate_key(size_t size)
    {
        if (size == 0)
        {
            throw std::invalid_argument("Size key's can not be 0.");
        }

        std::vector<std::byte> generated_key(size);
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        for (size_t i = 0; i < size; ++i) // заполняем вектор случ байтами
        {
            generated_key[i] = std::byte(std::rand() % 256);
        }
        return generated_key; // каждый эл-т вектора=случ байт
    }
};

void demo()
{
    try
    {                                                            // вектор байтов
        std::vector<std::byte> key = Encoder::generate_key(100); // длина ключа 100

        Encoder encoder(key); // созд об класса и передаем ключ
        std::string input_file = "input.txt";
        std::string encrypted_file = "encrypted.txt";
        std::string decrypted_file = "decrypted.txt";

        encoder.encode(input_file, encrypted_file, true);
        encoder.encode(encrypted_file, decrypted_file, false);
    }
    catch (const std::exception &err)
    {
        std::cout << "Error: " << err.what() << std::endl;
    }
}

int main()
{
    demo();
    return 0;
}
