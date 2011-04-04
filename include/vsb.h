/*-
 * Copyright (c) 2000-2008 Poul-Henning Kamp
 * Copyright (c) 2000-2008 Dag-Erling Coïdan Smørgrav
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer
 *    in this position and unchanged.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *      $FreeBSD: head/sys/sys/sbuf.h 212425 2010-09-10 16:42:16Z mdf $
 */

#ifndef VSB_H_INCLUDED
#define VSB_H_INCLUDED

#include <sys/types.h>

/*
 * Structure definition
 */
struct vsb {
	unsigned	s_magic;
	char		*s_buf;		/* storage buffer */
	int		 s_error;	/* current error code */
	ssize_t		 s_size;	/* size of storage buffer */
	ssize_t		 s_len;		/* current length of string */
#define	VSB_FIXEDLEN	0x00000000	/* fixed length buffer (default) */
#define	VSB_AUTOEXTEND	0x00000001	/* automatically extend buffer */
#define	VSB_USRFLAGMSK	0x0000ffff	/* mask of flags the user may specify */
#define	VSB_DYNAMIC	0x00010000	/* s_buf must be freed */
#define	VSB_FINISHED	0x00020000	/* set by vsb_finish() */
#define	VSB_DYNSTRUCT	0x00080000	/* vsb must be freed */
	int		 s_flags;	/* flags */
};

#ifdef __cplusplus
extern "C" {
#endif
/*
 * API functions
 */
struct vsb	*vsb_new(struct vsb *, char *, int, int);
#define		 vsb_new_auto()				\
	vsb_new(NULL, NULL, 0, VSB_AUTOEXTEND)
void		 vsb_clear(struct vsb *);
int		 vsb_setpos(struct vsb *, ssize_t);
int		 vsb_bcat(struct vsb *, const void *, size_t);
int		 vsb_bcpy(struct vsb *, const void *, size_t);
int		 vsb_cat(struct vsb *, const char *);
int		 vsb_cpy(struct vsb *, const char *);
int		 vsb_printf(struct vsb *, const char *, ...)
	__printflike(2, 3);
#ifdef va_start
int		 vsb_vprintf(struct vsb *, const char *, va_list)
	__printflike(2, 0);
#endif
int		 vsb_putc(struct vsb *, char);
int		 vsb_trim(struct vsb *);
int		 vsb_error(const struct vsb *);
int		 vsb_finish(struct vsb *);
char		*vsb_data(struct vsb *);
ssize_t		 vsb_len(struct vsb *);
int		 vsb_done(const struct vsb *);
void		 vsb_delete(struct vsb *);
void		 vsb_quote(struct vsb *s, const char *p, int len, int how);
const char	*vsb_unquote(struct vsb *s, const char *p, int len, int how);
#ifdef __cplusplus
};
#endif

#endif
