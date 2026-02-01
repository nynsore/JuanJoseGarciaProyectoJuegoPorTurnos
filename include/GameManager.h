#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include <unordered_map>
#include "TurnBasedSystem.h"

enum class GameState {
	MENU,
	COMBAT
};

class GameManager {
	
private:
	static GameManager* instance;
	GameState currentState;
	TurnBasedSystem*  turnSystem = nullptr;
	Enemy* playerTarget = nullptr;
	int targetIndex = 0;

	sf::RenderWindow window;
	sf::Font font;
	sf::Text textIntro;
	sf::Text textSelect;
	std::vector<sf::Text> enemyText;
	std::vector<std::string> enemyOptions = { "Bomb","Cactuar","Sahagin" };
	std::vector<std::string> playerNames = { "Tidus","Yuna","Auron" };
	const float distanceOptions = 150.0f;
	std::vector<Enemy*> selectedEenemies;
	std::vector<Player*> gamePlayers;
	std::map<std::string, Stats> charactersStatsDir;
	std::map<std::string, std::string> enemyTextureDir;
	sf::RectangleShape currentEnemy;
	const float marginX = 30.0f;
	const float marginY = 25.0f;
	
	int currentIndex;
	int enemiesLeft = 5;
	float startEnenmyPosY = 150.0f;

	sf::Texture backgroundTexture;
	sf::Sprite background;

	bool waitingPlayer = false;
	
	GameManager();
	
	void Render();
	void Update();
	void Inputs();

	void CreateMenuText();

	void LoadCharacters();
	void CreateEnemy(const std::string& );
	void CreatePlayers(const std::string&);
	void PositionEnemy();
	void UpdateCombat();

public:
	static GameManager* GetInstance();
	void GameStart();
};