#include "engine.hpp"
#include "order_book.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>

// Function to read CSV and load events into the engine
void load_market_data(const std::string& filename, Engine& sim, OrderBook& ob) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    std::string line;
    int event_count = 0;

    // Read file line by line
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;

        // Parse CSV columns
        std::getline(ss, token, ',');
        double timestamp = std::stod(token);

        std::getline(ss, token, ',');
        bool is_buy = (token == "B");

        std::getline(ss, token, ',');
        double price = std::stod(token);

        std::getline(ss, token, ',');
        int quantity = std::stoi(token);

        // Dynamically schedule the event in the simulator
        sim.add_event(timestamp, [&ob, price, quantity, is_buy, timestamp]() {
            std::string side = is_buy ? "Bid" : "Ask";
            //std::cout << "[Time " << timestamp << "] Market " << side << ": " << quantity << " @ $" << price << "\n";
            
            ob.limit_order(price, quantity, is_buy);
        });
        
        event_count++;
    }
    
    //std::cout << "Loaded " << event_count << " events from " << filename << "\n\n";
}

int main() {
    Engine sim;
    OrderBook ob;

    load_market_data("../data/stress_test.csv", sim, ob);

    // 1. Start the clock
    auto start_time = std::chrono::high_resolution_clock::now();

    // 2. Run the engine
    sim.run();

    // 3. Stop the clock
    auto end_time = std::chrono::high_resolution_clock::now();

    // 4. Calculate duration in microseconds
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();

    std::cout << "\n========================================\n";
    std::cout << "Engine processed events in: " << duration << " microseconds.\n";
    std::cout << "========================================\n";

    return 0;
}
