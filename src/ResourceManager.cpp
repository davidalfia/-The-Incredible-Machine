#include "ResourceManager.h"


//makes an instance and is created only once
ResourceManager& ResourceManager::instance()
{
	static ResourceManager instance;
	return instance;
}


sf::Texture* ResourceManager::getTexture(const Type_t name)
{
	return &(m_textures[name]);
}



sf::Font& ResourceManager::getFont(const Font name)
{
	return m_fonts[name];
}


sf::SoundBuffer& ResourceManager::getSound(const Sound name)
{
	return m_soundBuff[name];
}

std::string& ResourceManager::getLevelPath()
{
	return m_path;
}
                                 

//CTOR
ResourceManager::ResourceManager()
{
	//textures for windows----------
	// loadTexture("balloon.png", Type_t::balloon);
	// loadTexture("basketBall.png", Type_t::basketBall);
	// loadTexture("baseBall.png", Type_t::baseBall);
	// loadTexture("bowlingBall.png", Type_t::bowlingBall);
	// loadTexture("conveyor.png", Type_t::conveyor);
	// loadTexture("brick.png", Type_t::brickWall);
	// loadTexture("balloonButton.png", Type_t::balloonButton);
	// loadTexture("mouseEngine.png", Type_t::mouseEngine);
	// loadTexture("trampolineOPT1.png", Type_t::trampoline);
	// loadTexture("scissors.png", Type_t::scissors); 
	// loadTexture("pipeWall.png", Type_t::pipeWall); 
	// loadTexture("fancyWall.png", Type_t::fancyWall); 
	// loadTexture("basketButton.png", Type_t::basketButton);
	// loadTexture("baseButton.png", Type_t::baseButton);
	// loadTexture("bowlingButton.png", Type_t::bowlingButton);
	// loadTexture("conveyorButton.png", Type_t::conveyorButton);
	// loadTexture("brickButton.png", Type_t::brickWallButton);
	// loadTexture("resizeButton.png", Type_t::resizeButton);
	// loadTexture("rotateButton.png", Type_t::rotateButton);
	// loadTexture("mouseEngineButton.png", Type_t::mouseEngineButton);
	// loadTexture("beltButton.png", Type_t::beltButton);
	// loadTexture("trampolineButton.png", Type_t::trampolineButton);
	// loadTexture("scissorsButton.png", Type_t::scissorsButton);
	// loadTexture("pipeWallButton.png", Type_t::pipeWallButton); 
	// loadTexture("fancyWallButton.png", Type_t::fancyWallButton); 
	// loadTexture("engineConectButton.png", Type_t::connectButton);
  	// loadTexture("arrowLButton.png", Type_t::arrowLButton);
	// loadTexture("arrowRButton.png", Type_t::arrowRButton);
  	// loadTexture("advanceButton.png", Type_t::advanceButton);
	// loadTexture("puzzleComplete.png", Type_t::puzzleComplete);
	// loadTexture("replayButton.png", Type_t::replayButton);
	// loadTexture("save.png", Type_t::save);
	// loadTexture("build.png", Type_t::build);
	// loadTexture("play.png", Type_t::play);
	// loadTexture("exit.png", Type_t::exitButton);
	// loadTexture("playmenu.png", Type_t::startButton);
	// loadTexture("bomb.png", Type_t::reset);
	// loadTexture("sound.png", Type_t::sound);
	// loadTexture("choseLevelMenu.png", Type_t::choseLevelMenu);
	// loadTexture("playButton.png", Type_t::playButton);
	// loadTexture("up.png", Type_t::upButton);
	// loadTexture("down.png", Type_t::downButton);
	// loadTexture("up.png", Type_t::upSound);
	// loadTexture("down.png", Type_t::downSound);
	// loadTexture("menuBackground.png", Type_t::menuBackground);
	// loadTexture("frame.png", Type_t::frame);
 	// loadTexture("chooseLevelButton.png", Type_t::choseLevel);
 	// loadTexture("numbers.png", Type_t::numbers);
 	// loadTexture("score.png", Type_t::score);
	// loadTexture("1px.png", Type_t::onePixel);

	//textures for mac----------
	loadTexture("build/balloon.png", Type_t::balloon);
	loadTexture("build/basketBall.png", Type_t::basketBall);
	loadTexture("build/baseBall.png", Type_t::baseBall);
	loadTexture("build/bowlingBall.png", Type_t::bowlingBall);
	loadTexture("build/conveyor.png", Type_t::conveyor);
	loadTexture("build/brick.png", Type_t::brickWall);
	loadTexture("build/balloonButton.png", Type_t::balloonButton);
	loadTexture("build/mouseEngine.png", Type_t::mouseEngine);
	loadTexture("build/trampolineOPT1.png", Type_t::trampoline);
	loadTexture("build/scissors.png", Type_t::scissors); 
	loadTexture("build/pipeWall.png", Type_t::pipeWall); 
	loadTexture("build/fancyWall.png", Type_t::fancyWall); 
	loadTexture("build/basketButton.png", Type_t::basketButton);
	loadTexture("build/baseButton.png", Type_t::baseButton);
	loadTexture("build/bowlingButton.png", Type_t::bowlingButton);
	loadTexture("build/conveyorButton.png", Type_t::conveyorButton);
	loadTexture("build/brickButton.png", Type_t::brickWallButton);
	loadTexture("build/resizeButton.png", Type_t::resizeButton);
	loadTexture("build/rotateButton.png", Type_t::rotateButton);
	loadTexture("build/mouseEngineButton.png", Type_t::mouseEngineButton);
	loadTexture("build/beltButton.png", Type_t::beltButton);
	loadTexture("build/trampolineButton.png", Type_t::trampolineButton);
	loadTexture("build/scissorsButton.png", Type_t::scissorsButton);
	loadTexture("build/pipeWallButton.png", Type_t::pipeWallButton); 
	loadTexture("build/fancyWallButton.png", Type_t::fancyWallButton); 
	loadTexture("build/engineConectButton.png", Type_t::connectButton);
  	loadTexture("build/arrowLButton.png", Type_t::arrowLButton);
	loadTexture("build/arrowRButton.png", Type_t::arrowRButton);
  	loadTexture("build/advanceButton.png", Type_t::advanceButton);
	loadTexture("build/puzzleComplete.png", Type_t::puzzleComplete);
	loadTexture("build/replayButton.png", Type_t::replayButton);
	loadTexture("build/save.png", Type_t::save);
	loadTexture("build/build.png", Type_t::build);
	loadTexture("build/play.png", Type_t::play);
	loadTexture("build/exit.png", Type_t::exitButton);
	loadTexture("build/playmenu.png", Type_t::startButton);
	loadTexture("build/bomb.png", Type_t::reset);
	loadTexture("build/sound.png", Type_t::sound);
	loadTexture("build/choseLevelMenu.png", Type_t::choseLevelMenu);
	loadTexture("build/playButton.png", Type_t::playButton);
	loadTexture("build/up.png", Type_t::upButton);
	loadTexture("build/down.png", Type_t::downButton);
	loadTexture("build/up.png", Type_t::upSound);
	loadTexture("build/down.png", Type_t::downSound);
	loadTexture("build/menuBackground.png", Type_t::menuBackground);
	loadTexture("build/frame.png", Type_t::frame);
 	loadTexture("build/chooseLevelButton.png", Type_t::choseLevel);
 	loadTexture("build/numbers.png", Type_t::numbers);
 	loadTexture("build/score.png", Type_t::score);
	loadTexture("build/1px.png", Type_t::onePixel);


	//---------- font ---win------
	//loadFont("kongtext.ttf", Font::kongtext);
    //loadFont("Courier New.ttf", Font::CourierNew);
	//---------- font ---mac------
	loadFont("build/kongtext.ttf", Font::kongtext);
	loadFont("build/Courier New.ttf", Font::CourierNew);


	//---------- sound -------win---
	// loadSound("menu.ogg", Sound::menu);
	// loadSound("background.ogg", Sound::background);
	// loadSound("build.ogg", Sound::build);
	// loadSound("trampoline.ogg", Sound::trampoline);
	// loadSound("engine.ogg", Sound::engine);
	// loadSound("balloon.ogg", Sound::balloon);
	//---------- sound -------mac---
	loadSound("build/menu.ogg", Sound::menu);
	loadSound("build/background.ogg", Sound::background);
	loadSound("build/build.ogg", Sound::build);
	loadSound("build/trampoline.ogg", Sound::trampoline);
	loadSound("build/engine.ogg", Sound::engine);
	loadSound("build/balloon.ogg", Sound::balloon);

	//----levels-path----win
	//m_path = "levels.txt";
	//----levels-path----mac
	m_path = "build/levels.txt";

	setSounds();
}

void ResourceManager::loadTexture(const std::string path, const Type_t name)
{
	sf::Texture temp;
	temp.loadFromFile(path);
	m_textures[name] = temp;
}

void ResourceManager::loadFont(const std::string path, const Font name)
{
	sf::Font temp;
	temp.loadFromFile(path);
	m_fonts[name] = temp;
}

void ResourceManager::loadSound(const std::string path, const Sound name)
{
	sf::SoundBuffer temp;
	temp.loadFromFile(path);
	m_soundBuff[name] = temp;
}

void ResourceManager::setSounds()
{
	for(int i = 0; i < NUM_OF_SOUNDS; i++)
	{
		m_sounds.push_back(sf::Sound(getSound(Sound(i))));
		m_sounds[i].setVolume(m_volume);
		if (i<(int)Sound::trampoline)
			m_sounds[i].setLoop(true);
	}

}

void ResourceManager::stopAllSongs()
{
	for (auto& sound:m_sounds)
		sound.stop();
}

void ResourceManager::playSong()
{
	stopAllSongs();
	m_sounds[int(m_playing)].play();
}

void ResourceManager::playSFXtramp()
{
	m_sounds[(int)Sound::trampoline].play();
}

void ResourceManager::playSFXballoon()
{
	m_sounds[(int)Sound::balloon].play();
}

void ResourceManager::playSFXengine()
{
	if (m_sounds[(int)Sound::engine].getStatus() == false)
		m_sounds[(int)Sound::engine].play();
}

void ResourceManager::stopSFXengine()
{
	m_sounds[(int)Sound::engine].stop();
}

void ResourceManager::setSong(const int song)
{
	m_playing = (Sound)song;
	playSong();
}

void ResourceManager::volUp()
{
	if(m_volume+ VOL_STEP <VOL_MAX)
		m_volume += VOL_STEP;
	setVolume();
}

void ResourceManager::volDown()
{
	if(m_volume-VOL_STEP >= VOL_MIN)
		m_volume -= VOL_STEP;
	setVolume();
}

void ResourceManager::setVolume()
{
	for (auto& sound:m_sounds)
		sound.setVolume(m_volume);
}
