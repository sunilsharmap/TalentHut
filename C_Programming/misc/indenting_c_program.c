/*
 * test.c
 *
 *  Created on: 28-Aug-2015
 *      Author: sunilpatlamane
 *     version: v 1.00
 *
 *
 * indenting the c-program
 */


#include <stdio.h>

int open_paranthes[10] = {0};
int paranthes_count = 0;

int open_ls_gr[10] = {0};
int ls_gr_count = 0;

int open_apostrophe = 0x0000;

int open_quote = 0x0000;

int main()
{
	FILE *in_fp;
	FILE *out_fp;
	char ch;
	in_fp = fopen("in_file.txt", "r");
	out_fp = fopen("out_file.txt", "w");
	printf("in_file Reading.....\n");
	while( (ch = getc(in_fp)) != '~'){
		switch(ch){
		case ';':
			fputc(ch, out_fp);
			if(!open_paranthes[paranthes_count] && !open_apostrophe && !open_quote){
				fputc('\n', out_fp);
			}
			break;
		case '{':
			fputc(ch, out_fp);
			if(!open_paranthes[paranthes_count] && !open_apostrophe && !open_quote){
				fputc('\n', out_fp);
			}
			break;
		case '}':
			fputc(ch, out_fp);
			if(!open_paranthes[paranthes_count] && !open_apostrophe && !open_quote){
				fputc('\n', out_fp);
			}
			break;
		case '(':
			fputc(ch, out_fp);
			if(!open_paranthes[paranthes_count] && !open_apostrophe && !open_quote){
				open_paranthes[++paranthes_count] = 1;
			}
			break;
		case ')':
			fputc(ch, out_fp);
			open_paranthes[paranthes_count--] = 0;
			break;
		case '>':
			fputc(ch, out_fp);
			open_ls_gr[ls_gr_count--] = 0;
			if(!open_paranthes[paranthes_count] && !open_apostrophe && !open_quote){
				fputc('\n', out_fp);
			}
			break;
		case 0x0027:	/*apostrophe*/
			fputc(ch, out_fp);
			open_apostrophe = (open_apostrophe ^ 0xfff0);
			break;
		case '"':	/*double quote*/
			fputc(ch, out_fp);
			if(!open_paranthes[paranthes_count] && !open_apostrophe && !open_quote){
				open_quote = (open_quote ^ 0xfff0);
			}
			break;
		default:
			fputc(ch, out_fp);
			break;
		}
		}
	fclose(in_fp);
	fclose(out_fp);
	printf("...\n...\n...\n...\n....\nFile Indented.....\nReady to use.....\n");
	return 0;
}
