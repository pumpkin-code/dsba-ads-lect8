

#ifndef SAFE_ARRAY_H_
#define SAFE_ARRAY_H_

#include <cstddef>
#include <algorithm>        // std::min
#include <stdexcept>        // std::out_of_range

template<typename T>
class SafeArray {
public:

    /// The default constructor.
    SafeArray()
        : _arr(nullptr)
        , _size(0)
    {}

    /// Constructor creates an array with \a sz elements of value \a def
    SafeArray(size_t sz, T def = T())
        : SafeArray()                       // delegates the constructor call to
    {                                       // the default one
        if(!sz)
            return;

        _size = sz;
        _arr = new T[sz];

        for(int i = 0; i < sz; ++i)
            _arr[i] = def;
    }

    /// The copy constructor.
    SafeArray(const SafeArray& origin)
        : _size(origin._size),
          _arr(new T[origin._size])
    {
        //_size = origin._size;             // possible, but somewhat late
        //_arr = new int[_size];

        for(size_t i = 0; i < _size; ++i)
            _arr[i] = origin._arr[i];
    }


    /// The move constructor
    SafeArray(SafeArray&& other)
    {
        _size = other._size;
        _arr = other._arr;                  // stealing resources

        other._size = 0;                    // set temp obj in a proper state
        other._arr = nullptr;
    }


    /// Constructor with initializer list
    SafeArray(std::initializer_list<T> vals)
        : SafeArray()
    {
        if(!vals.size())
            return;

        _size = vals.size();
        _arr = new T[_size];
        size_t i = 0;
        for(const T& el : vals)
            _arr[i++] = el;
    }


    /// The Destructor. Implements RAII closing part.
    ~SafeArray()
    {
        if(_arr)                            // this check is not necessary
            delete [] _arr;
    }


    /// The Copy Assignment operator overloading.
    const SafeArray& operator = (const SafeArray& rhv)
    {
        if (this == &rhv)
            return *this;

        // the follows is a straightforward and unsafe approach
        //    if(_arr)
        //       delete [] _arr;

        //    _size = rhv._size;
        //    _arr = new T[_size];

        //    for(size_t i = 0; i < _size; ++i)
        //        _arr[i] = rhv._arr[i];

        //--< better approach with the copy-and-swap idiom >--
        SafeArray temp(rhv);
        swap(temp, *this);

        return *this;
    }
    

    /// The Move Assignment operator overloading.
    SafeArray& operator = (SafeArray&& rhv)
    {
        if (this == &rhv)
            return *this;

        delete [] _arr;

        _size = rhv._size;
        _arr = rhv._arr;                    // stealing resources

        rhv._size = 0;                      // set temp obj in a proper state
        rhv._arr = nullptr;

        //can we alternatively just swap the resources?
        // swap(rhv, *this);

        return *this;
    }

public:
    /// Resizes the array.
    void resize(size_t newSz, T def = T())
    {
        if(newSz == _size)
            return;

        if(!newSz)                          // need to delete
        {
            if(_arr)
            {
                delete [] _arr;
                _arr = nullptr;
                _size = 0;
            }
            return;

        }

        // creates a new array, copy elements of the old array, and removes the old
        T* newAr = new T[newSz];
        for (size_t i = 0; i < std::min(newSz, _size); ++i)
           newAr[i] = _arr[i];

        // if new array is bigger, need to feel the difference
        if(newSz > _size)
        {
            for(size_t j = _size; j < newSz; ++j)
                newAr[j] = def;
        }

        _size = newSz;
        delete [] _arr;
        _arr = newAr;
    }


    /// Getting the ref to i-th element with no checking out of range.
    T& operator [] (size_t i) noexcept { return _arr[i]; }
    const T& operator [] (size_t i) const noexcept { return _arr[i]; };

    /// Getting the ref to i-th element with checking out of range.
    T& at(size_t i)
    {
        if (i >= _size)
            throw std::out_of_range("Bad index");
        return _arr[i];
    }

    const T& at(size_t i) const
    {
        if (i >= _size)
            throw std::out_of_range("Bad index");
        return _arr[i];
    }

    // getters/setters
    size_t getSize() const { return _size; }
    const T* getPtr() const { return _arr; }


private:

    /// Auxialiary method swpping two array objects with a managed resource
    /// correctly. Method guarantees that it doesn't throw under any conditions.
    static void swap(SafeArray& lhv, SafeArray& rhv) noexcept
    {
        std::swap(lhv._arr, rhv._arr);
        std::swap(lhv._size, rhv._size);
    }

private:
    T* _arr;                ///< Actual resource handler.
    size_t _size;           ///< Stores size of an array.
};// SafeArray


template<typename T>
std::ostream& operator << (std::ostream& s, const SafeArray<T>& arr)
{
    s << "[";
    for (size_t i = 0; i < arr.getSize(); ++i)
    {
        if(i)
            s << ", ";
        s << arr[i];
    }

    s << "]";

    return s;
}



#endif // SAFE_ARRAY_H_
