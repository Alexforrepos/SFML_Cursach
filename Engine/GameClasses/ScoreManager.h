#pragma once

class ScoreManager {
private:
    int score = 200;
    ScoreManager() = default;
public:
    static ScoreManager& get() {
        static ScoreManager inst;
        return inst;
    }
    void reset() 
    { 
        score = 200; 
    }
    int getScore() const { return score; }
    void addScore(int delta) { score += delta; }
    bool spend(int cost) {
        if (score >= cost) { score -= cost; return true; }
        return false;
    }
};