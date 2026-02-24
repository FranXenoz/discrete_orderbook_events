#include <queue>
#include <vector>

// 1. The Event: A simple data structure
struct Event {
    double timestamp;
    int type; // Just a label for now

    // This makes the priority_queue a "Min-Heap" (lowest time first)
    bool operator>(const Event& other) const {
        return timestamp > other.timestamp;
    }
};

// 2. The Engine: The thing that runs the loop
class Engine {
public:
    void add_event(double ts, int type) {
        pq.push({ts, type});
    }

    void run(); // You will implement this in engine.cpp

private:
    std::priority_queue<Event, std::vector<Event>, std::greater<Event>> pq;
    double current_time = 0.0;
};
