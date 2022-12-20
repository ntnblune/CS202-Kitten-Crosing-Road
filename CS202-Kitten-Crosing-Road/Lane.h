#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include "Object.h"
#include "Vehicle.h"
#include "Light.h"
#include "Player.h"

class Road
{
public:
	Road() = default;
	Road(RenderWindow& window, int dir, Texture& texture, int x_coor, int y_coor, int unit);
	Road(RenderWindow& window, int dir, Texture& texture, int x_coor, int y_coor, int unit, float initVelo, float limVelo);
	Road(const Road& road);

	void addLight(RenderWindow& window, vector<Texture>& texture, int x_coor, int y_coor, int unit);
	bool insideView();
	void draw();
	void handleEvent();
	bool isCollided(Player& mPlayer);
	int getPosition();
private:

	int dir; // 0: left to right, 1: right to left
	int y_coor;
	vector<Vehicle*>	listVehicle;
	vector<Light>		listLight;
};

class RailWay
{
public:
	RailWay()
	{

	}
private:
};