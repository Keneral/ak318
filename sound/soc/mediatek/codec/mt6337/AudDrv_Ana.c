/*
* Copyright (C) 2015 MediaTek Inc.
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 as
* published by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.
* If not, see <http://www.gnu.org/licenses/>.
*/
/*******************************************************************************
 *
 * Filename:
 * ---------
 *   AudDrv_Ana.c
 *
 * Project:
 * --------
 *   MT6337  Audio Driver ana Register setting
 *
 * Description:
 * ------------
 *   Audio register
 *
 * Author:
 * -------
 *   Chipeng Chang (mtk02308)
 *   Chien-Wei Hsu (mtk10177)
 *
 *------------------------------------------------------------------------------
 *
 *
 *******************************************************************************/


/*****************************************************************************
 *                     C O M P I L E R   F L A G S
 *****************************************************************************/


/*****************************************************************************
 *                E X T E R N A L   R E F E R E N C E S
 *****************************************************************************/
#include "AudDrv_Ana.h"

#ifdef AUDIO_USING_WRAP_DRIVER
#include <mach/mt_pmic_wrap.h>
#endif

#include "AudDrv_Type_Def.h"

static DEFINE_SPINLOCK(ana_set_reg_lock);

/*****************************************************************************
 *                         D A T A   T Y P E S
 *****************************************************************************/
uint32 Ana_Get_Reg(uint32 offset)
{
	/* get pmic register */
	int ret = 0;
	uint32 Rdata = 0;
#ifdef AUDIO_USING_WRAP_DRIVER
	ret = pwrap_read(offset, &Rdata);
#endif
	PRINTK_ANA_REG("Ana_Get_Reg offset=0x%x,Rdata=0x%x,ret=%d\n", offset, Rdata, ret);
	return Rdata;
}
EXPORT_SYMBOL(Ana_Get_Reg);

void Ana_Set_Reg(uint32 offset, uint32 value, uint32 mask)
{
	/* set pmic register or analog CONTROL_IFACE_PATH */
	int ret = 0;
	uint32 Reg_Value;
	unsigned long flags = 0;

	PRINTK_ANA_REG("Ana_Set_Reg offset= 0x%x , value = 0x%x mask = 0x%x\n", offset, value,
		       mask);
#ifdef AUDIO_USING_WRAP_DRIVER
	spin_lock_irqsave(&ana_set_reg_lock, flags);
	Reg_Value = Ana_Get_Reg(offset);
	Reg_Value &= (~mask);
	Reg_Value |= (value & mask);
	ret = pwrap_write(offset, Reg_Value);
	spin_unlock_irqrestore(&ana_set_reg_lock, flags);

	Reg_Value = Ana_Get_Reg(offset);
	if ((Reg_Value & mask) != (value & mask))
		pr_warn("Ana_Set_Reg  mask = 0x%x ret = %d Reg_Value = 0x%x\n", mask, ret,
			 Reg_Value);
#endif
}
EXPORT_SYMBOL(Ana_Set_Reg);

void Ana_Log_Print(void)
{
	pr_debug("AFE_UL_DL_CON0	= 0x%x\n", Ana_Get_Reg(AFE_UL_DL_CON0));
	pr_debug("AFE_DL_SRC2_CON0_H	= 0x%x\n", Ana_Get_Reg(AFE_DL_SRC2_CON0_H));
	pr_debug("AFE_DL_SRC2_CON0_L	= 0x%x\n", Ana_Get_Reg(AFE_DL_SRC2_CON0_L));
	pr_debug("AFE_DL_SDM_CON0  = 0x%x\n", Ana_Get_Reg(AFE_DL_SDM_CON0));
	pr_debug("AFE_DL_SDM_CON1  = 0x%x\n", Ana_Get_Reg(AFE_DL_SDM_CON1));
	pr_debug("AFE_UL_SRC_CON0_H	= 0x%x\n", Ana_Get_Reg(AFE_UL_SRC_CON0_H));
	pr_debug("AFE_UL_SRC_CON0_L	= 0x%x\n", Ana_Get_Reg(AFE_UL_SRC_CON0_L));
	pr_debug("AFE_UL_SRC_CON1_H	= 0x%x\n", Ana_Get_Reg(AFE_UL_SRC_CON1_H));
	pr_debug("AFE_UL_SRC_CON1_L	= 0x%x\n", Ana_Get_Reg(AFE_UL_SRC_CON1_L));
	pr_debug("PMIC_AFE_TOP_CON0  = 0x%x\n", Ana_Get_Reg(PMIC_AFE_TOP_CON0));
	pr_debug("AFE_AUDIO_TOP_CON0	= 0x%x\n", Ana_Get_Reg(AFE_AUDIO_TOP_CON0));
	pr_debug("PMIC_AFE_TOP_CON0  = 0x%x\n", Ana_Get_Reg(PMIC_AFE_TOP_CON0));
	pr_debug("AFE_DL_SRC_MON0  = 0x%x\n", Ana_Get_Reg(AFE_DL_SRC_MON0));
	pr_debug("AFE_DL_SDM_TEST0  = 0x%x\n", Ana_Get_Reg(AFE_DL_SDM_TEST0));
	pr_debug("AFE_MON_DEBUG0	= 0x%x\n", Ana_Get_Reg(AFE_MON_DEBUG0));
	pr_debug("AFUNC_AUD_CON0	= 0x%x\n", Ana_Get_Reg(AFUNC_AUD_CON0));
	pr_debug("AFUNC_AUD_CON1	= 0x%x\n", Ana_Get_Reg(AFUNC_AUD_CON1));
	pr_debug("AFUNC_AUD_CON2	= 0x%x\n", Ana_Get_Reg(AFUNC_AUD_CON2));
	pr_debug("AFUNC_AUD_CON3	= 0x%x\n", Ana_Get_Reg(AFUNC_AUD_CON3));
	pr_debug("AFUNC_AUD_CON4	= 0x%x\n", Ana_Get_Reg(AFUNC_AUD_CON4));
	pr_debug("AFUNC_AUD_MON0	= 0x%x\n", Ana_Get_Reg(AFUNC_AUD_MON0));
	pr_debug("AFUNC_AUD_MON1	= 0x%x\n", Ana_Get_Reg(AFUNC_AUD_MON1));
	pr_debug("AUDRC_TUNE_MON0  = 0x%x\n", Ana_Get_Reg(AUDRC_TUNE_MON0));
	pr_debug("AFE_UP8X_FIFO_CFG0	= 0x%x\n", Ana_Get_Reg(AFE_UP8X_FIFO_CFG0));
	pr_debug("AFE_UP8X_FIFO_LOG_MON0	= 0x%x\n", Ana_Get_Reg(AFE_UP8X_FIFO_LOG_MON0));
	pr_debug("AFE_UP8X_FIFO_LOG_MON1	= 0x%x\n", Ana_Get_Reg(AFE_UP8X_FIFO_LOG_MON1));
	pr_debug("AFE_DL_DC_COMP_CFG0  = 0x%x\n", Ana_Get_Reg(AFE_DL_DC_COMP_CFG0));
	pr_debug("AFE_DL_DC_COMP_CFG1  = 0x%x\n", Ana_Get_Reg(AFE_DL_DC_COMP_CFG1));
	pr_debug("AFE_DL_DC_COMP_CFG2  = 0x%x\n", Ana_Get_Reg(AFE_DL_DC_COMP_CFG2));
	pr_debug("AFE_PMIC_NEWIF_CFG0  = 0x%x\n", Ana_Get_Reg(AFE_PMIC_NEWIF_CFG0));
	pr_debug("AFE_PMIC_NEWIF_CFG1  = 0x%x\n", Ana_Get_Reg(AFE_PMIC_NEWIF_CFG1));
	pr_debug("AFE_PMIC_NEWIF_CFG2  = 0x%x\n", Ana_Get_Reg(AFE_PMIC_NEWIF_CFG2));
	pr_debug("AFE_PMIC_NEWIF_CFG3  = 0x%x\n", Ana_Get_Reg(AFE_PMIC_NEWIF_CFG3));
	pr_debug("AFE_SGEN_CFG0  = 0x%x\n", Ana_Get_Reg(AFE_SGEN_CFG0));
	pr_debug("AFE_SGEN_CFG1  = 0x%x\n", Ana_Get_Reg(AFE_SGEN_CFG1));
	pr_debug("AFE_ADDA2_PMIC_NEWIF_CFG0  = 0x%x\n", Ana_Get_Reg(AFE_ADDA2_PMIC_NEWIF_CFG0));
	pr_debug("AFE_ADDA2_PMIC_NEWIF_CFG1  = 0x%x\n", Ana_Get_Reg(AFE_ADDA2_PMIC_NEWIF_CFG1));
	pr_debug("AFE_ADDA2_PMIC_NEWIF_CFG2  = 0x%x\n", Ana_Get_Reg(AFE_ADDA2_PMIC_NEWIF_CFG2));
	pr_debug("AFE_VOW_TOP  = 0x%x\n", Ana_Get_Reg(AFE_VOW_TOP));
	pr_debug("AFE_VOW_CFG0  = 0x%x\n", Ana_Get_Reg(AFE_VOW_CFG0));
	pr_debug("AFE_VOW_CFG1  = 0x%x\n", Ana_Get_Reg(AFE_VOW_CFG1));
	pr_debug("AFE_VOW_CFG2  = 0x%x\n", Ana_Get_Reg(AFE_VOW_CFG2));
	pr_debug("AFE_VOW_CFG3  = 0x%x\n", Ana_Get_Reg(AFE_VOW_CFG3));
	pr_debug("AFE_VOW_CFG4  = 0x%x\n", Ana_Get_Reg(AFE_VOW_CFG4));
	pr_debug("AFE_VOW_CFG5  = 0x%x\n", Ana_Get_Reg(AFE_VOW_CFG5));
	pr_debug("AFE_VOW_MON0  = 0x%x\n", Ana_Get_Reg(AFE_VOW_MON0));
	pr_debug("AFE_VOW_MON1  = 0x%x\n", Ana_Get_Reg(AFE_VOW_MON1));
	pr_debug("AFE_VOW_MON2  = 0x%x\n", Ana_Get_Reg(AFE_VOW_MON2));
	pr_debug("AFE_VOW_MON3  = 0x%x\n", Ana_Get_Reg(AFE_VOW_MON3));
	pr_debug("AFE_VOW_MON4  = 0x%x\n", Ana_Get_Reg(AFE_VOW_MON4));
	pr_debug("AFE_VOW_MON5  = 0x%x\n", Ana_Get_Reg(AFE_VOW_MON5));

	pr_debug("AFE_DCCLK_CFG0	= 0x%x\n", Ana_Get_Reg(AFE_DCCLK_CFG0));
	pr_debug("AFE_DCCLK_CFG1	= 0x%x\n", Ana_Get_Reg(AFE_DCCLK_CFG1));
	pr_debug("AFE_NCP_CFG0		= 0x%x\n", Ana_Get_Reg(AFE_NCP_CFG0));
	pr_debug("AFE_NCP_CFG1		= 0x%x\n", Ana_Get_Reg(AFE_NCP_CFG1));

	pr_debug("TOP_CKPDN_CON0	= 0x%x\n", Ana_Get_Reg(TOP_CKPDN_CON0));
	pr_debug("TOP_CKPDN_CON1	= 0x%x\n", Ana_Get_Reg(TOP_CKPDN_CON1));
	pr_debug("TOP_CKSEL_CON0	= 0x%x\n", Ana_Get_Reg(TOP_CKSEL_CON0));
	pr_debug("TOP_CKDIVSEL_CON0  = 0x%x\n", Ana_Get_Reg(TOP_CKDIVSEL_CON0));
	pr_debug("TOP_CKHWEN_CON0	= 0x%x\n", Ana_Get_Reg(TOP_CKHWEN_CON0));
	pr_debug("TOP_CKHWEN_CON1	= 0x%x\n", Ana_Get_Reg(TOP_CKHWEN_CON1));
	pr_debug("TOP_CKTST_CON0	= 0x%x\n", Ana_Get_Reg(TOP_CKTST_CON0));
	pr_debug("TOP_CKTST_CON1	= 0x%x\n", Ana_Get_Reg(TOP_CKTST_CON1));
	pr_debug("TOP_CLKSQ  = 0x%x\n", Ana_Get_Reg(TOP_CLKSQ));
	pr_debug("TOP_CLKSQ_RTC  = 0x%x\n", Ana_Get_Reg(TOP_CLKSQ_RTC));
	pr_debug("TOP_CLK_TRIM  = 0x%x\n", Ana_Get_Reg(TOP_CLK_TRIM));
	pr_debug("TOP_RST_CON0  = 0x%x\n", Ana_Get_Reg(TOP_RST_CON0));
	pr_debug("TOP_RST_CON1  = 0x%x\n", Ana_Get_Reg(TOP_RST_CON1));
	pr_debug("TOP_RST_CON2  = 0x%x\n", Ana_Get_Reg(TOP_RST_CON2));
	pr_debug("TOP_RST_MISC  = 0x%x\n", Ana_Get_Reg(TOP_RST_MISC));
	pr_debug("TOP_RST_STATUS  = 0x%x\n", Ana_Get_Reg(TOP_RST_STATUS));
	pr_debug("AFE_MON_DEBUG0= 0x%x\n", Ana_Get_Reg(AFE_MON_DEBUG0));
	pr_debug("ZCD_CON0  = 0x%x\n", Ana_Get_Reg(ZCD_CON0));
	pr_debug("ZCD_CON1  = 0x%x\n", Ana_Get_Reg(ZCD_CON1));
	pr_debug("ZCD_CON2  = 0x%x\n", Ana_Get_Reg(ZCD_CON2));
	pr_debug("ZCD_CON3  = 0x%x\n", Ana_Get_Reg(ZCD_CON3));
	pr_debug("ZCD_CON4  = 0x%x\n", Ana_Get_Reg(ZCD_CON4));
	pr_debug("ZCD_CON5  = 0x%x\n", Ana_Get_Reg(ZCD_CON5));
	pr_debug("LDO_VA18_CON0  = 0x%x\n", Ana_Get_Reg(LDO_VA18_CON0));
	pr_debug("LDO_VA18_CON1  = 0x%x\n", Ana_Get_Reg(LDO_VA18_CON1));

	pr_debug("AUDDEC_ANA_CON0  = 0x%x\n", Ana_Get_Reg(AUDDEC_ANA_CON0));
	pr_debug("AUDDEC_ANA_CON1  = 0x%x\n", Ana_Get_Reg(AUDDEC_ANA_CON1));
	pr_debug("AUDDEC_ANA_CON2  = 0x%x\n", Ana_Get_Reg(AUDDEC_ANA_CON2));
	pr_debug("AUDDEC_ANA_CON3  = 0x%x\n", Ana_Get_Reg(AUDDEC_ANA_CON3));
	pr_debug("AUDDEC_ANA_CON4  = 0x%x\n", Ana_Get_Reg(AUDDEC_ANA_CON4));
	pr_debug("AUDDEC_ANA_CON5  = 0x%x\n", Ana_Get_Reg(AUDDEC_ANA_CON5));
	pr_debug("AUDDEC_ANA_CON6  = 0x%x\n", Ana_Get_Reg(AUDDEC_ANA_CON6));
	pr_debug("AUDDEC_ANA_CON7  = 0x%x\n", Ana_Get_Reg(AUDDEC_ANA_CON7));
	pr_debug("AUDDEC_ANA_CON8  = 0x%x\n", Ana_Get_Reg(AUDDEC_ANA_CON8));
	pr_debug("AUDDEC_ANA_CON9  = 0x%x\n", Ana_Get_Reg(AUDDEC_ANA_CON9));
	pr_debug("AUDDEC_ANA_CON10  = 0x%x\n", Ana_Get_Reg(AUDDEC_ANA_CON10));

	pr_debug("AUDENC_ANA_CON0  = 0x%x\n", Ana_Get_Reg(AUDENC_ANA_CON0));
	pr_debug("AUDENC_ANA_CON1  = 0x%x\n", Ana_Get_Reg(AUDENC_ANA_CON1));
	pr_debug("AUDENC_ANA_CON2  = 0x%x\n", Ana_Get_Reg(AUDENC_ANA_CON2));
	pr_debug("AUDENC_ANA_CON3  = 0x%x\n", Ana_Get_Reg(AUDENC_ANA_CON3));
	pr_debug("AUDENC_ANA_CON4  = 0x%x\n", Ana_Get_Reg(AUDENC_ANA_CON4));
	pr_debug("AUDENC_ANA_CON5  = 0x%x\n", Ana_Get_Reg(AUDENC_ANA_CON5));
	pr_debug("AUDENC_ANA_CON6  = 0x%x\n", Ana_Get_Reg(AUDENC_ANA_CON6));
	pr_debug("AUDENC_ANA_CON7  = 0x%x\n", Ana_Get_Reg(AUDENC_ANA_CON7));
	pr_debug("AUDENC_ANA_CON8  = 0x%x\n", Ana_Get_Reg(AUDENC_ANA_CON8));
	pr_debug("AUDENC_ANA_CON9  = 0x%x\n", Ana_Get_Reg(AUDENC_ANA_CON9));
	pr_debug("AUDENC_ANA_CON10  = 0x%x\n", Ana_Get_Reg(AUDENC_ANA_CON10));
	pr_debug("AUDENC_ANA_CON11  = 0x%x\n", Ana_Get_Reg(AUDENC_ANA_CON11));
	pr_debug("AUDENC_ANA_CON12  = 0x%x\n", Ana_Get_Reg(AUDENC_ANA_CON12));
	pr_debug("AUDENC_ANA_CON13  = 0x%x\n", Ana_Get_Reg(AUDENC_ANA_CON13));
	pr_debug("AUDENC_ANA_CON14  = 0x%x\n", Ana_Get_Reg(AUDENC_ANA_CON14));
	pr_debug("AUDENC_ANA_CON15  = 0x%x\n", Ana_Get_Reg(AUDENC_ANA_CON15));
	pr_debug("AUDENC_ANA_CON16  = 0x%x\n", Ana_Get_Reg(AUDENC_ANA_CON16));

	pr_debug("TOP_CKPDN_CON0	= 0x%x\n", Ana_Get_Reg(TOP_CKPDN_CON0));
	pr_debug("GPIO_MODE0	= 0x%x\n", Ana_Get_Reg(GPIO_MODE0));
	pr_debug("-Ana_Log_Print\n");
}
EXPORT_SYMBOL(Ana_Log_Print);

int Ana_Debug_Read(char *buffer, const int size)
{
	int n = 0;

	n += scnprintf(buffer + n, size - n, "AFE_UL_DL_CON0  = 0x%x\n",
		       Ana_Get_Reg(AFE_UL_DL_CON0));
	n += scnprintf(buffer + n, size - n, "AFE_DL_SRC2_CON0_H  = 0x%x\n",
		       Ana_Get_Reg(AFE_DL_SRC2_CON0_H));
	n += scnprintf(buffer + n, size - n, "AFE_DL_SRC2_CON0_L  = 0x%x\n",
		       Ana_Get_Reg(AFE_DL_SRC2_CON0_L));
	n += scnprintf(buffer + n, size - n, "AFE_DL_SDM_CON0  = 0x%x\n",
		       Ana_Get_Reg(AFE_DL_SDM_CON0));
	n += scnprintf(buffer + n, size - n, "AFE_DL_SDM_CON1  = 0x%x\n",
		       Ana_Get_Reg(AFE_DL_SDM_CON1));
	n += scnprintf(buffer + n, size - n, "AFE_UL_SRC_CON0_H  = 0x%x\n",
		       Ana_Get_Reg(AFE_UL_SRC_CON0_H));
	n += scnprintf(buffer + n, size - n, "AFE_UL_SRC_CON0_L  = 0x%x\n",
		       Ana_Get_Reg(AFE_UL_SRC_CON0_L));
	n += scnprintf(buffer + n, size - n, "AFE_UL_SRC_CON1_H  = 0x%x\n",
		       Ana_Get_Reg(AFE_UL_SRC_CON1_H));
	n += scnprintf(buffer + n, size - n, "AFE_UL_SRC_CON1_L  = 0x%x\n",
		       Ana_Get_Reg(AFE_UL_SRC_CON1_L));
	n += scnprintf(buffer + n, size - n, "PMIC_AFE_TOP_CON0  = 0x%x\n",
		       Ana_Get_Reg(PMIC_AFE_TOP_CON0));
	n += scnprintf(buffer + n, size - n, "AFE_AUDIO_TOP_CON0  = 0x%x\n",
		       Ana_Get_Reg(AFE_AUDIO_TOP_CON0));
	n += scnprintf(buffer + n, size - n, "PMIC_AFE_TOP_CON0  = 0x%x\n",
		       Ana_Get_Reg(PMIC_AFE_TOP_CON0));
	n += scnprintf(buffer + n, size - n, "AFE_DL_SRC_MON0  = 0x%x\n",
		       Ana_Get_Reg(AFE_DL_SRC_MON0));
	n += scnprintf(buffer + n, size - n, "AFE_DL_SDM_TEST0  = 0x%x\n",
		       Ana_Get_Reg(AFE_DL_SDM_TEST0));
	n += scnprintf(buffer + n, size - n, "AFE_MON_DEBUG0  = 0x%x\n",
		       Ana_Get_Reg(AFE_MON_DEBUG0));
	n += scnprintf(buffer + n, size - n, "AFUNC_AUD_CON0  = 0x%x\n",
		       Ana_Get_Reg(AFUNC_AUD_CON0));
	n += scnprintf(buffer + n, size - n, "AFUNC_AUD_CON1  = 0x%x\n",
		       Ana_Get_Reg(AFUNC_AUD_CON1));
	n += scnprintf(buffer + n, size - n, "AFUNC_AUD_CON2  = 0x%x\n",
		       Ana_Get_Reg(AFUNC_AUD_CON2));
	n += scnprintf(buffer + n, size - n, "AFUNC_AUD_CON3  = 0x%x\n",
		       Ana_Get_Reg(AFUNC_AUD_CON3));
	n += scnprintf(buffer + n, size - n, "AFUNC_AUD_CON4  = 0x%x\n",
		       Ana_Get_Reg(AFUNC_AUD_CON4));
	n += scnprintf(buffer + n, size - n, "AFUNC_AUD_MON0  = 0x%x\n",
		       Ana_Get_Reg(AFUNC_AUD_MON0));
	n += scnprintf(buffer + n, size - n, "AFUNC_AUD_MON1  = 0x%x\n",
		       Ana_Get_Reg(AFUNC_AUD_MON1));
	n += scnprintf(buffer + n, size - n, "AUDRC_TUNE_MON0  = 0x%x\n",
		       Ana_Get_Reg(AUDRC_TUNE_MON0));
	n += scnprintf(buffer + n, size - n, "AFE_UP8X_FIFO_CFG0  = 0x%x\n",
		       Ana_Get_Reg(AFE_UP8X_FIFO_CFG0));
	n += scnprintf(buffer + n, size - n, "AFE_UP8X_FIFO_LOG_MON0  = 0x%x\n",
		       Ana_Get_Reg(AFE_UP8X_FIFO_LOG_MON0));
	n += scnprintf(buffer + n, size - n, "AFE_UP8X_FIFO_LOG_MON1  = 0x%x\n",
		       Ana_Get_Reg(AFE_UP8X_FIFO_LOG_MON1));
	n += scnprintf(buffer + n, size - n, "AFE_DL_DC_COMP_CFG0  = 0x%x\n",
		       Ana_Get_Reg(AFE_DL_DC_COMP_CFG0));
	n += scnprintf(buffer + n, size - n, "AFE_DL_DC_COMP_CFG1  = 0x%x\n",
		       Ana_Get_Reg(AFE_DL_DC_COMP_CFG1));
	n += scnprintf(buffer + n, size - n, "AFE_DL_DC_COMP_CFG2  = 0x%x\n",
		       Ana_Get_Reg(AFE_DL_DC_COMP_CFG2));
	n += scnprintf(buffer + n, size - n, "AFE_PMIC_NEWIF_CFG0  = 0x%x\n",
		       Ana_Get_Reg(AFE_PMIC_NEWIF_CFG0));
	n += scnprintf(buffer + n, size - n, "AFE_PMIC_NEWIF_CFG1  = 0x%x\n",
		       Ana_Get_Reg(AFE_PMIC_NEWIF_CFG1));
	n += scnprintf(buffer + n, size - n, "AFE_PMIC_NEWIF_CFG2  = 0x%x\n",
		       Ana_Get_Reg(AFE_PMIC_NEWIF_CFG2));
	n += scnprintf(buffer + n, size - n, "AFE_PMIC_NEWIF_CFG3  = 0x%x\n",
		       Ana_Get_Reg(AFE_PMIC_NEWIF_CFG3));
	n += scnprintf(buffer + n, size - n, "AFE_SGEN_CFG0  = 0x%x\n",
			Ana_Get_Reg(AFE_SGEN_CFG0));
	n += scnprintf(buffer + n, size - n, "AFE_SGEN_CFG1  = 0x%x\n",
			Ana_Get_Reg(AFE_SGEN_CFG1));
	n += scnprintf(buffer + n, size - n, "AFE_ADDA2_UP8X_FIFO_LOG_MON0  = 0x%x\n",
			Ana_Get_Reg(AFE_ADDA2_UP8X_FIFO_LOG_MON0));
	n += scnprintf(buffer + n, size - n, "AFE_ADDA2_UP8X_FIFO_LOG_MON1  = 0x%x\n",
			Ana_Get_Reg(AFE_ADDA2_UP8X_FIFO_LOG_MON1));
	n += scnprintf(buffer + n, size - n, "AFE_ADDA2_PMIC_NEWIF_CFG0  = 0x%x\n",
			Ana_Get_Reg(AFE_ADDA2_PMIC_NEWIF_CFG0));
	n += scnprintf(buffer + n, size - n, "AFE_ADDA2_PMIC_NEWIF_CFG1  = 0x%x\n",
			Ana_Get_Reg(AFE_ADDA2_PMIC_NEWIF_CFG1));
	n += scnprintf(buffer + n, size - n, "AFE_ADDA2_PMIC_NEWIF_CFG2  = 0x%x\n",
			Ana_Get_Reg(AFE_ADDA2_PMIC_NEWIF_CFG2));
	n += scnprintf(buffer + n, size - n, "AFE_VOW_TOP  = 0x%x\n", Ana_Get_Reg(AFE_VOW_TOP));
	n += scnprintf(buffer + n, size - n, "AFE_VOW_CFG0  = 0x%x\n", Ana_Get_Reg(AFE_VOW_CFG0));
	n += scnprintf(buffer + n, size - n, "AFE_VOW_CFG1  = 0x%x\n", Ana_Get_Reg(AFE_VOW_CFG1));
	n += scnprintf(buffer + n, size - n, "AFE_VOW_CFG2  = 0x%x\n", Ana_Get_Reg(AFE_VOW_CFG2));
	n += scnprintf(buffer + n, size - n, "AFE_VOW_CFG3  = 0x%x\n", Ana_Get_Reg(AFE_VOW_CFG3));
	n += scnprintf(buffer + n, size - n, "AFE_VOW_CFG4  = 0x%x\n", Ana_Get_Reg(AFE_VOW_CFG4));
	n += scnprintf(buffer + n, size - n, "AFE_VOW_CFG5  = 0x%x\n", Ana_Get_Reg(AFE_VOW_CFG5));
	n += scnprintf(buffer + n, size - n, "AFE_VOW_MON0  = 0x%x\n", Ana_Get_Reg(AFE_VOW_MON0));
	n += scnprintf(buffer + n, size - n, "AFE_VOW_MON1  = 0x%x\n", Ana_Get_Reg(AFE_VOW_MON1));
	n += scnprintf(buffer + n, size - n, "AFE_VOW_MON2  = 0x%x\n", Ana_Get_Reg(AFE_VOW_MON2));
	n += scnprintf(buffer + n, size - n, "AFE_VOW_MON3  = 0x%x\n", Ana_Get_Reg(AFE_VOW_MON3));
	n += scnprintf(buffer + n, size - n, "AFE_VOW_MON4  = 0x%x\n", Ana_Get_Reg(AFE_VOW_MON4));
	n += scnprintf(buffer + n, size - n, "AFE_VOW_MON5  = 0x%x\n", Ana_Get_Reg(AFE_VOW_MON5));

	n += scnprintf(buffer + n, size - n, "AFE_VOW_POSDIV_CFG0  = 0x%x\n", Ana_Get_Reg(AFE_VOW_POSDIV_CFG0));
	n += scnprintf(buffer + n, size - n, "AFE_VOW_TGEN_CFG0  = 0x%x\n", Ana_Get_Reg(AFE_VOW_TGEN_CFG0));

	n += scnprintf(buffer + n, size - n, "BUCK_VOW_CON0 = 0x%x\n", Ana_Get_Reg(0x416));
	n += scnprintf(buffer + n, size - n, "BUCK_VOW_CON3 = 0x%x\n", Ana_Get_Reg(0x41C));
	n += scnprintf(buffer + n, size - n, "TOP_CKSEL_CON2 = 0x%x\n", Ana_Get_Reg(0x26A));
	n += scnprintf(buffer + n, size - n, "BUCK_VCORE_CON8 = 0x%x\n", Ana_Get_Reg(0x610));

	n += scnprintf(buffer + n, size - n, "AFE_DCCLK_CFG0  = 0x%x\n",
		       Ana_Get_Reg(AFE_DCCLK_CFG0));
	n += scnprintf(buffer + n, size - n, "AFE_DCCLK_CFG1  = 0x%x\n",
		       Ana_Get_Reg(AFE_DCCLK_CFG1));
	n += scnprintf(buffer + n, size - n, "AFE_HPANC_CFG0  = 0x%x\n",
		       Ana_Get_Reg(AFE_HPANC_CFG0));
	n += scnprintf(buffer + n, size - n, "AFE_NCP_CFG0  = 0x%x\n",
		       Ana_Get_Reg(AFE_NCP_CFG0));
	n += scnprintf(buffer + n, size - n, "AFE_NCP_CFG1  = 0x%x\n",
		       Ana_Get_Reg(AFE_NCP_CFG1));
	n += scnprintf(buffer + n, size - n, "TOP_CKPDN_CON0  = 0x%x\n",
		       Ana_Get_Reg(TOP_CKPDN_CON0));
	n += scnprintf(buffer + n, size - n, "TOP_CKPDN_CON1  = 0x%x\n",
		       Ana_Get_Reg(TOP_CKPDN_CON1));
	n += scnprintf(buffer + n, size - n, "TOP_CKSEL_CON0  = 0x%x\n",
		       Ana_Get_Reg(TOP_CKSEL_CON0));
	n += scnprintf(buffer + n, size - n, "TOP_CKDIVSEL_CON0  = 0x%x\n",
		       Ana_Get_Reg(TOP_CKDIVSEL_CON0));
	n += scnprintf(buffer + n, size - n, "TOP_CKHWEN_CON0  = 0x%x\n",
		       Ana_Get_Reg(TOP_CKHWEN_CON0));
	n += scnprintf(buffer + n, size - n, "TOP_CKHWEN_CON1  = 0x%x\n",
		       Ana_Get_Reg(TOP_CKHWEN_CON1));
	n += scnprintf(buffer + n, size - n, "TOP_CKTST_CON0  = 0x%x\n",
		       Ana_Get_Reg(TOP_CKTST_CON0));
	n += scnprintf(buffer + n, size - n, "TOP_CKTST_CON1  = 0x%x\n",
		       Ana_Get_Reg(TOP_CKTST_CON1));
	n += scnprintf(buffer + n, size - n, "TOP_CLKSQ  = 0x%x\n", Ana_Get_Reg(TOP_CLKSQ));
	n += scnprintf(buffer + n, size - n, "TOP_CLKSQ_RTC  = 0x%x\n",
			Ana_Get_Reg(TOP_CLKSQ_RTC));
	n += scnprintf(buffer + n, size - n, "TOP_CLK_TRIM  = 0x%x\n",
			Ana_Get_Reg(TOP_CLK_TRIM));
	n += scnprintf(buffer + n, size - n, "TOP_RST_CON0  = 0x%x\n",
			Ana_Get_Reg(TOP_RST_CON0));
	n += scnprintf(buffer + n, size - n, "TOP_RST_CON1  = 0x%x\n",
			Ana_Get_Reg(TOP_RST_CON1));
	n += scnprintf(buffer + n, size - n, "TOP_RST_CON2  = 0x%x\n",
			Ana_Get_Reg(TOP_RST_CON2));
	n += scnprintf(buffer + n, size - n, "TOP_RST_MISC  = 0x%x\n",
			Ana_Get_Reg(TOP_RST_MISC));
	n += scnprintf(buffer + n, size - n, "TOP_RST_STATUS  = 0x%x\n",
			Ana_Get_Reg(TOP_RST_STATUS));
	n += scnprintf(buffer + n, size - n, "AFE_MON_DEBUG0= 0x%x\n",
			Ana_Get_Reg(AFE_MON_DEBUG0));
	n += scnprintf(buffer + n, size - n, "ZCD_CON0  = 0x%x\n", Ana_Get_Reg(ZCD_CON0));
	n += scnprintf(buffer + n, size - n, "ZCD_CON1  = 0x%x\n", Ana_Get_Reg(ZCD_CON1));
	n += scnprintf(buffer + n, size - n, "ZCD_CON2  = 0x%x\n", Ana_Get_Reg(ZCD_CON2));
	n += scnprintf(buffer + n, size - n, "ZCD_CON3  = 0x%x\n", Ana_Get_Reg(ZCD_CON3));
	n += scnprintf(buffer + n, size - n, "ZCD_CON4  = 0x%x\n", Ana_Get_Reg(ZCD_CON4));
	n += scnprintf(buffer + n, size - n, "ZCD_CON5  = 0x%x\n", Ana_Get_Reg(ZCD_CON5));
	n += scnprintf(buffer + n, size - n, "LDO_VA18_CON0  = 0x%x\n",
			Ana_Get_Reg(LDO_VA18_CON0));
	n += scnprintf(buffer + n, size - n, "LDO_VA18_CON1  = 0x%x\n",
			Ana_Get_Reg(LDO_VA18_CON1));
	n += scnprintf(buffer + n, size - n, "AUDDEC_ANA_CON0  = 0x%x\n",
		       Ana_Get_Reg(AUDDEC_ANA_CON0));
	n += scnprintf(buffer + n, size - n, "AUDDEC_ANA_CON1  = 0x%x\n",
		       Ana_Get_Reg(AUDDEC_ANA_CON1));
	n += scnprintf(buffer + n, size - n, "AUDDEC_ANA_CON2  = 0x%x\n",
		       Ana_Get_Reg(AUDDEC_ANA_CON2));
	n += scnprintf(buffer + n, size - n, "AUDDEC_ANA_CON3  = 0x%x\n",
		       Ana_Get_Reg(AUDDEC_ANA_CON3));
	n += scnprintf(buffer + n, size - n, "AUDDEC_ANA_CON4  = 0x%x\n",
		       Ana_Get_Reg(AUDDEC_ANA_CON4));
	n += scnprintf(buffer + n, size - n, "AUDDEC_ANA_CON5  = 0x%x\n",
		       Ana_Get_Reg(AUDDEC_ANA_CON5));
	n += scnprintf(buffer + n, size - n, "AUDDEC_ANA_CON6  = 0x%x\n",
		       Ana_Get_Reg(AUDDEC_ANA_CON6));
	n += scnprintf(buffer + n, size - n, "AUDDEC_ANA_CON7  = 0x%x\n",
		       Ana_Get_Reg(AUDDEC_ANA_CON7));
	n += scnprintf(buffer + n, size - n, "AUDDEC_ANA_CON8  = 0x%x\n",
		       Ana_Get_Reg(AUDDEC_ANA_CON8));
	n += scnprintf(buffer + n, size - n, "AUDDEC_ANA_CON9  = 0x%x\n",
		       Ana_Get_Reg(AUDDEC_ANA_CON9));
	n += scnprintf(buffer + n, size - n, "AUDDEC_ANA_CON10  = 0x%x\n",
		       Ana_Get_Reg(AUDDEC_ANA_CON10));

	n += scnprintf(buffer + n, size - n, "AUDENC_ANA_CON0  = 0x%x\n",
		       Ana_Get_Reg(AUDENC_ANA_CON0));
	n += scnprintf(buffer + n, size - n, "AUDENC_ANA_CON1  = 0x%x\n",
		       Ana_Get_Reg(AUDENC_ANA_CON1));
	n += scnprintf(buffer + n, size - n, "AUDENC_ANA_CON2  = 0x%x\n",
		       Ana_Get_Reg(AUDENC_ANA_CON2));
	n += scnprintf(buffer + n, size - n, "AUDENC_ANA_CON3  = 0x%x\n",
		       Ana_Get_Reg(AUDENC_ANA_CON3));
	n += scnprintf(buffer + n, size - n, "AUDENC_ANA_CON4  = 0x%x\n",
		       Ana_Get_Reg(AUDENC_ANA_CON4));
	n += scnprintf(buffer + n, size - n, "AUDENC_ANA_CON5  = 0x%x\n",
		       Ana_Get_Reg(AUDENC_ANA_CON5));
	n += scnprintf(buffer + n, size - n, "AUDENC_ANA_CON6  = 0x%x\n",
		       Ana_Get_Reg(AUDENC_ANA_CON6));
	n += scnprintf(buffer + n, size - n, "AUDENC_ANA_CON7  = 0x%x\n",
		       Ana_Get_Reg(AUDENC_ANA_CON7));
	n += scnprintf(buffer + n, size - n, "AUDENC_ANA_CON8  = 0x%x\n",
		       Ana_Get_Reg(AUDENC_ANA_CON8));
	n += scnprintf(buffer + n, size - n, "AUDENC_ANA_CON9  = 0x%x\n",
		       Ana_Get_Reg(AUDENC_ANA_CON9));
	n += scnprintf(buffer + n, size - n, "AUDENC_ANA_CON10  = 0x%x\n",
		       Ana_Get_Reg(AUDENC_ANA_CON10));
	n += scnprintf(buffer + n, size - n, "AUDENC_ANA_CON11  = 0x%x\n",
		       Ana_Get_Reg(AUDENC_ANA_CON11));
	n += scnprintf(buffer + n, size - n, "AUDENC_ANA_CON12  = 0x%x\n",
		       Ana_Get_Reg(AUDENC_ANA_CON12));
	n += scnprintf(buffer + n, size - n, "AUDENC_ANA_CON13  = 0x%x\n",
		       Ana_Get_Reg(AUDENC_ANA_CON13));
	n += scnprintf(buffer + n, size - n, "AUDENC_ANA_CON14  = 0x%x\n",
		       Ana_Get_Reg(AUDENC_ANA_CON14));
	n += scnprintf(buffer + n, size - n, "AUDENC_ANA_CON15  = 0x%x\n",
		       Ana_Get_Reg(AUDENC_ANA_CON15));
	n += scnprintf(buffer + n, size - n, "AUDENC_ANA_CON16  = 0x%x\n",
		       Ana_Get_Reg(AUDENC_ANA_CON16));
	n += scnprintf(buffer + n, size - n, "AUDRC_TUNE_MON0  = 0x%x\n",
		       Ana_Get_Reg(AUDRC_TUNE_MON0));
	n += scnprintf(buffer + n, size - n, "AFE_VOW_PERIODIC_CFG0  = 0x%x\n",
		       Ana_Get_Reg(AFE_VOW_PERIODIC_CFG0));
	n += scnprintf(buffer + n, size - n, "AFE_VOW_PERIODIC_CFG2  = 0x%x\n",
		       Ana_Get_Reg(AFE_VOW_PERIODIC_CFG2));
	n += scnprintf(buffer + n, size - n, "AFE_VOW_PERIODIC_CFG4  = 0x%x\n",
		       Ana_Get_Reg(AFE_VOW_PERIODIC_CFG4));
	n += scnprintf(buffer + n, size - n, "AFE_VOW_PERIODIC_CFG6  = 0x%x\n",
		       Ana_Get_Reg(AFE_VOW_PERIODIC_CFG6));
	n += scnprintf(buffer + n, size - n, "AFE_VOW_PERIODIC_CFG7  = 0x%x\n",
		       Ana_Get_Reg(AFE_VOW_PERIODIC_CFG7));
	n += scnprintf(buffer + n, size - n, "AFE_VOW_PERIODIC_CFG8  = 0x%x\n",
		       Ana_Get_Reg(AFE_VOW_PERIODIC_CFG8));
	n += scnprintf(buffer + n, size - n, "AFE_VOW_PERIODIC_CFG9  = 0x%x\n",
		       Ana_Get_Reg(AFE_VOW_PERIODIC_CFG9));
	n += scnprintf(buffer + n, size - n, "AFE_VOW_PERIODIC_CFG10  = 0x%x\n",
		       Ana_Get_Reg(AFE_VOW_PERIODIC_CFG10));
	n += scnprintf(buffer + n, size - n, "AFE_VOW_PERIODIC_CFG11  = 0x%x\n",
		       Ana_Get_Reg(AFE_VOW_PERIODIC_CFG11));
	n += scnprintf(buffer + n, size - n, "AFE_VOW_PERIODIC_CFG12  = 0x%x\n",
		       Ana_Get_Reg(AFE_VOW_PERIODIC_CFG12));
	n += scnprintf(buffer + n, size - n, "AFE_VOW_PERIODIC_MON0  = 0x%x\n",
		       Ana_Get_Reg(AFE_VOW_PERIODIC_MON0));
	n += scnprintf(buffer + n, size - n, "AFE_VOW_PERIODIC_MON1  = 0x%x\n",
		       Ana_Get_Reg(AFE_VOW_PERIODIC_MON1));
	return n;
}
EXPORT_SYMBOL(Ana_Debug_Read);

/* export symbols for other module using */
