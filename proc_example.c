/* proc_example.c
 * Author: Kiran Kankipati
 * Updated: 22-feb-2017
 * Discussed in the YouTube Episode: https://youtu.be/1gjW5krYpEU
 */
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/module.h> 
#include <linux/errno.h>
#include <linux/slab.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/skbuff.h>  
#include <linux/udp.h>
#include <linux/ip.h>
#include <linux/in.h>
#include <linux/string.h>
#include <linux/init.h>
#include <linux/net.h>
#include <linux/netdevice.h>
#include <linux/socket.h>
#include <linux/sockios.h>
#include <linux/inet.h>
#include <linux/inetdevice.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/if_arp.h>
#include <linux/icmp.h>
#include <linux/proc_fs.h>
#include <linux/netlink.h>
#include <linux/mroute.h>
#include <net/checksum.h>
#include <net/inet_ecn.h>
#include <net/xfrm.h>
#include <net/route.h>
#include <net/sock.h>
#include <net/ip.h>
#include <net/tcp.h>
#include <net/arp.h>
#include <net/udp.h>
#include <net/icmp.h>
#include <net/inetpeer.h>
#include <net/protocol.h>
#include <net/flow.h>
#include <asm/types.h>

struct proc_dir_entry *tlc_proc_a;

static ssize_t tlc_proc_a_read(struct file *fp, char *buf, size_t len, loff_t * off)
{	static int finished=0; if(finished) {finished=0;return 0;} finished=1;
	//int abc=100;
	//strcpy(buf, "abc: %d\n", abc);
	//sprintf(buf, "abc: %d\n", abc);
	memset(buf,0xaa,10);
	//return strlen(buf);
	return 10;
}

static struct file_operations tlc_proc_a_fops = { .owner=THIS_MODULE, .read=tlc_proc_a_read, };

static int hello_init(void)
{
 	tlc_proc_a = proc_create( "tlc_proc_a", 0444, NULL, &tlc_proc_a_fops); 
 	if(tlc_proc_a==NULL) {	printk(KERN_ALERT "Error: Could not initialize %s\n", "tlc_proc_a"); }
	
	return 0;
}

static void hello_exit(void) 
{  remove_proc_entry("tlc_proc_a", NULL);
}

module_init(hello_init);
module_exit(hello_exit);
