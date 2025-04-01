#include "Message.h"

Message::Message() : type(TypeMsg::UNDEFINED) {
    // чтобы убрать предупреждени€ компил€тора о инициализации
    memset(&damage, 0, sizeof(damage)); // «аполн€ем нул€ми
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
        // чтобы убрать предупреждени€ компил€тора о инициализации
        memset(&damage, 0, sizeof(damage)); // «аполн€ем нул€ми
        break;
    }
}
Message::~Message(){}