/* version.c - version information */
/* $Id$ */

#include "copyright.h"
#include "autoconf.h"

#include "db.h"
#include "mudconf.h"
#include "alloc.h"
#include "externs.h"
#include "patchlevel.h"

/*
 * TinyMUSH 3.0
 */

/*
 * 2.0
 * All known bugs fixed with disk-based.  Played with gdbm, it
 * sucked.  Now using bsd 4.4 hash stuff.
 */

/*
 * 1.12
 * * All known bugs fixed after several days of debugging 1.10/1.11.
 * * Much string-handling braindeath patched, but needs a big overhaul,
 * * really.   GAC 2/10/91
 */

/*
 * 1.11
 * * Fixes for 1.10.  (@name didn't call do_name, etc.)
 * * Added dexamine (debugging examine, dumps the struct, lots of info.)
 */

/*
 * 1.10
 * * Finally got db2newdb working well enough to run from the big (30000
 * * object) db with ATR_KEY and ATR_NAME defined.   GAC 2/3/91
 */

/*
 * TinyMUSH version.c file.  Add a comment here any time you've made a
 * * big enough revision to increment the TinyMUSH version #.
 */

void do_version(player, cause, extra)
dbref player, cause;
int extra;
{
	char *buff;

	notify(player, mudstate.version);
	buff = alloc_lbuf("do_version");
	sprintf(buff, "Build date: %s", MUSH_BUILD_DATE);
	notify(player, buff);
	if (Wizard(player)) {
	    sprintf(buff, "Build info: %s", mudstate.buildinfo);
	    notify(player, buff);
	}
	free_lbuf(buff);
}

void NDECL(init_version)
{
#ifdef BETA
#if PATCHLEVEL > 0
	sprintf(mudstate.version, "TinyMUSH Beta version %s patchlevel %d #%s",
		MUSH_VERSION, PATCHLEVEL, MUSH_BUILD_NUM);
	sprintf(mudstate.short_ver, "TinyMUSH Beta %s.p%d",
		MUSH_VERSION, PATCHLEVEL);
#else
	sprintf(mudstate.version, "TinyMUSH Beta version %s #%s",
		MUSH_VERSION, MUSH_BUILD_NUM);
	sprintf(mudstate.short_ver, "TinyMUSH Beta %s",
		MUSH_VERSION);
#endif /*
        * PATCHLEVEL 
        */
#else /*
       * not BETA 
       */
#if PATCHLEVEL > 0
	sprintf(mudstate.version, "TinyMUSH version %s patchlevel %d #%s [%s]",
		MUSH_VERSION, PATCHLEVEL, MUSH_BUILD_NUM, MUSH_RELEASE_DATE);
	sprintf(mudstate.short_ver, "TinyMUSH %s.p%d",
		MUSH_VERSION, PATCHLEVEL);
#else
	sprintf(mudstate.version, "TinyMUSH version %s #%s [%s]",
		MUSH_VERSION, MUSH_BUILD_NUM, MUSH_RELEASE_DATE);
	sprintf(mudstate.short_ver, "TinyMUSH %s",
		MUSH_VERSION);
#endif /*
        * PATCHLEVEL 
        */
#endif /*
        * BETA 
        */
	sprintf(mudstate.buildinfo, "%s %s",
		MUSH_BUILD_COMPILER, MUSH_BUILD_CFLAGS);
	STARTLOG(LOG_ALWAYS, "INI", "START")
		log_text((char *)"Starting: ");
		log_text(mudstate.version);
	ENDLOG
	STARTLOG(LOG_ALWAYS, "INI", "START")
		log_text((char *)"Build date: ");
		log_text((char *)MUSH_BUILD_DATE);
	ENDLOG
	STARTLOG(LOG_ALWAYS, "INI", "START")
		log_text((char *)"Build info: ");
		log_text(mudstate.buildinfo);
	ENDLOG
}
