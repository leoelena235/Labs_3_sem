#include <iostream>
#include <cmath>
#include <vector>
#include <initializer_list>
#include <stdexcept>
#include <algorithm>

class vector final
{
private:
    double *arr;
    size_t capacity, size; // вместимость массива, количество элементов

    void _resize(size_t new_capacity) // функция для изменения вместимости массива
    {
        double *resize = new double[new_capacity];
        auto count = std::min(size, new_capacity);
        std::copy(arr, arr + count, resize);
        delete[] arr; // делит старый мас
        arr = resize;
        capacity = new_capacity;
        size = count;
    }

public:
    class iterator final // только с об вект работа
    {
    private:
        double *ptr; // тек эл

    public:
        iterator(double *ptr) : ptr{ptr} {}
        double const &operator*() const // оп разым
        {
            return *ptr;
        }
        double &operator*() // можно менять
        {
            return *ptr;
        }

        iterator &operator++()
        {
            ptr++;
            return *this;
        }

        iterator operator++(int)
        {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        iterator &operator--()
        {
            ptr--;
            return *this;
        }

        iterator operator--(int)
        {
            iterator tmp = *this;
            --(*this);
            return tmp;
        }

        iterator operator+(int shift) const
        {
            return iterator(ptr + shift);
        }
        iterator &operator+=(int shift)
        {
            ptr += shift;
            return *this;
        }

        iterator operator-(int shift) const
        {
            return iterator(ptr - shift);
        }
        iterator &operator-=(int shift)
        {
            ptr -= shift;
            return *this;
        }

        double *operator->()
        {
            return ptr;
        }
        double const *operator->() const
        {
            return ptr;
        }
        double &operator[](int shift) // оп индексирования
        {
            return *(ptr + shift);
        }
        double operator[](int shift) const
        {
            return *(ptr + shift);
        }
        // оп вычит двух итер
        int operator-(const iterator &iter) const
        {
            return ptr - iter.ptr;
        }
        bool operator==(const iterator &iter) const
        {
            return ptr == iter.ptr;
        }
        bool operator!=(const iterator &iter) const
        {
            return ptr != iter.ptr;
        }
        bool operator>(const iterator &iter) const
        {
            return ptr > iter.ptr;
        }
        bool operator>=(const iterator &iter) const
        {
            return ptr >= iter.ptr;
        }
        bool operator<(const iterator &iter) const
        {
            return ptr < iter.ptr;
        }
        bool operator<=(const iterator &iter) const
        {
            return ptr <= iter.ptr;
        }
    };
    // констр с 2-мя парам
    vector(int count_elements, double default_value) : arr{new double[count_elements]},
                                                       size(count_elements),
                                                       capacity(count_elements)
    {
        std::fill_n(arr, count_elements, default_value);
    }
    // констр с 1 парам - вызывает констр с 2 парам
    vector(int count_elements) : vector(count_elements, 0.0) {}
    // констр с итерат
    template <typename Iterator>
    vector(Iterator const begin, Iterator const end)
    {
        auto distance = end - begin;
        arr = new double[distance];
        capacity = size = distance;
        std::copy(begin, end, arr);
    }
    // констр со списк иниц
    vector(std::initializer_list<double> init_list) : capacity{init_list.size()}, size(init_list.size()),
                                                      arr{new double[init_list.size()]}
    {
        std::copy(init_list.begin(), init_list.end(), arr);
    }
    // констр копир
    vector(const vector &v) : vector(v.begin(), v.end()) {}
    // возвращает ссылку на элемент с индексом index
    double &at(int index)
    {
        if (index < 0 || index >= size)
            throw std::range_error("Out of range");

        return arr[index];
    }

    double const &at(int index) const
    {
        if (index < 0 || index >= size)
            throw std::range_error("Out of range");

        return arr[index];
    }
    // возвращает ссылку на первый элемент массива.
    double &front()
    {
        if (size == 0)
            throw std::range_error("Out of range");

        return arr[0];
    }

    double const &front() const
    {
        if (size == 0)
            throw std::range_error("Out of range");

        return arr[0];
    }
    // возвращает ссылку на последний элемент массива.
    double &back()
    {
        if (size == 0)
            throw std::range_error("Out of range");

        return arr[size - 1];
    }

    double const &back() const
    {
        if (size == 0)
            throw std::range_error("Out of range");

        return arr[size - 1];
    }
    // возвращает указатель на внутренний массив данных.
    double *data()
    {
        return arr;
    }
    double const *data() const
    {
        return arr;
    } // возвращает bool, проверяя, пуст ли массив.
    bool empty() const
    {
        return size == 0;
    } // увеличивает вместимость массива до num, если текущая вместимость меньше.
    void reserve(size_t num)
    {
        if (num <= capacity)
            return;
        _resize(num);
    }

    int capacity_find() const
    {
        return capacity;
    }
    int size_find() const
    {
        return size;
    } // уменьшает вместимость массива до текущего размера, если вместимость больше
    void shrink_to_fit()
    {
        if (capacity > size)
            _resize(size);
    }
    // очищает массив, устанавливая его размер в 0.
    void clear() { size = 0; }
    // добавляет элемент elem в конец массива.
    void push_back(double elem)
    {
        if (capacity == size)
        {
            _resize(capacity * 2);
        }
        arr[size++] = elem;
    }
    // удаляет последний элемент массива.
    void pop_back()
    {
        if (size > 0)
            --size;
    }

    void resize(int new_size, double elem)
    {
        int old_size = size;
        _resize(new_size);
        if (new_size > old_size)
        {
            std::fill(arr + old_size, arr + new_size, elem);
        }
    }
    // удаляет элемент на позиции index, сдвигая все последующие элементы влево.
    void erase(int index)
    {
        if (index >= size)
            return;

        for (int i = index; i < size - 1; ++i)
        {
            arr[i] = arr[i + 1];
        }
        --size;
    }
    // вставляет элемент elem на позицию index, сдвигая все следующие элементы вправо.
    void insert(int index, double elem)
    {
        if (index > size)
        {
            throw std::range_error("Out of range");
        }
        if (size == capacity)
        {
            _resize(capacity * 2);
        }
        for (int i = size; i > index; --i)
        {
            arr[i] = arr[i - 1];
        }
        arr[index] = elem;
        ++size;
    }
    // проверку на равенство двух векторов
    bool operator==(vector const &v) const
    {
        if (size != v.size)
            return false;

        for (int i = 0; i < size; ++i)
        {
            if (arr[i] != v.arr[i])
                return false;
        }
        return true;
    }
    // оп трехстор сравн
    int operator<=>(vector const &v) const
    {
        for (int i = 0; i < size && i < v.size; ++i)
        {
            if (arr[i] < v.arr[i])
                return -1;
            if (arr[i] > v.arr[i])
                return 1;
        }
        if (size > v.size)
            return 1;
        if (size < v.size)
            return -1;
        return 0;
    }
    // опер присваив
    vector &operator=(vector const &v)
    {
        if (this != &v) // самоприсв
        {
            vector tmp(v.begin(), v.end());
            std::swap(arr, tmp.arr);
            std::swap(capacity, tmp.capacity);
            std::swap(size, tmp.size);
        }
        return *this;
    }
    // итератор на перв эл-т
    iterator begin()
    {
        return iterator(arr);
    }
    iterator end()
    {
        return iterator(arr + size);
    }

    const iterator begin() const
    {
        return iterator(arr);
    }
    const iterator end() const
    {
        return iterator(arr + size);
    }

    ~vector()
    {
        delete[] arr;
    }
};

int main()
{
    vector a{1.0, 2.0, 3.0, 4.0, 5.0};
    a.insert(2, 10.0);
    vector b(5, 4.0);

    std::cout << "Vector a elements:\n";
    for (auto elem : a)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    if (a == b)
    {
        std::cout << "Vector a == b\n";
    }
    else
    {
        std::cout << "Vector a != b\n";
    }

    const double &check = a.at(3);
    std::cout << "Element at index 3 in a: " << check << std::endl;

    double &check_a = a.at(4);
    std::cout << "Element at index 4 in a (modifiable): " << check_a << std::endl;

    return 0;
}
