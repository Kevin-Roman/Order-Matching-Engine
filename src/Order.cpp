#include "Order.h"

#include <string>

Order::Order(
    const std::string orderType,
    const std::string direction,
    const double price,
    const int quantity)
    : m_orderType(orderType), m_direction(direction), m_price(price), m_quantity(quantity){};

std::string Order::getDirection() const {
  return m_direction;
};

double Order::getPrice() const {
  return m_price;
};

int Order::getQuantity() const {
  return m_quantity;
};

void Order::subtractQuantity(int quantity) {
  m_quantity -= quantity;
};