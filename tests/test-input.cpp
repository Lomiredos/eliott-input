#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "input/InputManager.hpp"
#include "input/ActionMap.hpp"

enum class Action { Jump, Run };

using namespace ee::input;


TEST_CASE("Teste de l'action map") {
    
    ActionMap<Action> map;

    map.bind(Action::Jump, {{SDL_SCANCODE_SPACE, TriggerState::Down}});

    CHECK(map.getSize() == 1);

    CHECK(map.isActive(Action::Jump) == false);

    CHECK(map.isActive(Action::Run) == false);
}

TEST_CASE("test du singleton InputManager"){

    InputManager& im = InputManager::getInstance();

    CHECK(im.getMousePosX() == 0);

    CHECK(im.IsKeyDown(SDL_SCANCODE_A) == false);
    
    auto& a = InputManager::getInstance();
    auto& b = InputManager::getInstance();
    CHECK(&a == &b);  // même adresse = même objet





}
