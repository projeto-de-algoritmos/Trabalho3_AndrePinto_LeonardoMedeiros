#include <SFML/Graphics.hpp>
#include <vector>
#include <set>
#include <iostream>
#include <time.h>

using namespace sf;


const int WIDTH=720, HEIGHT=480;
const int NOT_TAKEN=0, TAKEN_BY_PLAYER=1, TAKEN_BY_NPC=2;
Font font;

const Vector2f v2f(30.0, 30.0);

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
		r.setFillColor(Color::Transparent);
		r.setOutlineColor(Color(0, 0, 0));
		r.setOutlineThickness(2);
		std::string number=std::to_string(value);
		text = Text(number, font, 19);
		text.setPosition(x+3, y);
		text.setFillColor(Color(0,255, 250));
	}

	void take(int player){
		state=player;
		if(state == TAKEN_BY_PLAYER){
			r.setFillColor(Color(1, 1, 200));
			r.setOutlineThickness(2);
		}else{
			r.setFillColor(Color(1, 120, 30));
			r.setOutlineThickness(2);
		}
	}


};

int main(int argc, char* argv[]){
	// Pre-processing
	font.loadFromFile("Sansation_Regular.ttf");
	std::vector<int> player_coins;
	std::vector<int> npc_coins;

	srand(time(NULL));
	// Arguments
	if(argc >= 2){
		try{
			std::cout << "\n" << argv[1] << '\n' ;
			int s = atoi(argv[1]);
			if(s&1){
				std::cout << "Numer of coins must be an even number." << std::endl;
			}else if(s>=8 and s<=14){
				coins = s;
			}else{
				std::cout << "Numer of coins must be between 8 and 14. Using default." << std::endl;
			}
		}
		catch(...){
			std::cout << "Invalid argument was passed, number of coins must be an integer. Using default." << std::endl;
		}
	}
	
	RenderWindow window(VideoMode(WIDTH, HEIGHT), "Can you win?");
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
	window.draw(sprite);
	window.display();

	
	Coin test(20, 300, 12);

	window.draw(sprite);
	window.display();
	int init_x = 20 + ((14-coins)/2)*50;
	int init_y = 100;
	std::vector<Coin> v_coins;
	for(int i=0; i<coins; i++){
		// incremento entre um bloco e outro = 50  (30 + 20)
		Coin c(init_x+i*50, init_y, (rand()%80)+20);
		v_coins.push_back(c);
		t.draw(c.r);
		t.display();
		t.draw(c.text);
		t.display();

		window.draw(sprite);
		window.display();
	}
	
	Text text("YOU LOSE!", font, 35);
	text.setPosition(WIDTH/2-80, 20);
	text.setFillColor(Color(250, 30, 30));

	int pick;

	int sum_even=0;
	for(int i=0; i<v_coins.size(); i+=2){
		sum_even+=v_coins[i].value;
	}

	int sum_odd=0;
	for(int i=0; i<v_coins.size(); i+=2){
		sum_odd+=v_coins[i].value;
	}

	if(sum_even==sum_odd){
		v_coins[0].value++;
		pick=0;
	}else if(sum_even>sum_odd){
		pick=0;
	}else{
		pick=1;
	}

	int left=0, right=coins-1;
	auto cl = v_coins[left];
	cl.r.setOutlineThickness(4);
	t.draw(cl.r);
	t.display();
	t.draw(cl.text);
	t.display();

	auto cr = v_coins[right];
	cr.r.setOutlineThickness(4);
	t.draw(cr.r);
	t.display();
	t.draw(cr.text);
	t.display();

	while(window.isOpen()){
		Event e;
		while(window.pollEvent(e)){
			if(e.type == Event::Closed){
				window.close();
			}
		}
		
		window.clear();
		window.draw(sprite);
		window.display();
	}

	return 0;
}
