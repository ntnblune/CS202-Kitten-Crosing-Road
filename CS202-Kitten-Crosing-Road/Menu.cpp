#include "Menu.h"
#include "SFML/Audio.hpp"

static Music music[2] = {};

Scene::Scene(RenderWindow& mWindow) : window(mWindow)
{
	sceneName = MenuList::Menu;
}

Scene::~Scene()
{

}

void Scene::draw(const Vector2f& mouse)
{
	// draw 
	for (int i = 0; i < background.size(); ++i)
	{
		background[i].draw();
	}
	for (int i = 0; i < buttons.size(); ++i)
	{
		buttons[i].draw(mouse, false);
	}
}

void Scene::getName()
{
	cerr << (int)sceneName << endl;
}


Menu::Menu(RenderWindow& mWindow) : Scene(mWindow)
{
	sceneName = MenuList::Menu;

	// Background
	Object sprite(window, commonAsset[0], 0, 0);
	Object menuboard(window, commonAsset[2], 59, 40);
	sprite.setPos(window.getView());
	menuboard.setPos(window.getView());
	background.push_back(sprite);
	background.push_back(menuboard);

	// Button
	for (int i = 0; i < menuTexture[sceneName].size(); ++i)
	{
		SystemButton button(window, menuTexture[sceneName][i].first, menuTexture[sceneName][i].second,  224, (50 + 17 * i), true);
		buttons.push_back(button);
	}
}

Menu::~Menu()
{

}

int Menu::handleEvent(const Event& event, vector<Scene*>& scene, const Vector2f& mousePosition)
{
	if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
	{
		for (int i = 0; i < buttons.size(); ++i)
		{
			if (buttons[i].isHere(mousePosition))
			{
				if (i == 2)
				{
					Scene* settings = new Settings(window);
					scene.push_back(settings);
				}
				else if (i == 3)
				{
					Scene* instruction = new Instruction(window);
					scene.push_back(instruction);
				}
				else if (i == 5)
				{
					const_cast<Event&>(event).type = Event::Closed;
				}
				else
				{
					Scene* mode = new Mode(window);
					scene.push_back(mode);
					return -(i + 1);
				}
				break;
			}
		}
	}
	return 0;
}

void Menu::draw(const Vector2f& mouse)
{
	Scene::draw(mouse);
}

Mode::Mode(RenderWindow& mWindow) : Scene(mWindow)
{
	sceneName = MenuList::Mode;
	// Background
	Object grassBackground(window, commonAsset[1], 0, 0);
	Object modeBoard(window, commonAsset[3], 77, 51);
	grassBackground.setPos(window.getView());
	modeBoard.setPos(window.getView());
	background.push_back(grassBackground);
	background.push_back(modeBoard);

	// Button
	SystemButton backButton(window, commonAsset.back(), commonAsset.back(), 0, 0, false);
	buttons.push_back(backButton);
	for (int i = 0; i < menuTexture[sceneName].size(); ++i)
	{
		SystemButton button(window, menuTexture[sceneName][i].first, menuTexture[sceneName][i].second, 224, (65 + 25 * i), true);
		buttons.push_back(button);
	}
}

Mode::~Mode()
{

}

int Mode::handleEvent(const Event& event, vector<Scene*>& scene, const Vector2f& mousePosition)
{
	if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
	{
		for (int i = 0; i < buttons.size(); ++i)
		{
			if (buttons[i].isHere(mousePosition))
			{
				if (i == 0)
				{
					scene.pop_back();
				}
				else if (i == 1)
				{
					cerr << "Classic Mode\n";
					//scene.pop_back();
					return 1;
				}
				else if (i == 2)
				{
					cerr << "Endless Mode\n";
					scene.pop_back();
					return 2;
				}
				break;
			}
		}
	}
	return 0;
}

void Mode::draw(const Vector2f& mouse)
{
	Scene::draw(mouse);
}

Settings::Settings(RenderWindow& mWindow) : Scene(mWindow)
{
	sceneName = MenuList::Settings;

	// Background
	Object grassBackground(window, commonAsset[1], 0, 0);
	Object settingsBoard(window, commonAsset[5], 42, 52);
	grassBackground.setPos(window.getView());
	settingsBoard.setPos(window.getView());
	background.push_back(grassBackground);
	background.push_back(settingsBoard);

	// Button
	SystemButton backButton(window, commonAsset.back(), commonAsset.back(), 0, 0, false);
	buttons.push_back(backButton);
	for (int i = 0; i < menuTexture[sceneName].size(); ++i)
	{
		SystemButton button(window, menuTexture[sceneName][i].first, menuTexture[sceneName][i].second, 224, (65 + 25 * i), true);
		buttons.push_back(button);
	}
}

Settings::~Settings()
{

}

int Settings::handleEvent(const Event& event, vector<Scene*>& scene, const Vector2f& mousePosition)
{
	if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
	{
		for (int i = 0; i < buttons.size(); ++i)
		{
			if (buttons[i].isHere(mousePosition))
			{
				if (i == 0)
				{
					scene.pop_back();
				}
				else if (i == 1)
				{
					Scene* soundSettings = new SoundSettings(window);
					scene.push_back(soundSettings);
				}
				else if (i == 2)
				{
					Scene* buttonSettings = new ButtonSettings(window);
					scene.push_back(buttonSettings);
				}
				break;
			}
		}
	}
	return 0;
}

void Settings::draw(const Vector2f& mouse)
{
	Scene::draw(mouse);
}

SoundSettings::SoundSettings(RenderWindow& mWindow) : Scene(mWindow)
{
	sceneName = MenuList::SoundSettings;

	// Background
	Object grassBackground(window, commonAsset[1], 0, 0);
	Object soundBoard(window, commonAsset[6], 42, 52);
	Object bgmText(window, menuTexture[sceneName][2].first, 62, 65);
	Object sfxText(window, menuTexture[sceneName][2].second, 62, 90);
	grassBackground.setPos(window.getView());
	soundBoard.setPos(window.getView());
	bgmText.setPos(window.getView());
	sfxText.setPos(window.getView());
	background.push_back(grassBackground);
	background.push_back(soundBoard);
	background.push_back(bgmText);
	background.push_back(sfxText);

	// Sound Bar
	soundBar.resize(2);
	for (int i = 0; i < 2; ++i)
	{
		Object blankBar(window, menuTexture[sceneName][3].first, 135, (64 + 25 * i));
		blankBar.setPos(window.getView());
		soundBar[i].push_back(blankBar);
		for (float f = 0; f < music[i].getVolume(); f += 25)
		{
			Object currentSound(window, menuTexture[sceneName][3].second, (135 + f / 5), (64 + 25 * i));
			currentSound.setPos(window.getView());
			soundBar[i].push_back(currentSound);
		}
	}

	// Button
	SystemButton backButton(window, commonAsset.back(), commonAsset.back(), 0, 0, false);
	buttons.push_back(backButton);
	for (int i = 0; i < 2; ++i)
	{
		SystemButton bgmButton(window, menuTexture[sceneName][i].first, menuTexture[sceneName][i].second, (122 + 37 * i), (68 - 2 * i), false);
		SystemButton sfxButton(window, menuTexture[sceneName][i].first, menuTexture[sceneName][i].second, (122 + 37 * i), (93 - 2 * i), false);
		buttons.push_back(bgmButton);
		buttons.push_back(sfxButton);
	}
}

SoundSettings::~SoundSettings()
{

}

int SoundSettings::handleEvent(const Event& event, vector<Scene*>& scene, const Vector2f& mousePosition)
{
	if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
	{
		for (int i = 0; i < buttons.size(); ++i)
		{
			if (buttons[i].isHere(mousePosition))
			{
				if (i == 0)
				{
					scene.pop_back();
				}
				else if (i < buttons.size() / 2 + 1 && music[i - 1].getVolume() > 0)
				{
					// Press the decrease-sound button
					soundBar[i - 1].pop_back();
					music[i - 1].setVolume(music[i - 1].getVolume() - 25);
				}
				else if (i > buttons.size() / 2 && music[i - 1 - buttons.size() / 2].getVolume() < 100)
				{
					// Press the increase-sound button
					Object currentSound(window, menuTexture[sceneName][3].second, (135 + music[i - 1 - buttons.size() / 2].getVolume() / 5), (64 + 25 * (i - 1 - buttons.size() / 2)));
					currentSound.setPos(window.getView());
					soundBar[i - 1 - buttons.size() / 2].push_back(currentSound);
					music[i - 1 - buttons.size() / 2].setVolume(music[i - 1 - buttons.size() / 2].getVolume() + 25);
				}
				break;
			}
		}
	}
	return 0;
}

void SoundSettings::draw(const Vector2f& mouse)
{
	Scene::draw(mouse);
	for (int i = 0; i < soundBar.size(); ++i)
	{
		for (int j = 0; j < soundBar[i].size(); ++j)
			soundBar[i][j].draw();
	}
}

ButtonSettings::ButtonSettings(RenderWindow& mWindow) : Scene(mWindow)
{
	sceneName = MenuList::ButtonSettings;

	// Background
	Object grassBackground(window, commonAsset[1], 0, 0);
	Object buttonSettingsBoard(window, commonAsset[7], 42, 37);
	grassBackground.setPos(window.getView());
	buttonSettingsBoard.setPos(window.getView());
	background.push_back(grassBackground);
	background.push_back(buttonSettingsBoard);

	// Button
	SystemButton backButton(window, commonAsset.back(), commonAsset.back(), 0, 0, false);
	buttons.push_back(backButton);
	for (int i = 0; i < menuTexture[sceneName].size(); ++i)
	{
		SystemButton button(window, menuTexture[sceneName][i].first, menuTexture[sceneName][i].second, 224, (50 + 25 * i), true);
		buttons.push_back(button);
	}
}

ButtonSettings::~ButtonSettings()
{

}

int ButtonSettings::handleEvent(const Event& event, vector<Scene*>& scene, const Vector2f& mousePosition)
{
	if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
	{
		for (int i = 0; i < buttons.size(); ++i)
		{
			if (buttons[i].isHere(mousePosition))
			{
				if (i == 0)
				{
					scene.pop_back();
				}
				break;
			}
		}
	}
	return 0;
}

void ButtonSettings::draw(const Vector2f& mouse)
{
	Scene::draw(mouse);
}

Instruction::Instruction(RenderWindow& mWindow) : Scene(mWindow)
{
	sceneName = MenuList::Instruction;

	// Initialize the number of instruction page
	pageIndex = 1;
	pageNum = 4;

	// Background
	Object grassBackground(window, commonAsset[1], 0, 0);
	Object instructionBoard(window, commonAsset[8], 5, 30);
	Object instruct(window, menuTexture[sceneName][pageIndex + 1].first, 13, 33);
	Object page(window, menuTexture[sceneName][pageIndex + 1].second, 102, 130);
	grassBackground.setPos(window.getView());
	instructionBoard.setPos(window.getView());
	instruct.setPos(window.getView());
	page.setPos(window.getView());
	background.push_back(grassBackground);
	background.push_back(instructionBoard);
	background.push_back(instruct);
	background.push_back(page);

	// Button
	SystemButton backButton(window, commonAsset.back(), commonAsset.back(), 0, 0, false);
	buttons.push_back(backButton);
	for (int i = 0; i < 2; ++i)
	{
		SystemButton button(window, menuTexture[sceneName][i].first, menuTexture[sceneName][i].second, (85 + 47 * i), 130, false);
		buttons.push_back(button);
	}
}

Instruction::~Instruction()
{

}

int Instruction::handleEvent(const Event& event, vector<Scene*>& scene, const Vector2f& mousePosition)
{
	if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
	{
		for (int i = 0; i < buttons.size(); ++i)
		{
			if (buttons[i].isHere(mousePosition))
			{
				if (i == 0)
				{
					scene.pop_back();
				}
				else if (i == 1 && pageIndex > 1)
				{
					--pageIndex;
					background.pop_back();
					background.pop_back();
					Object instruct(window, menuTexture[sceneName][pageIndex + 1].first, 13, 33);
					Object page(window, menuTexture[sceneName][pageIndex + 1].second, 102, 130);
					instruct.setPos(window.getView());
					page.setPos(window.getView());
					background.push_back(instruct);
					background.push_back(page);
				}
				else if (i == 2 && pageIndex < pageNum)
				{
					++pageIndex;
					background.pop_back();
					background.pop_back();
					Object instruct(window, menuTexture[sceneName][pageIndex + 1].first, 13, 33);
					Object page(window, menuTexture[sceneName][pageIndex + 1].second, 102, 130);
					instruct.setPos(window.getView());
					page.setPos(window.getView());
					background.push_back(instruct);
					background.push_back(page);
				}
				break;
			}
		}
	}
	return 0;
}

void Instruction::draw(const Vector2f& mouse)
{
	Scene::draw(mouse);
}