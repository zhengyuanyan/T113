include $(obj)/de/Makefile

# define_trace.h needs to know how to find our header
CFLAGS_disp_trace.o := -I$(src)

obj-$(CONFIG_DISP2_SUNXI) += disp.o

disp-objs :=  dev_disp.o dev_fb.o dev_disp_debugfs.o
disp-objs += disp_sys_intf.o
disp-objs += disp_trace.o
disp-$(CONFIG_DISP2_SUNXI_COMPOSER) += dev_composer.o
disp-objs += de/disp_display.o de/disp_features.o de/disp_device.o \
	     de/disp_lcd.o de/disp_manager.o de/disp_private.o \
	     de/disp_smart_backlight.o de/disp_enhance.o de/disp_capture.o \
	     de/disp_tv.o de/disp_vdevice.o \
	     de/disp_vga.o \
	     de/disp_vdpo.o de/disp_edp.o de/disp_rtwb.o
disp-$(CONFIG_EINK_PANEL_USED) += de/disp_eink_manager.o \
		de/eink_buffer_manager.o de/eink_pipeline_manager.o \
		de/disp_format_convert.o

disp-objs += de/disp_vga.o \
	     de/disp_vdpo.o de/disp_edp.o
disp-$(CONFIG_SUNXI_DISP2_FB_ROTATION_SUPPORT) += de/disp_rotation_sw.o
disp-$(CONFIG_SUNXI_DISP2_FB_HW_ROTATION_SUPPORT) += fb_g2d_rot.o

disp-objs += lcd/panels.o lcd/lcd_source.o lcd/default_panel.o
disp-objs += of_service.o de/lcd_debug.o
disp-objs += lcd/mipi_10_800x1280.o
disp-objs += lcd/mipi_8_800x1280.o

disp-$(CONFIG_LCD_SUPPORT_FL7703NI_4_720x720) += lcd/fl7703ni_mipi_4_720x720.o
disp-$(CONFIG_LCD_SUPPORT_ST7701S_2_1_480x480) += lcd/st7701s_mipi_2_1_480x480.o
disp-$(CONFIG_LCD_SUPPORT_HE0801A068) += lcd/he0801a068.o
disp-$(CONFIG_EINK_PANEL_USED) += lcd/default_eink.o
disp-$(CONFIG_LCD_SUPPORT_LT070ME05000) += lcd/lt070me05000.o
disp-$(CONFIG_LCD_SUPPORT_WTQ05027D01) += lcd/wtq05027d01.o
disp-$(CONFIG_LCD_SUPPORT_T27P06) += lcd/t27p06.o
disp-$(CONFIG_LCD_SUPPORT_DX0960BE40A1) += lcd/dx0960be40a1.o
disp-$(CONFIG_LCD_SUPPORT_TFT720X1280) += lcd/tft720x1280.o
disp-$(CONFIG_LCD_SUPPORT_S6D7AA0X01) += lcd/S6D7AA0X01.o
disp-$(CONFIG_LCD_SUPPORT_GG1P4062UTSW) += lcd/cpu_gg1p4062utsw.o
disp-$(CONFIG_LCD_SUPPORT_LS029B3SX02) +=  lcd/ls029b3sx02.o
disp-$(CONFIG_LCD_SUPPORT_FD055HD003S) += lcd/fd055hd003s.o
disp-$(CONFIG_LCD_SUPPORT_FRD450H40014) += lcd/frd450h40014.o
disp-$(CONFIG_LCD_SUPPORT_H245QBN02) += lcd/h245qbn02.o
disp-$(CONFIG_LCD_SUPPORT_ILI9341) += lcd/ili9341.o
disp-$(CONFIG_LCD_SUPPORT_LH219WQ1) += lcd/lh219wq1.o
disp-$(CONFIG_LCD_SUPPORT_ST7789V) += lcd/st7789v.o
disp-$(CONFIG_LCD_SUPPORT_ST7796S) += lcd/st7796s.o
disp-$(CONFIG_LCD_SUPPORT_ST7701S) += lcd/st7701s.o
disp-$(CONFIG_LCD_SUPPORT_WTL096601G03) += lcd/wtl096601g03.o
disp-$(CONFIG_LCD_SUPPORT_T30P106) += lcd/t30p106.o
disp-$(CONFIG_LCD_SUPPORT_TO20T20000) += lcd/to20t20000.o
disp-$(CONFIG_LCD_SUPPORT_S2003T46G) += lcd/s2003t46g.o
disp-$(CONFIG_LCD_SUPPORT_WILLIAMLCD) += lcd/WilliamLcd.o
disp-$(CONFIG_LCD_SUPPORT_LQ101R1SX03) += lcd/lq101r1sx03.o
disp-$(CONFIG_LCD_SUPPORT_INET_DSI_PANEL) += lcd/inet_dsi_panel.o
disp-$(CONFIG_LCD_SUPPORT_RT13QV005D) += lcd/rt13qv005d.o
disp-$(CONFIG_LCD_SUPPORT_ILI9881C) += lcd/ili9881c.o
disp-$(CONFIG_LCD_SUPPORT_TM_DSI_PANEL) += lcd/tm_dsi_panel.o
disp-$(CONFIG_LCD_SUPPORT_ST7789V_CPU) += lcd/st7789v_cpu.o
disp-$(CONFIG_LCD_SUPPORT_JD9366AB_3) += lcd/jd9366ab_3.o
disp-$(CONFIG_LCD_SUPPORT_TFT08006) += lcd/tft08006.o
disp-$(CONFIG_LCD_SUPPORT_BP101WX1_206) += lcd/bp101wx1-206.o
disp-$(CONFIG_LCD_SUPPORT_FX070) += lcd/fx070.o
disp-$(CONFIG_LCD_SUPPORT_K101IM2QA04) += lcd/k101im2qa04.o
disp-$(CONFIG_LCD_SUPPORT_CC08021801_310_800X1280) += lcd/CC08021801_310_800X1280.o
disp-$(CONFIG_LCD_SUPPORT_K080_IM2HYL802R_800X1280) += lcd/K080_IM2HYL802R_800X1280.o
disp-$(CONFIG_LCD_SUPPORT_K101_IM2BYL02_L_800X1280) += lcd/K101_IM2BYL02_L_800X1280.o
disp-$(CONFIG_LCD_SUPPORT_NT35510_MIPI) += lcd/nt35510.o
disp-$(CONFIG_LCD_SUPPORT_B080UAN01_MIPI1200X1920) += lcd/b080uan01_mipi1200x1920.o
disp-y += lcd/super_lcd_driver.o

disp-$(CONFIG_EINK_PANEL_USED) += de/disp_eink_manager.o \
		de/eink_buffer_manager.o de/eink_pipeline_manager.o \
		de/disp_format_convert.o lcd/default_eink.o

disp-objs += $(obj_low)

disp-$(CONFIG_SUNXI_DISP2_PQ) += pq/drv_pq.o pq/pq_common.o

