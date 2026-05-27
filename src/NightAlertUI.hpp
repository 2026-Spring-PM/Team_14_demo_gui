#pragma once
#include "UIBase.hpp"

class NightAlertUI : public UIBase {
public:
    NightAlertUI(const GameState* s) : UIBase(s) {}

    void Render() override {
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1f, 0.15f, 0.3f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.4f, 0.5f, 0.8f, 1.0f));

        auto flgs = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove;
        
        ImGui::SetNextWindowSize({400, 250});
        ImGui::SetNextWindowPos({440, 235}); 

        ImGui::Begin("NightPopup", nullptr, flgs);

        ImGui::Spacing();
        ImGui::Spacing();

        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.9f, 0.2f, 1.0f));
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("밤이 되었습니다.").x) * 0.5f);
        ImGui::Text("밤이 되었습니다.");
        ImGui::PopStyleColor();

        ImGui::Spacing();

        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("적들의 공격을 막아내세요!").x) * 0.5f);
        ImGui::Text("적들의 공격을 막아내세요!");

        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();

        ImVec2 bSz = {200, 60};
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - bSz.x) * 0.5f); 

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.7f, 0.2f, 0.2f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.3f, 0.3f, 1.0f));

        if (ImGui::Button("START", bSz)) {
            // 팝업 닫기 (gs->showNightAlert = false;) 및 디펜스 웨이브 시작
            const_cast<GameState*>(gs)->showNightAlert = false;
            const_cast<GameState*>(gs)->TransitionToNight();         
        }

        ImGui::PopStyleColor(2); 

        ImGui::End();

        ImGui::PopStyleColor(2); 
    }
};
