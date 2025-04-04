
#include "st7701s_mipi_2_1_480x480.h"

static void lcd_power_on(u32 sel);
static void lcd_power_off(u32 sel);
static void lcd_bl_open(u32 sel);
static void lcd_bl_close(u32 sel);

static void lcd_panel_init(u32 sel);
static void lcd_panel_exit(u32 sel);

#define power_en(sel, val) sunxi_lcd_gpio_set_value(sel, 0, val)
#define panel_reset(sel, val) sunxi_lcd_gpio_set_value(sel, 1, val)

static void lcd_cfg_panel_info(struct panel_extend_para *info)
{
	u32 i = 0, j = 0;
	u32 items;
	u8 lcd_gamma_tbl[][2] = {
	    {0, 0},     {15, 15},   {30, 30},   {45, 45},   {60, 60},
	    {75, 75},   {90, 90},   {105, 105}, {120, 120}, {135, 135},
	    {150, 150}, {165, 165}, {180, 180}, {195, 195}, {210, 210},
	    {225, 225}, {240, 240}, {255, 255},
	};

	u32 lcd_cmap_tbl[2][3][4] = {
	    {
		{LCD_CMAP_G0, LCD_CMAP_B1, LCD_CMAP_G2, LCD_CMAP_B3},
		{LCD_CMAP_B0, LCD_CMAP_R1, LCD_CMAP_B2, LCD_CMAP_R3},
		{LCD_CMAP_R0, LCD_CMAP_G1, LCD_CMAP_R2, LCD_CMAP_G3},
	    },
	    {
		{LCD_CMAP_B3, LCD_CMAP_G2, LCD_CMAP_B1, LCD_CMAP_G0},
		{LCD_CMAP_R3, LCD_CMAP_B2, LCD_CMAP_R1, LCD_CMAP_B0},
		{LCD_CMAP_G3, LCD_CMAP_R2, LCD_CMAP_G1, LCD_CMAP_R0},
	    },
	};

	items = sizeof(lcd_gamma_tbl) / 2;
	for (i = 0; i < items - 1; i++) {
		u32 num = lcd_gamma_tbl[i + 1][0] - lcd_gamma_tbl[i][0];

		for (j = 0; j < num; j++) {
			u32 value = 0;

			value =
			    lcd_gamma_tbl[i][1] +
			    ((lcd_gamma_tbl[i + 1][1] - lcd_gamma_tbl[i][1]) *
			     j) /
				num;
			info->lcd_gamma_tbl[lcd_gamma_tbl[i][0] + j] =
			    (value << 16) + (value << 8) + value;
		}
	}
	info->lcd_gamma_tbl[255] = (lcd_gamma_tbl[items - 1][1] << 16) +
				   (lcd_gamma_tbl[items - 1][1] << 8) +
				   lcd_gamma_tbl[items - 1][1];

	memcpy(info->lcd_cmap_tbl, lcd_cmap_tbl, sizeof(lcd_cmap_tbl));
}

static s32 lcd_open_flow(u32 sel)
{
	LCD_OPEN_FUNC(sel, lcd_power_on, 120);
	LCD_OPEN_FUNC(sel, lcd_panel_init, 1);
	LCD_OPEN_FUNC(sel, sunxi_lcd_tcon_enable, 5);
	LCD_OPEN_FUNC(sel, lcd_bl_open, 0);
	return 0;
}

static s32 lcd_close_flow(u32 sel)
{
	LCD_CLOSE_FUNC(sel, lcd_bl_close, 0);
	LCD_CLOSE_FUNC(sel, lcd_panel_exit, 200);
	LCD_CLOSE_FUNC(sel, sunxi_lcd_tcon_disable, 0);
	LCD_CLOSE_FUNC(sel, lcd_power_off, 500);

	return 0;
}

static void lcd_power_on(u32 sel)
{
	sunxi_lcd_power_enable(sel, 0);
	sunxi_lcd_delay_ms(10);
	sunxi_lcd_power_enable(sel, 1);
	sunxi_lcd_delay_ms(10);
	sunxi_lcd_pin_cfg(sel, 1);
	sunxi_lcd_delay_ms(50);

    power_en(sel ,1);
	panel_reset(sel, 1);
	sunxi_lcd_delay_ms(100);
	panel_reset(sel, 0);
	sunxi_lcd_delay_ms(100);
	panel_reset(sel, 1);

        //sunxi_lcd_gpio_set_value(sel, 1, 1);
	//sunxi_lcd_gpio_set_value(sel, 0, 1);
	//sunxi_lcd_delay_ms(500);
        //sunxi_lcd_gpio_set_value(sel, 1, 0);
	//sunxi_lcd_delay_ms(500);
	//sunxi_lcd_gpio_set_value(sel, 1, 1);
}

static void lcd_power_off(u32 sel)
{
	sunxi_lcd_pin_cfg(sel, 0);
	sunxi_lcd_delay_ms(1);
	panel_reset(sel, 0);
	sunxi_lcd_delay_ms(1);
	sunxi_lcd_power_disable(sel, 0);
}

static void lcd_bl_open(u32 sel)
{
	sunxi_lcd_pwm_enable(sel);
	sunxi_lcd_backlight_enable(sel);
}

static void lcd_bl_close(u32 sel)
{
	sunxi_lcd_backlight_disable(sel);
	sunxi_lcd_pwm_disable(sel);
}

#define REGFLAG_DELAY         0XFE
#define REGFLAG_END_OF_TABLE  0xFC   /* END OF REGISTERS MARKER */

struct LCM_setting_table {
	u8 cmd;
	u32 count;
	u8 para_list[65];
};


static struct LCM_setting_table lcm_initialization_setting[] = {
    // {0x11, 1, {0x00} },
	// {REGFLAG_DELAY, 120, {} },
	{0xff, 5, {0x77,0x01,0x00,0x00,0x13} },
    {0xEF, 1, {0x08} },

    {0xff, 5, {0x77,0x01,0x00,0x00,0x10} },
    {0xc0, 2, {0x3B,0x00} },  //NL = (0x3B+1 )* 8 = 480
    {0xc1, 2, {0x0D,0x02} },  //VBP=13 vfp=2
    {0xc2, 2, {0x00,0x02} }, 
	{0xcc, 1, {0x10} },
	{0xcd, 1, {0x08} },

    {0xb0, 16, {0x00,0x11,0x16,0x0E,0x11,0x06,0x05,0x09,0x08,0x21,0x06,0x13,0x10,0x29,0x31,0x18} },
    {0xb1, 16, {0x00,0x11,0x16,0x0E,0x11,0x07,0x05,0x09,0x09,0x21,0x05,0x13,0x11,0x2A,0x31,0x18} },
    {0xff, 5, {0x77, 0x01, 0x00, 0x00, 0x11} },
    {0xb0, 1, {0x5D} },
    {0xb1, 1, {0x37} },
    {0xb2, 1, {0x8B} },
    {0xb3, 1, {0x80} },
    {0xb5, 1, {0x43} },
    {0xb7, 1, {0x85} },
    {0xb8, 1, {0x20} },
    {0xc1, 1, {0x78} },
    {0xc2, 1, {0x78} },
    {0xd0, 1, {0x88} },
    {REGFLAG_DELAY, 20, {} },

    {0xe0, 3, {0x00, 0x00, 0x02} },
    {0xe1, 11,{0x03,0xA0,0x00,0x00,0x04,0xA0,0x00,0x00,0x00,0x20,0x20} },
    {0xe2, 13,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00} },
    {0xe3, 4, {0x00, 0x00, 0x11, 0x00} },
    {0xe4, 2, {0x22, 0x00} },
    {0xe5, 16,{0x05,0xEC,0xF6,0xCA,0x07,0xEE,0xF6,0xCA,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00} },
    {0xe6, 4, {0x00, 0x00, 0x11, 0x00} },
    {0xe7, 2, {0x22, 0x00} },
    {0xe8, 16,{0x06,0xED,0xF6,0xCA,0x08,0xEF,0xF6,0xCA,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00} },
    {0xeb, 7, {0x00,0x00,0x40,0x40,0x00,0x00,0x00} },

    {0xed, 16, {0xFF,0xFF,0xFF,0xAB,0x0A,0xBF,0x45,0xFF,0xFF,0x54,0xFB,0xA0,0xBA,0xFF,0xFF,0xFF} },
    {0xef, 6, {0x10,0x0D,0x04,0x08,0x3F,0x1F} },

    {0xff, 5, {0x77,0x01,0x00,0x00,0x13} },
    {0xe8, 2, {0x00,0x0E} },

    {0xff, 5, {0x77,0x01,0x00,0x00,0x00} },

	{0x36, 1, {0x10} },
	{0x3A, 1, {0x77} },


    {0x11, 1, {0x00} },
	{REGFLAG_DELAY, 120, {} },

	{0xff, 5, {0x77,0x01,0x00,0x00,0x13} },
    {0xe8, 2, {0x00,0x0C} },
	{REGFLAG_DELAY, 50, {} },
	{0xe8, 2, {0x00,0x00} },
    {0xff, 5, {0x77,0x01,0x00,0x00,0x00} },
    {0x29, 1, {0x00} },
    {REGFLAG_DELAY, 20, {} },
    {REGFLAG_END_OF_TABLE, 0x00, {} }
};

static void lcd_panel_init(u32 sel)
{
	printk(KERN_ERR"--kernel!! st7701s mipi 480x480 init\n");

	u32 i = 0;

	sunxi_lcd_dsi_clk_enable(sel);
	sunxi_lcd_delay_ms(10);

	for (i = 0;; i++) {
		if (lcm_initialization_setting[i].cmd == REGFLAG_END_OF_TABLE)
			break;
		else if (lcm_initialization_setting[i].cmd == REGFLAG_DELAY)
			sunxi_lcd_delay_ms(lcm_initialization_setting[i].count);
		else {
			sunxi_lcd_dsi_dcs_write(0, lcm_initialization_setting[i].cmd,
				   lcm_initialization_setting[i].para_list,
				   lcm_initialization_setting[i].count);
		}
	}
}

static void lcd_panel_exit(u32 sel)
{
	sunxi_lcd_dsi_dcs_write_0para(sel, 0x28);
	sunxi_lcd_delay_ms(10);
	sunxi_lcd_dsi_dcs_write_0para(sel, 0x10);
	sunxi_lcd_delay_ms(10);
}

/*sel: 0:lcd0; 1:lcd1*/
static s32 lcd_user_defined_func(u32 sel, u32 para1, u32 para2, u32 para3)
{
	return 0;
}

struct __lcd_panel st7701s_2_1_mipi_panel = {
	/* panel driver name, must mach the name of
	 * lcd_drv_name in sys_config.fex
	 */
	.name = "st7701s_480x480",
	.func = {
		.cfg_panel_info = lcd_cfg_panel_info,
			.cfg_open_flow = lcd_open_flow,
			.cfg_close_flow = lcd_close_flow,
			.lcd_user_defined_func = lcd_user_defined_func,
	},
};
