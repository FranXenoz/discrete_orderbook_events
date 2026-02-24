#pragma once
#include <map>
#include <iostream>

class OrderBook {
public:
    void limit_order(double price, int quantity, bool is_buy) {
        if (is_buy) {
            // MATCHING LOGIC FOR BUYERS
            // Look at the lowest ask (sells). asks.begin() gets the smallest key (price)
            while (quantity > 0 && !asks.empty() && asks.begin()->first <= price) {
                auto best_ask = asks.begin();
                double trade_price = best_ask->first;
                int available_qty = best_ask->second;

                int trade_qty = std::min(quantity, available_qty);
                std::cout << ">>> TRADE EXECUTED: " << trade_qty << " shares @ $" << trade_price << " <<<\n";

                quantity -= trade_qty;
                best_ask->second -= trade_qty;

                // If the seller's order is completely filled, remove it from the book
                if (best_ask->second == 0) {
                    asks.erase(best_ask);
                }
            }
            // If we still have quantity left over, add it to our bids
            if (quantity > 0) {
                bids[price] += quantity;
            }

        } else {
            // MATCHING LOGIC FOR SELLERS
            // Look at the highest bid. std::map is sorted low-to-high, so rbegin() gets the highest.
            while (quantity > 0 && !bids.empty() && bids.rbegin()->first >= price) {
                // We use an iterator to the highest bid
                auto best_bid = std::prev(bids.end()); 
                double trade_price = best_bid->first;
                int available_qty = best_bid->second;

                int trade_qty = std::min(quantity, available_qty);
                std::cout << ">>> TRADE EXECUTED: " << trade_qty << " shares @ $" << trade_price << " <<<\n";

                quantity -= trade_qty;
                best_bid->second -= trade_qty;

                if (best_bid->second == 0) {
                    bids.erase(best_bid);
                }
            }
            // Add remaining quantity to asks
            if (quantity > 0) {
                asks[price] += quantity;
            }
        }
    }

    void print() const {
        std::cout << "\n--- Order Book Status ---" << std::endl;
        std::cout << "Asks (Sells):" << std::endl;
        for (auto it = asks.rbegin(); it != asks.rend(); ++it) {
            std::cout << "  " << it->first << " : " << it->second << std::endl;
        }
        std::cout << "Bids (Buys):" << std::endl;
        for (auto it = bids.rbegin(); it != bids.rend(); ++it) {
            std::cout << "  " << it->first << " : " << it->second << std::endl;
        }
        std::cout << "-------------------------\n" << std::endl;
    }

private:
    std::map<double, int> bids; 
    std::map<double, int> asks; 
};
