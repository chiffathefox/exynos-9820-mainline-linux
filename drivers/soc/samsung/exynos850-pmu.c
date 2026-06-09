// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright 2026 Linaro Ltd.
 *
 * Exynos850 PMU support
 */

#define pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#include <linux/bits.h>
#include <linux/printk.h>
#include <linux/regmap.h>
#include <linux/soc/samsung/exynos-pmu.h>
#include <linux/soc/samsung/exynos-regs-pmu.h>
#include <linux/topology.h>
#include <asm/cputype.h>

#include "exynos-pmu.h"

static int exynos850_cpu_pmu_offline(struct exynos_pmu_context *pmu_context, unsigned int cpu)
	__must_hold(&pmu_context->cpupm_lock)
{
	int cluster_id, core_id;
	u32 reg, mask;

	cluster_id = topology_cluster_id(cpu);
	if (cluster_id < 0) {
		pr_err_ratelimited("invalid cluster ID for cpu: %u\n", cpu);
		return -EINVAL;
	}

	core_id = topology_core_id(cpu);
	if (core_id < 0) {
		pr_err_ratelimited("invalid core ID for cpu: %u\n", cpu);
		return -EINVAL;
	}

	/* set cpu inform hint */
	regmap_write(pmu_context->pmureg, EXYNOS850_CPU_INFORM(cpu), CPU_INFORM_C2);

	mask = BIT(cpu);
	regmap_update_bits(pmu_context->pmuintrgen, EXYNOS_GRP2_INTR_BID_ENABLE,
			   mask, BIT(cpu));

	regmap_read(pmu_context->pmuintrgen, EXYNOS_GRP1_INTR_BID_UPEND, &reg);
	regmap_write(pmu_context->pmuintrgen, EXYNOS_GRP1_INTR_BID_CLEAR, reg & mask);

	mask = (BIT(cpu + 8));
	regmap_read(pmu_context->pmuintrgen, EXYNOS_GRP1_INTR_BID_UPEND, &reg);
	regmap_write(pmu_context->pmuintrgen, EXYNOS_GRP1_INTR_BID_CLEAR, reg & mask);

	regmap_update_bits(pmu_context->pmureg,
			   EXYNOS850_CLUSTER_CPU_INT_EN(cluster_id, core_id), 1 << 3, 1 << 3);
	return 0;
}

static int exynos850_cpu_pmu_online(struct exynos_pmu_context *pmu_context, unsigned int cpu)
	__must_hold(&pmu_context->cpupm_lock)
{
	int cluster_id, core_id;
	u32 reg, mask;

	cluster_id = topology_cluster_id(cpu);
	if (cluster_id < 0) {
		pr_err_ratelimited("invalid cluster ID for cpu: %u\n", cpu);
		return -EINVAL;
	}

	core_id = topology_core_id(cpu);
	if (core_id < 0) {
		pr_err_ratelimited("invalid core ID for cpu: %u\n", cpu);
		return -EINVAL;
	}

	/* clear cpu inform hint */
	regmap_write(pmu_context->pmureg, EXYNOS850_CPU_INFORM(cpu), CPU_INFORM_CLEAR);

	mask = BIT(cpu);
	regmap_update_bits(pmu_context->pmuintrgen, EXYNOS_GRP2_INTR_BID_ENABLE,
			   mask, (0 << cpu));

	regmap_read(pmu_context->pmuintrgen, EXYNOS_GRP2_INTR_BID_UPEND, &reg);

	regmap_write(pmu_context->pmuintrgen, EXYNOS_GRP2_INTR_BID_CLEAR, reg & mask);

	regmap_update_bits(pmu_context->pmureg,
			   EXYNOS850_CLUSTER_CPU_INT_EN(cluster_id, core_id), 1 << 3, 0 << 3);
	return 0;
}

const struct exynos_pmu_data exynos850_pmu_data = {
	.pmu_cpuhp = true,
	.cpu_pmu_offline = exynos850_cpu_pmu_offline,
	.cpu_pmu_online = exynos850_cpu_pmu_online,
};
