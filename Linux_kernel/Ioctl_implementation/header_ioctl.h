/*
 * header_ioctl.h
 *
 * Description: http://opensourceforu.com/2011/08/io-control-in-linux/
 *              Anil Kumar Pugalia
 *
 *  Created on: 29-Apr-2020
 *      Author: Sunil Sharma P <sunilsharma.pv@gmail.com>
 *
 *     Version: 1.0v
 */

#ifndef HEADER_IOCTL_H_
#define HEADER_IOCTL_H_

#include <linux/ioctl.h>

typedef struct {
	int status;
	int dignity;
	int ego;
} query_arg_t;

#define QUERY_GET_VARIABLES _IOR('q', 1, query_arg_t *)
#define QUERY_SET_VARIABLES _IOW('q', 3, query_arg_t *)
#define QUERY_CLR_VARIABLES _IO('q', 2)

#endif /* HEADER_IOCTL_H_ */
