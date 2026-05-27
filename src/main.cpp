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
#include "DaySettlementUI.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Team14 Game");
    window.setFramerateLimit(60); 
    ImGui::SFML::Init(window);

    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->Clear();
    io.Fonts->AddFontFromFileTTF("/app/assets/fonts/NanumGothic.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesKorean());
    ImGui::SFML::UpdateFontTexture();

    GameState gs;
    gs.LoadAllTextures();
    gs.Reset();
    MainUI mUI(&gs);
    BottomUI bUI(&gs);
    MapUI mapUI(&gs);
    ShopUI shopUI(&gs);
    PauseUI pauseUI(&gs);
    NightAlertUI nightUI(&gs);
    GameOverUI overUI(&gs);
    DaySettlementUI settlementUI(&gs);

    sf::Clock clock;
    sf::Clock deltaClock; 

    while (window.isOpen()) {
        float deltaTime = deltaClock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Num0) gs.status = Status::MAIN;
                if (event.key.code == sf::Keyboard::Num1) {
                    gs.farm.Hour = 8;
                    gs.status = Status::AM;
                }
                if (event.key.code == sf::Keyboard::Num2) {
                    gs.farm.Hour = 20;
                    gs.status = Status::PM;
                }
                if (event.key.code == sf::Keyboard::Num3) gs.status = Status::SHOP;
                if (event.key.code == sf::Keyboard::Num4) gs.status = Status::PAUSE;
                if (event.key.code == sf::Keyboard::Escape){
                    pauseUI.beforestatus=gs.status;
                    gs.status = Status::PAUSE;

                }
                if (event.key.code == sf::Keyboard::Num5) gs.status = Status::PM;
                if (event.key.code == sf::Keyboard::Num6) gs.status = Status::GAMEOVER;
                if (event.key.code == sf::Keyboard::Num7) gs.showInv = !gs.showInv;
                if (event.key.code == sf::Keyboard::Num8) gs.status = Status::SETTLEMENT;
                
                if (event.key.code == sf::Keyboard::Num9) {
                    gs.farm.ActiveEnemies.push_back(Enemy(0.5f, 8.0f, EnemyType::NONE, 0, 100));
                }
            }
        }

        for (auto& enemy : gs.farm.ActiveEnemies) {
            enemy.Move(deltaTime);
        }

        ImGui::SFML::Update(window, clock.restart());
        window.clear(sf::Color(45, 45, 45));

        if (gs.status == Status::MAIN) {
            mUI.Render();
        } 
        else {
            mapUI.Render();
            bUI.Render();

            if (gs.status == Status::SHOP) shopUI.Render();
            if (gs.status == Status::PAUSE) pauseUI.Render();
            if (gs.status == Status::GAMEOVER) overUI.Render();
            if (gs.status == Status::SETTLEMENT) settlementUI.Render();
            if (gs.showNightAlert) nightUI.Render();
        }

        ImGui::SetNextWindowPos({10, 10});
        ImGui::Begin("Test Guide", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("숫자키 0: 메인 메뉴로");
        
        ImGui::Text("숫자키 1: 기본 게임 화면 (낮 Map)");
        ImGui::Text("숫자키 2: 기본 게임 화면 (밤 Map)");
        ImGui::Text("숫자키 3: 상점 팝업 띄우기");
        ImGui::Text("숫자키 4 or esc: 일시정지 팝업 띄우기");
        ImGui::Text("숫자키 5: 밤 알림 팝업 띄우기");
        ImGui::Text("숫자키 6: 게임오버 팝업 띄우기");
        ImGui::Text("숫자키 7: 하단 인벤토리 전환");
        ImGui::Text("숫자키 8: 낮 정산 팝업 띄우기");
        ImGui::Text("숫자키 9: 도둑 소환 (오른쪽 도로)");
        ImGui::End();

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    
    std::cout << "UI Test Finished!" << std::endl;
    return 0;
}
