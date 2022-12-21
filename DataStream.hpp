#pragma once
#define SIZEOFCHAR 1
#include <vector>
#include <list>
#include <map>
#include <set>
#include <cstring>
#include <iostream>
#include <algorithm>
#include "Serializable.hpp"
using namespace std;

namespace uuy
{
namespace serialize
{


class DataStream
{
public:
    DataStream() : m_pos(0)
    {
        getByteOrder();
    }
    ~DataStream() {}
    /**
     * @brief  序列化最基本方法
     * 
     * @param value 数据
     * @param len 长度
     */
    void write(const char* value, std::size_t len);
    void write(const bool value);
    void write(const char value);
    void write(const int16_t value);
    void write(const int32_t value);
    void write(const uint32_t value);
    void write(const int64_t value);
    void write(const uint64_t value);
    void write(const float value);
    void write(const double value);
    void write(const string& value);
    template<typename T>
    void write(const std::vector<T>& value);
    template<typename T>
    void write(const std::list<T>& value);
    template<typename K, typename V>
    void write(const std::map<K, V>& value);
    template<typename T>
    void write(const std::set<T>& value);
    void write(const Serializeble& value);

    template<typename T, typename ...Args>
    void write_args(const T& value, const Args& ... args);
    void write_args();


    bool read(bool& value);
    bool read(char& value);
    bool read(const char* value, int len);
    bool read(int16_t& value);
    bool read(int32_t& value);
    bool read(uint32_t& value);
    bool read(int64_t& value);
    bool read(uint64_t& value);
    bool read(float& value);
    bool read(double& value);
    bool read(string& value);
    template<typename T>
    bool read(std::vector<T>& value);
    template<typename T>
    bool read(std::list<T>& value);
    template<typename K, typename V>
    bool read(std::map<K, V>& value);
    template<typename T>
    bool read(std::set<T>& value);
    bool read(Serializeble& value);

    template<typename T, typename ...Args>
    bool read_args(T& value, Args& ... args);
    bool read_args();



    template<typename T>
    DataStream& operator>>(T& value);

    template<typename T>
    DataStream& operator<<(T& value);
private:
    /**
     * @brief 为vector容器预申请空间
     * 
     * @param len 数据长度
     */
    void myReserve(std::size_t len);
    void getByteOrder();

public:
    enum class ElemType
    {
        BOOL = 0,
        CHAR,
        INT16,
        INT32,
        INT64,
        UINT32,
        UINT64,
        FLOAT,
        DOUBLE,
        STRING,
        VECTOR,
        LIST,
        MAP,
        SET,
        CUSTOM,
    };
    
    union ByteOrder
    {
        uint16_t x = 0x0011;
        char y[2];
    };
    
    std::vector<char> m_buf;
    std::size_t m_pos;
    bool isLittleEndian;
};

void DataStream::myReserve(std::size_t len)
{
    std::size_t size = m_buf.size();
    std::size_t cap = m_buf.capacity();

    while(size + len > cap)
    {
        if(cap == 0)
        {
            cap = 1;
        }
        else
        {
            cap *= 2;
        }
        
    }
    m_buf.reserve(cap);
}

void DataStream::getByteOrder()
{
    ByteOrder byteOrder;
    if (byteOrder.y[0] == 0x11)
    {
        isLittleEndian = true;
    }
    else if (byteOrder.y[0] == 0x00)
    {
        isLittleEndian = false;
    }
}

void DataStream::write(const char* value, std::size_t len)
{
    myReserve(len);
    std::size_t size = m_buf.size();
    m_buf.resize(size + len);
    std::memcpy(&m_buf[size], value, len);//将数�?拷贝到m_buf[size]的空位置，size为起始位�?
}

void DataStream::write(const bool value)
{
    char type = static_cast<char>(ElemType::BOOL);
    write(&type, SIZEOFCHAR);
    write(reinterpret_cast<char*> (const_cast<bool*>(&value)), sizeof(bool));
    
}

void DataStream::write(const char value)
{
    char type = static_cast<char> (ElemType::CHAR);
    write(&type, SIZEOFCHAR);
    write(reinterpret_cast<char*> (const_cast<char*>(&value)), sizeof(char));
}

void DataStream::write(const int16_t value)
{
    char type = static_cast<char> (ElemType::INT16);
    write(&type, SIZEOFCHAR);
    char* first = reinterpret_cast<char*> (const_cast<int16_t*>(&value));
    if(!isLittleEndian)
    {
        std::reverse(first, 
            first + sizeof(int16_t));
    }
    write(first, sizeof(int16_t));
}

void DataStream::write(const int32_t value)
{
    char type = static_cast<char> (ElemType::INT32);
    write(&type, SIZEOFCHAR);
    char* first = reinterpret_cast<char*> (const_cast<int32_t*>(&value));
    if(!isLittleEndian)
    {
        std::reverse(first, 
            first + sizeof(int32_t));
    }
    write(first, sizeof(int32_t));
}

void DataStream::write(const uint32_t value)
{
    char type = static_cast<char> (ElemType::UINT32);
    write(&type, SIZEOFCHAR);
    char* first = reinterpret_cast<char*> (const_cast<uint32_t*>(&value));
    if(!isLittleEndian)
    {
        std::reverse(first, 
            first + sizeof(uint32_t));
    }
    write(first, sizeof(uint32_t));
}

void DataStream::write(const int64_t value)
{
    char type = static_cast<char> (ElemType::INT64);
    write(&type, SIZEOFCHAR);
    
    char* first = reinterpret_cast<char*> (const_cast<int64_t*>(&value));
    if(!isLittleEndian)
    {
        std::reverse(first, 
            first + sizeof(int64_t));
    }
    write(first, sizeof(int64_t));
}

void DataStream::write(const uint64_t value)
{
    char type = static_cast<char> (ElemType::UINT64);
    write(&type, SIZEOFCHAR);
    char* first = reinterpret_cast<char*> (const_cast<uint64_t*>(&value));
    if(!isLittleEndian)
    {
        std::reverse(first, 
            first + sizeof(uint64_t));
    }
    write(first, sizeof(uint64_t));
}

void DataStream::write(const float value)
{
    char type = static_cast<char> (ElemType::FLOAT);
    write(&type, SIZEOFCHAR);
    char* first = reinterpret_cast<char*> (const_cast<float*>(&value));
    if(!isLittleEndian)
    {
        std::reverse(first, 
            first + sizeof(float));
    }
    write(first, sizeof(float));
}

void DataStream::write(const double value)
{
    char type = static_cast<char> (ElemType::DOUBLE);
    write(&type, SIZEOFCHAR);
char* first = reinterpret_cast<char*> (const_cast<double*>(&value));
    if(!isLittleEndian)
    {
        std::reverse(first, 
            first + sizeof(double));
    }
    write(first, sizeof(double));
}

void DataStream::write(const string &value)
{
    char type = static_cast<char> (ElemType::STRING);
    write(&type, SIZEOFCHAR);
    int len = value.length();
    write(len);
    write(value.data(), len);
}

template<typename T>
void DataStream::write(const std::vector<T>& value)
{
    char type = static_cast<char> (ElemType::VECTOR);
    write(&type, SIZEOFCHAR);
    int len = value.size();
    write(len);
    for(auto it = value.begin(); it != value.end(); ++it)
    {
        write(*it);
    }
}
template<typename T>
void DataStream::write(const std::list<T>& value)
{
    char type = static_cast<char> (ElemType::LIST);
    write(&type, SIZEOFCHAR);
    int len = value.size();
    write(len);
    for(auto it = value.begin(); it != value.end(); ++it)
    {
        write(*it);
    }
}

template<typename K, typename V>
void DataStream::write(const std::map<K, V>& value)
{
    char type = static_cast<char> (ElemType::MAP);
    write(&type, SIZEOFCHAR);
    int len = value.size();
    write(len);
    for (auto it = value.begin(); it != value.end(); ++it)
    {
        write(it->first);
        write(it->second);
    }
}
template<typename T>
void DataStream::write(const std::set<T>& value)
{
    char type = static_cast<char> (ElemType::SET);
    write(&type, SIZEOFCHAR);
    int len = value.size();
    write(len);
    for (auto it = value.begin(); it != value.end(); ++it)
    {
        write(*it);
    }
}

void DataStream::write(const Serializeble& value)
{
    value.serialize(*this);
}

template<typename T, typename ...Args>
void DataStream::write_args(const T& value, const Args& ... args)
{
    write(value);
    write_args(args...);
}

void DataStream::write_args() {}

bool DataStream::read(bool& value)
{
    if(m_buf[m_pos] != static_cast<char>(ElemType::BOOL))
    {
        return false;
    }
    ++m_pos;
    value = static_cast<bool>(m_buf[m_pos]);
    ++m_pos;
    return true;
}

bool DataStream::read(char& value)
{
    if(m_buf[m_pos] != static_cast<char> (ElemType::CHAR))
    {
        return false;
    }
    ++m_pos;
    value = static_cast<char> (m_buf[m_pos]);
    ++m_pos;
    return true;
}

bool DataStream::read(const char* value, int len)
{
    memcpy(const_cast<char*>(value), &m_buf[m_pos], len);
    if(*(const_cast<char*>(value)) != static_cast<char>(ElemType::CUSTOM))
    {
        return false;
    }
    m_pos += len;
    return true;
}

bool DataStream::read(int16_t& value)
{
    if(m_buf[m_pos] != static_cast<char> (ElemType::INT16))
    {
        return false;
    }
    ++m_pos;
    
    value = *(reinterpret_cast<int16_t*> (&m_buf[m_pos]));
    if(!isLittleEndian)
    {
        char* first = reinterpret_cast<char*>(&value);
        std::reverse(first, first + sizeof(int16_t));
    }
    m_pos += 2;

    return true;
}

bool DataStream::read(int32_t& value)
{
    if(m_buf[m_pos] != static_cast<char> (ElemType::INT32))
    {
        return false;
    }
    ++m_pos;
    value = *(reinterpret_cast<int32_t*> (&m_buf[m_pos]));
    if(!isLittleEndian)
    {
        char* first = reinterpret_cast<char*>(&value);
        std::reverse(first, first + sizeof(int32_t));
    }
    m_pos += 4;

    return true;
}

bool DataStream::read(uint32_t& value)
{
    if(m_buf[m_pos] != static_cast<char> (ElemType::UINT32))
    {
        return false;
    }
    ++m_pos;
    value = *(reinterpret_cast<uint32_t*> (&m_buf[m_pos]));
    if(!isLittleEndian)
    {
        char* first = reinterpret_cast<char*>(&value);
        std::reverse(first, first + sizeof(uint32_t));
    }
    m_pos += 4;

    return true;
}

bool DataStream::read(int64_t& value)
{
    if(m_buf[m_pos] != static_cast<char> (ElemType::INT64))
    {
        return false;
    }
    ++m_pos;
    value = *(reinterpret_cast<int64_t*> (&m_buf[m_pos]));
    if(!isLittleEndian)
    {
        char* first = reinterpret_cast<char*>(&value);
        std::reverse(first, first + sizeof(int64_t));
    }
    m_pos += 8;

    return true;
}
bool DataStream::read(uint64_t& value)
{
    if(m_buf[m_pos] != static_cast<char> (ElemType::UINT64))
    {
        return false;
    }
    ++m_pos;
    value = *(reinterpret_cast<uint64_t*> (&m_buf[m_pos]));
    if(!isLittleEndian)
    {
        char* first = reinterpret_cast<char*>(&value);
        std::reverse(first, first + sizeof(uint64_t));
    }
    m_pos += 8;

    return true;
}
bool DataStream::read(float& value)
{
    if(m_buf[m_pos] != static_cast<char> (ElemType::FLOAT))
    {
        return false;
    }
    ++m_pos;
    value = *(reinterpret_cast<float*> (&m_buf[m_pos]));
    if(!isLittleEndian)
    {
        char* first = reinterpret_cast<char*>(&value);
        std::reverse(first, first + sizeof(float));
    }
    m_pos += 4;

    return true;
}
bool DataStream::read(double& value)
{
    if(m_buf[m_pos] != static_cast<char> (ElemType::DOUBLE))
    {
        return false;
    }
    ++m_pos;
    value = *(reinterpret_cast<double*> (&m_buf[m_pos]));
    if(!isLittleEndian)
    {
        char* first = reinterpret_cast<char*>(&value);
        std::reverse(first, first + sizeof(double));
    }
    m_pos += 8;

    return true;
}
bool DataStream::read(string& value)
{
    if(m_buf[m_pos] != static_cast<char> (ElemType::STRING))
    {
        return false;
    }
    ++m_pos;
    int len;
    read(len);
    if(len < 0)
    {
        return false;
    }
    // value = *(reinterpret_cast<string*> (&m_buf[m_pos]));
    value.assign(reinterpret_cast<char*> (&m_buf[m_pos]), len);
    m_pos += len;

    return true;
}
template<typename T>
bool DataStream::read(std::vector<T>& value)
{
    value.clear();
    if(m_buf[m_pos] != static_cast <char> (ElemType::VECTOR))
    {
        return false;
    }
    ++m_pos;
    int len;
    read(len);
    for(auto i = 0; i < len; ++i)
    {
        T temp;
        read(temp);
        value.push_back(temp);
    }
    return true;
}

template<typename T>
bool DataStream::read(std::list<T>& value)
{
    value.clear();
    if(m_buf[m_pos] != static_cast <char> (ElemType::LIST))
    {
        return false;
    }
    ++m_pos;
    int len;
    read(len);
    for(auto i = 0; i < len; ++i)
    {
        T temp;
        read(temp);
        value.push_back(temp);
    }
    return true;
}
template<typename K, typename V>
bool DataStream::read(std::map<K, V>& value)
{
    value.clear();
    if(m_buf[m_pos] != static_cast <char> (ElemType::MAP))
    {
        return false;
    }
    ++m_pos;
    int len;
    read(len);
    for(auto i = 0; i < len; ++i)
    {
        K k;
        read(k);

        V v;
        read(v);
        value[k] = v;
    }
    return true;
}
template<typename T>
bool DataStream::read(std::set<T>& value)
{
    value.clear();
    if(m_buf[m_pos] != static_cast <char> (ElemType::SET))
    {
        return false;
    }
    ++m_pos;
    int len;
    read(len);
    for(auto i = 0; i < len; ++i)
    {
        T temp;
        read(temp);
        value.insert(temp);
    }
    return true;
}

bool DataStream::read(Serializeble& value)
{
    value.deserialize(*this);
    return true;
}

template<typename T, typename ...Args>
bool DataStream::read_args(T& value, Args& ... args)
{
    read(value);
    
    return read_args(args ...);;
}
bool DataStream::read_args() { return true; }


template<typename T>
DataStream& DataStream::operator<<(T& value)
{
    write(value);
    return *this;
}

template<typename T>
DataStream& DataStream::operator>>(T& value)
{
    read(value);
    return *this;
}

}
}

