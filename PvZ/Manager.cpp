#include "Manager.h"

Manager* Manager::born = nullptr;

Manager::Manager() : game_object(), message() {}
Manager::Manager(const Manager&) {}
Manager::~Manager() {
	for (auto obj : game_object) {
		delete obj;
	}
	game_object.clear();

	for (auto msg : message) {
		delete msg;
	}
	message.clear();

	delete born;
	born = nullptr;
}

Manager* Manager::GetBorn() {
	if (!born) born = new Manager;
	return born;
}
void Manager::UpdateAll(double dt) {
	for (auto obj : game_object) {
		obj->SendMsg(dt);
	}

	for (auto msg : message) {
		// Сообщение для manager
		if (msg->type == TypeMsg::DEATH) {
			auto res = std::find(game_object.begin(), game_object.end(), msg->death.creature);
			delete* res; // удаляем сам объект
			game_object.erase(res); // удаляем указатель на объект в списке
		}
		else if (msg->type == TypeMsg::CREATE) {
			game_object.push_back(msg->create.new_object);
		}

		// Сообщение для game_object
		if (msg->type == TypeMsg::DAMAGE or
			msg->type == TypeMsg::MOVE) {
			for (auto obj : game_object) {
				obj->ReceiveMsg(msg);
			}
		}
	}
}
void Manager::LoadTextures(sf::Texture texture, UnitId id) {

}