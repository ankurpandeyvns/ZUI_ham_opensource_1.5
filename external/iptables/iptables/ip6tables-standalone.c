/*
 * Author: Paul.Russell@rustcorp.com.au and mneuling@radlogic.com.au
 *
 * (C) 2000-2002 by the netfilter coreteam <coreteam@netfilter.org>:
 * 		    Paul 'Rusty' Russell <rusty@rustcorp.com.au>
 * 		    Marc Boucher <marc+nf@mbsi.ca>
 * 		    James Morris <jmorris@intercode.com.au>
 * 		    Harald Welte <laforge@gnumonks.org>
 * 		    Jozsef Kadlecsik <kadlec@blackhole.kfki.hu>
 *
 * Based on the ipchains code by Paul Russell and Michael Neuling
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
#include <ip6tables.h>
#include "ip6tables-multi.h"

int
ip6tables_main(int argc, char *argv[])
{
	int ret;
	char *table = "filter";
	struct xtc_handle *handle = NULL;

	ip6tables_globals.program_name = "ip6tables";
	ret = xtables_init_all(&ip6tables_globals, NFPROTO_IPV6);
	if (ret < 0) {
		fprintf(stderr, "%s/%s Failed to initialize xtables\n",
				ip6tables_globals.program_name,
				ip6tables_globals.program_version);
		exit(1);
	}

#if defined(ALL_INCLUSIVE) || defined(NO_SHARED_LIBS)
	init_extensions();
	init_extensions6();
#endif
	 //gaorw1 20150603 add for net rule start
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
				ret = do_command6(argc, argv, &table, &handle, false);
				p = ptr+1;
			}
		}while(ptr);
		if(p){
			argv[7] = "--uid-owner\0";
			argv[8] = p;
			fprintf(stdout,"%s\n\r",p);
			ret = do_command6(argc, argv, &table, &handle, false);
		}
		if (ret) {
				ret = ip6tc_commit(handle);
				ip6tc_free(handle);
		}
		
	}else{
		ret = do_command6(argc, argv, &table, &handle, false);
		if (ret) {
			ret = ip6tc_commit(handle);
			ip6tc_free(handle);
		}
	}
     //gaorw1 20150603 add for net rule end

	if (!ret) {
		if (errno == EINVAL) {
			fprintf(stderr, "ip6tables: %s. "
					"Run `dmesg' for more information.\n",
				ip6tc_strerror(errno));
		} else {
			fprintf(stderr, "ip6tables: %s.\n",
				ip6tc_strerror(errno));
		}
	}

	exit(!ret);
}
