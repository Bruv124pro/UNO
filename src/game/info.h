#pragma once

#include <iostream>
#include <array>
#include <vector>
#include <cstring>
#include <algorithm>
#include <memory>

#include "../network/msg.h"

namespace UNO { namespace Game {

using namespace Network;

struct Info
{};

struct JoinGameInfo : public Info {
    std::string mUsername;

    JoinGameInfo() {}
    JoinGameInfo(const std::string &username) : mUsername(username) {}

    void Serialize(uint8_t *buffer) const;
    static std::unique_ptr<JoinGameInfo> Deserialize(const uint8_t *buffer);
};

struct GameStartInfo : public Info {
    std::array<Card, 7> mInitHandCards;
    Card mFlippedCard;
    int mFirstPlayer;
    std::vector<std::string> mUsernames;

    GameStartInfo() {}
    GameStartInfo(const std::array<Card, 7> &initHandCards,
        Card flippedCard, int firstPlayer,
        const std::vector<std::string> &usernames) 
        : mInitHandCards(initHandCards), mFlippedCard(flippedCard),
        mFirstPlayer(firstPlayer), mUsernames(usernames) {}

    void Serialize(uint8_t *buffer) const;
    static std::unique_ptr<GameStartInfo> Deserialize(const uint8_t *buffer);

    friend std::ostream& operator<<(std::ostream& os, const GameStartInfo& info);
};

struct ActionInfo : public Info {
    ActionType mActionType;
    int mPlayerIndex;

    ActionInfo() {}
    ActionInfo(ActionType actionType) : mActionType(actionType) {}

    void Serialize(uint8_t *buffer) const;
    static std::unique_ptr<ActionInfo> Deserialize(const uint8_t *buffer);

    friend std::ostream& operator<<(std::ostream& os, const ActionInfo& info);

    // enable polymorphism
    virtual ~ActionInfo() {}
};

struct DrawInfo : public ActionInfo {
    int mNumber;

    DrawInfo() {}
    DrawInfo(int number) : ActionInfo(ActionType::DRAW), mNumber(number) {}

    void Serialize(uint8_t *buffer) const;
    static std::unique_ptr<DrawInfo> Deserialize(const uint8_t *buffer);

    friend std::ostream& operator<<(std::ostream& os, const DrawInfo& info);
};

struct SkipInfo : public ActionInfo {
    SkipInfo() : ActionInfo(ActionType::SKIP) {}

    void Serialize(uint8_t *buffer) const;
    static std::unique_ptr<SkipInfo> Deserialize(const uint8_t *buffer);

    friend std::ostream& operator<<(std::ostream& os, const SkipInfo& info);
};

struct PlayInfo : public ActionInfo {
    Card mCard;
    CardColor mNextColor;

    PlayInfo() {}
    PlayInfo(Card card, CardColor nextColor)
        : ActionInfo(ActionType::PLAY), mCard(card), mNextColor(nextColor) {}

    void Serialize(uint8_t *buffer) const;
    static std::unique_ptr<PlayInfo> Deserialize(const uint8_t *buffer);

    friend std::ostream& operator<<(std::ostream& os, const PlayInfo& info);
};

struct DrawRspInfo : public Info {
    int mNumber;
    std::vector<Card> mCards;

    DrawRspInfo() {}
    DrawRspInfo(int number, const std::vector<Card> cards) 
        : mNumber(number), mCards(cards) {}

    void Serialize(uint8_t *buffer) const;
    static std::unique_ptr<DrawRspInfo> Deserialize(const uint8_t *buffer);

    friend std::ostream& operator<<(std::ostream& os, const DrawRspInfo& info);
};
}}