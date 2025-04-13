
#pragma once
#include <SFML/Audio.hpp>
#include <map>
#include <list>
#include <string>
#include <memory>
class SoundEditor
{
private:
    static SoundEditor* born;

    sf::Music music;

    std::map<std::string, sf::SoundBuffer> buffers;
    std::list<std::unique_ptr<sf::Sound>> playingSounds;

    SoundEditor();
    SoundEditor(const SoundEditor&) = delete;
    SoundEditor& operator=(const SoundEditor&) = delete;

public:
    static SoundEditor* getBorn();
    ~SoundEditor();

    void addSound(const std::string& name, const std::string& filename);
    void loadAllSounds();
    void playSound(const std::string& soundName, int volume = 100, bool loop = false);
    void cleanupSounds();
    sf::SoundBuffer& getBuffer(const std::string& name);
    void setMusicStop();
};
