#include "Order.h"
#include "OrderData.h"

#include <ctime>
#include <string>

Order::Order(OrderData orderData) : m_orderData(orderData){};

int Order::id() const {
  return m_orderData.orderId;
};

std::string Order::side() const {
  return m_orderData.side;
};

double Order::price() const {
  return m_orderData.price;
};

int Order::volume() const {
  return m_orderData.volume;
};

std::time_t Order::time() const {
  return m_orderData.time;
}

void Order::subtractVolume(int volume) {
  m_orderData.volume -= volume;
};