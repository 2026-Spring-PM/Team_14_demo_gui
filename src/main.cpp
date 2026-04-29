#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

// 아래있는 코드는 예시 코드를 넣은 것 뿐이라, 대부분 지우고 다시 쓰는 것을 추천해!

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Team14 Game");
    ImGui::SFML::Init(window);

    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }

        ImGui::SFML::Update(window, clock.restart());
        ImGui::Begin("Hello");
        ImGui::Text("Game Running");
        ImGui::End();

        window.clear();
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}
