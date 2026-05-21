// SPDX-License-Identifier: GPL-2.0-only
/*
 * UFS PHY driver data for Samsung EXYNOS9820 SoC.

 * Copyright (C) 2018 Samsung Electronics Co., Ltd.
 * Author: chiffathefox <chiffathefoxx@gmail.com>
 */

#include "phy-samsung-ufs.h"

#define EXYNOS9820_PHY_CTRL		0x724
#define EXYNOS9820_PHY_CTRL_MASK	0x1
#define EXYNOS9820_PHY_CTRL_EN		BIT(0)
#define PHY_EXYNOS9820_LANE_OFFSET	(0x400 >> 2)

#define PHY_TRSV_REG_CFG_EXYNOS9820(o, v, d) \
	PHY_TRSV_REG_CFG_OFFSET(o, v, d, PHY_EXYNOS9820_LANE_OFFSET)

#define PHY_TRSV_ADDR_EXYNOS9820(reg, lane) \
	(PHY_APB_ADDR((reg) + ((lane) * PHY_EXYNOS9820_LANE_OFFSET)))

/* Calibration for phy initialization */
static const struct samsung_ufs_phy_cfg exynos9820_pre_init_cfg[] = {
	PHY_COMN_REG_CFG(0x3F, 0x10, PWR_MODE_ANY),

	PHY_TRSV_REG_CFG_EXYNOS9820(0x1B6, 0x40, PWR_MODE_ANY),

	PHY_TRSV_REG_CFG_EXYNOS9820(0x1C2, 0x25, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS9820(0x10C, 0x04, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS9820(0x18A, 0x13, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS9820(0x19f, 0x19, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS9820(0x1A2, 0x30, PWR_MODE_ANY),

	PHY_TRSV_REG_CFG_EXYNOS9820(0x168, 0x40, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS9820(0x169, 0x38, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS9820(0x1B9, 0x18, PWR_MODE_ANY),

	PHY_COMN_REG_CFG(0x3F, 0x18, PWR_MODE_ANY),
	PHY_COMN_REG_CFG(0x3F, 0x00, PWR_MODE_ANY),

	END_UFS_PHY_CFG,
};

static const struct samsung_ufs_phy_cfg exynos9820_post_init_cfg[] = {
	PHY_COMN_REG_CFG(0x3F, 0x10, PWR_MODE_ANY),

	PHY_TRSV_REG_CFG_EXYNOS9820(0x1B6, 0xC0, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS9820(0x101, 0x06, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS9820(0x102, 0x06, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS9820(0x104, 0x01, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS9820(0x105, 0x11, PWR_MODE_ANY),

	PHY_TRSV_REG_CFG_EXYNOS9820(0x193, 0x06, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS9820(0x19A, 0x00, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS9820(0x19C, 0x00, PWR_MODE_ANY),

	PHY_TRSV_REG_CFG_EXYNOS9820(0x12F, 0x12, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS9820(0x131, 0x12, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS9820(0x133, 0x00, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS9820(0x135, 0x00, PWR_MODE_ANY),

	PHY_COMN_REG_CFG(0x27, 0x11, PWR_MODE_ANY),
	PHY_COMN_REG_CFG(0x28, 0x11, PWR_MODE_ANY),
	PHY_COMN_REG_CFG(0x43, 0x00, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS9820(0x119, 0x33, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS9820(0x11A, 0x37, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS9820(0x11B, 0x31, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS9820(0x11C, 0x00, PWR_MODE_ANY),

	PHY_TRSV_REG_CFG_EXYNOS9820(0x181, 0x00, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS9820(0x182, 0x82, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS9820(0x183, 0x00, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS9820(0x184, 0x98, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS9820(0x186, 0x60, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS9820(0x188, 0x70, PWR_MODE_ANY),

	PHY_TRSV_REG_CFG_EXYNOS9820(0x11D, 0x33, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS9820(0x11E, 0x37, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS9820(0x11F, 0x31, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS9820(0x120, 0x00, PWR_MODE_ANY),

	PHY_TRSV_REG_CFG_EXYNOS9820(0x126, 0x00, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS9820(0x127, 0x00, PWR_MODE_ANY),

	PHY_TRSV_REG_CFG_EXYNOS9820(0x152, 0x2D, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS9820(0x153, 0xB7, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS9820(0x154, 0x00, PWR_MODE_ANY),

	PHY_COMN_REG_CFG(0x3F, 0x18, PWR_MODE_ANY),
	PHY_COMN_REG_CFG(0x3F, 0x00, PWR_MODE_ANY),

	END_UFS_PHY_CFG,
};

static const struct samsung_ufs_phy_cfg exynos9820_pre_pwr_hs[] = {
	PHY_TRSV_REG_CFG_EXYNOS9820(0x106, 0x3C, PWR_MODE_HS_G3_ANY),
	PHY_TRSV_REG_CFG_EXYNOS9820(0x13A, 0x03, PWR_MODE_HS_ANY),

	END_UFS_PHY_CFG,
};

static const struct samsung_ufs_phy_cfg *exynos9820_ufs_phy_cfgs[CFG_TAG_MAX] = {
	[CFG_PRE_INIT]		= exynos9820_pre_init_cfg,
	[CFG_POST_INIT]		= exynos9820_post_init_cfg,
	[CFG_PRE_PWR_HS]	= exynos9820_pre_pwr_hs,
};

#define EXYNOS9820_CAL_DELAY_US		200
#define EXYNOS9820_CAL_TIMEOUT_US	40000
#define EXYNOS9820_CAL_MASK		0x8
#define EXYNOS9820_CAL_REG		0x1ED

static int exynos9820_phy_wait_for_calibration(struct phy *phy, u8 lane)
{
	struct samsung_ufs_phy *ufs_phy = get_samsung_ufs_phy(phy);
	u32 val;
	int err;

	udelay(EXYNOS9820_CAL_DELAY_US);

	err = readl_poll_timeout(
		ufs_phy->reg_pma +
			PHY_TRSV_ADDR_EXYNOS9820(EXYNOS9820_CAL_REG, lane),
		val, (val & EXYNOS9820_CAL_MASK), EXYNOS9820_CAL_DELAY_US,
		EXYNOS9820_CAL_TIMEOUT_US);
	if (err)
		dev_err(ufs_phy->dev, "failed to get phy cal done %d\n", err);

	return err;
}

#define EXYNOS9820_CDR_LOCK_DELAY_US		400
#define EXYNOS9820_CDR_LOCK_MASK		0x8
#define EXYNOS9820_CDR_LOCK_REG			0x1EE
#define EXYNOS9820_CDR_LOCK_RETRY_COUNT		100

static int exynos9820_phy_wait_for_cdr_lock(struct phy *phy, u8 lane)
{
	struct samsung_ufs_phy *ufs_phy = get_samsung_ufs_phy(phy);
	u32 reg;
	u32 i;

	struct samsung_ufs_phy_cfg cfg[4] = {
		PHY_TRSV_REG_CFG_EXYNOS9820(0x118, 0x10, PWR_MODE_HS_ANY),
		PHY_TRSV_REG_CFG_EXYNOS9820(0x118, 0x18, PWR_MODE_HS_ANY),

		PHY_TRSV_REG_CFG_EXYNOS9820(0x13A, 0x01, PWR_MODE_HS_ANY),

		END_UFS_PHY_CFG,
	};

	for (i = 0; i < EXYNOS9820_CDR_LOCK_RETRY_COUNT; i++) {
		udelay(EXYNOS9820_CDR_LOCK_DELAY_US);

		reg = readl(ufs_phy->reg_pma +
			    PHY_TRSV_ADDR_EXYNOS9820(EXYNOS9820_CDR_LOCK_REG,
						     lane));

		if (reg & EXYNOS9820_CDR_LOCK_MASK) {
			samsung_ufs_phy_config(ufs_phy, &cfg[2], lane);

			return 0;
		}

		udelay(EXYNOS9820_CDR_LOCK_DELAY_US);

		/* Disable and enable CDR */
		samsung_ufs_phy_config(ufs_phy, &cfg[0], lane);
		samsung_ufs_phy_config(ufs_phy, &cfg[1], lane);
	}

	dev_err(ufs_phy->dev, "failed to get phy cdr lock\n");

	return -ETIMEDOUT;
}

const struct samsung_ufs_phy_drvdata exynos9820_ufs_phy = {
	.cfgs = exynos9820_ufs_phy_cfgs,
	.isol = {
		.offset = EXYNOS9820_PHY_CTRL,
		.mask = EXYNOS9820_PHY_CTRL_MASK,
		.en = EXYNOS9820_PHY_CTRL_EN,
	},
	.wait_for_cal = exynos9820_phy_wait_for_calibration,
	.wait_for_cdr = exynos9820_phy_wait_for_cdr_lock,
};
