#include <SFML/Graphics.hpp>
#include <vector>
#include <set>
#include <iostream>
#include <time.h>

using namespace sf;


const int WIDTH=720, HEIGHT=480;
const int NOT_TAKEN=0, TAKEN_BY_PLAYER=1, TAKEN_BY_NPC=2;

const Vector2f v2f(30.0, 30.0);
Font font;

int coins=8;

class Coin{
public:
	int x, y, value;
	int state=NOT_TAKEN;
	Text text;
	RectangleShape r;
	Coin(int x, int y, int value): x(x), y(y), value(value) {
		r = RectangleShape(v2f);
		r.setPosition(x, y);
		//std::string number=std::to_string(value);
		std::string number = "AA";
		text = Text(number, font, 25);
		text.setPosition(x+5, y-5);
		text.setFillColor(Color(0,255, 255));
	}

	void take(int player){
		state=player;
	}

};

int main(int argc, char* argv[]){
	// Pre-processing
	font.loadFromFile("Sansation_Regular.ttf");
	std::vector<int> player_coins;
	std::vector<int> npc_coins;

	// Arguments
	srand(time(NULL));
	if(argc >= 2){
		try{
			int s = atoi(argv[1]);
			if(s&1){
				std::cout << "Numer of coins must be an even number." << std::endl;
			}else if(s>=8 and s<=32){
				coins = s;
			}else{
				std::cout << "Numer of coins must be between 8 and 32. Using default." << std::endl;
			}
		}
		catch(...){
			std::cout << "Invalid argument was passed, number of coins must be an integer. Using default." << std::endl;
		}
	}
	
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	//RenderWindow window(VideoMode(WIDTH, HEIGHT), "Can you win?", Style::Default, settings);
	RenderWindow window(VideoMode(WIDTH, HEIGHT), "Can you win?");
	
	Image icon;
	icon.loadFromFile("icon.png");
	window.setIcon(641, 617, icon.getPixelsPtr());
	
	auto desktop = VideoMode::getDesktopMode();
	Vector2i v2i(desktop.width/2 - window.getSize().x/2, desktop.height/2 - window.getSize().y/2);
	window.setPosition(v2i);
	window.setFramerateLimit(60);

	Texture texture;
	texture.loadFromFile("background.jpg");
	Sprite sBackground(texture);
	
	Sprite sprite;
	RenderTexture t;
	t.create(WIDTH, HEIGHT);
	t.setSmooth(true);
	sprite.setTexture(t.getTexture());
	t.clear();
	t.draw(sBackground);
	
	
	Coin test(200, 200, 9);
	test.take(TAKEN_BY_PLAYER);

	window.draw(test.r);
	window.draw(test.text);

	Text text("YOU LOSE!", font, 35);
	text.setPosition(WIDTH/2-80, 20);
	window.draw(text);
	bool win=false;
	


	while(window.isOpen()){
		Event e;
		while(window.pollEvent(e)){
			if(e.type == Event::Closed){
				window.close();
			}else if(e.type == Event::KeyPressed){
			
			}
			
			
		}
		
		window.clear();
		window.draw(sprite);
		window.display();
	
	}

	return 0;
}
