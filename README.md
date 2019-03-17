# load-balancer

Very simple load balancer, built using boost::asio.

To build:
```sh
mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

To run:
```sh
./main --config_file_path ../config.ini
```

List of supported features:
- health checks
- two scheduling algorithms: `round_robin` and `weighted_round_robin`
- sticky sessions, either by inserting cookie, or using cookie configured by backend server
