#pragma once
#ifdef _DEBUG  
#pragma comment(lib,"sfml-graphics-d.lib")  
#pragma comment(lib,"sfml-audio-d.lib")  
#pragma comment(lib,"sfml-system-d.lib")  
#pragma comment(lib,"sfml-window-d.lib")  
#pragma comment(lib,"sfml-network-d.lib")  
#else  
#pragma comment(lib,"sfml-graphics.lib")  
#pragma comment(lib,"sfml-audio.lib")  
#pragma comment(lib,"sfml-system.lib")  
#pragma comment(lib,"sfml-window.lib")  
#pragma comment(lib,"sfml-network.lib")  
#endif  

#include <iostream>
#include <random>
#include <memory>
#include <SFML/Graphics.hpp> 

// global access to window size
const int WINDOW_HEIGHT = 800;
const int WINDOW_WIDTH = 1200;

//global for PI
const float PI = 3.14159f;

//important reusable global functions
sf::Vector2f normalize(const sf::Vector2f& vec);
float getMagnitude(const sf::Vector2f& vec);
sf::Vector2f randomPosition(const sf::Vector2f& vec);

// static textures
static sf::Texture gruntTexture;
