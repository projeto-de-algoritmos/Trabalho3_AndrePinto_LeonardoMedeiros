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
		text.setFillColor(Color(0, 0, 0));
	}

	void take(int player){
		state=player;
		if(state == TAKEN_BY_PLAYER){
			r.setFillColor(Color(1, 1, 200));
			r.setOutlineThickness(2);
		}else{
			r.setFillColor(Color(231, 84, 128));
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

	int pick;

	int sum_even=0;
	for(int i=0; i<(int)v_coins.size(); i+=2){
		sum_even+=v_coins[i].value;
	}

	int sum_odd=0;
	for(int i=1; i<(int)v_coins.size(); i+=2){
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


	int player_amount=0;
	int npc_amount=0;

	std::string s_player="Player amount:\n";
	Text text_player(s_player+"0", font, 25);
	text_player.setPosition(10, HEIGHT-80);
	text_player.setFillColor(Color(0, 0, 0));
	t.draw(text_player);
	t.display();

	std::string s_npc="BOT amount:\n";
	Text text_npc(s_npc, font, 25);
	text_npc.setPosition(WIDTH-180, HEIGHT-80);
	text_npc.setFillColor(Color(0, 0, 0));
	t.draw(text_npc);
	t.display();

	RectangleShape rwhite(v2f);
	rwhite.setOutlineThickness(4);
	rwhite.setOutlineColor(Color(255, 255, 255));

	// NPC picks one:
	if(pick){
		if(left&1){
			//take left
			auto co = v_coins[left];
			co.take(TAKEN_BY_NPC);
			rwhite.setPosition(co.x, co.y);
			t.draw(rwhite);
			t.draw(co.r);
			t.draw(co.text);
			t.display();
			npc_amount+=co.value;

			left++;
			co = v_coins[left];
			co.r.setOutlineThickness(4);
			t.draw(co.r);
			t.display();
		}else{
			//take right
			auto co = v_coins[right];
			co.take(TAKEN_BY_NPC);
			rwhite.setPosition(co.x, co.y);
			t.draw(rwhite);
			t.draw(co.r);
			t.draw(co.text);
			t.display();
			npc_amount+=co.value;

			right--;
			co = v_coins[right];
			co.r.setOutlineThickness(4);
			t.draw(co.r);
			t.display();
		}
	}else{
		if(left&1){
			//take right
			auto co = v_coins[right];
			co.take(TAKEN_BY_NPC);
			rwhite.setPosition(co.x, co.y);
			t.draw(rwhite);
			t.draw(co.r);
			t.draw(co.text);
			t.display();
			npc_amount+=co.value;

			right--;
			co = v_coins[right];
			co.r.setOutlineThickness(4);
			t.draw(co.r);
			t.display();
		}else{
			//take left
			auto co = v_coins[left];
			co.take(TAKEN_BY_NPC);
			rwhite.setPosition(co.x, co.y);
			t.draw(rwhite);
			t.draw(co.r);
			t.draw(co.text);
			t.display();
			npc_amount+=co.value;

			left++;
			co = v_coins[left];
			co.r.setOutlineThickness(4);
			t.draw(co.r);
			t.display();
		}
	}

	text_npc.setString(s_npc+std::to_string(npc_amount));
	t.draw(text_npc);
	t.display();

	window.clear();
	window.draw(sprite);
	window.display();

	Text text_top("Pick your next coin!", font, 35);
	text_top.setPosition(WIDTH/2-160, 160);
	text_top.setFillColor(Color(0, 0, 0));
	t.draw(text_top);
	t.display();
	Text text_b("(Use left and right keys to play)", font, 25);
	text_b.setPosition(WIDTH/2-175, 200);
	text_b.setFillColor(Color(0, 0, 0));
	t.draw(text_b);
	t.display();


	Text text_lose("YOU LOSE!", font, 35);
	text_lose.setPosition(WIDTH/2-80, 40);
	text_lose.setFillColor(Color(0, 0, 0));

	bool isPlaying=true;

	while(window.isOpen()){
		Event e;
		while(window.pollEvent(e)){
			if(e.type == Event::Closed){
				window.close();
			}else if(e.type == Event::KeyPressed and isPlaying){
				switch (e.key.code){
					case Keyboard::Left :{
						auto co = v_coins[left];
						co.take(TAKEN_BY_PLAYER);
						rwhite.setPosition(co.x, co.y);
						t.draw(rwhite);
						t.draw(co.r);
						t.draw(co.text);
						t.display();
						player_amount+=co.value;

						left++;
						co = v_coins[left];
						co.r.setOutlineThickness(4);
						t.draw(co.r);
						t.display();
						break;
					}
					case Keyboard::Right :{
						auto co = v_coins[right];
						co.take(TAKEN_BY_PLAYER);
						rwhite.setPosition(co.x, co.y);
						t.draw(rwhite);
						t.draw(co.r);
						t.draw(co.text);
						t.display();
						player_amount+=co.value;

						right--;
						co = v_coins[right];
						co.r.setOutlineThickness(4);
						t.draw(co.r);
						t.display();
						break;
					}
					default:{
						continue;
						break;
					}
				}
				if(pick){
					if(left&1){
						//take left
						auto co = v_coins[left];
						co.take(TAKEN_BY_NPC);
						rwhite.setPosition(co.x, co.y);
						t.draw(rwhite);
						t.draw(co.r);
						t.draw(co.text);
						t.display();
						npc_amount+=co.value;

						left++;
						co = v_coins[left];
						co.r.setOutlineThickness(4);
						t.draw(co.r);
						t.display();
					}else{
						//take right
						auto co = v_coins[right];
						co.take(TAKEN_BY_NPC);
						rwhite.setPosition(co.x, co.y);
						t.draw(rwhite);
						t.draw(co.r);
						t.draw(co.text);
						t.display();
						npc_amount+=co.value;

						right--;
						co = v_coins[right];
						co.r.setOutlineThickness(4);
						t.draw(co.r);
						t.display();
					}
				}else{
					if(left&1){
						//take right
						auto co = v_coins[right];
						co.take(TAKEN_BY_NPC);
						rwhite.setPosition(co.x, co.y);
						t.draw(rwhite);
						t.draw(co.r);
						t.draw(co.text);
						t.display();
						npc_amount+=co.value;

						right--;
						co = v_coins[right];
						co.r.setOutlineThickness(4);
						t.draw(co.r);
						t.display();
					}else{
						//take left
						auto co = v_coins[left];
						co.take(TAKEN_BY_NPC);
						rwhite.setPosition(co.x, co.y);
						t.draw(rwhite);
						t.draw(co.r);
						t.draw(co.text);
						t.display();
						npc_amount+=co.value;

						left++;
						co = v_coins[left];
						co.r.setOutlineThickness(4);
						t.draw(co.r);
						t.display();
					}
				}

				// atualiza os amounts
				Vector2f v2fwhite(720.0, 30.0);
				RectangleShape rwhite2(v2fwhite);
				rwhite2.setPosition(0, HEIGHT-50);
				t.draw(rwhite2);
				t.display();

				text_npc.setString(s_npc+std::to_string(npc_amount));
				t.draw(text_npc);
				t.display();

				text_player.setString(s_player+std::to_string(player_amount));
				t.draw(text_player);
				t.display();
			}
		}

		if(!isPlaying){
			t.draw(text_lose);
			t.display();
			window.clear();
			window.draw(sprite);
			window.display();
			continue;
		}

		if(left==right){
			isPlaying=false;
		}

		window.clear();
		window.draw(sprite);
		window.display();
	}

	return 0;
}
