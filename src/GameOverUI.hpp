#pragma once
#include "UIBase.hpp"

class GameOverUI : public UIBase {
public:
    GameOverUI(const GameState* s) : UIBase(s) {}

    void Render() override {
        // TODO: gs->status == Status::GAMEOVER 일 때 호출

        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.3f, 0.1f, 0.1f, 0.95f));

        auto flgs = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove;
        
        ImGui::SetNextWindowSize({400, 300});
        ImGui::SetNextWindowPos({440, 210}); 

        ImGui::Begin("GameOverPopup", nullptr, flgs);

        ImGui::Spacing();
        ImGui::Spacing();

        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.4f, 0.4f, 1.0f)); 
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("GAME OVER").x) * 0.5f);
        ImGui::Text("GAME OVER");
        ImGui::PopStyleColor();

        ImGui::Separator();
        ImGui::Spacing();
        ImGui::Spacing();

        char resTxt[64];
        sprintf(resTxt, "최종 생존 일수 : Day %d", gs->state.farm.Day);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(resTxt).x) * 0.5f);
        ImGui::Text("%s", resTxt);

        ImGui::Spacing();

        char moneyTxt[64];
        sprintf(moneyTxt, "남은 소지금 : $%d", gs->state.Money);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(moneyTxt).x) * 0.5f);
        ImGui::Text("%s", moneyTxt);

        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();

        ImVec2 bSz = {250, 50};
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - bSz.x) * 0.5f);

        if (ImGui::Button("메인 메뉴로 (Main Menu)", bSz)) {
            // TODO: GameState 내의 모든 변수 처음 상태로 초기화, gs->status = Status::MAIN;
        }

        ImGui::End();

        ImGui::PopStyleColor(); 
    }
};
