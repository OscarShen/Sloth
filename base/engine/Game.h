#pragma once
#ifndef SLOTH_GAME_H_
#define SLOTH_GAME_H_

class Game {
public:
	Game();
	void input();
	void update();
	void render();

	bool shouldGameClose() const;
	void setShouldClose(bool shouldClose);
private:
	bool shouldClose;
};

#endif // !SLOTH_GAME_H_
