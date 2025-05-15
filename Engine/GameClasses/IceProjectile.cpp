//#include "IceProjectile.h"
//
//
//void IceProjectile::update() {
//    // двигаем пулю
//    Projectile::update();
//
//    // проверяем пересечение со зомби
//    for (auto& objPtr : O_Manager::get().getVector()) {
//        if (objPtr->type() != int(Types::BaseZombieType))
//            continue;
//
//        auto* zombie = static_cast<Zombie*>(objPtr.get());
//        if (this->getBounds().intersects(zombie->getBounds())) {
//            // назначаем зомби замедление в 2 раза на 2 секунды
//            zombie->applyStatus(StatusEffect::Slow,
//                /*factor=*/0.5f,
//                /*duration=*/sf::seconds(2.f));
//
//            // шлём сообщение об уничтожении пули (через ваш MSG_Manager)
//            MSG_Manager::get().addMSG(
//                std::make_shared<Engine::MSG_TYPE_KILL>(this, this)
//            );
//            break;
//        }
//    }
//}