// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2026 chiffathefox <chiffathefoxx@gmail.com>
 *
 * EXYNOS9820 PMU (Power Management Unit) support
 */

#include <linux/array_size.h>
#include <linux/bits.h>
#include <linux/soc/samsung/exynos-pmu.h>
#include <linux/soc/samsung/exynos-regs-pmu.h>
#include <linux/regmap.h>
#include <linux/topology.h>

#include "exynos-pmu.h"

static unsigned exynos9820_cluster_offsets[] = {
	GS101_CLUSTER0_OFFSET,
	GS101_CLUSTER1_OFFSET,
	GS101_CLUSTER2_OFFSET,
};

static int exynos9820_cpu_pmu_offline(struct exynos_pmu_context *pmu_context,
				      unsigned int cpu)
	__must_hold(&pmu_context->cpupm_lock)
{
	int smp_id, cluster_id, core_id;
	u32 reg, mask;

	smp_id = smp_processor_id();
	if (cpu != smp_id) {
		pr_err_ratelimited(
			"offline: not on target CPU: cpu=%u smp_id=%d\n", cpu,
			smp_id);

		return -EINVAL;
	}

	cluster_id = topology_cluster_id(cpu);
	if (cluster_id < 0 ||
	    cluster_id >= ARRAY_SIZE(exynos9820_cluster_offsets)) {
		pr_err_ratelimited("invalid cluster ID for cpu: %u\n", cpu);

		return -EINVAL;
	}

	core_id = topology_core_id(cpu);
	if (core_id < 0) {
		pr_err_ratelimited("invalid core ID for cpu: %u\n", cpu);

		return -EINVAL;
	}

	regmap_write(pmu_context->pmureg, GS101_CPU_INFORM(smp_processor_id()),
		     CPU_INFORM_C2);

	mask = BIT(cpu);
	regmap_update_bits(pmu_context->pmuintrgen, EXYNOS_GRP2_INTR_BID_ENABLE,
			   mask, BIT(cpu));

	regmap_read(pmu_context->pmuintrgen, EXYNOS_GRP1_INTR_BID_UPEND, &reg);
	regmap_write(pmu_context->pmuintrgen, EXYNOS_GRP1_INTR_BID_CLEAR,
		     reg & mask);

	mask = (BIT(cpu + 8));
	regmap_read(pmu_context->pmuintrgen, EXYNOS_GRP1_INTR_BID_UPEND, &reg);
	regmap_write(pmu_context->pmuintrgen, EXYNOS_GRP1_INTR_BID_CLEAR,
		     reg & mask);

	regmap_update_bits(
		pmu_context->pmureg,
		GS101_CLUSTER_CPU_INT_EN(exynos9820_cluster_offsets[cluster_id],
					 core_id),
		BIT(3), BIT(3));

	return 0;
}

static int exynos9820_cpu_pmu_online(struct exynos_pmu_context *pmu_context,
				     unsigned int cpu)
	__must_hold(&pmu_context->cpupm_lock)
{
	int smp_id, cluster_id, core_id;
	u32 reg, mask;

	smp_id = smp_processor_id();
	if (cpu != smp_id) {
		pr_err_ratelimited(
			"offline: not on target CPU: cpu=%u smp_id=%d\n", cpu,
			smp_id);

		return -EINVAL;
	}

	cluster_id = topology_cluster_id(cpu);
	if (cluster_id < 0 ||
	    cluster_id >= ARRAY_SIZE(exynos9820_cluster_offsets)) {
		pr_err_ratelimited("invalid cluster ID for cpu: %u\n", cpu);
		return -EINVAL;
	}

	core_id = topology_core_id(cpu);
	if (core_id < 0) {
		pr_err_ratelimited("invalid core ID for cpu: %u\n", cpu);
		return -EINVAL;
	}

	regmap_write(pmu_context->pmureg, GS101_CPU_INFORM(smp_processor_id()),
		     CPU_INFORM_CLEAR);

	mask = BIT(cpu);
	regmap_update_bits(pmu_context->pmuintrgen, EXYNOS_GRP2_INTR_BID_ENABLE,
			   mask, (0 << cpu));

	regmap_read(pmu_context->pmuintrgen, EXYNOS_GRP2_INTR_BID_UPEND, &reg);
	regmap_write(pmu_context->pmuintrgen, EXYNOS_GRP2_INTR_BID_CLEAR,
		     reg & mask);

	regmap_update_bits(
		pmu_context->pmureg,
		GS101_CLUSTER_CPU_INT_EN(exynos9820_cluster_offsets[cluster_id],
					 core_id),
		BIT(3), 0);

	return 0;
}

const struct exynos_pmu_data exynos9820_pmu_data = {
	.pmu_cpuhp = true,
	.cpu_pmu_offline = exynos9820_cpu_pmu_offline,
	.cpu_pmu_online = exynos9820_cpu_pmu_online,
};
