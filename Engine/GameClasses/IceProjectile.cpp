//#include "IceProjectile.h"
//
//
//void IceProjectile::update() {
//    // ������� ����
//    Projectile::update();
//
//    // ��������� ����������� �� �����
//    for (auto& objPtr : O_Manager::get().getVector()) {
//        if (objPtr->type() != int(Types::BaseZombieType))
//            continue;
//
//        auto* zombie = static_cast<Zombie*>(objPtr.get());
//        if (this->getBounds().intersects(zombie->getBounds())) {
//            // ��������� ����� ���������� � 2 ���� �� 2 �������
//            zombie->applyStatus(StatusEffect::Slow,
//                /*factor=*/0.5f,
//                /*duration=*/sf::seconds(2.f));
//
//            // ��� ��������� �� ����������� ���� (����� ��� MSG_Manager)
//            MSG_Manager::get().addMSG(
//                std::make_shared<Engine::MSG_TYPE_KILL>(this, this)
//            );
//            break;
//        }
//    }
//}