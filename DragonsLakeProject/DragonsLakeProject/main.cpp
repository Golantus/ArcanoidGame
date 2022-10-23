#include "header.h"

/* Test Framework realization */
class MyFramework : public Framework {
private:
	int scr_width, scr_height;
	bool fullscreen;
	double proportionX;
	double proportionY;

	double timer;
	double movementTimer; 
	double buffTimer;
	double randomTimeNumber;

	bool hasWon;
	bool hasLost;
	bool myExit;
	bool readyToWin;
	int lives;
	
	Brick *brickArray[BRICKS_COUNT];
	Ball *ball[MAX_BALLS_COUNT];
	Platform *platform;
	Buff *buff1;
	Buff *buff2;
	Actor *coursor;
	Actor *loseScreen;
	Actor *wonScreen;
	Sprite *heart;
public:
	
	MyFramework(int width, int height, bool fullscreen) {
		this->scr_width = width;
		this->scr_height = height;
		this->fullscreen = fullscreen;
		proportionX = width / 16;
		proportionY = height / 9;
	}

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		width = this->scr_width;
		height = this->scr_height;
		fullscreen = this->fullscreen;
	}	

	virtual bool Init() {
		showCursor(false);

		movementTimer = 0;
		buffTimer = 0;
		hasWon = false;
		hasLost = false;
		lives = 0;
		readyToWin = 0;
		myExit = 0;


		//Actor(x, y) constructor and actor.set_sprite(path, w, h)
		platform = new Platform(scr_width / 2 - proportionX, scr_height - proportionY);
		if (!platform->set_sprite("data/50-Breakout-Tiles.png", proportionX * 2, proportionY / 2))
			return 0;

		for (int i = 0; i < MAX_BALLS_COUNT; i++)
			if (i > 0)
				ball[i] = nullptr;
		
		if (!createBall(scr_width / 2 - proportionX / 6, scr_height - proportionY * 1.35, &ball[0]))
			return 0;
		
		coursor = new Actor(100,100);
		if (!coursor->set_sprite("data/59-Breakout-Tiles.png", proportionX / 2, proportionY / 2))
			return 0;

		loseScreen = new Actor(0, 0);
		if (!loseScreen->set_sprite("data/youlost.png", scr_width, scr_height))
			return 0;

		wonScreen = new Actor(0, 0);
		if (!wonScreen->set_sprite("data/youwon.png", scr_width, scr_height))
			return 0;

		heart = createSprite("data/60-Breakout-Tiles.png");
		if (!heart)
			return 0;
		setSpriteSize(heart, proportionY/2, proportionY/2);

		if (!initBlockArray())
			return 0;

		buff1 = nullptr;
		buff2 = nullptr;

		return true;
	}

	int initBlockArray() {
		for (int i = 0, rows = 1, cols = 1; i < BRICKS_COUNT; i++, cols++) {
			bool isRed;
			if (getRandomNumber(1, 100) > 90) //chance of spawning red brick
				isRed = true;
			else
				isRed = false;
			brickArray[i] = new Brick(cols * proportionX, rows * proportionY * 1.25, isRed);
			if (isRed) {
				if (!brickArray[i]->set_sprite("data/07-Breakout-Tiles.png", proportionX, proportionY / 2))
					return 0;
			}
			else {
				if (!brickArray[i]->set_sprite("data/01-Breakout-Tiles.png", proportionX, proportionY / 2))
					return 0;
			}
			if (cols % 14 == 0) {
				cols = 0;
				rows += 1;
			}
		}
		return 1;
	}

	int createBall(int posX, int posY, Ball **ball) {
		*ball = new Ball(posX, posY, 3);
		if (!(*ball)->set_sprite("data/63-Breakout-Tiles.png", proportionX / 3, proportionY / 3))
			return 0;
		return 1;
	}

	virtual void Close() {
		for (int i = 0, j = 0; i < BRICKS_COUNT; i++, j++) 
			delete(brickArray[i]);
		delete(platform);
		delete(coursor);
		if (buff1)
			delete(buff1);
		if (buff2)
			delete(buff2);
		delete(wonScreen);
		delete(loseScreen);
		for (int i = 0; i < MAX_BALLS_COUNT; i++) {
			if (ball[i])
				delete(ball[i]);
		}
		destroySprite(heart);
	}

	virtual bool Tick() {

		if (myExit)
			return 1;


		double lastTime = timer;
		timer = getTickCount() / 1000.0;
		movementTimer += timer - lastTime;


		if (hasLost) {
			loseScreen->draw_sprite();
		}
		else if (hasWon) {
			wonScreen->draw_sprite();
		}
		else {

			if (randomTimeNumber == 0) {
				randomTimeNumber = getRandomNumber(1000, 5000) / 1000;
			}
			//buffs spawn
			if (buffTimer > randomTimeNumber) {
				if (!buff1) {
					if (!buffSetUp(&buff1))
						return 0;
				}
				else if (!buff2) {
					if (!buffSetUp(&buff2))
						return 0;
				}
				buffTimer = 0;
				randomTimeNumber = 0;
			}


			if (movementTimer >= 0.009) {
				bool all_lost = true;
				bool onplatform = true;
				for (int i = 0; i < MAX_BALLS_COUNT; i++) {
					if (ball[i] != nullptr) {
						if (!ball[i]->getOnPlatform()) {
							onplatform = false;
							ball[i]->move();
							int collided = check_ball_collisions(ball[i]);
							if (collided == 1) {
								ball[i]->move();
								all_lost = false;
							}
							else if (collided == 0)
								all_lost = false;
							else if (collided == -1) {
								delete(ball[i]);
								ball[i] = nullptr;
							}
						}
						else
							all_lost = false;
					}
				}
				if (!onplatform)
					buffTimer += timer - lastTime;
				if (all_lost)
					restart();
				if (buff1)
					buffMovement(&buff1);
				if (buff2)
					buffMovement(&buff2);
				movementTimer -= 0.009;
			}


			bool anyBricks = false;
			//drawing
			drawTestBackground();
			for (int i = 0; i < lives; i++)
				drawSprite(heart, i * proportionY/2, 0);
			for (int i = 0; i < BRICKS_COUNT; i++) {
				if (!brickArray[i]->getDestroyed()) {
					brickArray[i]->draw_sprite();
					anyBricks = true;
				}
			}
			if (!anyBricks)
				readyToWin = true;
			platform->draw_sprite();
			for (int i = 0; i < MAX_BALLS_COUNT; i++)
				if(ball[i])
					ball[i]->draw_sprite();
			if (buff1)
				buff1->draw_sprite();
			if (buff2)
				buff2->draw_sprite();
		}
		coursor->draw_sprite();

		return false;
	}

	int check_ball_collisions(Ball* ball) { //returns 0 if no collision;   1 if collided with something;  -1 if ball lost
		int collided = 0;

		//walls collision
		if (ball->getX() < 0) {
			ball->setX(0);
			ball->changeDX();
			ball->move();
			return 1;
		}
		else if (ball->getRigthBorder() > scr_width) {
			ball->setX(scr_width - ball->getWidth());
			ball->changeDX();
			ball->move();
			return 1;
		}
		if (ball->getY() < 0) {
			ball->setY(0);
			ball->changeDY();
			ball->move();
			return 1;
		}
		else if (ball->getLowerBorder() > scr_height) {
			ball->setY(scr_height - ball->getHeight() - 10);
			ball->changeDY();
			ball->move();
			return -1;
		}

		//platform collision
		collided = ball->blocksCollision(platform);
		if (collided) {
			ball->changeSpeed(1);
			if (readyToWin)
				hasWon = true;
			return collided;
		}

		//bricks collision
		for (int i = 0; i < BRICKS_COUNT; i++) {
			if (brickArray[i]->getDestroyed())
				continue;
			collided = ball->blocksCollision(brickArray[i]);
			if (collided) {
				if (brickArray[i]->getIsRed()) { //check if player can destroy redBrick
					bool onlyReds = 1;
					for (int j = 0; j < BRICKS_COUNT; j++) {
						if (j == i || brickArray[j]->getDestroyed())
							continue;
						if (!brickArray[j]->getIsRed()) {
							onlyReds = 0;
							break;
						}
					}
					if (onlyReds) {
						brickArray[i]->setDestroyed(true);
						ball->changeSpeed(0);
					}
				}
				else {
					brickArray[i]->setDestroyed(true);
					ball->changeSpeed(0);
				}
			}
			if (collided)
				break;
		}
		return collided;
	}

	int buffSetUp(Buff **buff) {
		buffList bufftype = static_cast<buffList>(getRandomNumber(DAMAGED, COUNT - 1));
		int randomX = getRandomNumber(proportionX, scr_width - proportionX);
		int randomY = getRandomNumber(0, proportionY*4);
		*buff = new Buff(randomX, randomY, bufftype, scr_height);
		switch (bufftype)
		{
		case DAMAGED:
			if (!(*buff)->set_sprite("data/61-Breakout-Tiles.png", proportionY, proportionY))
				return 0;
		break; 
		case HEALTH:
			if (!(*buff)->set_sprite("data/60-Breakout-Tiles.png", proportionY, proportionY))
				return 0;
			break;
		case SIZEUP:
			if (!(*buff)->set_sprite("data/47-Breakout-Tiles.png", proportionX, proportionY / 2))
				return 0; 
			break;
		case SIZEDOWN:
			if (!(*buff)->set_sprite("data/46-Breakout-Tiles.png", proportionX, proportionY / 2))
				return 0;
			break;
		case SPEEDUP:
			if (!(*buff)->set_sprite("data/42-Breakout-Tiles.png", proportionX, proportionY / 2))
				return 0;
			break;
		case SPEEDDOWN:
			if (!(*buff)->set_sprite("data/41-Breakout-Tiles.png", proportionX, proportionY / 2))
				return 0;
			break;
		case EXTRABALLS:
			if (!(*buff)->set_sprite("data/43-Breakout-Tiles.png", proportionX, proportionY / 2))
				return 0;
			break;
		default:
			break;
		}
		return 1;
	}

	void applyBuff(buffList bufftype) {
		int ballsToSpawn = 2;
		bool firstBall = true;
		switch (bufftype)
		{
		case DAMAGED:
			if (lives > 0)
				lives -=1;
			break;
		case HEALTH:
			if (lives < 3)
				lives += 1;
			break;
		case SIZEUP:
			platform->resetSize();
			platform->changeSize(proportionX/2, 0);
			break;
		case SIZEDOWN:
			platform->resetSize();
			platform->changeSize(-proportionX / 2, 0);
			break;
		case SPEEDUP:
			for (int i = 0; i < MAX_BALLS_COUNT; i++)
				if (ball[i])
					ball[i]->setBuffSpeed(0);
			break;
		case SPEEDDOWN:
			for (int i = 0; i < MAX_BALLS_COUNT; i++)
				if (ball[i])
					ball[i]->setBuffSpeed(1);
			break;
		case EXTRABALLS:

			int startX, startY;
			double startSpeed;
			for (int i = 0; i < MAX_BALLS_COUNT; i++) { //finding first existing ball
				if (ball[i] && firstBall) {
					startX = ball[i]->getX();
					startY = ball[i]->getY();
					startSpeed = ball[i]->getSpeed();
					firstBall = false;	
					break;
				}
			}
			for (int i = 0; i < MAX_BALLS_COUNT; i++) { //spawning two balls
				if (ballsToSpawn == 0)
					break;
				if (!ball[i] && !firstBall) {
					createBall(startX, startY, &ball[i]);
					ball[i]->setSpeed(startSpeed);
					int dX, dY;
					do
					{
						dX = getRandomNumber(-100, 100);
						dY = getRandomNumber(-100, 100);
					} while (abs(dX) - abs(dY) < 10); //check that the ball isn't going to OX or OY
					ball[i]->launch(dX, dY);
					ballsToSpawn -= 1;
				}
			}
			break;
		default:
			break;
		}
	}

	void buffMovement(Buff **buff) {
		if (*buff) {
			if (!(*buff)->fallDown()) {
				delete((*buff));
				(*buff) = nullptr;
				return;
			}
		}
		if ((*buff)->checkCollision(platform)) {
			applyBuff((*buff)->getBuffType());
			delete((*buff));
			(*buff) = nullptr;
			return;
		}
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {
		coursor->setX(x - coursor->getWidth() / 2);
		coursor->setY(y - coursor->getHeight() / 2);
	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {
		if (ball[0]) {
			if (ball[0]->getOnPlatform()) {
				if (button == FRMouseButton::LEFT) {
					if (coursor->getY() > ball[0]->getY())
						return;
					ball[0]->launch(coursor->getX() - ball[0]->getX(), ball[0]->getY() - coursor->getY());
				}

			}
		}
		if (hasLost || hasWon) {
			if (isReleased) {
				switch (button)
				{
				case FRMouseButton::LEFT:
					restart();
					break;
				case FRMouseButton::RIGHT:
					myExit = 1;
					break;
				default:
					break;
				}
			}
		}
	}

	void restart() {
		for (int i = 0; i < MAX_BALLS_COUNT; i++) {
			if (ball[i]) {
				delete(ball[i]);
				ball[i] = nullptr;
			}
		}
		if (buff1) {
			delete(buff1);
			buff1 = nullptr;
		}
		if (buff2) {
			delete(buff2);
			buff2 = nullptr;
		}
		createBall(scr_width / 2 - proportionX / 6, scr_height - proportionY * 1.35, &ball[0]);
		platform->resetSize();
		platform->reset();
		lives -= 1;
		if (lives < 0) {
			if (!hasLost && !hasWon) {
				hasLost = true;
				return;
			}
		}
		if (hasLost || hasWon) {
			lives = 0;
			for (int i = 0; i < BRICKS_COUNT; i++) {
				delete(brickArray[i]);
				brickArray[i] = nullptr;
			}
			initBlockArray();
			hasWon = 0;
			hasLost = 0;
			movementTimer = 0;
			buffTimer = 0;
			readyToWin = 0;
		}
	}

	virtual void onKeyPressed(FRKey k) {
		switch (k)
		{
		case FRKey::RIGHT:
			if (platform->getRigthBorder() >= scr_width)
				break;
			platform->changeX(platform->getWidth() / 2);
			if (ball[0]) {
				if (ball[0]->getOnPlatform())
					ball[0]->changeX(platform->getWidth() / 2);
			}
			break;
		case FRKey::LEFT:
			if (platform->getX() <= 0)
				break;
			platform->changeX(-platform->getWidth() / 2);
			if (ball[0]) {
				if (ball[0]->getOnPlatform())
					ball[0]->changeX(-platform->getWidth() / 2);
			}
			break;
		default:
			break;
		}
	}

	virtual void onKeyReleased(FRKey k) {
	}
	
	virtual const char* GetTitle() override {
		return "Arcanoid";
	}

	virtual ~MyFramework() {
		Close();
	}
};

int main(int argc, const char *argv[]) {
	//default settings
	srand(static_cast<unsigned int>(time(0)));
	int width = 800, height = 600;
	bool fullscreen = 0;
	screen_settings(&width, &height, &fullscreen, argc, argv);

	return run(new MyFramework(width, height, fullscreen));
}
