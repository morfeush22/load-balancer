//
// Created by morfeush22 on 05.03.19.
//

#include "../include/ProxyConnectionFactory.h"

ProxyConnectionFactory::ProxyConnectionFactory(boost::asio::io_context &io_context):
_io_context(io_context)
{}

std::shared_ptr<ProxyConnection> ProxyConnectionFactory::MakeProxyConnection() {
    return std::make_shared<ProxyConnection>(_io_context);
}
