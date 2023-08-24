#include "MatchingEngine.h"
#include "Order.h"
#include "ConsoleOutput.h"

#include <iostream>
#include <memory>

int main() {
  auto orderBook = std::make_unique<OrderBook>();
  ConsoleOutput consoleOutput(*orderBook);

  auto buyOrder1 = std::make_unique<Order>("limit", "buy", 102.55, 24);
  auto buyOrder2 = std::make_unique<Order>("limit", "buy", 102.55, 14);
  auto buyOrder3 = std::make_unique<Order>("limit", "buy", 102.54, 131);
  auto buyOrder4 = std::make_unique<Order>("limit", "buy", 101.87, 32);
  auto sellOrder1 = std::make_unique<Order>("limit", "sell", 103.23, 48);
  auto sellOrder2 = std::make_unique<Order>("limit", "sell", 103.98, 84);
  auto sellOrder3 = std::make_unique<Order>("limit", "sell", 104.17, 38);
  auto sellOrder4 = std::make_unique<Order>("limit", "sell", 104.75, 127);

  orderBook->add(std::move(buyOrder1));
  orderBook->add(std::move(buyOrder2));
  orderBook->add(std::move(buyOrder3));
  orderBook->add(std::move(buyOrder4));
  orderBook->add(std::move(sellOrder1));
  orderBook->add(std::move(sellOrder2));
  orderBook->add(std::move(sellOrder3));
  orderBook->add(std::move(sellOrder4));

  MatchingEngine engine(std::move(orderBook));

  consoleOutput.displayOrderBook();
  std::getchar();

  auto sellOrder5 = std::make_unique<Order>("limit", "sell", 102.55, 40);
  engine.process(std::move(sellOrder5));
  consoleOutput.displayOrderBook();
  std::getchar();
}