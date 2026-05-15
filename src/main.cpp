#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <iostream>

#include "GameState.hpp" 
#include "MainMenuView.hpp"
#include "BottomUI.hpp"
#include "MapUI.hpp"
#include "ShopUI.hpp"
#include "PauseUI.hpp"
#include "NightAlertUI.hpp"
#include "GameOverUI.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Team14 Game");
    window.setFramerateLimit(60); 
    ImGui::SFML::Init(window);

    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->Clear();
    io.Fonts->AddFontFromFileTTF("/app/assets/fonts/NanumGothic.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesKorean());
    ImGui::SFML::UpdateFontTexture();

    GameState gs;
    gs.status = Status::AM; 
    gs.showInv = false;

    if (!gs.houseTexture.loadFromFile("assets/image/House.png")) {
        std::cerr << "Failed to load House.png" << std::endl;
    }
    if (!gs.slingshotTexture.loadFromFile("assets/image/Slingshot.png")) {
        std::cerr << "Failed to load Slingshot.png" << std::endl;
    }
    if (!gs.DoorTexture.loadFromFile("assets/image/Door.png")) {
        std::cerr << "Failed to load Door.png" << std::endl;
    }
    if (!gs.roadTexture.loadFromFile("assets/image/Road.png")) {
        std::cerr << "Failed to load Road.png" << std::endl;
    }
    if (!gs.fieldTexture.loadFromFile("assets/image/Field.png")) {
        std::cerr << "Failed to load Field.png" << std::endl;
    }
    if (!gs.outsideTexture.loadFromFile("assets/image/Outside.png")) {
        std::cerr << "Failed to load Outside.png" << std::endl;
    }
    if (!gs.riceSeedTexture.loadFromFile("assets/image/RiceShoot.png")) {
        std::cerr << "Failed to load RiceShoot.png" << std::endl;
    }
    if (!gs.potatoSeedTexture.loadFromFile("assets/image/PotatoSeeds.png")) {
        std::cerr << "Failed to load PotatoSeeds.png" << std::endl;
    }
    if (!gs.carrotSeedTexture.loadFromFile("assets/image/CarrotSeeds.png")) {
        std::cerr << "Failed to load CarrotSeeds.png" << std::endl;
    }
    if (!gs.cowTrapTexture.loadFromFile("assets/image/Cow.png")) {
        std::cerr << "Failed to load Cow.png" << std::endl;
    }
    if (!gs.pigTrapTexture.loadFromFile("assets/image/Pig.png")) {
        std::cerr << "Failed to load Pig.png" << std::endl;
    }
    if (!gs.horseTrapTexture.loadFromFile("assets/image/Horse.png")) {
        std::cerr << "Failed to load Horse.png" << std::endl;
    }
    if (!gs.immatureRiceTexture.loadFromFile("assets/image/ImmatureRice.png")) {
        std::cerr << "Failed to load ImmatureRice.png" << std::endl;
    }
    if (!gs.immaturePotatoTexture.loadFromFile("assets/image/ImmaturePotato.png")) {
        std::cerr << "Failed to load ImmaturePotato.png" << std::endl;
    }
    if (!gs.immatureCarrotTexture.loadFromFile("assets/image/ImmatureCarrot.png")) {
        std::cerr << "Failed to load ImmatureCarrot.png" << std::endl;
    }

    gs.state.inventory.SeedCount[SeedType::SEED1] = 10; 
    gs.state.inventory.SeedCount[SeedType::SEED2] = 5;  
    gs.state.inventory.SeedCount[SeedType::SEED3] = 49; 

    gs.state.inventory.TrapCount[TrapType::ANIMAL1] = 3;
    gs.state.inventory.TrapCount[TrapType::ANIMAL2] = 2;
    gs.state.inventory.TrapCount[TrapType::ANIMAL3] = 5;

    MainUI mUI(&gs);
    BottomUI bUI(&gs);
    MapUI mapUI(&gs);
    ShopUI shopUI(&gs);
    PauseUI pauseUI(&gs);
    NightAlertUI nightUI(&gs);
    GameOverUI overUI(&gs);

    bool testShop = false;
    bool testPause = false;
    bool testNight = false;
    bool testOver = false;

    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);
            
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Num1) testShop = !testShop;
                if (event.key.code == sf::Keyboard::Num2) testPause = !testPause;
                if (event.key.code == sf::Keyboard::Num3) testNight = !testNight;
                if (event.key.code == sf::Keyboard::Num4) testOver = !testOver;
                if (event.key.code == sf::Keyboard::Num5) gs.showInv = !gs.showInv;
            }
        }

        ImGui::SFML::Update(window, clock.restart());
        
        window.clear(sf::Color(45, 45, 45));

        mapUI.Render();
        bUI.Render();

        if (testShop) shopUI.Render();
        if (testPause) pauseUI.Render();
        if (testNight) nightUI.Render();
        if (testOver) overUI.Render();

        ImGui::SetNextWindowPos({10, 10});
        ImGui::Begin("Test Guide", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("숫자키 1: 상점 창 켜기/끄기");
        ImGui::Text("숫자키 2: 일시정지 창 켜기/끄기");
        ImGui::Text("숫자키 3: 밤 알림 창 켜기/끄기");
        ImGui::Text("숫자키 4: 게임오버 창 켜기/끄기");
        ImGui::Text("숫자키 5: 하단 인벤토리 전환");
        ImGui::End();

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    
    std::cout << "UI Test Finished!" << std::endl;
    return 0;
}
