#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <chrono>
#include <thread>
#include <sched.h>
#include <sys/mman.h>
#include <bcm2835.h>
#include <sstream>
#include <stdio.h>
#include <sched.h>
#include <sys/mman.h>
#include <string.h>

struct Color
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;

	bool operator!=(const Color& other) const
	{
		if (this->red != other.red || this->green != other.green || this->blue != other.blue )
		{
			return true;
		}

		return false;
	}
};

struct Position
{
	unsigned int x;
	unsigned int y; 
};

enum class AnimationType{ stream, matrix, unknown};
enum class MatrixParam{ left, righ, up, down, upLeft, upRight, downLeft, downRight, unknown};

struct Animation
{
	AnimationType animationType = AnimationType::unknown;
	MatrixParam matrixParam = MatrixParam::unknown;
	std::size_t colorStep = 1;
	std::size_t animationSpeed = 30;
	std::size_t animationWidth = 1;
	std::vector<Color> colors;


	std::vector<Color> run(int current, int total)
	{
		std::vector<Color> generatedColor;

		return generatedColor;
	}
};

int targetFPS = 60;
std::size_t ledCount = 0;

std::vector<Animation> animations;
std::map<unsigned,std::vector<Position>> leds;

const Color Black = {0, 0, 0};
const Color White = {255, 255, 255};
const Color Red = {255, 0, 0};
const Color Green = {0, 255, 0};
const Color Blue = {0, 0, 255};

std::vector<Color> generateTestSequence(std::size_t size)
{
        static int currentLed = 0;
        std::vector<Color> generatedColor;

        for (std::size_t i = 0; i < size; ++i)
        {
                if (i==currentLed)
                {
                        generatedColor.push_back(Blue);
                }
                else
                {
                        generatedColor.push_back(Red);
                }
        }

        currentLed = (++currentLed) % size;

        return generatedColor;
}

std::vector<Color> runAnimations()
{
	static int currentLed = 0;
	static int currentAnimation = 0;

	std::vector<Color> generatedColor;

	switch (animations[currentAnimation].animationType)
	{
		case AnimationType::stream:
		{
			break;
		}
		case AnimationType::matrix:
		{
			break;
		}
	}

	if (currentLed == ledCount - 1)
	{
		currentAnimation = (++currentAnimation) % animations.size();
	}

	currentLed = (++currentLed) % ledCount;

	return generatedColor;
}

void drawAllLeds(const std::vector<Color>& colorList)
{
        for (int i = 0; i < colorList.size(); ++i )
        {
                if (colorList[i] != Black)
                {
                        //std::cout << "Led nr: " << i+1 << " is colored: " << "R: " << int(colorList[i].red) << " G: " << int(colorList[i].green) << " B: " << int(colorList[i].blue) << std::endl;
                }
        }

	uint16_t colorSize = uint16_t(colorList.size());
	bcm2835_spi_transfer(colorSize >> 8);
	bcm2835_spi_transfer(colorSize & 0x00FF);
	for (int i = 0; i < colorList.size(); ++i)
	{
		(void)bcm2835_spi_transfer(colorList[i].red);
                (void)bcm2835_spi_transfer(colorList[i].green);
                (void)bcm2835_spi_transfer(colorList[i].blue);
	}
}

bool readInputFile(const std::string& inputFileName)
{
        std::cout << "InputFileName : " << inputFileName << std::endl;

	std::ifstream inputFile(inputFileName);
	if (!inputFile.is_open())
	{
		std::cout << "readInputFile failed to open file: " << inputFileName << std::endl;
		return false;
	}
	
	inputFile >> ledCount;
	std::cout << "LedCount is: " << ledCount << std::endl;
	
	for (std::size_t i = 0; i < ledCount; ++i)
	{
		std::size_t group;
		Position pos;
		inputFile >> group >> pos.x >> pos.y;
		
		auto search = leds.find(group);	
		if (search == leds.end())
		{
			std::vector<Position> groupPosition;
			groupPosition.push_back(pos);
			leds.insert(std::pair<unsigned,std::vector<Position>>(group, groupPosition));
		}
		else
		{
			leds[group].push_back(pos);
		}

		std::cout << "Group is: " << group << " X: " << pos.x <<" Y: " << pos.y << std::endl;
	}
	
	inputFile.close();
	return true;
}

bool readAnimationFiles(const std::vector<std::string>& animationList)
{
	for (int i = 0; i < animationList.size(); ++i)
	{
		std::ifstream animationFile(animationList[i]);
		if (!animationFile.is_open())
		{
			std::cout << "readAnimationFiles failed to open " << animationList[i] << std::endl;
			return false;
		}
		
		Animation animation;
		
		std::string line;
		while(std::getline(animationFile, line))
		{
			std::stringstream stream(line);
			std::string param;
			getline(stream, param, ' ');
			
			if (param == "animationType:")
			{
				std::cout << "animationType" << std::endl;
				std::string animType;
				getline(stream, animType, ' ');	
				if (animType == "stream")
				{
					animation.animationType = AnimationType::stream;
				}
				else if (animType == "matrix")
				{
					animation.animationType = AnimationType::matrix;
				}
				else
				{
					animation.animationType = AnimationType::unknown;
				}
			}
			else if (param == "matrixParam:")
			{
                                std::cout << "matrixParam" << std::endl;
				std::string matParam;
				getline(stream, matParam, ' ');	
				if (matParam == "left")
				{
					animation.matrixParam = MatrixParam::left;
				}
				else
				{
					animation.matrixParam = MatrixParam::unknown;
				}
			}
			else if (param == "colorStep:")
			{
	                	std::cout << "colorStep" << std::endl;
				animationFile >> animation.colorStep;
			}
			else if (param == "animationSpeed:")
			{
                                std::cout << "animationSpeed" << std::endl;
				animationFile >> animation.animationSpeed;
			}
			else if (param == "animationWidth:")
			{
                                std::cout << "animationWidth" << std::endl;
				animationFile >> animation.animationWidth;
			}
			else if (param == "colors:")
			{
                                std::cout << "colors" << std::endl;
				std::size_t colorCount = 0;
				animationFile >> colorCount;
				for (int j = 0; j < colorCount; ++j)
				{
					Color color;
					animationFile >> color.red >> color.green >> color.blue;
					animation.colors.push_back(color);
				}
			}
			else
			{
				std::cout << "readAnimationFiles failed to read " << animationList[i] << " garbage value " << param << std::endl;
				return false;
			}

			std::cout << line << std::endl;
		}

		animationFile.close();		
		animations.push_back(animation);
	}
	
	return true;
}

bool init (int argc, char* argv[])
{
        if (argc < 3)
        {
                std::cout << "Params are not enough!" << std::endl;
                std::cout << "Please call the program like this:" << std::endl;
                std::cout << "  " << argv[0] << " \"InputFile\" \"AnimationFile1\" [\"AnimationFile2\" .. \"AnimationFileN\"]" << std::endl;

                return false;
        }

	if (!readInputFile(argv[1]))
	{
		std::cout << "Error with inputFile: " << argv[1] << std::endl; 	
		return false;
	}

        std::vector<std::string> animationList;

        for (int i = 0; i < argc - 2; ++i)
        {
                std::cout << "Animation" << i + 1 << " : " << argv[2+i] << std::endl;
                animationList.push_back(argv[2+i]);
        }

	if (!readAnimationFiles(animationList))
	{
		std::cout << "Error with animationFiles" << std::endl;
		return false;
	}

	if (!bcm2835_init())
	{
		std::cout << "bcm2835_init failed. Are yopu running as root??" << std::endl;
		return false;
	}

	if (!bcm2835_spi_begin())
	{
		std::cout << "bcm2835_spi_begin failed. Are you running as root??" <<std::endl;
	}

	bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_LSBFIRST);      // The default
    	bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                   // The default
  	bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_1024); // The default
   	bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                      // The default
   	bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);      // the default

	return true;
}

void update()
{
	while(true)
	{
		auto startTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		
		drawAllLeds(generateTestSequence(600));

		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - startTime;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000/targetFPS - duration));
	}	
}

int main(int argc, char* argv[])
{
	struct sched_param sp;
	memset(&sp, 0, sizeof(sp));
	sp.sched_priority = sched_get_priority_max(SCHED_FIFO);
	sched_setscheduler(0, SCHED_FIFO, &sp);
	mlockall(MCL_CURRENT | MCL_FUTURE);

	if (!init( argc, argv))
	{
		return 0;
	}

	update();
	
	bcm2835_spi_end();
	bcm2835_close();
	return 0;
}
