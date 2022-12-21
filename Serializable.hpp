#pragma once
namespace uuy
{
namespace serialize
{

class DataStream;

class Serializeble
{
public:
    virtual void serialize(DataStream& stream) const = 0;
    virtual bool deserialize(DataStream& stream) = 0;
};

#define SERIALIZE(...)                                                  \
    void serialize(DataStream& stream) const                            \
    {                                                                   \
        char type = static_cast<char>(DataStream::ElemType::CUSTOM);    \
        stream.write(&type, sizeof(char));                              \
        stream.write_args(__VA_ARGS__);                                 \
    }                                                                   \
                                                                        \
    bool deserialize(DataStream& stream)                                \
    {                                                                   \
        char type;                                                      \
        stream.read(&type, sizeof(char));                               \
        if(type != static_cast<char>(DataStream::ElemType::CUSTOM))     \
        {                                                               \
            return false;                                               \
        }                                                               \
        stream.read_args(__VA_ARGS__);                                  \
        return true;                                                    \
    }                                                                   \



}
}