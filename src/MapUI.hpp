#pragma once
#include "UIBase.hpp"
#include <string>
#include <utility>
#include <algorithm>
#include <SFML/Window/Keyboard.hpp>

class MapUI : public UIBase {
public:
    MapUI(const GameState* s) : UIBase(s) {}

    void Render() override {
        auto flgs = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse;
        
        ImGui::SetNextWindowSize({1280, 620});
        ImGui::SetNextWindowPos({0, 0});

        bool isNight = (gs->farm.Hour >= 18 || gs->farm.Hour < 6);
        ImVec4 bgCol = isNight ? ImVec4(0.15f, 0.15f, 0.22f, 1.0f) : ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        ImGui::PushStyleColor(ImGuiCol_WindowBg, bgCol);
        ImGui::Begin("MapArea", nullptr, flgs);
        renderIntegratedMap();
        ImGui::End();
        ImGui::PopStyleColor();

        renderItemPreview();
    }

private:
    int activeTimerR = -1;
    int activeTimerC = -1;
    void renderIntegratedMap() {

        int layout[5][9] = {
            {1, 1, 1, 0, 0, 0, 0, 0, 0}, 
            {1, 1, 1, 0, 0, 0, 0, 0, 0}, 
            {7, 7, 7, 2, 2, 2, 2, 2, 2}, 
            {1, 1, 1, 0, 0, 0, 0, 0, 0}, 
            {1, 1, 1, 0, 0, 0, 0, 0, 0}  
        };

        const float tileWidth = 130.0f; 
        const float tileHeight = 110.0f; 

        bool drawDeferredHover = false;
        ImVec2 deferredRangeMin, deferredRangeMax;
        
        bool drawDeferredPreview = false;
        sf::Texture* deferredPreviewTex = nullptr;
        ImVec2 deferredPreviewPos;
        float deferredScaleX, deferredScaleY;

        ImVec2 gridStartPos = ImGui::GetCursorScreenPos();
        float spacingX = ImGui::GetStyle().ItemSpacing.x;
        float spacingY = ImGui::GetStyle().ItemSpacing.y;

        for (int r = 0; r < 5; r++) {
            for (int c = 0; c < 9; c++) {
                int tileType = layout[r][c];
                if (tileType == 7) {
                    if (c == 0) { 
                        float mergedWidth = (tileWidth * 3.0f) + (spacingX * 2.0f); 
                        
                        ImGui::PushID(r * 9 + c); 
                        
                        ImVec2 posBefore = ImGui::GetCursorPos(); 
                        ImGui::Dummy({mergedWidth, tileHeight}); 
                        
                        ImGui::SameLine();
                        ImVec2 posNextTile = ImGui::GetCursorPos();
                        
                        sf::Sprite houseSprite;
                        houseSprite.setTexture(gs->houseTexture);
                        
                        float hOrigW = gs->houseTexture.getSize().x;
                        float hOrigH = gs->houseTexture.getSize().y;
                        float hScale = (tileHeight * 0.8f) / hOrigH; 
                        houseSprite.setScale({hScale, hScale}); 
                        
                        float hScaledH = hOrigH * hScale;
                        
                        ImGui::SetCursorPos({posBefore.x + 10.0f, posBefore.y + (tileHeight - hScaledH) * 0.5f}); 
                        ImGui::Image(houseSprite); 
                        
                        sf::Sprite doorSprite;
                        doorSprite.setTexture(gs->DoorTexture);
                        
                        float dOrigW = gs->DoorTexture.getSize().x;
                        float dOrigH = gs->DoorTexture.getSize().y;
                        float dScale = (tileHeight * 0.8f) / dOrigH; 
                        doorSprite.setScale({dScale, dScale});
                        
                        float dScaledW = dOrigW * dScale;
                        float dScaledH = dOrigH * dScale;
                        
                        ImGui::SetCursorPos({posBefore.x + mergedWidth - dScaledW - 10.0f, posBefore.y + (tileHeight - dScaledH) * 0.5f});
                        ImGui::Image(doorSprite); 
                        
                        ImGui::SetCursorPos(posNextTile); 
                        ImGui::PopID(); 
                    }
                    continue; 
                }

                ImGui::PushID(r * 9 + c);

                if (tileType == 1 || tileType == 2 || tileType == 0) {
                    ImVec2 currentCursorPos = ImGui::GetCursorPos();
                    ImVec2 screenPos = ImGui::GetCursorScreenPos(); 
                    
                    sf::Sprite tileSprite;
                    float scaleX = 1.0f;
                    float scaleY = 1.0f;
                    
                    if (tileType == 1) {
                        tileSprite.setTexture(gs->fieldTexture);
                        scaleX = tileWidth / gs->fieldTexture.getSize().x;
                        scaleY = tileHeight / gs->fieldTexture.getSize().y;
                    } else if (tileType == 2) {
                        tileSprite.setTexture(gs->roadTexture);
                        scaleX = tileWidth / gs->roadTexture.getSize().x;
                        scaleY = tileHeight / gs->roadTexture.getSize().y;
                    } else if (tileType == 0) {
                        tileSprite.setTexture(gs->outsideTexture);
                        scaleX = tileWidth / gs->outsideTexture.getSize().x;
                        scaleY = tileHeight / gs->outsideTexture.getSize().y;
                    }
                    
                    tileSprite.setScale({scaleX, scaleY});
                    ImGui::Image(tileSprite);
                    
                    if (tileType == 1 && gs->farm.SeedField[r][c] != nullptr) {
                        Seed* seed = gs->farm.SeedField[r][c]; 
                        SeedType sType = seed->Type;
                        sf::Texture* cropTex = nullptr;
                    
                        bool isMature = seed->IsGrown();
                        
                        if (sType == SeedType::SEED1) cropTex = isMature ? const_cast<sf::Texture*>(&gs->matureRiceTexture) : const_cast<sf::Texture*>(&gs->immatureRiceTexture);
                        else if (sType == SeedType::SEED2) cropTex = isMature ? const_cast<sf::Texture*>(&gs->maturePotatoTexture) : const_cast<sf::Texture*>(&gs->immaturePotatoTexture);
                        else if (sType == SeedType::SEED3) cropTex = isMature ? const_cast<sf::Texture*>(&gs->matureCarrotTexture) : const_cast<sf::Texture*>(&gs->immatureCarrotTexture);

                        if (cropTex) {
                            sf::Sprite cropSprite(*cropTex);
                            float cropScale = 0.6f;
                            cropSprite.setScale({(tileWidth / cropTex->getSize().x) * cropScale, (tileHeight / cropTex->getSize().y) * cropScale});
                            
                            float offsetX = tileWidth * (1.0f - cropScale) / 2.0f;
                            float offsetY = tileHeight * (1.0f - cropScale) / 2.0f;
                            
                            ImGui::SetCursorPos({currentCursorPos.x + offsetX, currentCursorPos.y + offsetY});
                            ImGui::Image(cropSprite);
                        }

                        if (!isMature) {
                            if (gs->wateringCanTexture.getSize().x > 0) {
                                sf::Sprite wcSprite(gs->wateringCanTexture);
                                float wcScale = 0.25f; 
                                wcSprite.setScale({(tileWidth / gs->wateringCanTexture.getSize().x) * wcScale, (tileHeight / gs->wateringCanTexture.getSize().y) * wcScale});
                                
                                float wcOffsetX = 5.0f;
                                float wcOffsetY = tileHeight - (tileHeight * wcScale) - 5.0f; 
                                ImGui::SetCursorPos({currentCursorPos.x + wcOffsetX, currentCursorPos.y + wcOffsetY});
                                ImGui::Image(wcSprite);
                                if (ImGui::IsItemHovered()) {
                                    if (gs->farm.SeedField[r][c] != nullptr) {
                                        ImGui::SetTooltip("습도: %d%%", seed->Humid);
                                    }
                                }

                                if (ImGui::IsItemClicked()) {
                                    if(gs->status==Status::AM){
                                        const_cast<GameState*>(gs)->farm.WaterSeed(r,c);
                                        const_cast<GameState*>(gs)->Update();
                                    }
                                }
                            }

                            if (gs->clockTexture.getSize().x > 0) {
                                sf::Sprite clockSprite(gs->clockTexture);
                                float clockScale = 0.25f; 
                                clockSprite.setScale({(tileWidth / gs->clockTexture.getSize().x) * clockScale, (tileHeight / gs->clockTexture.getSize().y) * clockScale});
                                
                                float clockOffsetX = tileWidth - (tileWidth * clockScale) - 5.0f; 
                                float clockOffsetY = tileHeight - (tileHeight * clockScale) - 5.0f; 
                                
                                ImGui::SetCursorPos({currentCursorPos.x + clockOffsetX, currentCursorPos.y + clockOffsetY});
                                ImGui::Image(clockSprite);
                                
                                if (ImGui::IsItemHovered()) {
                                    if (gs->farm.SeedField[r][c] != nullptr) {
                                        int remainingTime = static_cast<int>(gs->farm.SeedField[r][c]->CoolDown - gs->farm.SeedField[r][c]->Timer);
                                        if (remainingTime < 0) remainingTime = 0;
                                        ImGui::SetTooltip("남은 시간: %d", remainingTime);
                                    }
                                }
            
                            }
                        }
                    } 
                    else if (tileType == 0 && gs->farm.TrapField[r][c] != nullptr) {
                        TrapType tType = gs->farm.TrapField[r][c]->Type;
                        sf::Texture* tTex = nullptr;
                        if (tType == TrapType::ANIMAL1) tTex = const_cast<sf::Texture*>(&gs->cowTrapTexture);
                        else if (tType == TrapType::ANIMAL2) tTex = const_cast<sf::Texture*>(&gs->pigTrapTexture);
                        else if (tType == TrapType::ANIMAL3) tTex = const_cast<sf::Texture*>(&gs->horseTrapTexture);

                        if (tTex) {
                            sf::Sprite tSprite(*tTex);
                            float trapScale = 0.8f;
                            tSprite.setScale({(tileWidth / tTex->getSize().x) * trapScale, (tileHeight / tTex->getSize().y) * trapScale});
                            
                            float offsetX = tileWidth * (1.0f - trapScale) / 2.0f;
                            float offsetY = tileHeight * (1.0f - trapScale) / 2.0f;
                            
                            ImGui::SetCursorPos({currentCursorPos.x + offsetX, currentCursorPos.y + offsetY});
                            ImGui::Image(tSprite);
                        }
                    }

                    bool canInstall = false;
                    if (tileType == 1 && gs->selectedSeed != SeedType::NONE && gs->farm.SeedField[r][c] == nullptr) {
                        canInstall = true;
                    } else if (tileType == 0 && gs->selectedTrap != TrapType::NONE && gs->farm.TrapField[r][c] == nullptr) {
                        canInstall = true;
                    }

                    if (canInstall) {
                        ImVec2 p_max = {screenPos.x + tileWidth, screenPos.y + tileHeight};
                        ImGui::GetWindowDrawList()->AddRect(screenPos, p_max, IM_COL32(0, 255, 0, 255), 0.0f, 0, 3.0f);
                    }

                    ImGui::SetCursorPos(currentCursorPos);

                    if (tileType == 1 || tileType == 0) {
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
                        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
                        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));                        

                        bool isClicked = ImGui::Button("##tile", {tileWidth, tileHeight});
                        bool isHovered = ImGui::IsItemHovered();
                        ImGui::PopStyleColor(3);

                        GameState* mgs = const_cast<GameState*>(gs);

                        if (isClicked) {
                            if (tileType == 1 && mgs->selectedSeed != SeedType::NONE && mgs->farm.SeedField[r][c] == nullptr) {
                                SeedType heldSeed = mgs->selectedSeed;
                                mgs->targetRow = r;
                                mgs->targetCol = c;
                                mgs->wantToPlantSeed = true;

                                // 작물 심기
                                if (mgs->farm.PlantSeed(r, c, heldSeed)) {
                                    mgs->Update();
                                    mgs->inventory.UseSeed(heldSeed,1);
                                }
                                
                                mgs->selectedSeed = SeedType::NONE;
                            } 
                            else if (tileType == 0 && mgs->selectedTrap != TrapType::NONE && mgs->farm.TrapField[r][c] == nullptr) {
                                TrapType heldTrap = mgs->selectedTrap;
                                mgs->targetRow = r;
                                mgs->targetCol = c;
                                mgs->wantToInstallTrap = true;

                                // 함정 설치
                                auto it = GameData::TrapTable.find(heldTrap);
                                if (mgs->farm.InstallTrap(r, c, heldTrap)) {
                                    mgs->Update(); // 시간 체크 및 상태 업데이트
                                    mgs->inventory.UseTrap(heldTrap,1);
                                }
                                
                                mgs->selectedTrap = TrapType::NONE;
                            }
                        }
			if (isHovered && tileType == 0) {
                            TrapType activeTrap = TrapType::NONE;
                            
                            if (mgs->farm.TrapField[r][c] != nullptr) {
                                activeTrap = mgs->farm.TrapField[r][c]->Type;
                            } else if (mgs->selectedTrap != TrapType::NONE) {
                                activeTrap = mgs->selectedTrap;
                            }

                            if (activeTrap != TrapType::NONE) {
                                drawDeferredHover = true;
                                bool isBelowRoad = (r > 2); 

                                if (activeTrap == TrapType::ANIMAL2) { 
                                    if (isBelowRoad) {
                                        deferredRangeMin = {screenPos.x - (tileWidth * 2.0f), screenPos.y - tileHeight};
                                        deferredRangeMax = {screenPos.x + (tileWidth * 3.0f), screenPos.y + (tileHeight * 2.0f)};
                                    } else {
                                        deferredRangeMin = {screenPos.x - (tileWidth * 2.0f), screenPos.y};
                                        deferredRangeMax = {screenPos.x + (tileWidth * 3.0f), screenPos.y + (tileHeight * 3.0f)};
                                    }
                                } else if (activeTrap == TrapType::ANIMAL1 || activeTrap == TrapType::ANIMAL3) { 
                                    if (isBelowRoad) {
                                        deferredRangeMin = {screenPos.x - tileWidth, screenPos.y - tileHeight};
                                        deferredRangeMax = {screenPos.x + (tileWidth * 2.0f), screenPos.y + tileHeight};
                                    } else {
                                        deferredRangeMin = {screenPos.x - tileWidth, screenPos.y};
                                        deferredRangeMax = {screenPos.x + (tileWidth * 2.0f), screenPos.y + (tileHeight * 2.0f)};
                                    }
                                }
                            }

                            if (mgs->selectedTrap != TrapType::NONE && mgs->farm.TrapField[r][c] == nullptr) {
                                if (mgs->selectedTrap == TrapType::ANIMAL1) deferredPreviewTex = const_cast<sf::Texture*>(&gs->cowTrapTexture);
                                else if (mgs->selectedTrap == TrapType::ANIMAL2) deferredPreviewTex = const_cast<sf::Texture*>(&gs->pigTrapTexture);
                                else if (mgs->selectedTrap == TrapType::ANIMAL3) deferredPreviewTex = const_cast<sf::Texture*>(&gs->horseTrapTexture);

                                if (deferredPreviewTex) {
                                    drawDeferredPreview = true;
                                    float pScale = 0.8f;
                                    float pOffX = tileWidth * (1.0f - pScale) / 2.0f;
                                    float pOffY = tileHeight * (1.0f - pScale) / 2.0f;
                                    
                                    deferredPreviewPos = {screenPos.x + pOffX, screenPos.y + pOffY};
                                    deferredScaleX = (tileWidth / deferredPreviewTex->getSize().x) * pScale;
                                    deferredScaleY = (tileHeight / deferredPreviewTex->getSize().y) * pScale;
                                }
                            }
                        }
                    } else if (tileType == 2) {
                        ImGui::Dummy({tileWidth, tileHeight});
                    }
                }
		ImGui::PopID();

                if (c < 8) ImGui::SameLine();
            }
        }

        ImDrawList* drawList = ImGui::GetWindowDrawList();
        GameState* mgs = const_cast<GameState*>(gs);

        for (const auto& enemy : mgs->farm.ActiveEnemies) {
            if (enemy.EnemyState != State::ALIVE) continue; 

            float posX = gridStartPos.x + enemy.Pos * (tileWidth + spacingX);
            float posY = gridStartPos.y + 2.0f * (tileHeight + spacingY);

            if (mgs->thiefTexture.getSize().x > 0) {
                float scale = 0.5f; 
                float tw = mgs->thiefTexture.getSize().x;
                float th = mgs->thiefTexture.getSize().y;
                float renderW = tileWidth * scale;
                float renderH = (renderW / tw) * th; 
                float offX = (tileWidth - renderW) / 2.0f;
                float offY = (tileHeight - renderH) / 2.0f;

                drawList->AddImage(
                    (void*)(intptr_t)mgs->thiefTexture.getNativeHandle(),
                    ImVec2(posX + offX, posY + offY),
                    ImVec2(posX + offX + renderW, posY + offY + renderH)
                );
            }

            float hpWidth = 80.0f;
            float hpHeight = 10.0f;
            float hpX = posX + (tileWidth - hpWidth) / 2.0f;
            float hpY = posY + 2.0f; 

            drawList->AddRectFilled(ImVec2(hpX, hpY), ImVec2(hpX + hpWidth, hpY + hpHeight), IM_COL32(50, 50, 50, 255)); 
            
            float currentHpWidth = hpWidth * ((float)enemy.HP / enemy.MaxHP);
            drawList->AddRectFilled(ImVec2(hpX, hpY), ImVec2(hpX + currentHpWidth, hpY + hpHeight), IM_COL32(220, 20, 20, 255)); 
            
            drawList->AddRect(ImVec2(hpX, hpY), ImVec2(hpX + hpWidth, hpY + hpHeight), IM_COL32(0, 0, 0, 255)); 
        }

        if (drawDeferredHover) {
            ImGui::GetWindowDrawList()->AddRect(deferredRangeMin, deferredRangeMax, IM_COL32(255, 0, 0, 255), 0.0f, 0, 3.0f);
        }

        if (drawDeferredPreview && deferredPreviewTex) {
            ImVec2 backupCursor = ImGui::GetCursorScreenPos();
            
            ImGui::SetCursorScreenPos(deferredPreviewPos);
            sf::Sprite pSprite(*deferredPreviewTex);
            pSprite.setScale({deferredScaleX, deferredScaleY});
            pSprite.setColor(sf::Color(255, 255, 255, 150)); 
            ImGui::Image(pSprite);
            
            ImGui::SetCursorScreenPos(backupCursor);
        }
    }

    void renderItemPreview() {
        if (gs->selectedTrap == TrapType::NONE && gs->selectedSeed == SeedType::NONE) return;

        sf::Texture* tex = nullptr;
        
        if (gs->selectedTrap != TrapType::NONE) {
            if (gs->selectedTrap == TrapType::ANIMAL1) tex = const_cast<sf::Texture*>(&gs->cowTrapTexture);
            else if (gs->selectedTrap == TrapType::ANIMAL2) tex = const_cast<sf::Texture*>(&gs->pigTrapTexture);
            else if (gs->selectedTrap == TrapType::ANIMAL3) tex = const_cast<sf::Texture*>(&gs->horseTrapTexture);
        } else if (gs->selectedSeed != SeedType::NONE) {
            if (gs->selectedSeed == SeedType::SEED1) tex = const_cast<sf::Texture*>(&gs->riceSeedTexture);
            else if (gs->selectedSeed == SeedType::SEED2) tex = const_cast<sf::Texture*>(&gs->potatoSeedTexture);
            else if (gs->selectedSeed == SeedType::SEED3) tex = const_cast<sf::Texture*>(&gs->carrotSeedTexture);
        }

        if (tex && tex->getSize().x > 0) {
            ImVec2 mousePos = ImGui::GetMousePos();
            
            const float previewWidth = 130.0f;
            const float previewHeight = 110.0f;

            ImGui::SetNextWindowPos({mousePos.x - (previewWidth / 2.0f), mousePos.y - (previewHeight / 2.0f)});
            
            ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            
            ImGuiWindowFlags previewFlags = 
                ImGuiWindowFlags_NoDecoration | 
                ImGuiWindowFlags_NoInputs | 
                ImGuiWindowFlags_AlwaysAutoResize | 
                ImGuiWindowFlags_NoSavedSettings | 
                ImGuiWindowFlags_NoFocusOnAppearing | 
                ImGuiWindowFlags_NoNav |
                ImGuiWindowFlags_Tooltip;

            ImGui::Begin("ItemPreviewWindow", nullptr, previewFlags);

            sf::Sprite previewSprite(*tex);
            float scaleX = previewWidth / tex->getSize().x;
            float scaleY = previewHeight / tex->getSize().y;
            previewSprite.setScale({scaleX, scaleY});

            previewSprite.setColor(sf::Color(255, 255, 255, 100)); 
            
            ImGui::Image(previewSprite);

            ImGui::End();
            
            ImGui::PopStyleVar(2);
            ImGui::PopStyleColor();
        }
    }
};
