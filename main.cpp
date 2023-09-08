#include "MatchingEngine.h"
#include "Order.h"
#include "OrderData.h"
#include "ConsoleOutput.h"
#include "CSVParser.h"

#include <iostream>
#include <memory>
#include <ctime>
#include <fstream>
#include <sstream>
#include <thread>

int main() {
  auto orderBook = std::make_unique<OrderBook>();

  std::ifstream file("C:/Users/kevro/Programming/Order-Matching-Engine/data/market_data1.csv");
  CSVParser csvParser(&file);

  ConsoleOutput consoleOutput(*orderBook);
  MatchingEngine engine(std::move(orderBook), &csvParser);

  std::thread orders(&MatchingEngine::parseOrders, &engine);
  std::thread process(&MatchingEngine::run, &engine);
  std::thread display(&ConsoleOutput::displayOrderBook, &consoleOutput);

  orders.join();
  process.join();
  display.join();

  file.close();
}