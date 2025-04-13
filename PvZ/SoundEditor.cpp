
#include "SoundEditor.h"
#include <iostream>

SoundEditor* SoundEditor::born = nullptr;

SoundEditor::SoundEditor() {

    if (!music.openFromFile("sounds\\MUSIC.ogg")) {
        std::cerr << "Ошибка загрузки музыки!" << std::endl;
    }
    else {
        music.setLoop(true);
        music.setVolume(30);
        music.play();
    }
}

SoundEditor* SoundEditor::getBorn() {
    if (!born) {
        born = new SoundEditor();
    }
    return born;
}

SoundEditor::~SoundEditor() {
    born = nullptr;
}

void SoundEditor::addSound(const std::string& name, const std::string& filename) {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filename)) {
        std::cerr << "Ошибка загрузки звука: " << filename << std::endl;
        return;
    }
    buffers[name] = std::move(buffer);
}

void SoundEditor::loadAllSounds() {
    addSound("zombies_are_coming", "sounds\\zombies_are_coming.ogg");
    addSound("pea_hit", "sounds\\peaHit.ogg");
    addSound("sun_pull_up", "sounds\\sunPullUp.ogg");
    addSound("zombie_chewing", "sounds\\zombieChew.ogg");
    addSound("cars_start", "sounds\\carsStart.ogg");
    addSound("plant", "sounds\\plant.ogg");
    addSound("Noo", "sounds\\Noo.ogg");
}

void SoundEditor::playSound(const std::string& soundName, int volume, bool loop) {

    auto it = buffers.find(soundName);
    if (it == buffers.end()) {
        std::cerr << "Звук не найден " << soundName << std::endl;
        return;
    }

    auto sound = std::make_unique<sf::Sound>();
    sound->setBuffer(it->second);
    sound->setVolume(volume);
    sound->setLoop(loop);
    sound->play();

    playingSounds.push_back(std::move(sound));
    cleanupSounds();
}

void SoundEditor::cleanupSounds() {
    for (auto it = playingSounds.begin(); it != playingSounds.end(); ) {
        if ((*it)->getStatus() == sf::Sound::Stopped) {
            it = playingSounds.erase(it);
        }
        else {
            it++;
        }
    }
}
sf::SoundBuffer& SoundEditor::getBuffer(const std::string& name) {
    auto it = buffers.find(name);
    if (it != buffers.end()) {
        return it->second;
    }
}

void SoundEditor::setMusicStop()
{
    music.stop();
}
