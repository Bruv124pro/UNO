#include "cards.h"

namespace UNO { namespace Game {

void HandCards::GetInitHandCards(const std::array<Card, 7> &cards)
{
    mCards.resize(cards.size());
    std::copy(cards.begin(), cards.end(), mCards.begin());
}

void HandCards::Draw(const std::vector<Card> &cards)
{
    std::for_each(cards.begin(), cards.end(), [this](const Card &card) {
        mCards.push_back(card);
    });
}

bool HandCards::Play(int index, Card lastPlayedCard)
{
    if (index >= mCards.size()) {
        return false;
    }

    Card cardToPlay = mCards[index];
    bool isUno = mCards.size() == 1;
    if (!cardToPlay.CanBePlayerAfter(lastPlayedCard, isUno)) {
        return false;
    }

    mCards.erase(mCards.begin() + index);
    return true;
}

bool Card::CanBePlayerAfter(Card lastPlayedCard, bool isUno)
{
    std::set<CardText> specialTexts{CardText::SKIP, CardText::REVERSE, 
        CardText::DRAW_TWO, CardText::WILD, CardText::DRAW_FOUR};

    // special cards can not be played as the last one
    if (isUno && specialTexts.count(mText)) {
        return false;
    }

    // if the last played card is skip, you can only play a skip
    if (lastPlayedCard.mText == CardText::SKIP) {
        return mText == CardText::SKIP;
    }

    // if the last played card is draw two, you can only play a draw two or draw four
    if (lastPlayedCard.mText == CardText::DRAW_TWO) {
        return (mText == CardText::DRAW_TWO || mText == CardText::DRAW_FOUR);
    }

    // if the last played card is draw four, you can only play a draw four
    if (lastPlayedCard.mText == CardText::DRAW_FOUR) {
        return mText == CardText::DRAW_FOUR;
    }

    // wild card can always be played except above conditions
    if (mColor == CardColor::BLACK) {
        return true;
    }

    // if not wild card, only cards with the same num or color can be played
    return (mColor == lastPlayedCard.mColor || mText == lastPlayedCard.mText);
}

std::ostream& operator<<(std::ostream& os, const HandCards& handCards)
{
    os << "Your hand cards are: [";
    if (handCards.mCards.empty()) {
        os << "]";
        return os;
    }

    for (int i = 0; i < handCards.mCards.size() - 1; i++) {
        os << handCards.mCards[i] << ", ";
    }
    os << handCards.mCards.back() << "]";
    return os;
}

Card::Card(const char *str)
{
    switch (*str) {
        case 'R': mColor = CardColor::RED;    str++; break;
        case 'Y': mColor = CardColor::YELLOW; str++; break;
        case 'G': mColor = CardColor::GREEN;  str++; break;
        case 'B': mColor = CardColor::BLUE;   str++; break;
        default:  mColor = CardColor::BLACK;
    }

    switch (*str) {
        case '0': mText = CardText::ZERO;    break;
        case '1': mText = CardText::ONE;     break;
        case '2': mText = CardText::TWO;     break;
        case '3': mText = CardText::THREE;   break;
        case '4': mText = CardText::FOUR;    break;
        case '5': mText = CardText::FIVE;    break;
        case '6': mText = CardText::SIX;     break;
        case '7': mText = CardText::SEVEN;   break;
        case '8': mText = CardText::EIGHT;   break;
        case '9': mText = CardText::NINE;    break;
        case 'S': mText = CardText::SKIP;    break;
        case 'R': mText = CardText::REVERSE; break;
        case 'W': mText = CardText::WILD;    break;
        case '+': mText = (*(str + 1) == '2') ? 
            CardText::DRAW_TWO : CardText::DRAW_FOUR; 
            break;
        default: assert(0);
    }
}

CardColor Card::FromChar(char c)
{
    switch (c) {
        case 'R': return CardColor::RED;
        case 'Y': return CardColor::YELLOW;
        case 'G': return CardColor::GREEN;
        case 'B': return CardColor::BLUE;
    }
    assert(0);
}

std::ostream& operator<<(std::ostream& os, const Card& card)
{
    std::string color;
    std::string text;

    switch (card.mColor) {
        case CardColor::RED:    color = "R"; break;
        case CardColor::YELLOW: color = "Y"; break;
        case CardColor::GREEN:  color = "G"; break;
        case CardColor::BLUE:   color = "B"; break;
        case CardColor::BLACK:  color = "";  break;
        default: assert(0);
    }

    switch (card.mText) {
        case CardText::ZERO:        text = "0";  break;
        case CardText::ONE:         text = "1";  break;
        case CardText::TWO:         text = "2";  break;
        case CardText::THREE:       text = "3";  break;
        case CardText::FOUR:        text = "4";  break;
        case CardText::FIVE:        text = "5";  break;
        case CardText::SIX:         text = "6";  break;
        case CardText::SEVEN:       text = "7";  break;
        case CardText::EIGHT:       text = "8";  break;
        case CardText::NINE:        text = "9";  break;
        case CardText::SKIP:        text = "S";  break;
        case CardText::REVERSE:     text = "R";  break;
        case CardText::DRAW_TWO:    text = "+2"; break;
        case CardText::WILD:        text = "W";  break;
        case CardText::DRAW_FOUR:   text = "+4"; break;
        default: assert(0);
    }

    os << color << text;
    return os;
}

std::ostream& operator<<(std::ostream& os, const CardColor& color)
{
    std::string colorStr;
    switch (color) {
        case CardColor::RED:    colorStr = "RED";    break;
        case CardColor::YELLOW: colorStr = "YELLOW"; break;
        case CardColor::GREEN:  colorStr = "GREEN";  break;
        case CardColor::BLUE:   colorStr = "BLUE";   break;
        default: assert(0);
    }

    os << colorStr;
    return os;
}

}}