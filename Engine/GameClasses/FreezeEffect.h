#include "Effect.h"
#include "GameClasses/Zombie.h"

class FreezeEffect : public Effect {
public:
    FreezeEffect()
        : Effect(200, 1)  // ������ � ID �������
    {
    }

    //void influence(Zombie& target) override {
    //    target.velocity = std::max(0.0f, target.velocity - 2.0f);  // ���������� �� 2.0
    //}
};