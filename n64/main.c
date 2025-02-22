#include <stdlib.h>

#include <nusys.h>
#include <nualstl_n.h>

#include "debug.h"
#include "level.h"
#include "loop.h"
#include "segment.h"
#include "vec.h"

#define NUM_PI_MSGS 8

#define INITIAL_LEVEL 1
#define INITIAL_LIVES 3
#define INITIAL_SCORE 0

// Controller
NUContData contdata[1];
u8 contPattern;

// Audio
musHandle sndHandle = 0;

// Parallel interface
static OSMesg PiMessages[NUM_PI_MSGS];
static OSMesgQueue PiMessageQ;

void audio_init(void)
{
    nuAuStlInit();
    nuAuStlPtrBankInit(PBANK_SIZE);
    nuAuStlPtrBankSet((u8*)PBANK_START, PBANK_SIZE, (u8*)WBANK_START);
    nuAuStlSndPlayerDataSet((u8*)SFX_START, SFX_SIZE);
}

void controller_init(int controller_number)
{
    s32 ret = nuContRmbCheck(controller_number);
    if (ret) {
        debug_printf("Rumble Pak: Fail (%d)\n", ret);
    } else {
        debug_printf("Rumble Pak: OK\n");
        nuContRmbModeSet(controller_number, NU_CONT_RMB_MODE_ENABLE);
        nuContRmbStart(controller_number, 128, 10);
    }
}

void mainproc(void)
{
    nuGfxInit();
    debug_init();
    debug_printf("Starting...\n");
    contPattern = nuContInit();
    controller_init(0);
    audio_init();

    srand(contdata[0].stick_x);

    level_init(INITIAL_LEVEL, INITIAL_LIVES, INITIAL_SCORE);
    set_main_loop(level_loop);
    run_main_loop();
}
