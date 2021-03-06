#include "build_factory.h"

#include "ziplist.h"

int
build_zl_hash_value(rdb_parser_t *rp, rdb_object_builder_t *ob, bip_buf_t *bb, rdb_kv_chain_t **vall, size_t *size)
{
    int rc = 0;

    /* val */
    rc = build_string_value(rp, ob, bb, &ob->tmp_val);

    /* over */
    if (rc == OB_OVER) {
        load_ziplist_hash_or_zset(rp, ob->tmp_val.data, vall, size);

        nx_pfree(rp->o_pool, ob->tmp_val.data);
        nx_str_null(&ob->tmp_val);
    }
    return rc;
}
