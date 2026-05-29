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

        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("최종 결과").x) * 0.5f);
        ImGui::Text("최종 결과");

        ImGui::Separator();
        ImGui::Spacing();
        ImGui::Spacing();

        char resTxt[64];
        sprintf(resTxt, "Day %d (NEW RECORD)", gs->farm.Day);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(resTxt).x) * 0.5f);
        ImGui::Text("%s", resTxt);

        ImGui::Spacing();

        char moneyTxt[64];
        sprintf(moneyTxt, "돈 : %d$", gs->Money);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(moneyTxt).x) * 0.5f);
        ImGui::Text("%s", moneyTxt);

        ImGui::Spacing();

        char trapTxt[128];
        // TODO: 보유 개수를 관리하는 실제 변수로 수정 
        sprintf(trapTxt, "함정 : 소 x %d, 돼지 x %d, 말 x %d", gs->inventory.TrapCount.at(TrapType::COW)
        ,gs->inventory.TrapCount.at(TrapType::PIG),gs->inventory.TrapCount.at(TrapType::HORSE)); 
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(trapTxt).x) * 0.5f);
        ImGui::Text("%s", trapTxt);

        ImGui::Spacing();

        char seedTxt[128];
        // TODO: 보유 개수를 관리하는 실제 변수로 수정.
        sprintf(seedTxt, "씨앗 : 밀 x %d, 감자 x %d, 당근 x %d",
                gs->inventory.SeedCount.at(SeedType::WHEAT), 
                gs->inventory.SeedCount.at(SeedType::POTATO), 
                gs->inventory.SeedCount.at(SeedType::CARROT));
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(seedTxt).x) * 0.5f);
        ImGui::Text("%s", seedTxt);

        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();

        ImVec2 bSz = {250, 50};
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - bSz.x) * 0.5f);

        if (ImGui::Button("메인 메뉴로 (Main Menu)", bSz)){
            GameState* mgs = const_cast<GameState*>(gs);
            mgs->Reset();
        }
        ImGui::End();
        ImGui::PopStyleColor(); 
    }
};
