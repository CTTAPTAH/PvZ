#include "UIManager.h"

// �����������, ����������
UIManager::UIManager()
	: isPreviewing(false),
	color_indicator(255, 255, 255, 100),
	chosen_shovel(false),
	plant_infos(),
	chosenPlantIdx(-1),
	frame_icon(*LoadTexture::getBorn().getTexture("frame_icon")),
	plant_icons(),
	board(*LoadTexture::getBorn().getTexture("board")),
	shovel(*LoadTexture::getBorn().getTexture("shovel"))
{
	frame_icon.setPosition({ 0, 0 });
	board.setPosition(Config::BOARD_POS_X, Config::BOARD_POS_Y);
	shovel.setPosition(Config::BOARD_POS_X + board.getTextureRect().width, Config::SHOVEL_POS_Y);
}

// ������
void UIManager::createPlantSelection(const std::vector<PlantInfo>& plants) {
	plant_icons.clear(); // �������, ���� �� ����
	plant_infos = plants;

	float y = Config::ICON_OFFSET_Y; // �������� �� ��� Y

	for (const auto& plant : plants) {
		sf::Sprite icon(*plant.icon);
		icon.setPosition(Config::ICON_OFFSET_X, y);
		plant_icons.push_back(icon);

		y += plant.icon->getSize().y + Config::ICON_SPACING;
	}
}
void UIManager::draw(sf::RenderWindow& win)

{
	for (const auto& icon : plant_icons) {
		win.draw(icon);
	}

	win.draw(board);
	win.draw(shovel);
	
	if (chosenPlantIdx != -1) win.draw(frame_icon);
	if (chosen_shovel) win.draw(frame_icon);

	// ������ ���������
	if (isPreviewing) {
		// ���������� ��� ���������
		Manager* mng = Manager::getBorn();
		Map map = mng->getMap();
		sf::Vector2i cursor_position = sf::Mouse::getPosition(win);
		sf::Vector2i idx_field = map.getFieldIdx(cursor_position);
		if (map.getIsPlaced(idx_field.x, idx_field.y) and !chosen_shovel) {
			return;
		}
		if (!map.isValidIndex(idx_field)) { // ������ ��� �����
			return;
		}
		sf::Vector2i pos_field = map.getFieldPosition(idx_field);
		sf::IntRect size_map = map.getRect();

		// ������
		sf::RectangleShape horizontal(sf::Vector2f(size_map.width, map.getFieldHeight()));
		horizontal.setPosition(sf::Vector2f(size_map.left, pos_field.y));
		horizontal.setFillColor(color_indicator);

		sf::RectangleShape vertical(sf::Vector2f(map.getFieldWidth(), size_map.height));
		vertical.setPosition(sf::Vector2f(pos_field.x, size_map.top));
		vertical.setFillColor(color_indicator);

		win.draw(horizontal);
		win.draw(vertical);
	}
}
void UIManager::handleMousePress(sf::Vector2f mousePos)
{
	// ������ ��������
	for (int i = 0; i < plant_icons.size(); i++) {
		if (plant_icons[i].getGlobalBounds().contains(mousePos)) {
			chosenPlantIdx = i;
			sf::Vector2f pos = plant_icons[i].getPosition(); // ������� ����� � ����
			pos.x += Config::FRAME_ICON_OFFSET_X; // ��������� ����� �� X
			pos.y += Config::FRAME_ICON_OFFSET_Y; // ��������� ����� �� Y
			frame_icon.setPosition(pos);

			if (chosen_shovel) chosen_shovel = false;
			isPreviewing = true;
			
			return;
		}
	}

	// ������ ������
	if (shovel.getGlobalBounds().contains(mousePos)) {
		chosen_shovel = true;
		sf::Vector2f pos = shovel.getPosition(); // ������� ����� � ����
		pos.x += Config::FRAME_ICON_OFFSET_X; // ��������� ����� �� X
		pos.y += Config::FRAME_ICON_OFFSET_Y; // ��������� ����� �� Y
		frame_icon.setPosition(pos);

		if (chosenPlantIdx != -1) chosenPlantIdx = -1;
		isPreviewing = true;

		return;
	}
}
void UIManager::handleMouseRelease(sf::Vector2f mousePos)
{
	isPreviewing = false;
	// ������� �� ������ ��������
	for (int i = 0; i < plant_icons.size(); i++) {
		if (plant_icons[i].getGlobalBounds().contains(mousePos)) {
			return;
		}
	}

	if (chosenPlantIdx != -1) {
		Message msg;
		msg.type = TypeMsg::ADD_PLANT;
		msg.add_plant.mousePos = mousePos;
		msg.add_plant.type = plant_infos[chosenPlantIdx].type;
		msg.add_plant.cost = plant_infos[chosenPlantIdx].cost;
		Manager::getBorn()->addMessage(msg);

		chosenPlantIdx = -1; // ����� ����, ��� ��������� ��������, ����� �������� �����
	}

	//-------------------------------------------
	// ������� �� ������
	if (!shovel.getGlobalBounds().contains(mousePos) and chosen_shovel) {
		chosen_shovel = false; // ���� ������� ������ � ������ ��������� �� �� ���,
		// �� �������� ����� ������
		Manager* mng = Manager::getBorn();
		std::list<GameObject*> list_obj = mng->getListObject();
		sf::Vector2i mousePosI = { static_cast<int>(mousePos.x), static_cast<int>(mousePos.y) };

		for (const auto& obj : list_obj) {
			if (obj->getTypeObj() == TypeObject::PLANT and obj->getRect().contains(mousePosI)) {
				Message msg;
				msg.type = TypeMsg::DEATH;
				msg.death.creature = obj;
				mng->addMessage(msg);
				
				sf::Vector2i vect = mng->getMap().getFieldIdx(mousePosI);
				mng->getMap().setIsPlaced(vect, false);
			}
		}
	}
}

// �������, �������
