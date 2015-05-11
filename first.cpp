#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>

struct Position
{
    float latitude;
    float longitude;
};

class Gps
{
    public:
        Gps(char filename[20]);
        void GetDistance();
        void GetAngleOfLine();

    private:
        Position position[2];

        void readPositionCoordinates(char filename[20]);
        float calculateDistance();
        float calculateAngleOfLine();
};

Gps::Gps(char filename[20])
{
    this->readPositionCoordinates(filename);
}

void Gps::GetDistance()
{
    float distance = calculateDistance();
    std::cout<<"Distance between 2 points = "<<distance<<std::endl;
}

void Gps::GetAngleOfLine()
{
    float angle = calculateAngleOfLine();
    std::cout<<"Angle of line between 2 points (in degrees) = "<<angle<<std::endl;
}

void Gps::readPositionCoordinates(char filename[20])
{
   std::ifstream file;
    file.open(filename);
    std::string line;
    int points=0;
    while(std::getline(file,line))
    {
        std::vector<float> lineData;
        std::stringstream  lineStream(line);
        int value;
        while(lineStream >> value)
        {
            lineData.push_back(value);
        }
        position[points].latitude=lineData[0];
        position[points].longitude=lineData[1];
        std::cout<<position[points].latitude<<" "<<position[points].longitude<<std::endl;
        points++;
    }
    file.close();
}

float Gps::calculateDistance()
{
    return sqrt(pow(position[0].latitude - position[1].latitude,2) + pow(position[0].longitude - position[1].longitude,2));
}

float Gps::calculateAngleOfLine()
{
    return (atan2(position[1].longitude - position[0].longitude,position[1].latitude - position[0].latitude))*(180/M_PI);
}

int main()
{
    Gps g("abc.txt");
    g.GetDistance();
    g.GetAngleOfLine();
    return 0;
}
