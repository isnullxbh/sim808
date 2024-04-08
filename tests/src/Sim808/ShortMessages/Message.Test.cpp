/**
 * @file    Message.Test.cpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    06.04.2024
 */

#include <gtest/gtest.h>

#include <Sim808/ShortMessages/Message.hpp>

TEST(ShortMessages_Message, Parse)
{
    using Sim808::ShortMessages::Message;
    using Sim808::ShortMessages::MessageStorageType;
    using Sim808::ShortMessages::MessageTransferType;

    {
        // Delivery message
        const std::string_view str = "1,\"REC UNREAD\",\"+79230022855\",\"\",\"24/04/06,00:31:24+28\"\r\nHi!";
        const auto message = Message::parse(str);
        ASSERT_TRUE(message);
        EXPECT_EQ(message->index(), 1U);
        EXPECT_EQ(message->storageType(), MessageStorageType::Unread);
        EXPECT_EQ(message->senderNumber(), "+79230022855");
        EXPECT_EQ(message->sender(), "");
        EXPECT_EQ(message->timestamp(), "24/04/06,00:31:24+28");
        EXPECT_EQ(message->text(), "Hi!");
    }
}
