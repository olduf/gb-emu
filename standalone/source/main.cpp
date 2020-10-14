#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>

#include <cxxopts.hpp>
#include <iostream>
#include <string>

#include "lib/gameboy.hpp"

int defaultMain();
int sfmlMain();

gb_lib::GameBoy* gameboy;

int main(int argc, char** argv) {
  cxxopts::Options options(argv[0], "A program to welcome the world!");

  //std::string language;
  std::string romPath;

  // clang-format off
  options.add_options()
    ("h,help", "Show help")
    ("p,path", "Path to the rom", cxxopts::value(romPath))
    //("l,lang", "Language code to use", cxxopts::value(language)->default_value("en"))
  ;
  // clang-format on

  auto result = options.parse(argc, argv);

  if (result["help"].as<bool>()) {
    std::cout << options.help() << std::endl;
    return 0;
  }

  if (!romPath.empty())
  {
      gameboy = new gb_lib::GameBoy(romPath);

      return defaultMain();
  }

  return sfmlMain();
}

int defaultMain()
{
    bool loop = true;

    while (loop)
    {
        gameboy->stepInstruction();
    }

    return 0;
}

int sfmlMain()
{
  // Create the main window
  sf::RenderWindow window(sf::VideoMode(1080, 768), "Gb Emu");

  // Sound tests
  //============================================================================
  const unsigned SAMPLES = 44100;
  const unsigned SAMPLE_RATE = 44100;
  const unsigned AMPLITUDE = 30000;

  sf::Int16 raw[SAMPLES];

  const double TWO_PI = 6.28318;
  const double increment = 440./44100;
  double x = 0;
  for (unsigned i = 0; i < SAMPLES; i++) {
    raw[i] = AMPLITUDE * sin(x*TWO_PI);
    x += increment;
  }

  sf::SoundBuffer Buffer;
  if (!Buffer.loadFromSamples(raw, SAMPLES, 1, SAMPLE_RATE)) {
    std::cerr << "Loading failed!" << std::endl;
    return 1;
  }

  sf::Sound Sound;
  Sound.setBuffer(Buffer);
  Sound.setLoop(true);
  Sound.play();
  //============================================================================

  // Start the game loop
  while (window.isOpen())
  {
      // Process events
      sf::Event event;
      while (window.pollEvent(event))
      {
          // Close window: exit
          if (event.type == sf::Event::Closed)
          {
              window.close();
          }

          // Escape pressed: exit
          if (event.type == sf::Event::KeyPressed)
          {
              if (event.key.code == sf::Keyboard::Escape)
              {
                  window.close();
              }
          }
      }

      window.clear();

      // Update the window
      window.display();
  }

  return EXIT_SUCCESS;
}
