/**
 * @file    DefaultCommandGateway.cpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    22.03.2024
 */

#include <Sim808/DefaultCommandGateway.hpp>

#include <asio/read_until.hpp>

namespace Sim808
{

DefaultCommandGateway::DefaultCommandGateway(asio::io_context& ioc, const std::filesystem::path& path)
    : _serial(ioc, path.string())
{
    _serial.set_option(asio::serial_port::baud_rate(115200));
    _serial.send_break();
}

DefaultCommandGateway::~DefaultCommandGateway()
{
    if (_serial.is_open())
    {
        _serial.close();
    }
}

auto DefaultCommandGateway::send(std::string_view command) -> Response
{
    _serial.write_some(asio::buffer(command));
    return readResponse();
}

auto DefaultCommandGateway::sendData(std::string_view data) -> void
{
    _serial.write_some(asio::buffer(data));
}

auto DefaultCommandGateway::waitFor(std::string_view str) -> void
{
    std::string tmp;
    asio::read_until(_serial, asio::dynamic_buffer(tmp), str);
}

auto DefaultCommandGateway::readResponse() -> Response
{
    Response response;

    std::string buffer;
    while (true)
    {
        const auto chunk_size = asio::read_until(_serial, asio::dynamic_buffer(buffer), cr_lf);
        const auto chunk_data = std::string_view(buffer.data(), chunk_size);

        if (const auto maybe_code = tryConvertToResultCode(chunk_data))
        {
            response.code = maybe_code.value();
            break;
        }

        response.data += chunk_data;
        buffer.erase(0, chunk_size);
    }

    while (response.data.starts_with(cr_lf))
    {
        response.data.erase(0, cr_lf.size());
    }

    return response;
}

} // namespace Sim808
