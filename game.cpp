#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <ctime>
#include <iostream> 
#include<SFML/Graphics.hpp> 

float speed = 200.0f;  
const sf::Time timefps = sf::seconds(1.f / 60.f ) ;
    
    class game 
    {   

  public: 
    game(); 
    void run();
  private: 
    void        processEvent(); // player input handler  
    void      update(sf::Time delta) ; // update frame 
    void      render();  // rendr sprite 
    void      handlePlayerInput(sf::Keyboard::Key key , bool isPressed);
  private: 
      sf::RenderWindow window ;  // main window 
      sf::CircleShape player;  // sprite to render 
      bool up , down , left , right ; 
 


  
}; 


    game::game( ) : window( sf::VideoMode(800,800) , "SFML app ") , player() 
{

  player.setRadius(40.f);
  player.setPosition(100.f , 100.f); 
  player.setFillColor(sf::Color::Cyan) ; 



} 


void game::handlePlayerInput(sf::Keyboard::Key key , bool isPressed) 
{ 

  if ( key == sf::Keyboard::Z )  
    this->up = isPressed; 

  else  if ( key == sf::Keyboard::Q ) 
    this->left = isPressed; 

  else if ( key == sf::Keyboard::D) 
    this->right = isPressed; 

  else if (key == sf::Keyboard::S ) 
    this->down = isPressed; 

  else 
    std::cout << " QZDS are the keys  \n ";

}

void game::processEvent()
{
  sf::Event event; 

     
  while (window.pollEvent(event) )
  {
 
     
    switch (event.type) 
    {

      case sf::Event::KeyPressed : 
        handlePlayerInput(event.key.code , true); break ; 
      
      case sf::Event::KeyReleased : 
        handlePlayerInput(event.key.code,false); break ; 

      case sf::Event::Closed : 
             this->window.close(); break; 

      default: 
             
            break; 

    
    }

}
} 

void game::update(sf::Time dtime)
{
    sf::Vector2f Pmove(0.f,0.f); 
    

    if (this->up) 
      Pmove.y -= 1; 
    if (this->down ) 
      Pmove.y += 1; 

    if (this->left) 
      Pmove.x -= 1 ; 
    if(this->right)
     Pmove.x +=1 ; 

      Pmove *= speed *dtime.asSeconds();

    player.move(Pmove);



}
void game::render()
{
    window.clear();
    window.draw(this->player); 
window.display();

  
}

void game::run()
  {
    sf::Clock clock ;
     sf::Time lastupdate = sf::Time::Zero  ; // from the start  
     while (this->window.isOpen()) 
      { 
        this->processEvent(); 
        lastupdate+= clock.restart();  
         
         while (lastupdate   > timefps  )
         {
          lastupdate -= timefps; 
          processEvent(); 
          update(timefps);
        }
        render(); 
     }
  }



int main()
{

  game g; 
  g.run(); 

}
