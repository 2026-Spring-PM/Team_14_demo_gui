#pragma once
#include "UIBase.hpp"

class PauseUI : public UIBase {
public:
    PauseUI(const GameState* s) : UIBase(s) {}
    Status beforestatus;
    void Render() override {
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.2f, 0.2f, 0.2f, 0.9f));

        auto flgs = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove;
        
        ImGui::SetNextWindowSize({300, 310});
        ImGui::SetNextWindowPos({490, 195}); 

        ImGui::Begin("PausePopup", nullptr, flgs);

        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("일시 정지").x) * 0.5f);
        ImGui::Text("일시 정지");
        ImGui::Separator();
        
        ImGui::Spacing();
        ImGui::Spacing();

        char dayTxt[64];
        sprintf(dayTxt, "Day %d", gs->farm.Day);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(dayTxt).x) * 0.5f);
        ImGui::Text("%s", dayTxt);

        char bulletTxt[64];
        sprintf(bulletTxt, "총알 : %d", gs->inventory.Bullets);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(bulletTxt).x) * 0.5f);
        ImGui::Text("%s", bulletTxt);

        char moneyTxt[64];
        sprintf(moneyTxt, "돈 : %d$", gs->Money);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(moneyTxt).x) * 0.5f);
        ImGui::Text("%s", moneyTxt);

        char trapTxt[128];
        sprintf(trapTxt, "함정 : 소 x %d, 돼지 x %d, 말 x %d",gs->inventory.TrapCount.at(TrapType::COW)
        ,gs->inventory.TrapCount.at(TrapType::PIG),gs->inventory.TrapCount.at(TrapType::HORSE));
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(trapTxt).x) * 0.5f);
        ImGui::Text("%s", trapTxt);

        char seedTxt[128];
        sprintf(seedTxt, "씨앗 : 밀 x %d, 감자 x %d, 당근 x  %d", 
                gs->inventory.SeedCount.at(SeedType::WHEAT), 
                gs->inventory.SeedCount.at(SeedType::POTATO), 
                gs->inventory.SeedCount.at(SeedType::CARROT));
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(seedTxt).x) * 0.5f);
        ImGui::Text("%s", seedTxt);

        ImGui::Spacing();

        ImVec2 bSz = {280, 50};

        if (ImGui::Button("계속하기 (Resume)", bSz)) {
            const_cast<GameState*>(gs)->status =beforestatus;
        }

        ImGui::Spacing();

        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.3f, 0.3f, 1.0f));
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("* 진행 상황이 모두 사라집니다 *").x) * 0.5f);
        ImGui::Text("* 진행 상황이 모두 사라집니다 *");
        ImGui::PopStyleColor(); 

        if (ImGui::Button("메인 메뉴로 (Main Menu)", bSz)) {
            // TODO: 게임 상태 완전 초기화 후, 상태를 MAIN으로 변경
            
            const_cast<GameState*>(gs)->status =Status::MAIN;
        }

        ImGui::End();
        ImGui::PopStyleColor(); 
    }
};
