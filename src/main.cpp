#include "engine.hpp"
#include "order_book.hpp"
#include <iostream>

int main() {
    Engine sim;
    OrderBook ob; // This is our market state

    // Event 1: Alice places a buy order at time 1.0
    // Notice the [&ob] - this is a "capture by reference". 
    // It lets the event modify our actual OrderBook, not a copy.
    sim.add_event(1.0, [&ob]() {
        std::cout << "[Time 1.0] Alice places Bid: 10 shares @ $150.00\n";
        ob.limit_order(150.00, 10, true);
    });

    // Event 2: Bob places a sell order at time 2.5
    sim.add_event(2.5, [&ob]() {
        std::cout << "[Time 2.5] Bob places Ask: 5 shares @ $151.00\n";
        ob.limit_order(151.00, 5, false);
    });

    // Event 3: Charlie places another buy order at time 3.0
    sim.add_event(3.0, [&ob]() {
        std::cout << "[Time 3.0] Charlie places Bid: 20 shares @ $149.50\n";
        ob.limit_order(149.50, 20, true);
    });

    // Event 4: Print the final state of the book at time 4.0
    sim.add_event(4.0, [&ob]() {
        ob.print();
    });

    // Start the time machine!
    sim.run();

    return 0;
}
