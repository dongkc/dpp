#ifndef bsp_h
#define bsp_h

uint32_t const BSP_TICKS_PER_SEC = static_cast<uint32_t>(50);

void BSP_init(void);
void BSP_displayPaused(uint8_t const paused);
void BSP_displayPhilStat(uint8_t const n, char_t const *stat);
void BSP_terminate(int16_t const result);

void BSP_randomSeed(uint32_t const seed); // random seed
uint32_t BSP_random(void);                // pseudo-random generator

#endif // bsp_h
