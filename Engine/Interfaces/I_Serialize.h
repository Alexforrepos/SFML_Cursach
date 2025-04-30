#pragma once
#include "Utils/Serialization_Utils.h"
#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>
#include "Engine/R_Manager.h"
#include <sstream>
#include <memory>

class I_Serialize : public std::enable_shared_from_this<I_Serialize>
{
public:
    virtual ~I_Serialize() = default;

    // Виртуальный метод для сериализации
    template <class Archive>
    void serialize(Archive& ar)
    {// Базовая реализация (может быть пустой)
    };

    std::string serializeToStream() {
        std::stringstream ss;
        {
            cereal::BinaryOutputArchive archive(ss);
            archive(cereal::make_nvp("object", shared_from_this()));
        }
        
        return ss.str();
    }

    void deserializeFromStream(const std::string& data) {
        std::stringstream ss(data);
        {
            cereal::BinaryInputArchive archive(ss);
            std::shared_ptr<I_Serialize> temp;
            archive(cereal::make_nvp("object", temp));
            if (temp) {
                this->serialize(archive); // или другая логика копирования
            }
        }
    }
};
