#include "UIManager.h"
#include "Manager.h" // ����������� �������� � .cpp

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
	shovel(*LoadTexture::getBorn().getTexture("shovel")),
	bar_size(Config::WAVE_BAR_WIDTH, Config::WAVE_BAR_HEIGHT),
	bar_pos(Config::WAVE_BAR_POS_X, Config::WAVE_BAR_POS_Y),
	wave_bar_border(),
	wave_bar_background(),
	wave_bar_fill(),
	waves_started(false),
	head_zm(*LoadTexture::getBorn().getTexture("head_zm"))
{
	frame_icon.setPosition({ 0, 0 });
	board.setPosition(Config::BOARD_POS_X, Config::BOARD_POS_Y);
	shovel.setPosition(Config::BOARD_POS_X + board.getTextureRect().width, Config::SHOVEL_POS_Y);

	// ������
	if (!font.loadFromFile("fonts\\Share-Tech-CYR-Bold.otf")) {
		std::cerr << "�� ������� ��������� �����!\n";
		return;
	}
	money_text.setFont(font);
	money_text.setCharacterSize(Config::SIZE_MONEY); // ������
	money_text.setFillColor(sf::Color::Black); // ����
	money_text.setPosition(Config::MONEY_POS_X, Config::MONEY_POS_Y); // �������
	updateMoneyText(Config::MONEY); // ��������� ��������� �����

	// �����
	wave_bar_border.setSize(bar_size);
	wave_bar_border.setPosition(bar_pos);
	wave_bar_border.setOutlineThickness(Config::WAVE_BAR_THIKNESS_FRAME);
	wave_bar_border.setOutlineColor(sf::Color(48, 61, 96));

	// ���
	wave_bar_background.setSize(bar_size);
	wave_bar_background.setPosition(bar_pos);
	wave_bar_background.setFillColor(sf::Color::Black);

	// ��������
	wave_bar_fill.setSize({ 0.f, bar_size.y });
	wave_bar_fill.setPosition(bar_pos);
	wave_bar_fill.setFillColor(sf::Color(85, 152, 10));
}

// ������
void UIManager::updateInfo() {
	plant_infos = Manager::getBorn()->getPlayer().getPlantSlots();
}
void UIManager::updateWaves(double progress_ratio)
{
	if (!waves_started) waves_started = true;

	float new_width = progress_ratio * bar_size.x;
	wave_bar_fill.setSize({ new_width, bar_size.y });
	sf::Vector2f new_pos(bar_pos.x + (bar_size.x - new_width), bar_pos.y);
	wave_bar_fill.setPosition(new_pos);

	// �������� ����� ���-�� ������ (-4)
	head_zm.setPosition({ new_pos.x - head_zm.getLocalBounds().width / 2,
		new_pos.y - (head_zm.getLocalBounds().height / 2) + 4 });
}
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
	Player player = Manager::getBorn()->getPlayer();

	// ������ ������
	for (const auto& icon : plant_icons) {
		win.draw(icon);
	}

	// ���� ������� �������� ������, �� ������ ������ �������� + ������������ (����� �������)
	for (int i = 0; i < plant_infos.size(); i++) {
		if (player.getMoney() < plant_infos[i].cost or
			plant_infos[i].reload > 0) {
			// �������� ������� � ������� �������
			sf::FloatRect bounds = plant_icons[i].getGlobalBounds();

			// ������ �������������
			sf::RectangleShape overlay;
			overlay.setSize({ bounds.width, bounds.height });
			overlay.setPosition({ bounds.left, bounds.top });

			// ����������� ����: ������ � �������������
			overlay.setFillColor(sf::Color(0, 0, 0, 150));
			
			win.draw(overlay);

			// ���������� �����������
			if (plant_infos[i].reload > 0) {
				// ������ �������������
				double coef = 1 - plant_infos[i].reload / plant_infos[i].time_reload;
				float height = (double)bounds.height * coef;
				float pos_y = bounds.top + (bounds.height - height);
				overlay.setSize({ bounds.width, height });
				overlay.setPosition({ bounds.left, pos_y });

				// ����������� ����: ����� � �������������
				overlay.setFillColor(sf::Color(255, 255, 255, 75));

				win.draw(overlay);
			}
		}
	}
	// ������ ������� ����
	if (waves_started) {
		win.draw(wave_bar_border);
		win.draw(wave_bar_background);
		win.draw(wave_bar_fill);
		win.draw(head_zm);
	}

	// ������ ���������
	win.draw(board);
	win.draw(shovel);
	win.draw(money_text);
	
	if (chosenPlantIdx != -1) win.draw(frame_icon);
	if (chosen_shovel) win.draw(frame_icon);

	// ������ ���������
	if (isPreviewing) {
		// ���������� ��� ���������
		Manager* mng = Manager::getBorn();
		Map map = mng->getMap();
		sf::Vector2f cursor_position = (sf::Vector2f)sf::Mouse::getPosition(win);
		sf::Vector2f idx_field = map.getFieldIdx(cursor_position);
		if (map.getIsPlaced(idx_field.x, idx_field.y) and !chosen_shovel) {
			return;
		}
		if (!map.isValidIndex(idx_field)) { // ������ ��� �����
			return;
		}
		sf::Vector2f pos_field = map.getFieldPosition(idx_field);
		sf::FloatRect size_map = map.getRect();

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

			Player& player = Manager::getBorn()->getPlayer();
			if (plant_infos[chosenPlantIdx].reload > 0 or // ��� �� �������������
				player.getMoney() < plant_infos[chosenPlantIdx].cost) { // �� ������� �����
				chosenPlantIdx = -1;
				return;
			}

			// ��� ��������� �����
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
		msg.add_plant.idx = chosenPlantIdx;
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
		sf::Vector2f mousePosI = {mousePos.x,mousePos.y};

		for (const auto& obj : list_obj) {
			if (obj->getTypeObj() == TypeObject::PLANT and obj->getRect().contains(mousePosI)) {
				sf::Vector2f idx_cursor = mng->getMap().getFieldIdx(mousePosI);
				sf::Vector2f central_pos_plant = {
					float(obj->getRect().left + (obj->getRect().width / 2)),
					float(obj->getRect().top + (obj->getRect().height / 2)) };
				sf::Vector2f idx_plant = mng->getMap().getFieldIdx(central_pos_plant);

				// ���� �� ������� �������, �� ������ ��������
				if (idx_cursor.x == idx_plant.x and
					idx_cursor.y == idx_plant.y) {
					Message msg;
					msg.type = TypeMsg::DEATH;
					msg.death.creature = obj;
					mng->addMessage(msg);

					mng->getMap().setIsPlaced(idx_cursor, false);
				}
			}
		}
	}
}
void UIManager::receiveMsg(Message* msg)
{
	if (msg->type == TypeMsg::SET_MONEY) {
		updateMoneyText(msg->set_money.money);
	}
}
void UIManager::updateMoneyText(int money_)
{
	money = money_;
	money_text.setString(std::to_string(money));

	// ������������� ���������� �������
	sf::FloatRect rect_text = money_text.getLocalBounds();
	sf::FloatRect rect_display = frame_icon.getLocalBounds();
	rect_display.left += Config::MONEY_DISPLAY_OFFSET_X;
	rect_display.width = Config::MONEY_DISPLAY_WIDTH;
 
	sf::Vector2f pos_text;
	pos_text.x = rect_display.left + (rect_display.width - rect_text.width) / 2.f;
	pos_text.y = Config::BOARD_POS_Y;

	money_text.setPosition(pos_text.x, pos_text.y);
}

// �������, �������
