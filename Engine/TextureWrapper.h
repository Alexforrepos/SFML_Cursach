#pragma once
#include "Interfaces/I_Serialize.h"


//class TextureWrapper : public sf::Texture, public I_Serialize
//{
//private:
//    std::string textureId; // ������������� ��� ��������� ��������
//    std::string sourcePath; // ���� � ����� �������� (�����������)
//
//public:
//    template <class Archive>
//    void serialize(Archive& ar) {
//        bool isRepeated = isRepeated();
//        bool isSmooth = isSmooth();
//        sf::Vector2u size = getSize();
//
//        ar(textureId, sourcePath, isRepeated, isSmooth, size);
//
//        if constexpr (Archive::is_loading::value) {
//            // �������� �������� ����� �������� ��������
//            if (!sourcePath.empty()) {
//                loadFromFile(sourcePath);
//            }
//            setRepeated(isRepeated);
//            setSmooth(isSmooth);
//        }
//    }
//
//    // ��������� �������� ����� �������� ��������
//    //void setTextureById(const std::string& id, R_Manager& resManager) {
//    //    textureId = id;
//    //    const auto& texture = resManager.access<sf::Texture>(id);
//    //    (*this). = texture; // �������� �������� ��������
//    //}
//
//    // �������� �� ����� � ����������� ����
//    bool loadFromFile(const std::string& filename) {
//        sourcePath = filename;
//        return sf::Texture::loadFromFile(filename);
//    }
//
//    const std::string& getTextureId() const { return textureId; }
//    const std::string& getSourcePath() const { return sourcePath; }
//};
//
