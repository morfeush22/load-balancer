//
// Created by morfeush22 on 04.03.19.
//

#ifndef LOAD_BALANCER_PROXYCONNECTION_H
#define LOAD_BALANCER_PROXYCONNECTION_H

#include "BackendServersRepository.h"
#include "SchedulingStrategy.h"
#include <boost/asio.hpp>


class ProxyConnection : public std::enable_shared_from_this<ProxyConnection> {

public:
    /**
     * Mediator that handles connections between client and backend server. Acts like Reverse Proxy. Chooses backend server
     * using cookie settings or SchedulingStrategy class object.
     * @param io_context Reference to Boost io_context object
     * @param backend_servers_repository Pointer to BackendServersRepository class instance
     * @param scheduling_strategy Pointer to SchedulingStrategy class instance
     * @param backend_insert_cookie Whether to insert cookie to enable sticky sessions - further request will always be handled
     * with the same backend server
     * @param backend_cookie_name Name of cookie to be looked for in client headers, can be empty to disable search
     */
    ProxyConnection(boost::asio::io_context &io_context,
                        std::shared_ptr<BackendServersRepository> backend_servers_repository,
                        std::shared_ptr<SchedulingStrategy> scheduling_strategy,
                        bool backend_insert_cookie,
                        std::string backend_cookie_name);

    /**
     * Returns reference to client part socket of connection.
     * @return Reference to boost::asio::ip::tcp::socket object
     */
    boost::asio::ip::tcp::socket &FrontendSocket();

    /**
     * Starts operation of proxying.
     */
    void run();

private:
    bool backend_insert_cookie_;
    std::string backend_cookie_name_;
    BackendServerDescription chosen_server_;
    std::shared_ptr<BackendServersRepository> backend_servers_repository_;
    boost::beast::flat_buffer client_buffer_;
    boost::beast::http::request<boost::beast::http::string_body> client_request_;
    boost::beast::http::response<boost::beast::http::string_body> client_response_;
    boost::asio::ip::tcp::socket client_socket_;
    boost::asio::ip::tcp::resolver resolver_;
    boost::beast::flat_buffer server_buffer_;
    boost::beast::http::request<boost::beast::http::string_body> server_request_;
    boost::beast::http::response<boost::beast::http::string_body> server_response_;
    boost::asio::ip::tcp::socket server_socket_;
    std::shared_ptr<SchedulingStrategy> scheduling_strategy_;

    void on_client_read(boost::beast::error_code error_code, std::size_t bytes_transferred);

    void on_client_write(boost::beast::error_code error_code, std::size_t bytes_transferred);

    void on_server_resolve(
            boost::beast::error_code error_code,
            boost::asio::ip::tcp::resolver::iterator endpoint_iterator);

    void on_server_connect(
            boost::beast::error_code error_code,
            boost::asio::ip::tcp::resolver::iterator endpoint_iterator);

    void on_server_read(boost::beast::error_code error_code, std::size_t bytes_transferred);

    void on_server_write(boost::beast::error_code error_code, std::size_t bytes_transferred);

    void do_close();
};


#endif //LOAD_BALANCER_PROXYCONNECTION_H
