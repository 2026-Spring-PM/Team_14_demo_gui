#pragma once
#include "UIBase.hpp"

class PauseUI : public UIBase {
public:
    PauseUI(const GameState* s) : UIBase(s) {}

    void Render() override {
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.2f, 0.2f, 0.2f, 0.9f));

        auto flgs = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove;
        
        ImGui::SetNextWindowSize({300, 220});
        ImGui::SetNextWindowPos({490, 250}); 

        ImGui::Begin("PausePopup", nullptr, flgs);

        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("PAUSED").x) * 0.5f);
        ImGui::Text("PAUSED");
        ImGui::Separator();
        
        ImGui::Spacing();
        ImGui::Spacing();

        ImVec2 bSz = {280, 50};

        if (ImGui::Button("계속하기 (Resume)", bSz)) {
            // TODO:  일시정지 해제 (gs->isPaused = false;)
        }

        ImGui::Spacing();

        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.3f, 0.3f, 1.0f));
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("* 진행 상황이 모두 사라집니다 *").x) * 0.5f);
        ImGui::Text("* 진행 상황이 모두 사라집니다 *");
        ImGui::PopStyleColor(); 

        if (ImGui::Button("메인 메뉴로 (Main Menu)", bSz)) {
            // TODO: 게임 상태 완전 초기화 후, 상태를 MAIN으로 변경
        }

        ImGui::End();
        ImGui::PopStyleColor(); 
    }
};
