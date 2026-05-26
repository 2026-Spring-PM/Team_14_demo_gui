#pragma once
#include "UIBase.hpp"

class DaySettlementUI : public UIBase {
public:
    DaySettlementUI(const GameState* s) : UIBase(s) {}

    void Render() override {
        // TODO: 밤이 끝나고 낮으로 전환될 때 자동으로 호출
	    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1f, 0.15f, 0.3f, 0.95f));

        auto flgs = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove;
        
        ImGui::SetNextWindowSize({400, 300});
        ImGui::SetNextWindowPos({440, 210}); 

        ImGui::Begin("DaySettlementPopup", nullptr, flgs);

        ImGui::Spacing();
        ImGui::Spacing();

        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)); 
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("축하합니다").x) * 0.5f);
        ImGui::Text("축하합니다");
        
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("살아남았습니다").x) * 0.5f);
        ImGui::Text("살아남았습니다");
        ImGui::PopStyleColor();

        ImGui::Separator();
        ImGui::Spacing();
        ImGui::Spacing();

        char dayTxt[64];
        sprintf(dayTxt, "Day %d", gs->farm.Day);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(dayTxt).x) * 0.5f);
        ImGui::Text("%s", dayTxt);

        ImGui::Spacing();

        char bulletTxt[64];
        // TODO: 실제 총알(돌) 변동 전/후 데이터
        char bulletdifference[20]; 
        int bulletdif = gs->inventory.Bullets - gs->inventory.BulletsBefore;
        if (bulletdif > 0) {
            sprintf(bulletdifference, "+%d", bulletdif);
        } 
        else {
            sprintf(bulletdifference, "%d", bulletdif);
        }
        sprintf(bulletTxt, "총알 : %d -> %d (%s)",gs->inventory.BulletsBefore,gs->inventory.Bullets,bulletdifference);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(bulletTxt).x) * 0.5f);
        ImGui::Text("%s", bulletTxt);

        ImGui::Spacing();

        char moneyTxt[64];
        // TODO: 실제 정산 전/후 소지금 및 획득 금액 
        char moneydifference[20]; 
        int moneydif = gs->Money - gs->MoneyBefore;
        if (moneydif > 0) {
            sprintf(moneydifference, "+%d", moneydif);
        } 
        else {
            sprintf(moneydifference, "%d", moneydif);
        }
        sprintf(moneyTxt, "돈 : %d$ -> %d$ (%s$)",gs->MoneyBefore,gs->Money,moneydifference);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(moneyTxt).x) * 0.5f);
        ImGui::Text("%s", moneyTxt);

        ImGui::Spacing();

        // 5. 함정 상태 표시 (Trap1, Trap2, Trap3)
        char trapTxt[128];
        char trapDiff[10];
        // TODO: 실제 보유 현황
        int trapsum=gs->inventory.TrapCount.at(TrapType::COW)+gs->inventory.TrapCount.at(TrapType::PIG)+gs->inventory.TrapCount.at(TrapType::HORSE);
        if (trapsum > 0) {
            snprintf(trapDiff, sizeof(trapDiff), "+%d", trapsum);
        } 
        else {
            snprintf(trapDiff, sizeof(trapDiff), "%d", trapsum);
        }
        sprintf(trapTxt, "함정 : 소 x %d, 돼지 x %d, 말 x %d (%s)",gs->inventory.TrapCount.at(TrapType::COW),gs->inventory.TrapCount.at(TrapType::PIG),gs->inventory.TrapCount.at(TrapType::HORSE),trapDiff);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(trapTxt).x) * 0.5f);
        ImGui::Text("%s", trapTxt);

        ImGui::Spacing();

        // TODO: 실제 보유 현황 
        char seedTxt[128];
        char seedDiff[10];

        int seedsum = gs->inventory.SeedCount.at(SeedType::WHEAT) + gs->inventory.SeedCount.at(SeedType::POTATO) + gs->inventory.SeedCount.at(SeedType::CARROT);

        if (seedsum > 0) {
            snprintf(seedDiff, sizeof(seedDiff), "+%d", seedsum);
        } 
        else {
            snprintf(seedDiff, sizeof(seedDiff), "%d", seedsum);
        }

        sprintf(seedTxt, "씨앗 : 밀 x %d, 감자 x %d, 당근 x %d (%s)", 
                gs->inventory.SeedCount.at(SeedType::WHEAT), 
                gs->inventory.SeedCount.at(SeedType::POTATO), 
                gs->inventory.SeedCount.at(SeedType::CARROT), 
                seedDiff);

        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(seedTxt).x) * 0.5f);
        ImGui::Text("%s", seedTxt);

        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();

        ImVec2 bSz = {120, 35};
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - bSz.x) * 0.5f);

        if (ImGui::Button("계속하기", bSz)) {
            // TODO: 정산 창을 닫고 다음 낮(AM) 진행 상태로 온전히 넘어가도록 연결
            auto event = const_cast<GameState*>(gs)->TransitionToDay();
        }

        ImGui::End();

        ImGui::PopStyleColor(); 
    }
};
