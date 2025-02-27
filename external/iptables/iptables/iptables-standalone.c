/*
 * Author: Paul.Russell@rustcorp.com.au and mneuling@radlogic.com.au
 *
 * Based on the ipchains code by Paul Russell and Michael Neuling
 *
 * (C) 2000-2002 by the netfilter coreteam <coreteam@netfilter.org>:
 * 		    Paul 'Rusty' Russell <rusty@rustcorp.com.au>
 * 		    Marc Boucher <marc+nf@mbsi.ca>
 * 		    James Morris <jmorris@intercode.com.au>
 * 		    Harald Welte <laforge@gnumonks.org>
 * 		    Jozsef Kadlecsik <kadlec@blackhole.kfki.hu>
 *
 *	iptables -- IP firewall administration for kernels with
 *	firewall table (aimed for the 2.3 kernels)
 *
 *	See the accompanying manual page iptables(8) for information
 *	about proper usage of this program.
 *
 *	This program is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 2 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program; if not, write to the Free Software
 *	Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <iptables.h>
#include "iptables-multi.h"

int
iptables_main(int argc, char *argv[])
{
	int ret;
	char *table = "filter";
	struct xtc_handle *handle = NULL;

	signal(SIGPIPE, SIG_IGN);

	iptables_globals.program_name = "iptables";
	ret = xtables_init_all(&iptables_globals, NFPROTO_IPV4);
	if (ret < 0) {
		fprintf(stderr, "%s/%s Failed to initialize xtables\n",
				iptables_globals.program_name,
				iptables_globals.program_version);
				exit(1);
	}
#if defined(ALL_INCLUSIVE) || defined(NO_SHARED_LIBS)
	init_extensions();
	init_extensions4();
#endif
   //gaorw1 20150528 add for net rule start
	fprintf(stdout,"\n\r%d  %s\n\r",argc,argv[8]);
	if(argc==13&&strncmp(argv[7],"-uidgroup\0",9)==0){
		fprintf(stdout,"%s\n\r","getMyOpt");
		char *ptr,*p, sp = '+';
		int offset = 0;
		char dest[10] = "\0";
		p = argv[8];
		do{
			ptr =  strchr(p,sp);
			if(ptr){
				offset = ptr-p;
				fprintf(stdout,"%s %d\n\r","<--offset=",offset);
				strncpy(dest,p,offset);
				//strcat(dest,"\0");
				dest[offset] = '\0';
				fprintf(stdout,"%s\n\r",dest);
				argv[7] = "--uid-owner\0";
				argv[8] = dest;
				ret = do_command4(argc, argv, &table, &handle, false);
				p = ptr+1;
			}
		}while(ptr);
		if(p){
			argv[7] = "--uid-owner\0";
			argv[8] = p;
			fprintf(stdout,"%s\n\r",p);
			ret = do_command4(argc, argv, &table, &handle, false);
		}
		if (ret) {
				ret = iptc_commit(handle);
				iptc_free(handle);
		}
		
	}else{
		ret = do_command4(argc, argv, &table, &handle, false);
		if (ret) {
			ret = iptc_commit(handle);
			iptc_free(handle);
		}
	}
     //gaorw1 20150528 add for net rule end
	if (!ret) {
		if (errno == EINVAL) {
			fprintf(stderr, "iptables: %s. "
					"Run `dmesg' for more information.\n",
				iptc_strerror(errno));
		} else {
			fprintf(stderr, "iptables: %s.\n",
				iptc_strerror(errno));
		}
		if (errno == EAGAIN) {
			exit(RESOURCE_PROBLEM);
		}
	}

	exit(!ret);
}
