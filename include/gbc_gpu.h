// to display a sprite in the upper left corner of the screen set sprite X=8, Y=16.
#define SPRITE_INI_X 8
#define SPRITE_INI_Y 16

// pixels
#define SIZE_X 160
#define SIZE_Y 144

// sprite border
#define SPRITE_END_X SPRITE_INI_X + SIZE_X
#define SPRITE_END_Y SPRITE_INI_Y + SIZE_Y

#define LINES 154

// duration of each screen state
#define DUR_FRAME 70224
#define DUR_OAM 80
#define DUR_OAM_VRAM 172
#define DUR_HBLANK 204
#define DUR_LINE 456 // 80 + 172 + 204
#define DUR_VBLANK 4560

// start of each screen state in each line / frame
#define TL_OAM 0
#define TL_OAM_VRAM TL_OAM + DUR_OAM
#define TL_HBLANK TL_OAM_VRAM + DUR_OAM_VRAM
#define TF_VBLANK DUR_LINE * SIZE_Y

#define FPS 59.73

#define MASK_OBJ_PRIORITY (0x01 << 7)
#define MASK_OBJ_Y_FLIP   (0x01 << 6)
#define MASK_OBJ_X_FLIP   (0x01 << 5)
#define MASK_OBJ_PALETTE  (0x01 << 4)

#define TRANSPARENT 8

typedef struct {
	uint8_t id;
	uint8_t x;
	uint8_t y;
	uint8_t pat;
	uint8_t flags;
} obj_t;

uint8_t *screen_get_fb();
//void screen_write_fb();
void screen_start_frame();
int screen_emulate(uint32_t cycles);
void screen_write_8(uint16_t addr, uint8_t v);
uint8_t screen_read_8(uint16_t addr);

typedef struct {
    u8 fb[SIZE_X * SIZE_Y];
    u8 bg_disp[256 * 256];
    u8 win_disp[256 * 256];
    u8 obj_disp[256 * 256];

    int t_oam, t_oam_vram, t_hblank, t_vblank;
    u8 cur_line, cmp_line;
    u8 reset;
    u8 bg_palette[4], obj0_palette[4], obj1_palette[4];

    // registers
    u8 BGP, OBP0, OBP1;
    u8 lcd_stat;
    u8 scroll_x, scroll_y, wndpos_x, wndpos_y;
} gbc_gpu;

