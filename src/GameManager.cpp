#include "GameManager.h"

GameManager* GameManager::instance = nullptr;

GameManager::GameManager() {
	window.create(sf::VideoMode(1200, 800),"TurnBasedGame");
	window.setFramerateLimit(60);
	currentState = GameState::MENU;
	currentIndex = 0;

	font.loadFromFile("../assets/font/arial.ttf");
	
	CreateMenuText();
	LoadCharacters();

	for (int i = 0; i < static_cast<int>(playerNames.size()); i++) {
		CreatePlayers(playerNames[i]);
	}

	backgroundTexture.loadFromFile("../assets/sprites/background.png");
	background.setTexture(backgroundTexture);
	background.setScale(static_cast<float>(window.getSize().x) / static_cast<float>(backgroundTexture.getSize().x), static_cast<float>(window.getSize().y) / static_cast<float>(backgroundTexture.getSize().y));
}

GameManager* GameManager::GetInstance() {
	if (instance == nullptr) {
		instance = new GameManager();
	}
	return instance;
}

void GameManager::GameStart() {
	while (window.isOpen()) {
		Render();
		Update();
		Inputs();
	}
}

void GameManager::Update() {
	switch (currentState)
	{
	case GameState::MENU:
		break;
	case GameState::COMBAT:
		UpdateCombat();
		break;
	}
}

void GameManager::Render() {
	window.clear(sf::Color::Black);

	if (currentState == GameState::MENU) {
		window.draw(textIntro);
		window.draw(textSelect);
		for (sf::Text enemyText : enemyText) {
			window.draw(enemyText);
		}
		window.draw(currentEnemy);
	}
	else if (currentState == GameState::COMBAT) {
		window.draw(background);
		for (Enemy* enemy : selectedEenemies) {
			enemy->SetSpriteScale(200.0f, 200.0f);
			enemy->DrawCharacter(window);
			enemy->DrawHealth(font,window);
		}
	}

	window.display();
}

void GameManager::Inputs() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}

		if (event.type == sf::Event::KeyPressed && currentState == GameState::MENU) {
			if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left) {
				currentIndex--;
				if (currentIndex < 0) currentIndex = static_cast<int>(enemyOptions.size()-1);
			}
			else if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) {
				currentIndex++;
				if (currentIndex > enemyOptions.size()-1) currentIndex = 0;
			}
			else if (event.key.code == sf::Keyboard::Space) {
				CreateEnemy(enemyOptions[currentIndex]);
				if (enemiesLeft > 0) enemiesLeft--;
				textSelect.setString("Seleciona un maximo de 5 enemigos usando el espacio: Quedan " + std::to_string(enemiesLeft));
			}
			else  if (event.key.code == sf::Keyboard::Enter && selectedEenemies.size() != 0) {
				currentState = GameState::COMBAT;
				turnSystem = new TurnBasedSystem(gamePlayers, selectedEenemies);
				PositionEnemy();
				turnSystem->StartTurn();
				playerTarget = selectedEenemies[0];
			}
			currentEnemy.setSize(sf::Vector2f(enemyText[currentIndex].getLocalBounds().width + (marginX * 2), enemyText[currentIndex].getLocalBounds().height + (marginY * 2)));
			currentEnemy.setPosition(enemyText[currentIndex].getPosition() - sf::Vector2f(marginX, marginY));
		}
		else if (event.type == sf::Event::KeyPressed && currentState == GameState::COMBAT && waitingPlayer) {
			if (event.key.code == sf::Keyboard::Space) {
				turnSystem->GetCurrentCharTurn()->Attack(turnSystem->CalculateAttackDamage(turnSystem->GetCurrentCharTurn(), selectedEenemies[targetIndex]), selectedEenemies[targetIndex]);
			}
			if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left) {
				targetIndex--;
				if (targetIndex < 0) targetIndex = static_cast<int>(selectedEenemies.size() - 1);
			}
			else if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) {
				targetIndex++;
				if (targetIndex > static_cast<int>(selectedEenemies.size() - 1)) targetIndex = 0;
			}
		}
	}
}

void GameManager::CreateMenuText() {
	textIntro.setFont(font);
	textIntro.setCharacterSize(20);
	textIntro.setString("Crea un combate para empezar");
	textIntro.setPosition(450.0f, 25.0f);

	textSelect.setFont(font);
	textSelect.setCharacterSize(20);
	textSelect.setString("Seleciona un maximo de 5 enemigos usando el espacio: Quedan " + std::to_string(enemiesLeft));
	textSelect.setPosition(300.0f, 225.0f);

	enemyText.resize(enemyOptions.size());
	for (int i = 0; i < enemyOptions.size(); i++) {
		enemyText[i].setFont(font);
		enemyText[i].setCharacterSize(20);
		enemyText[i].setString(enemyOptions[i]);
		enemyText[i].setPosition(400.0f + distanceOptions * i, 350.0f);
	}

	currentEnemy.setSize(sf::Vector2f(enemyText[currentIndex].getLocalBounds().width + (marginX*2) , enemyText[currentIndex].getLocalBounds().height + (marginY * 2)));
	currentEnemy.setFillColor(sf::Color::Transparent);
	currentEnemy.setOutlineColor(sf::Color::Yellow);
	currentEnemy.setOutlineThickness(1.0f);
	currentEnemy.setPosition(enemyText[currentIndex].getPosition() - sf::Vector2f(marginX, marginY));
}

void GameManager::LoadCharacters() {
	charactersStatsDir["Bomb"] = Stats(100,25,3.0f,5.0f,10.0f,15.0f,3.0f,0,0.1f,0.9f);
	enemyTextureDir["Bomb"] = "../assets/sprites/bombEnemy.png";
	charactersStatsDir["Cactuar"] = Stats(200, 0, 20.0f, 2.0f, 0.0f, 2.0f, 10.0f, 25, 0.4f, 0.7f);
	enemyTextureDir["Cactuar"] = "../assets/sprites/cactuarEnemy.png";
	charactersStatsDir["Sahagin"] = Stats(35, 10, 8.0f, 3.0f, 3.0f, 3.0f, 5.0f, 10, 0.2f, 0.8f);
	enemyTextureDir["Sahagin"] = "../assets/sprites/sahaginEenemy.png";

	charactersStatsDir["Tidus"] = Stats(325, 40, 8.0f, 8.0f, 4.0f, 5.0f, 12.0f, 15, 0.2f, 0.8f);
	charactersStatsDir["Yuna"] = Stats(245, 72, 3.0f, 4.0f, 10.0f, 14.0f, 8.0f, 15, 0.1f, 0.7f);
	charactersStatsDir["Auron"] = Stats(450, 24, 12.0f, 11.0f, 1.0f, 3.0f, 7.0f, 15, 0.1f, 0.7f);
}

void GameManager::CreateEnemy(const std::string& enemyName) {
	if (charactersStatsDir.count(enemyName) == 0) return;

	Enemy* enemy = new Enemy(enemyName, charactersStatsDir[enemyName], enemyTextureDir[enemyName], sf::Vector2f(0.0f, 0.0f));
	selectedEenemies.push_back(enemy);
}

void GameManager::CreatePlayers(const std::string& playerName) {
	if (charactersStatsDir.count(playerName) == 0) return;

	Player* player = new Player(playerName, charactersStatsDir[playerName],"", sf::Vector2f(0.0f, 0.0f));
	gamePlayers.push_back(player);
}

void GameManager::PositionEnemy() {
	float startX = (window.getSize().x - (static_cast<int>(selectedEenemies.size() * 100.f + (static_cast<int>(selectedEenemies.size() -1 ) * 120.0f)))) / 2.0f;
	for (int i = 0; i < static_cast<int>(selectedEenemies.size()); i++) {
		selectedEenemies[i]->SetPosition(sf::Vector2f(startX + (100.0f + 120.0f) * i, startEnenmyPosY));
	}
}

void GameManager::UpdateCombat() {
	if (!waitingPlayer) return;

	Character* next = turnSystem->WhoIsNext();
	if (next != nullptr) {
		if (dynamic_cast<Player*>(next)) { waitingPlayer = true; }
		else {
			next->ConsumeTurn();
		}
	}else if (next == nullptr) {
		turnSystem->StartTurn();
	}
}