#pragma once

#include <vector>
#include <utility>
#include <thread>

#include "../game/stat.h"
#include "view.h"
#include "inputter.h"
#include "outputter.h"

namespace UNO { namespace UI {

using namespace Game;

class UIManager {
public:
    UIManager(std::unique_ptr<GameStat> &gameStat,
              std::vector<PlayerStat> &playerStats,
              std::unique_ptr<HandCards> &handCards);

    ~UIManager() { mTimerThread->join(); }

    void RunTimerThread();

    void Render();

    std::pair<InputAction, int> GetAction(bool lastCardCanBePlayed, 
        bool hasChanceToPlayAfterDraw);

    CardColor SpecifyNextColor();

    void NextTurn();

    void MoveCursorTo(int index) { mCursorIndex = index; }

private:
    void TimerThreadLoop();

    void Print() const;

    void ResetCursor() { MoveCursorTo(0); }

    void ResetTimeLeft() { mTimeLeft = 15000; }

    int PlayerNum() const { return mPlayerStats.size(); }

    void RenderSelf();

    void RenderOthers();

    void ClearScreen() const;

private:
    std::unique_ptr<View> mView;
    std::unique_ptr<Inputter> mInputter;
    std::unique_ptr<Outputter> mOutputter;

    std::unique_ptr<GameStat> &mGameStat;
    std::vector<PlayerStat> &mPlayerStats;
    std::unique_ptr<HandCards> &mHandCards;
    int mCursorIndex{0};
    int mTimeLeft;

    std::unique_ptr<std::thread> mTimerThread;

    bool mLastCardCanBePlayed;
    bool mHasChanceToPlayAfterDraw;
    bool mIsSpecifyingNextColor;
};
}}