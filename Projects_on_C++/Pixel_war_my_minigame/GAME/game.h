#include<map>
#include<string>
#include<sstream>
#include <vector>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>

#include"Player.h"
#include"Bullet.h"
#include"Enemy02.h"

class Game
{
private:
	sf::RenderWindow* Menuwindow;
	sf::Text StartThegameText;
	sf::Text GameNameText;
	sf::Sprite MenuBackground;
	sf::Texture MenuBackgroundTex;

	sf::RenderWindow* window;
	
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;

	sf::Font font;//רנטפע
	sf::Text pointText;
	sf::Text gameOverText;

	sf::Texture worldBackgroundTex;
	sf::Sprite worldBackground;

	unsigned points;

	Player* player;

	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy02*> enemies;

	void initMenuWindow();
	void initMenuGUI();
	void initBackgroundMenu();

	void initWindow();
	void initTextures();
	void initGUI();
	void initWorld();
	void initSystems();

	void initPlayer();
	void initEnemies();

public:
	Game();
	virtual ~Game();

	void run();

	void initMenu();
	void updateMenuPollEvents();
	void renderMenu();

	void updatePollEvents();
	void updateInput();
	void updateGUI();
	void updateWorld();
	void updateCollision();
	void updateBullets();
	void updateEnemies();
	void updateCombat();
	void update();
	
	void renderGUI();
	void renderWorld();
	void render();
};
