#ifndef TESTING

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

#include "lib/cpu/cpu.hpp"
#include "lib/cpu/instructions.hpp"
#include "lib/cpu/interrupt_handler.hpp"
#include "lib/cpu/registers.hpp"
#include "lib/cpu/speedmode_handler.hpp"
#include "lib/gameboy.hpp"
#include "lib/graphic/lcd_handler.hpp"
#include "lib/graphic/ppu.hpp"
#include "lib/memory/dma/dma_handler.hpp"
#include "lib/memory/dma/hdma_handler.hpp"
#include "lib/memory/dma/null_mediator.hpp"
#include "lib/memory/mmu_factory.hpp"
#include "lib/timer_handler.hpp"

int defaultMain();
int sfmlMain();

std::string getProgramStateString(gb_lib::Instruction* instruction, gb_lib::Registers& registers);
uint32_t loadFile(const char* filePath, uint8_t** buffer);
void tickProgram();

uint8_t* rom = nullptr;
//uint32_t romSize = loadFile("./roms/test/cpu_instrs/individual/07-jr,jp,call,ret,rst.gb", &rom);
uint32_t romSize = loadFile("./roms/tetris.gb", &rom);
uint32_t cpuCycle = 0;

gb_lib::DMAMediator dmaMediator;
gb_lib::NullMediator hdmaMediator;
gb_lib::MMUFactory mmuFactory;
gb_lib::MMU* mmu = mmuFactory.create(rom, romSize, &dmaMediator, &hdmaMediator, false);
gb_lib::Registers registers;
gb_lib::SpeedModeHandler speedModeHandler(mmu);
gb_lib::DMAHandler dmaHandler(mmu, &dmaMediator, &speedModeHandler);
gb_lib::HDMAHandler hdmaHandler(mmu, &hdmaMediator, &speedModeHandler);
gb_lib::PPU ppu(mmu, nullptr);


gb_lib::InterruptHandler interruptHandler(mmu, &registers);
gb_lib::Cpu cpu(&interruptHandler, mmu, &registers, &speedModeHandler);
gb_lib::LCDHandler lcdHandler(&interruptHandler, mmu->getIORegisters(), &ppu, false);
gb_lib::TimerHandler timerHandler(&interruptHandler, mmu);

uint8_t code = 0;
gb_lib::Instruction* instruction = nullptr;
//gb_lib::GameBoy gb("./roms/tetris.gb");

int main()
{
    return defaultMain();

    //return sfmlMain();
}

void tickProgram()
{
    uint16_t cb = 0;
    uint16_t pc = registers.getPC();
    code = mmu->getByte(pc);
    if (code == 0xCB)
    {
        instruction = gb_lib::instructions[1][mmu->getByte(pc + 1)];
        cb = 1;
    }
    else
    {
        instruction = gb_lib::instructions[0][code];
    }

    std::stringstream ss;
    ss << "PC: " << std::setw(4) << std::setfill('0') << std::hex << pc << ", operation: " << instruction->getLabel() << " ";
    if (instruction->getArgumentLength() == 1)
    {


          ss << "(n = " << std::setw(2) << std::setfill('0') << std::uppercase << std::hex << (uint16_t)mmu->getByte(pc + cb + 1) << ")";
    }
    else if (instruction->getArgumentLength() == 2)
    {
          ss << "(nn = " << std::setw(2) << std::setfill('0') << std::uppercase << std::hex << (uint16_t)mmu->getByte(pc + cb + 2);
          ss << std::setw(2) << std::setfill('0') << std::uppercase << std::hex << (uint16_t)mmu->getByte(pc + cb + 1) << ")";
    }
    // ss << " - LY: " << std::setw(2) << std::setfill('0') << std::uppercase << std::hex << (uint16_t)mmu->getByte(gb_lib::LY);
    // ss << " - IF: " << std::setw(2) << std::setfill('0') << std::uppercase << std::hex << (uint16_t)mmu->getByte(gb_lib::IF);
    // ss << " - IE: " << std::setw(2) << std::setfill('0') << std::uppercase << std::hex << (uint16_t)mmu->getByte(gb_lib::IE);
    ss <<  "\n";
    std::cout << ss.str();

    if (registers.getPC() == 0x0040)
    {
        std::cout << getProgramStateString(instruction, registers);
        std::string input;
        std::getline(std::cin, input);
    }

    uint32_t consumedCpuCycle = 4;

    if (hdmaHandler.isTransferInProgress())
    {
        hdmaHandler.tick(consumedCpuCycle);
    }
    else
    {
        consumedCpuCycle = cpu.tick();
    }

    dmaHandler.tick(consumedCpuCycle);
    timerHandler.updateTimers(consumedCpuCycle);
    lcdHandler.updateLCD(consumedCpuCycle);

    cpuCycle += consumedCpuCycle;
    if (cpuCycle >= 69905) {cpuCycle -= 69905;}
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
  if (!texture.create(160, 144)) {
      return EXIT_FAILURE;
  }

  // pixel is what we're going to update
  sf::Uint8* pixels = new sf::Uint8[160 * 144 * 4];
  for (int i = 0; i < 160 * 144 * 4; i++)
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
  screen.setTextureRect(sf::IntRect(500, 800, 160, 144));

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
