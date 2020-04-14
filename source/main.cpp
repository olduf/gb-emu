#ifndef TESTING

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "lib/gameboy.hpp"
#include <iostream>

int defaultMain();
//int sfmlMain();

uint8_t* rom = nullptr;
// failed - cpu_instrs/cpu_instrs.gb
// passed - cpu_instrs/individual/01-special.gb
// passed - cpu_instrs/individual/02-interrupts.gb
// passed - cpu_instrs/individual/03-op sp,hl.gb
// passed - cpu_instrs/individual/04-op r,imm.gb
// passed - cpu_instrs/individual/05-op rp.gb
// passed - cpu_instrs/individual/06-ld r,r.gb
// passed - cpu_instrs/individual/07-jr,jp,call,ret,rst.gb
// passed - cpu_instrs/individual/08-misc instrs.gb
// passed - cpu_instrs/individual/09-op r,r.gb
// passed - cpu_instrs/individual/10-bit ops.gb
// passed - cpu_instrs/individual/11-op a,(hl).gb

// failed - instr_timing/instr_timing.gb

// passed - mooneye/acceptance/timer/div_write.gb
// passed - mooneye/acceptance/timer/rapid_toggle.gb
// failed - mooneye/acceptance/timer/tim00.gb
// failed - mooneye/acceptance/timer/tim00_div_trigger.gb
// failed - mooneye/acceptance/timer/tim01.gb
// failed - mooneye/acceptance/timer/tim01_div_trigger.gb
// failed - mooneye/acceptance/timer/tim10.gb
// failed - mooneye/acceptance/timer/tim10_div_trigger.gb
// failed - mooneye/acceptance/timer/tim11.gb
// failed - mooneye/acceptance/timer/tim11_div_trigger.gb
// failed - mooneye/acceptance/timer/tima_reload.gb
// failed - mooneye/acceptance/timer/tima_write_reloading.gb
// failed - mooneye/acceptance/timer/tma_write_reloading.gb

bool debug = false;
gb_lib::GameBoy* gameboy;

int main(int argc, char** argv)
{
    if (argc >= 2)
    {
        gameboy = new gb_lib::GameBoy(argv[1]);

        return defaultMain();
    }

    return 0;
}

int defaultMain()
{
    bool loop = true;
    int i = 1;

    while (loop)
    {
        // printf("%i\n", i++);
        gameboy->stepInstruction();
        // char c;
        // std::cin.get(c);
    }

    return 0;
}
//
// int sfmlMain()
// {
//   // Create the main window
//   sf::RenderWindow window(sf::VideoMode(1080, 768), "GBEMU");
//
//   // Set the Icon
//   sf::Image icon;
//   if (!icon.loadFromFile(std::string("./resources/icon.png"))) {
//       return EXIT_FAILURE;
//   }
//   window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
//
//   // Create a graphical text to display
//   sf::Font font;
//   if (!font.loadFromFile(std::string("./resources/sansation.ttf"))) {
//       return EXIT_FAILURE;
//   }
//   sf::Text text(getProgramStateString(instruction, registers), font, 24);
//   text.setFillColor(sf::Color::White);
//   text.setPosition(6, 312);
//
//   // Load a sprite to display
//   sf::Texture texture;
//   if (!texture.create(160, 144)) {
//       return EXIT_FAILURE;
//   }
//
//   // pixel is what we're going to update
//   sf::Uint8* pixels = new sf::Uint8[160 * 144 * 4];
//   for (int i = 0; i < 160 * 144 * 4; i++)
//   {
//       pixels[i] = 0xFF;
//   }
//   texture.update(pixels);
//
//   // Screen
//   sf::RectangleShape screen(sf::Vector2f(332, 288));
//   screen.setOutlineThickness(10);
//   screen.setOutlineColor(sf::Color(250, 150, 100));
//   screen.setPosition(16, 16);
//   screen.setTexture(&texture);
//   screen.setTextureRect(sf::IntRect(500, 800, 160, 144));
//
//   // Start the game loop
//   while (window.isOpen())
//   {
//       // Process events
//       sf::Event event;
//       while (window.pollEvent(event))
//       {
//           // Close window: exit
//           if (event.type == sf::Event::Closed)
//           {
//               window.close();
//           }
//
//           // Escape pressed: exit
//           if (event.type == sf::Event::KeyPressed)
//           {
//               if (event.key.code == sf::Keyboard::Enter)
//               {
//                   tickProgram();
//                   text.setString(getProgramStateString(instruction, registers));
//               }
//               else if (event.key.code == sf::Keyboard::Escape)
//               {
//                   window.close();
//               }
//           }
//       }
//
//       // Clear screen
//       window.clear(sf::Color::Black);
//
//       // Draw the string
//       window.draw(text);
//
//       // Draw the screen
//       window.draw(screen);
//
//       // Update the window
//       window.display();
//   }
//
//   return EXIT_SUCCESS;
// }

#endif

// #include <cmath>
// Play sound
// const unsigned SAMPLES = 44100;
// const unsigned SAMPLE_RATE = 44100;
// const unsigned AMPLITUDE = 30000;
//
// sf::Int16 raw[SAMPLES];
//
// const double TWO_PI = 6.28318;
// const double increment = 440./44100;
// double x = 0;
// for (unsigned i = 0; i < SAMPLES; i++) {
//   raw[i] = AMPLITUDE * sin(x*TWO_PI);
//   x += increment;
// }
//
// sf::SoundBuffer Buffer;
// if (!Buffer.loadFromSamples(raw, SAMPLES, 1, SAMPLE_RATE)) {
//   std::cerr << "Loading failed!" << std::endl;
//   return 1;
// }
//
// sf::Sound Sound;
// Sound.setBuffer(Buffer);
// Sound.setLoop(true);
// Sound.play();
