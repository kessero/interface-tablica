#include "get_send_data.hpp"
#include "connect_to_led.hpp"

nlohmann::json Prepare_Data::parse_data_from_socket_stream(int sock_data){
  int n;
  using json = nlohmann::json;
  std::stringstream stringStream;
  //$address $speed $delete $size $place $red $green $blue $l1 $l2 $l3 $l4 $l5 $l6 $l7 $l8 $loop_work
  unsigned char buffer[500];
  bzero(buffer,500);
  n = read(sock_data,buffer,499);
  std::cout <<"bufor: "<< buffer << "\n";
  // fill a stream with JSON text
  stringStream << buffer;
  json j_complete_data = json::parse(stringStream);
  return j_complete_data;
};

int Prepare_Data::calculate_configuration_number(nlohmann::json recive_d){
   return recive_d[1].get<int>()*64+ recive_d[2].get<int>()*32+ recive_d[3].get<int>()*16+ recive_d[4].get<int>()*8+ recive_d[7].get<int>()*4+ recive_d[6].get<int>()*2+ recive_d[5].get<int>();
};

bool check_if_zero (int i) { return ((i==0)==1); };
std::vector <int> Prepare_Data::sort_data_recived(nlohmann::json recive_data, int config_number){
  std::vector<int> data_sorted;
  data_sorted.push_back(recive_data[0].get<int>());
  data_sorted.push_back(config_number);
  int seven_fields_are_for_configuration = 7;
  int counter = recive_data.size()-seven_fields_are_for_configuration;
  for (int i = 2; i< counter; i++){
    data_sorted.push_back(recive_data[i+6].get<int>());
  }
  if(recive_data[recive_data.size()-1].get<int>()<1){
    data_sorted.push_back(127);
  }else{
    data_sorted.push_back(126);
  }
  int suma_kontrolna = 0;
  for (int i = 0; i<data_sorted.size(); i++){
    suma_kontrolna += data_sorted[i];
  }
  data_sorted.push_back(suma_kontrolna%128);
  return data_sorted;
}

Prepare_Data::Prepare_Data(std::string port_n, int baud_r, int sock_n){
  nlohmann::json complet_recive_data = parse_data_from_socket_stream(sock_n);
  int configuration = calculate_configuration_number(complet_recive_data);
  std::vector < int > data_send_to_LED = sort_data_recived(complet_recive_data, configuration);
  //usuwanie elementow zerowych ponieważ tablica nie radzi sobie z tymi wartosciami i pokazuje %^&*(); Ostatni element musi być pominięty przy usuwaniu zer, ponieważ może modulo z sumy kontrolnej wyjść zero.
  std::vector<int>::iterator newEnd = std::remove_if (data_send_to_LED.begin(), data_send_to_LED.end()-1, check_if_zero);
  data_send_to_LED.erase(newEnd, data_send_to_LED.end()-1);
  int *pv = &data_send_to_LED[0];
  int rec_data;
  Connect_to_led conn_to_led;
  conn_to_led.openPort_USB(port_n, baud_r);
  //send data to LED
  conn_to_led.writePort(pv, data_send_to_LED.size());
  sleep(1);
  rec_data = conn_to_led.readPort();
  //close port
  conn_to_led.closePort_USB();
  //info about correct data send if rc_data = 1 data send OK
  int led_answer_data;
  if(rec_data == 1){
    led_answer_data = write(sock_n,"OK",2);
  }else{
    led_answer_data = write(sock_n,"Transmision ERROR!!!",100);
  }

}
