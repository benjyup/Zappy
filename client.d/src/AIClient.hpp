//
// Created by vincent on 24/06/17.
//

#ifndef CLIENT_D_AICLIENT_HPP
#define CLIENT_D_AICLIENT_HPP


#include <utility>
#include <cstring>

class AIClient
{
  AIClient(const std::pair<size_t, size_t> &worldDimension);
  ~AIClient();

 private:
  std::pair<size_t , size_t >		_worldDimension();
};


#endif //CLIENT_D_AICLIENT_HPP
