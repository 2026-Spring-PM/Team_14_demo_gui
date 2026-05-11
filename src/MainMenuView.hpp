#pragma once
#include "UIBase.hpp"

class MainUI : public UIBase {
public:
    MainUI(const GameState* s) : UIBase(s) {}

    void Render() override {
        auto flgs = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove;
        
        ImGui::SetNextWindowSize({300, 200});
        ImGui::SetNextWindowPos({490, 260}); 

        ImGui::Begin("Main", nullptr, flgs);

        // 제목
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("FARM GAME").x) * 0.5f);
        ImGui::Text("FARM GAME");
        ImGui::Separator();

        ImVec2 bSz = {280, 40};

        if (ImGui::Button("New Game", bSz)) {
            // TODO: gs->status = Status::AM; 및 초기 게임 세팅 로직 연결
        }

        if (ImGui::Button("Exit", bSz)) {
            // TODO: sf::RenderWindow의 close() 등을 호출하여 프로그램 종료
        }

        ImGui::End();
    }
};
