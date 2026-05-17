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
        sprintf(dayTxt, "Day %d", gs->state.farm.Day);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(dayTxt).x) * 0.5f);
        ImGui::Text("%s", dayTxt);

        ImGui::Spacing();

        char bulletTxt[64];
        // TODO: 실제 총알(돌) 변동 전/후 데이터
        sprintf(bulletTxt, "총알 : 5 -> 4 (-1)");
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(bulletTxt).x) * 0.5f);
        ImGui::Text("%s", bulletTxt);

        ImGui::Spacing();

        char moneyTxt[64];
        // TODO: 실제 정산 전/후 소지금 및 획득 금액 
        sprintf(moneyTxt, "돈 : 561$ -> 591$ (+30$)");
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(moneyTxt).x) * 0.5f);
        ImGui::Text("%s", moneyTxt);

        ImGui::Spacing();

        // 5. 함정 상태 표시 (Trap1, Trap2, Trap3)
        char trapTxt[128];
        // TODO: 실제 보유 현황 
        sprintf(trapTxt, "함정 : 소 x 1, 돼지 x 1, 말 x 0 (-)");
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(trapTxt).x) * 0.5f);
        ImGui::Text("%s", trapTxt);

        ImGui::Spacing();

        char seedTxt[128];
        // TODO: 실제 보유 현황 
        sprintf(seedTxt, "씨앗 : 밀 x 10, 감자 x 49, 당근 x 0 (+49)");
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(seedTxt).x) * 0.5f);
        ImGui::Text("%s", seedTxt);

        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();

        ImVec2 bSz = {120, 35};
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - bSz.x) * 0.5f);

        if (ImGui::Button("계속하기", bSz)) {
            // TODO: 정산 창을 닫고 다음 낮(AM) 진행 상태로 온전히 넘어가도록 연결
        }

        ImGui::End();

        ImGui::PopStyleColor(); 
    }
};
