#include "IOutput.h"
#include "ConsoleOutput.h"

#include <iostream>
#include <algorithm>
#include <iomanip>

ConsoleOutput::ConsoleOutput(const OrderBook& orderBook) : IOutput(orderBook){};

void ConsoleOutput::displayOrderBook() const {
  system("cls");

  std::cout << std::fixed << std::setprecision(2);

  std::cout << "         BIDS             ASKS" << std::endl;
  std::cout << " QUANTITY    PRICE   PRICE    QUANTITY" << std::endl;

  size_t maxSize = std::max(m_orderBook.bidSize(), m_orderBook.askSize());
  const auto& bids = m_orderBook.getBids();
  const auto& asks = m_orderBook.getAsks();

  auto bidIt = bids.begin();
  auto askIt = asks.begin();

  for (size_t i = 0; i < maxSize; ++i) {
    std::cout << "[";

    if (bidIt != bids.end()) {
      std::cout << (*bidIt)->getQuantity() << std::string(7, ' ') << "-" << std::string(2, ' ')
                << (*bidIt)->getPrice();
      ++bidIt;
    } else {
      std::cout << std::string(17, ' ');
    }

    std::cout << " | ";

    if (askIt != asks.end()) {
      std::cout << (*askIt)->getPrice() << std::string(2, ' ') << "-" << std::string(7, ' ')
                << (*askIt)->getQuantity();
      ++askIt;
    } else {
      std::cout << std::string(17, ' ');
    }

    std::cout << "]" << std::endl;
  }
};