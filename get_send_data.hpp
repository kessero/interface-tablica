#ifndef PREPAREDATA_H
#define PREPAREDATA_H
#include <string.h>
#include "json.hpp"
#include <vector>

class Prepare_Data{
public:
  Prepare_Data(std::string port_number, int baud_rate, int sock);

private:
  nlohmann::json parse_data_from_socket_stream(int sock_d);
  int calculate_configuration_number(nlohmann::json recive_d);
  std::vector <int> sort_data_recived(nlohmann::json recive_data, int config_number);

};
#endif
