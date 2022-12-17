#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include "Object.h"

class Button : public Object {
public:
	Button(RenderWindow& mWindow, Texture& texture, int x_coor, int y_coor, bool setCenter);

};

class Scene : public ListTextures {
public:
	Scene(RenderWindow& mWindow);

	virtual void handleEvent(Event& event, vector<Scene*>& scene, Vector2f mousePosition) = 0;
	virtual void draw();
protected:
	RenderWindow& window;
	vector<Button*> buttons;
	vector<Sprite> background;
};

class Menu : public Scene {
public:
	Menu(RenderWindow& mWindow);

	void handleEvent(Event& event, vector<Scene*>& scene, Vector2f mousePosition) override;
	void draw() override;
};

class Instruction : public Scene {
public:
	Instruction(RenderWindow& mWindow);

	void handleEvent(Event& event, vector<Scene*>& scene, Vector2f mousePosition) override;
	void draw() override;
};