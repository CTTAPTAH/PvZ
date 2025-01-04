#include "Message.h"

Message::Message() : object(), type(TypeMsg::UNDEFINED)
{
}
Message::Message(const Message& msg) : object()
{
    type = msg.type;
    switch (type)
    {
    case TypeMsg::UNDEFINED:
        break;
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
    case TypeMsg::ADD_MAP:
        add_map = msg.add_map;
        break;
    default:
        break;
    }
}