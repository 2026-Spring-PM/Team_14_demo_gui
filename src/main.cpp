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

enum class ScreenState {
    MAIN_MENU,
    MAP,
    SHOP,
    PAUSE,
    NIGHT,
    GAME_OVER
};

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

    gs.LoadAllTextures();

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

    ScreenState currentScreen = ScreenState::MAIN_MENU;

    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Num0) currentScreen = ScreenState::MAIN_MENU;
                if (event.key.code == sf::Keyboard::Num1) currentScreen = ScreenState::MAP;
                if (event.key.code == sf::Keyboard::Num2) currentScreen = ScreenState::SHOP;
                if (event.key.code == sf::Keyboard::Num3) currentScreen = ScreenState::PAUSE;
                if (event.key.code == sf::Keyboard::Num4) currentScreen = ScreenState::NIGHT;
                if (event.key.code == sf::Keyboard::Num5) currentScreen = ScreenState::GAME_OVER;
                if (event.key.code == sf::Keyboard::Num6) gs.showInv = !gs.showInv;
            }
        }

        ImGui::SFML::Update(window, clock.restart());
        window.clear(sf::Color(45, 45, 45));

        if (currentScreen == ScreenState::MAIN_MENU) {
            mUI.Render();
        } 
        else {
            mapUI.Render();
            bUI.Render();

            if (currentScreen == ScreenState::SHOP) shopUI.Render();
            if (currentScreen == ScreenState::PAUSE) pauseUI.Render();
            if (currentScreen == ScreenState::NIGHT) nightUI.Render();
            if (currentScreen == ScreenState::GAME_OVER) overUI.Render();
        }

        ImGui::SetNextWindowPos({10, 10});
        ImGui::Begin("Test Guide", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("숫자키 0: 메인 메뉴로");
        ImGui::Text("숫자키 1: 기본 게임 화면 (Map)");
        ImGui::Text("숫자키 2: 상점 팝업 띄우기");
        ImGui::Text("숫자키 3: 일시정지 팝업 띄우기");
        ImGui::Text("숫자키 4: 밤 알림 팝업 띄우기");
        ImGui::Text("숫자키 5: 게임오버 팝업 띄우기");
        ImGui::Text("숫자키 6: 하단 인벤토리 전환");
        ImGui::End();

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    
    std::cout << "UI Test Finished!" << std::endl;
    return 0;
}
