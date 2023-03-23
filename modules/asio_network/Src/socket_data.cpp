#include <network_module.hpp>

anet::socket_data::socket_data(const io__::any_io_executor& ios) : socket_(ios)
{
}

void anet::socket_data::shutdown() noexcept
{
    if (!socket_.is_open())
        return;
    try
    {
        socket_.shutdown(io__::ip::tcp::socket::shutdown_both);
        socket_.close();
    }
    catch (const boost::system::system_error &ex)
    {
        std::cerr << "@thread:" << boost::this_thread::get_id() << ": " << ex.what() << '\n';
        std::terminate();
    }
}

anet::socket_data::~socket_data() { shutdown(); }


anet::socket_data_ptr anet::make_socket_data(const io__::any_io_executor& ios)
{
    return std::make_shared<socket_data>(ios);
}

anet::end_point_wrapper::end_point_wrapper(unsigned short port, const std::string &address)
    : point_(io__::ip::make_address(address, error_), port)
{
}

anet::end_point_wrapper::end_point_wrapper(unsigned short port, const io__::ip::tcp &address)
    : point_(address, port)
{
}
