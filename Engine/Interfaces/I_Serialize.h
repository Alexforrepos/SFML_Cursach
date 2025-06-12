#pragma once
#include "Utils/Serialization_Utils.h"
#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>
#include "Engine/R_Manager.h"
#include <sstream>
#include <memory>

class I_Serialize : 
    public std::enable_shared_from_this<I_Serialize>
{
public:
    virtual ~I_Serialize() = default;

    static std::shared_ptr<I_Serialize> create() = delete;

    
    template <class Archive>
    void serialize(Archive& ar)
    {
    };

    std::string serializeToStream() {
       
        std::stringstream ss;
        {
            cereal::BinaryOutputArchive archive(ss);
            archive(this->shared_from_this());
        }
        return ss.str();
    }

    template <typename T>
    static std::shared_ptr<T> deserializeFromStream(const std::string& data) {
        std::stringstream ss(data);
        std::shared_ptr<T> obj;
        {
            cereal::BinaryInputArchive archive(ss);
            archive(obj);
        }
        return obj;
    }
};
