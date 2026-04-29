#pragma once
#include "Enums.hpp"

int EnemyCount(int level);

EnemyType EnemyTypeSet(int level);

int EnemySpeed(int level, EnemyType type);

int EnemyCoolDown(int level, EnemyType type);

int EnemyHealthPoint(int level, EnemyType type);

int SpawnDelay(NightType type);

NightType SetNightType();

bool DroughtTrigger();

bool PestTrigger();

bool TrapBreakTrigger();
