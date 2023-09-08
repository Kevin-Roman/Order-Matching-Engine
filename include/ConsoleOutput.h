#pragma once

#include "IOutput.h"
#include "OrderBook.h"

#include <iostream>

/// @brief Class for displaying the orderbook to the standard output stream.
class ConsoleOutput : public IOutput {
 public:
  ConsoleOutput(const OrderBook& orderBook);

  void displayOrderBook() const override;
};