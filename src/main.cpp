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
        ImGui::End();

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    
    std::cout << "UI Test Finished!" << std::endl;
    return 0;
}
