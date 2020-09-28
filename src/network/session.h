#pragma once

#include <iostream>
#include <asio.hpp>

#include "msg.h"
#include "../game/info.h"

namespace UNO { namespace Network {

using asio::ip::tcp;

class Session {
public:
    explicit Session(tcp::socket socket);

    template <typename InfoT>
    std::unique_ptr<InfoT> ReceiveInfo() {
        Read();
        return InfoT::Deserialize(mReadBuffer);
    }

    template <typename InfoT>
    void DeliverInfo(const InfoT &info) {
        info.Serialize(mWriteBuffer);
        Write();
    }

private:
    // read from mSocket to mReadBuffer
    void Read();

    // write from mWriteBuffer to mSocket
    void Write();

private:
    constexpr static int MAX_BUFFER_SIZE = 256;

    tcp::socket mSocket;
    uint8_t mReadBuffer[MAX_BUFFER_SIZE];
    uint8_t mWriteBuffer[MAX_BUFFER_SIZE];
};
}}