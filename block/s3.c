#include "qemu/osdep.h"


#include "block/block-io.h"
#include "block/block_int.h"
#include "block/qdict.h"
#include "qapi/error.h"
#include "qemu/error-report.h"
#include "qemu/module.h"
#include "qemu/option.h"
#include "qemu/ctype.h"
#include "qemu/cutils.h"
#include "qemu/sockets.h"
#include "qemu/uri.h"
/*
#include "qapi/qapi-visit-sockets.h"
#include "qapi/qapi-visit-block-core.h"
#include "qapi/qmp/qdict.h"
#include "qapi/qmp/qstring.h"
#include "qapi/qobject-input-visitor.h"
#include "qapi/qobject-output-visitor.h"
#include "trace.h"
*/

typedef struct BDRVS3State {
} BDRVS3State;

static QemuOptsList s3_create_opts = {
    .name = "ssh-s3_create_opts-opts",
    .head = QTAILQ_HEAD_INITIALIZER(s3_create_opts.head),
    .desc = {
        {
            .name = BLOCK_OPT_SIZE,
            .type = QEMU_OPT_SIZE,
            .help = "Virtual disk size"
        },
        { /* end of list */ }
    }
};

static const char *const s3_strong_runtime_opts[] = {
    /*
    "host",
    "port",
    "path",
    "user",
    "host_key_check",
    "server.",
    */
    NULL
};

static BlockDriver bdrv_s3 = {
    .format_name                  = "s3",
    .protocol_name                = "s3",
    .instance_size                = sizeof(BDRVS3State),
    .bdrv_parse_filename          = s3_parse_filename,
    .bdrv_file_open               = s3_file_open,
    .bdrv_co_create               = s3_co_create,
    .bdrv_co_create_opts          = s3_co_create_opts,
    .bdrv_close                   = s3_close,
    .bdrv_has_zero_init           = s3_has_zero_init,
    .bdrv_co_readv                = s3_co_readv,
    .bdrv_co_writev               = s3_co_writev,
    .bdrv_co_getlength            = s3_co_getlength,
    .bdrv_co_truncate             = s3_co_truncate,
    .bdrv_co_flush_to_disk        = s3_co_flush,
    .bdrv_refresh_filename        = s3_refresh_filename,
    .bdrv_dirname                 = s3_bdrv_dirname,
    .create_opts                  = &s3_create_opts,
    .strong_runtime_opts          = s3_strong_runtime_opts,
};

static void s3_parse_filename(const char *filename, QDict *options,
                               Error **errp) {

                               }

static int s3_file_open(BlockDriverState *bs, QDict *options, int bdrv_flags,
                         Error **errp) {
    return 0;
}

static int s3_co_create(BlockdevCreateOptions *options, Error **errp)
{
    return 0;
}

static int coroutine_fn s3_co_create_opts(BlockDriver *drv,
                                           const char *filename,
                                           QemuOpts *opts,
                                           Error **errp)
{
    return 0;
}

static void s3_close(BlockDriverState *bs)
{
}

static int s3_has_zero_init(BlockDriverState *bs)
{
    return 0;
}

static coroutine_fn int s3_co_readv(BlockDriverState *bs,
                                     int64_t sector_num,
                                     int nb_sectors, QEMUIOVector *qiov)
{
    return ret;
}

static coroutine_fn int s3_co_writev(BlockDriverState *bs,
                                      int64_t sector_num,
                                      int nb_sectors, QEMUIOVector *qiov,
                                      int flags)
{
    return ret;
}

static int64_t coroutine_fn s3_co_getlength(BlockDriverState *bs)
{
    return 0;
}

static int coroutine_fn s3_co_truncate(BlockDriverState *bs, int64_t offset,
                                        bool exact, PreallocMode prealloc,
                                        BdrvRequestFlags flags, Error **errp)
{
    return 0;
}

static coroutine_fn int s3_co_flush(BlockDriverState *bs)
{
    return ret;
}

static void s3_refresh_filename(BlockDriverState *bs)
{
}

static char *s3_bdrv_dirname(BlockDriverState *bs, Error **errp)
{
    return NULL;
}