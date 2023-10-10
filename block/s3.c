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
/*
#include <aws/auth/credentials.h>
#include <aws/common/command_line_parser.h>
#include <aws/common/condition_variable.h>
#include <aws/common/mutex.h>
#include <aws/common/zero.h>
#include <aws/io/channel_bootstrap.h>
#include <aws/io/event_loop.h>
#include <aws/io/logging.h>
#include <aws/io/uri.h>
*/

typedef struct BDRVS3State {
} BDRVS3State;

static QemuOptsList s3_create_opts = {
    .name = "s3-create-opts",
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
                               Error **errp) 
{
}

static int s3_file_open(BlockDriverState *bs, QDict *options, int bdrv_flags,
                         Error **errp) 
{
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
    return 0;
}

static coroutine_fn int s3_co_writev(BlockDriverState *bs,
                                      int64_t sector_num,
                                      int nb_sectors, QEMUIOVector *qiov,
                                      int flags)
{
    return 0;
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
    return 0;
}

static void s3_refresh_filename(BlockDriverState *bs)
{
}

static char *s3_bdrv_dirname(BlockDriverState *bs, Error **errp)
{
    return NULL;
}

static int s3_init(void)
{
    struct aws_allocator *allocator = aws_default_allocator();
    aws_s3_library_init(allocator);

    struct app_ctx app_ctx;
    AWS_ZERO_STRUCT(app_ctx);
    app_ctx.allocator = allocator;
    app_ctx.c_var = (struct aws_condition_variable)AWS_CONDITION_VARIABLE_INIT;
    aws_mutex_init(&app_ctx.mutex);

    /* event loop */
    struct aws_event_loop_group *event_loop_group = aws_event_loop_group_new_default(allocator, 0, NULL);

    /* resolver */
    struct aws_host_resolver_default_options resolver_options = {
        .el_group = event_loop_group,
        .max_entries = 8,
    };
    struct aws_host_resolver *resolver = aws_host_resolver_new_default(allocator, &resolver_options);

    /* client bootstrap */
    struct aws_client_bootstrap_options bootstrap_options = {
        .event_loop_group = event_loop_group,
        .host_resolver = resolver,
    };
    app_ctx.client_bootstrap = aws_client_bootstrap_new(allocator, &bootstrap_options);
    if (app_ctx.client_bootstrap == NULL) {
        printf("ERROR initializing client bootstrap\n");
        return -1;
    }

    /* credentials */
    struct aws_credentials_provider_chain_default_options credentials_provider_options;
    AWS_ZERO_STRUCT(credentials_provider_options);
    credentials_provider_options.bootstrap = app_ctx.client_bootstrap;
    app_ctx.credentials_provider = aws_credentials_provider_new_chain_default(allocator, &credentials_provider_options);

    return 0;
}

static void bdrv_s3_init(void)
{
    int r;
    r = s3_init();
    if (r != 0) {
        fprintf(stderr, "libaws-c-s3 initialization failed, %d\n", r);
        exit(EXIT_FAILURE);
    }

    bdrv_register(&bdrv_s3);
}

block_init(bdrv_s3_init);