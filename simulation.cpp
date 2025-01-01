#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <iostream>
#include <thread>
#include <chrono>

const int rows = 100;
const int cols = 100;

double fire_decay_rate = 0.2;

// Create a random number generator
std::random_device rd;
std::mt19937 gen(rd());

// Define the distribution
std::uniform_real_distribution<double> dist(0.0, 1.0);
std::uniform_real_distribution<double> small_dist(0.0, 0.001);

struct Cell {
    double growth_value = std::round(dist(gen) * 100) / 100.0;
    double flame_intensity = 0.0;
};

void drawScreen(double& growth_value, double& flame_intensity, int& yPos, int& xPos, sf::RenderWindow& window) {
    // First calculate colors:

    int growth_value_color = round(growth_value * 150);
    int flame_intensity_color = round(flame_intensity * 255);

    sf::RectangleShape rectangle(sf::Vector2f(100, 100));
    rectangle.setPosition(sf::Vector2f(xPos, yPos));
    if (flame_intensity_color == 0) {
        rectangle.setFillColor(sf::Color(0, growth_value_color, 0));
    } else {
        rectangle.setFillColor(sf::Color(flame_intensity_color, 0, 0));
    }
    window.draw(rectangle);

}

double calc_fireburst_odds(Cell (&pixelArray)[rows][cols], int row, int col) {
    //First calculate average flame intensity around the cell

    double heatcount = 0.0;
    double fireburst_odds = 0.0;
    int out_of_bounds_cells = 0;
    for (int i = (col - 1); i < col + 2; ++i) {
        for (int k = (row - 1); k < row + 2; ++k) {
            if (i < 0 || k < 0 || i >= cols || k >= rows) {
                out_of_bounds_cells += 1;
            } else if (k == row && i == col) {
                //Intentionally empty--we don't want to include the cell itself!
            } else {
                heatcount += pixelArray[k][i].flame_intensity;
            }
        }
    }
    fireburst_odds = heatcount / (8 - out_of_bounds_cells);
    if (fireburst_odds != 0) {
        fireburst_odds = fireburst_odds * pixelArray[row][col].growth_value * 0.8;
    } else {
        fireburst_odds = pixelArray[row][col].growth_value * 0.00001;
    }
    std::cout << "[" << pixelArray[row][col].growth_value << ", " << fireburst_odds << ", " << heatcount << "]";
    return fireburst_odds;
}

void updateCells(Cell (&pixelArray)[rows][cols]) {

    Cell updatedArray[rows][cols]; // Need to change struct so that we're not generating random numbers every time

    //First determine the odds that a cell catches fire
    for (int r = 1; r < rows; ++r) {
            for (int c = 1; c < cols; ++c) {
                bool willcatchfire = false;
                double fireburst_odds = calc_fireburst_odds(pixelArray, r, c);
                if (pixelArray[r][c].flame_intensity == 0 && fireburst_odds < 1) {
                    double randomValue = dist(gen);
                    if (randomValue <= fireburst_odds) {
                        willcatchfire = true;
                    } else {
                        willcatchfire = false;
                    }
                } else if (fireburst_odds > 1) {
                    willcatchfire = true;
                }
            
            if (willcatchfire == true && pixelArray[r][c].flame_intensity == 0.0) {
                pixelArray[r][c].flame_intensity = 1.0;
                pixelArray[r][c].growth_value = 0.0;
            } else if (pixelArray[r][c].flame_intensity == 0.0 && pixelArray[r][c].growth_value <= 1.0) {
                pixelArray[r][c].growth_value += small_dist(gen);
            } else if (pixelArray[r][c].growth_value <= 1.0) {
                pixelArray[r][c].flame_intensity -= 0.25;
            }

            }
        }
    std::cout << "Here!";
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void runSim(Cell (&pixelArray)[rows][cols]) {
    // Initialize window
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Wildfire Simulation v0.1");

    // run the program as long as the window is open
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
        // check the type of the event...
            switch (event.type) {
                // window closed
                case sf::Event::Closed:
                    window.close();
                    break;
                    
                // we don't process other types of events
                default:
                    break;
            }
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        for (int r = 1; r < rows; ++r) {
            for (int c = 1; c < cols; ++c) {
                int xPos = r * 10;
                int yPos = c * 10;
                drawScreen(pixelArray[r][c].growth_value, pixelArray[r][c].flame_intensity, xPos, yPos, window);
            }
        }

        window.display();
        updateCells(pixelArray);
    }
}

int main() {
    Cell pixelArray[rows][cols];

    runSim(pixelArray);


    return 0;
}