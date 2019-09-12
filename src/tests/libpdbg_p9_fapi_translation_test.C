#include <stdio.h>
#include <inttypes.h>

#define class klass
#include "libpdbg/libpdbg.h"
#include "libpdbg/hwunit.h"
#include "libpdbg/target.h"
#undef class

#include "p9_scominfo.H"

#define MAX_INDEX 30

extern struct hw_unit_info p9_core_hw_unit;
extern struct hw_unit_info p9_ex_hw_unit;
extern struct hw_unit_info p9_mba_hw_unit;
extern struct hw_unit_info p9_mcs_hw_unit;
extern struct hw_unit_info p9_xbus_hw_unit;
extern struct hw_unit_info p9_abus_hw_unit;
extern struct hw_unit_info p9_l4_hw_unit;
extern struct hw_unit_info p9_eq_hw_unit;
extern struct hw_unit_info p9_mca_hw_unit;
extern struct hw_unit_info p9_mcbist_hw_unit;
extern struct hw_unit_info p9_mi_hw_unit;
extern struct hw_unit_info p9_dmi_hw_unit;
extern struct hw_unit_info p9_obus_hw_unit;
extern struct hw_unit_info p9_obus_brick_hw_unit;
extern struct hw_unit_info p9_sbe_hw_unit;
extern struct hw_unit_info p9_ppe_hw_unit;
extern struct hw_unit_info p9_pec_hw_unit;
extern struct hw_unit_info p9_phb_hw_unit;
extern struct hw_unit_info p9_mc_hw_unit;
extern struct hw_unit_info p9_mem_port_hw_unit;
extern struct hw_unit_info p9_nmmu_hw_unit;
extern struct hw_unit_info p9_pau_hw_unit;
extern struct hw_unit_info p9_iohs_hw_unit;
extern struct hw_unit_info p9_fc_hw_unit;
extern struct hw_unit_info p9_pauc_hw_unit;
extern struct hw_unit_info p9_chiplet_hw_unit;

int test_unit_translation(struct pdbg_target *target, p9ChipUnits_t cu, int index, uint64_t addr)
{
	uint64_t pdbg_addr, fapi_addr;

	target->index = index;

	/* TODO: Check standard chiplet translation */
	if (!target->translate)
		return 1;

	pdbg_addr = target->translate(target, addr);
	fapi_addr = p9_scominfo_createChipUnitScomAddr(cu, index, addr, 0);

	if (pdbg_addr != fapi_addr)
		printf("PDBG Address 0x%016" PRIx64 " does not match FAPI Address 0x%016" PRIx64
		       " for address 0x%016" PRIx64 " on target %s@%d\n",
		       pdbg_addr, fapi_addr, addr, pdbg_target_path(target), index);

	return pdbg_addr == fapi_addr;
}

int main(void)
{
	uint64_t addr;
	int i, index;
	struct pdbg_target *p9_cu[NONE] = {0};

	pdbg_set_logfunc(NULL);

	p9_cu[PU_C_CHIPUNIT] = (struct pdbg_target *) p9_core_hw_unit.hw_unit;
        p9_cu[PU_EQ_CHIPUNIT] = (struct pdbg_target *) p9_eq_hw_unit.hw_unit;
        p9_cu[PU_EX_CHIPUNIT] = (struct pdbg_target *) p9_ex_hw_unit.hw_unit;
        p9_cu[PU_XBUS_CHIPUNIT] = (struct pdbg_target *) p9_xbus_hw_unit.hw_unit;
        p9_cu[PU_OBUS_CHIPUNIT] = (struct pdbg_target *) p9_obus_hw_unit.hw_unit;
        p9_cu[PU_PEC_CHIPUNIT] = (struct pdbg_target *) p9_pec_hw_unit.hw_unit;
        p9_cu[PU_PHB_CHIPUNIT] = (struct pdbg_target *) p9_phb_hw_unit.hw_unit;
        p9_cu[PU_MI_CHIPUNIT] = (struct pdbg_target *) p9_mi_hw_unit.hw_unit;
        p9_cu[PU_DMI_CHIPUNIT] = (struct pdbg_target *) p9_dmi_hw_unit.hw_unit;
        p9_cu[PU_MCS_CHIPUNIT] = (struct pdbg_target *) p9_mcs_hw_unit.hw_unit;
        p9_cu[PU_MCA_CHIPUNIT] = (struct pdbg_target *) p9_mca_hw_unit.hw_unit;
        p9_cu[PU_MCBIST_CHIPUNIT] = (struct pdbg_target *) p9_mcbist_hw_unit.hw_unit;
        p9_cu[PU_PERV_CHIPUNIT] = (struct pdbg_target *) p9_chiplet_hw_unit.hw_unit;
        p9_cu[PU_PPE_CHIPUNIT] = (struct pdbg_target *) p9_ppe_hw_unit.hw_unit;
        p9_cu[PU_SBE_CHIPUNIT] = (struct pdbg_target *) p9_sbe_hw_unit.hw_unit;
        p9_cu[PU_MC_CHIPUNIT] = (struct pdbg_target *) p9_mc_hw_unit.hw_unit;


	/* Need to initialise the dn_name so pdbg_target_path doesn't segfault */
	((struct pdbg_target *) p9_core_hw_unit.hw_unit)->dn_name = "p9_core";
	((struct pdbg_target *) p9_chiplet_hw_unit.hw_unit)->dn_name = "p9_chiplet";
	((struct pdbg_target *) p9_ex_hw_unit.hw_unit)->dn_name = "p9_ex";
	((struct pdbg_target *) p9_mba_hw_unit.hw_unit)->dn_name = "p9_mba";
	((struct pdbg_target *) p9_mcs_hw_unit.hw_unit)->dn_name = "p9_mcs";
	((struct pdbg_target *) p9_xbus_hw_unit.hw_unit)->dn_name = "p9_xbus";
	((struct pdbg_target *) p9_abus_hw_unit.hw_unit)->dn_name = "p9_abus";
	((struct pdbg_target *) p9_l4_hw_unit.hw_unit)->dn_name = "p9_l4";
	((struct pdbg_target *) p9_eq_hw_unit.hw_unit)->dn_name = "p9_eq";
	((struct pdbg_target *) p9_mca_hw_unit.hw_unit)->dn_name = "p9_mca";
	((struct pdbg_target *) p9_mcbist_hw_unit.hw_unit)->dn_name = "p9_mcbist";
	((struct pdbg_target *) p9_mi_hw_unit.hw_unit)->dn_name = "p9_mi";
	((struct pdbg_target *) p9_dmi_hw_unit.hw_unit)->dn_name = "p9_dmi";
	((struct pdbg_target *) p9_obus_hw_unit.hw_unit)->dn_name = "p9_obus";
	((struct pdbg_target *) p9_obus_brick_hw_unit.hw_unit)->dn_name = "p9_obus_brick";
	((struct pdbg_target *) p9_sbe_hw_unit.hw_unit)->dn_name = "p9_sbe";
	((struct pdbg_target *) p9_ppe_hw_unit.hw_unit)->dn_name = "p9_ppe";
	((struct pdbg_target *) p9_pec_hw_unit.hw_unit)->dn_name = "p9_pec";
	((struct pdbg_target *) p9_phb_hw_unit.hw_unit)->dn_name = "p9_phb";
	((struct pdbg_target *) p9_mc_hw_unit.hw_unit)->dn_name = "p9_mc";
	((struct pdbg_target *) p9_mem_port_hw_unit.hw_unit)->dn_name = "p9_mem_port";
	((struct pdbg_target *) p9_nmmu_hw_unit.hw_unit)->dn_name = "p9_nmmu";
	((struct pdbg_target *) p9_pau_hw_unit.hw_unit)->dn_name = "p9_pau";
	((struct pdbg_target *) p9_iohs_hw_unit.hw_unit)->dn_name = "p9_iohs";
	((struct pdbg_target *) p9_fc_hw_unit.hw_unit)->dn_name = "p9_fc";
	((struct pdbg_target *) p9_pauc_hw_unit.hw_unit)->dn_name = "p9_pauc";

	for (i = 0; i < NONE; i++) {
		if (p9_cu[i])
			for (index = 0; index < MAX_INDEX; index++) {
				printf("Testing %s@%d\n", pdbg_target_path(p9_cu[i]), index);

				/* Test every sat offset */
				for (addr = 0; addr < 0xffffffff; addr += 0x40)
					assert(test_unit_translation(p9_cu[i], (p9ChipUnits_t) i, index, addr));
			}
	}
}
