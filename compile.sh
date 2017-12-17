
g++ -std=c++11 -O2 -c get_send_data.cpp
g++ -std=c++11 -O2 -c connect_to_led.cpp
g++ -std=c++11 -O2 -c server.cpp
g++ -o server server.o get_send_data.o connect_to_led.o

rm connect_to_led.o
rm server.o
rm get_send_data.o
