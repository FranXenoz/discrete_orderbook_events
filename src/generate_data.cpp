#include <iostream>
#include <fstream>
#include <random>
#include <iomanip>

int main() {
    // Open the file in the data folder
    std::ofstream file("data/stress_test.csv");
    
    // We use a fixed seed (42) so the "random" data is exactly the same every time.
    // This guarantees deterministic benchmarks!
    std::mt19937 gen(42); 
    std::uniform_real_distribution<> price_dist(145.0, 155.0);
    std::uniform_int_distribution<> qty_dist(1, 100);
    std::uniform_int_distribution<> side_dist(0, 1);

    double time = 10.0;
    
    std::cout << "Generating 1,000,000 events... This might take a second.\n";
    
    for(int i = 0; i < 1000000; ++i) {
        time += 0.001; // Advance time by 1 millisecond
        std::string side = side_dist(gen) ? "B" : "S";
        
        // Format to 2 decimal places
        file << std::fixed << std::setprecision(3) << time << "," 
             << side << "," 
             << std::setprecision(2) << price_dist(gen) << "," 
             << qty_dist(gen) << "\n";
    }

    file.close();
    std::cout << "Done! Saved to data/stress_test.csv\n";
    return 0;
}
