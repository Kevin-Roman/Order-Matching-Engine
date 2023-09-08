#include "IOutput.h"
#include "ConsoleOutput.h"
#include "OrderBook.h"

#include <iostream>
#include <algorithm>
#include <iomanip>

ConsoleOutput::ConsoleOutput(const OrderBook& orderBook) : IOutput(orderBook){};

void ConsoleOutput::displayOrderBook() const {
  while (true) {
    // Clear the terminal.
    system("cls");

    // Set precision of price double values (the price) to 2 decimal points.
    std::cout << std::fixed << std::setprecision(2);

    std::cout << "         BIDS                    ASKS" << std::endl;
    std::cout << " VOLUME        PRICE    PRICE           VOLUME" << std::endl;

    // Display only the first 10 rows of the order book.
    size_t maxSize = 10;

    // In order to prevent reading the bids and asks sets whilst they are being modified, create
    // deepcopies and display them.
    std::multiset<std::unique_ptr<Order>, DecreasingPriceComparator> deepCopyBids;
    std::multiset<std::unique_ptr<Order>, IncreasingPriceComparator> deepCopyAsks;

    for (const auto& originalPtr : m_orderBook.bids()) {
      // Create a deep copy of the Order object and its associated unique_ptr.
      std::unique_ptr<Order> newCopy(new Order(*originalPtr));
      deepCopyBids.insert(std::move(newCopy));
    }

    for (const auto& originalPtr : m_orderBook.asks()) {
      // Create a deep copy of the Order object and its associated unique_ptr.
      std::unique_ptr<Order> newCopy(new Order(*originalPtr));
      deepCopyAsks.insert(std::move(newCopy));
    }

    auto bidIt = deepCopyBids.begin();
    auto askIt = deepCopyAsks.begin();

    for (size_t i = 0; i < maxSize; ++i) {
      std::cout << "[";

      if (bidIt != deepCopyBids.end()) {
        // TODO: vary the number of spaces depending on the length of the price and volume strings.
        std::cout << (*bidIt)->volume() << std::string(7, ' ') << "-" << std::string(2, ' ')
                  << (*bidIt)->price();
        ++bidIt;
      } else {
        std::cout << std::string(17, ' ');
      }

      std::cout << " | ";

      if (askIt != deepCopyAsks.end()) {
        std::cout << (*askIt)->price() << std::string(2, ' ') << "-" << std::string(7, ' ')
                  << (*askIt)->volume();
        ++askIt;
      } else {
        std::cout << std::string(17, ' ');
      }

      std::cout << "]" << std::endl;
    }
  }
};