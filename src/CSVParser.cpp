#include "CSVParser.h"
#include "Order.h"
#include "OrderData.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <optional>

CSVParser::CSVParser(std::istream* file) : m_file(file) {
  // Skip the column titles row.
  std::getline(*m_file, m_line);
}

std::optional<OrderData> CSVParser::nextOrder() {
  std::getline(*m_file, m_line);

  std::vector<std::string> cells;
  std::string cell;
  std::stringstream lineStream(m_line);

  // Handle if reach end of the file.
  if (!lineStream) {
    return std::nullopt;
  }

  while (std::getline(lineStream, cell, ',')) {
    cells.push_back(cell);
  }

  OrderData orderData{
      stoi(cells[0]),
      stoi(cells[1]),
      cells[2],
      stoi(cells[3]),
      cells[4] == "B" ? "buy" : "sell",
      cells[5] != "" ? stoi(cells[5]) : NULL,
      cells[6] != "" ? stoi(cells[6]) : NULL,
      cells.size() == 8 ? cells[7] : ""};

  return orderData;
}
