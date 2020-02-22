#ifndef TESTING

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

#include "lib/cpu/cpu.hpp"
#include "lib/cpu/interrupt_handler.hpp"
#include "lib/cpu/registers.hpp"
#include "lib/cpu/speedmode_handler.hpp"
#include "lib/graphic/lcd_handler.hpp"
#include "lib/memory/mmu_factory.hpp"
#include "lib/cpu/instructions.hpp"

void runFrame();
int defaultMain();
int sfmlMain();

std::string getProgramStateString(gb_lib::Instruction* instruction, gb_lib::Registers& registers);
uint32_t loadFile(const char* filePath, uint8_t** buffer);
void tickProgram();

uint8_t* rom = nullptr;
//uint32_t romSize = loadFile("./roms/test/cpi/instrs/cpu_instrs.gb", &rom);
uint32_t romSize = loadFile("./roms/tetris.gb", &rom);
uint32_t cpuCycle = 0;

gb_lib::MMUFactory mmuFactory;
gb_lib::MMU* mmu = mmuFactory.create(rom, romSize, false);
gb_lib::Registers registers;
gb_lib::SpeedModeHandler speedModeHandler(mmu);

gb_lib::InterruptHandler interruptHandler(mmu, &registers);
gb_lib::Cpu cpu(&interruptHandler, mmu, &registers, &speedModeHandler);
gb_lib::LCDHandler lcdHandler(&interruptHandler, mmu, false);

uint8_t code = 0;
gb_lib::Instruction* instruction = nullptr;

int main()
{
    return defaultMain();

    //return sfmlMain();
}

void tickProgram()
{
    uint16_t pc = registers.getPC();
    code = mmu->getByte(pc);
    if (code == 0xCB)
    {
        instruction = gb_lib::instructions[1][mmu->getByte(pc) + 1];
    }
    else
    {
        instruction = gb_lib::instructions[0][code];
    }

    uint32_t consumedCpuCycle = cpu.tick();
    lcdHandler.updateLCD(consumedCpuCycle);

    cpuCycle += consumedCpuCycle;
}

void runFrame()
{
    uint32_t cpuCycle = 0;

    while (cpuCycle < 69905)
    {
        uint32_t consumedCpuCycle = cpu.tick();
        // update timers
        lcdHandler.updateLCD(consumedCpuCycle);
        cpuCycle += consumedCpuCycle;
    }
}

std::string getProgramStateString(gb_lib::Instruction* instruction, gb_lib::Registers& registers)
{
    std::stringstream ss;

    ss << "Cycle: " << std::dec << cpuCycle << "\n";

    ss << "CPU Registers:\n";
    ss << "AF: 0x" << std::setw(4) << std::setfill('0') << std::uppercase << std::hex << registers.getAF() << ", ";
    ss << "BC: 0x" << std::setw(4) << std::setfill('0') << std::uppercase << std::hex << registers.getBC() << ", ";
    ss << "DE: 0x" << std::setw(4) << std::setfill('0') << std::uppercase << std::hex << registers.getDE() << ", ";
    ss << "HL: 0x" << std::setw(4) << std::setfill('0') << std::uppercase << std::hex << registers.getHL() << ", ";
    ss << "SP: 0x" << std::setw(4) << std::setfill('0') << std::uppercase << std::hex << registers.getSP() << ", ";
    ss << "PC: 0x" << std::setw(4) << std::setfill('0') << std::uppercase << std::hex << registers.getPC() << ", ";
    ss << "IME: " << registers.isIME() << "\n";

    if (instruction != nullptr)
    {
        ss << "Operation: " << instruction->getLabel() << ", ";
        ss << "code : 0x" << std::setw(2) << std::setfill('0') << std::uppercase << std::hex << instruction->getCode() << ", ";
        ss << "cycle: " << std::dec << instruction->getCpuCycle() << "\n";
    }

    return ss.str();
}

uint32_t loadFile(const char* filePath, uint8_t** buffer)
{
    FILE* file = fopen(filePath, "rb");
    uint32_t sizeOfFile = 0;

    if (file) {
        fseek(file, 0, SEEK_END);
        sizeOfFile = ftell(file);
        fseek(file, 0, SEEK_SET);

        *buffer = new uint8_t[sizeOfFile];

        fread(*buffer, 1, sizeOfFile, file);
        fclose(file);
    }

    file = nullptr;

    return sizeOfFile;
}

int defaultMain()
{
    std::cout << getProgramStateString(instruction, registers);

    bool loop = true;
    while (loop)
    {
        if (registers.getPC() > 0x0239)
        {
            std::string input;
            std::getline(std::cin, input);

            std::cout << getProgramStateString(instruction, registers);
        }

        tickProgram();
    }

    return 0;
}

int sfmlMain()
{
  // Create the main window
  sf::RenderWindow window(sf::VideoMode(1080, 768), "GBEMU");

  // Set the Icon
  sf::Image icon;
  if (!icon.loadFromFile(std::string("./resources/icon.png"))) {
      return EXIT_FAILURE;
  }
  window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

  // Create a graphical text to display
  sf::Font font;
  if (!font.loadFromFile(std::string("./resources/sansation.ttf"))) {
      return EXIT_FAILURE;
  }
  sf::Text text(getProgramStateString(instruction, registers), font, 24);
  text.setFillColor(sf::Color::White);
  text.setPosition(6, 312);

  // Load a sprite to display
  sf::Texture texture;
  if (!texture.create(166, 144)) {
      return EXIT_FAILURE;
  }

  // pixel is what we're going to update
  sf::Uint8* pixels = new sf::Uint8[166 * 144 * 4];
  for (int i = 0; i < 166 * 144 * 4; i++)
  {
      pixels[i] = 0xFF;
  }
  texture.update(pixels);

  // Screen
  sf::RectangleShape screen(sf::Vector2f(332, 288));
  screen.setOutlineThickness(10);
  screen.setOutlineColor(sf::Color(250, 150, 100));
  screen.setPosition(16, 16);
  screen.setTexture(&texture);
  screen.setTextureRect(sf::IntRect(500, 800, 166, 144));

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
              if (event.key.code == sf::Keyboard::Enter)
              {
                  tickProgram();
                  text.setString(getProgramStateString(instruction, registers));
              }
              else if (event.key.code == sf::Keyboard::Escape)
              {
                  window.close();
              }
          }
      }

      // Clear screen
      window.clear(sf::Color::Black);

      // Draw the string
      window.draw(text);

      // Draw the screen
      window.draw(screen);

      // Update the window
      window.display();
  }

  return EXIT_SUCCESS;
}

#endif

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