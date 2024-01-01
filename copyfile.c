/*
 * Copyright (c) 2004-2020 Apple, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */

#include <copyfile.h>
#include <err.h>
#include <stdio.h>
#include <stdbool.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <xattr_flags.h>

#define qtn_file_t void *

struct _copyfile_state
{
        char *src;
        char *dst;
        int src_fd;
        int dst_fd;
        struct stat sb;
        filesec_t fsec;
        copyfile_flags_t flags;
        unsigned int internal_flags;
        void *stats;
        uint32_t debug;
        copyfile_callback_t statuscb;
        void *ctx;
        qtn_file_t qinfo;
        filesec_t original_fsec;
        filesec_t permissive_fsec;
        off_t totalCopied;
        int err;
        char *xattr_name;
        xattr_operation_intent_t copyIntent;
        bool was_cloned;
        bool set_dst_perms;
        bool forbid_cross_mount;
        uint32_t src_bsize;
        uint32_t dst_bsize;
};

#define COPYFILE_DEBUG (1<<31)
#define COPYFILE_OPTION(x) { #x, COPYFILE_ ## x },

struct {char *name; int value;} opts[] = {
        COPYFILE_OPTION(ACL)
        COPYFILE_OPTION(STAT)
        COPYFILE_OPTION(XATTR)
        COPYFILE_OPTION(DATA)
        COPYFILE_OPTION(SECURITY)
        COPYFILE_OPTION(METADATA)
        COPYFILE_OPTION(ALL)
        COPYFILE_OPTION(NOFOLLOW_SRC)
        COPYFILE_OPTION(NOFOLLOW_DST)
        COPYFILE_OPTION(NOFOLLOW)
        COPYFILE_OPTION(EXCL)
        COPYFILE_OPTION(MOVE)
        COPYFILE_OPTION(UNLINK)
        COPYFILE_OPTION(PACK)
        COPYFILE_OPTION(UNPACK)
        COPYFILE_OPTION(CHECK)
        COPYFILE_OPTION(CLONE)
        COPYFILE_OPTION(CLONE_FORCE)
        COPYFILE_OPTION(VERBOSE)
        COPYFILE_OPTION(RECURSIVE)
        COPYFILE_OPTION(DATA_SPARSE)
        COPYFILE_OPTION(RUN_IN_PLACE)
        COPYFILE_OPTION(PRESERVE_DST_TRACKED)
        {NULL, 0}
};

int main(int argc, char *argv[])
{
        int i, ret;
        int flags = 0;
        copyfile_state_t state = NULL;

        if (argc < 3)
                errx(1, "usage: src dst [flags...]");

        while(argc-- > 3)
        {
                for (i = 0; opts[i].name != NULL; ++i)
                {
                        if (strcasecmp(opts[i].name, argv[argc]) == 0)
                        {
                                printf("option %d: %s <- %d\n", argc, opts[i].name, opts[i].value);
                                flags |= opts[i].value;
                                break;
                        }
                }
        }

        if (flags & COPYFILE_DEBUG) {
                state = copyfile_state_alloc();
                state->debug = 10; // Turn on all debug statements
        }
        ret = copyfile(argv[1], argv[2], state, flags);
        if (state) {
                (void)copyfile_state_free(state);
        }

        return ret;
}
