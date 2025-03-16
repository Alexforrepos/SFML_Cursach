#pragma once
#include "MSG.h"
#include <vector>
#include <memory>

//
//������ ���������� ��������� � ���������
//MSG_Manager::get().addMSG(new MSG_TYPE_MOVE({123,123},this))
//


class MSG_Manager {
private:
    std::vector<std::shared_ptr<MSG>> MSGVector;

    // �������� ����������� ��� ���������� singleton ��������
    MSG_Manager() = default;

public:
    // �������� ����� ��� ������� � ���������� MSG_Manager
    static MSG_Manager& get() {
        static MSG_Manager inst;
        return inst;
    }

    // ����� ��� ���������� ���������
    void addMSG(std::shared_ptr<MSG> msg)
    {
        MSGVector.emplace_back(std::move(msg)); 
    }

    // ����� ��� ������� �������
    void clear()
    {
        MSGVector.clear();
    }

    // ����� ��� ��������� ������� ���������
    std::vector<std::shared_ptr<MSG>>& getVector()
    {
        return MSGVector;
    }
};