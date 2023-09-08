#pragma once

#include "Order.h"
#include "OrderData.h"

#include <iostream>
#include <vector>
#include <optional>

// TODO: create a base Parser base class to allow derived class to parse data from different
// sources.
/// @brief  Class for parsing Optiver's Ready Trader Go market data files.
class CSVParser {
 public:
  CSVParser(std::istream* file);
  std::optional<OrderData> nextOrder();

 private:
  /// @brief  The file that is being parsed.
  std::istream* m_file;

  /// @brief  The current line that is being parsed.
  std::string m_line;
};