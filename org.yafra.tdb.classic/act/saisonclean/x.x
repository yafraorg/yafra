	if (status != (int)MPOK || row_cnt == 0) {
		/* ------ commit work ------ */
		(void)MPAPIdb_committrx();
		return status;
	}
