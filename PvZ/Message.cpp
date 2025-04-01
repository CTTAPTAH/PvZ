#include "Message.h"

Message::Message() : type(TypeMsg::UNDEFINED) {
    // ����� ������ �������������� ����������� � �������������
    memset(&damage, 0, sizeof(damage)); // ��������� ������
}
Message::Message(const Message& msg) {
    type = msg.type;
    switch (type)
    {
    case TypeMsg::DAMAGE:
        damage = msg.damage;
        break;
    case TypeMsg::DEATH:
        death = msg.death;
        break;
    case TypeMsg::CREATE:
        create = msg.create;
        break;
    case TypeMsg::MOVE:
        move = msg.move;
        break;
    case TypeMsg::ADD_PLANT:
        add_plant = msg.add_plant;
        break;
    default:
        // ����� ������ �������������� ����������� � �������������
        memset(&damage, 0, sizeof(damage)); // ��������� ������
        break;
    }
}
Message::~Message(){}