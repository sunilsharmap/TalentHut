#!/usr/bin/env python
# Python program to convert JSON file to CSV
# author: Sunil Sharma P <sunilsharma.pv@gmail.com>

import json  # For parsing json file
import csv  # For creating csv file
import argparse  # For parsing command line arguments

# /home/sunilsp/Documents/json2csv/json_file.json
# /home/sunilsp/Documents/json2csv/Comments_CVS_File.csv
#
# Command Running:
# python convert_json_to_csv.py -i <path to json>/Json_file.json \
#                               -o <path to out csv>/Comments_CVS_File.csv

# Parsed arguments
args = {}


# For Type of Errors
class ErrorType:
    INFO = 0x1,
    WARN = 0x2,
    ERR = 0x3


# For colour print
class TermColors:
    BLACK_CLR = '\033[0;30m'
    RED_CLR = '\033[0;31m'
    GREEN_CLR = '\033[0;32m'
    BROWN_CLR = '\033[0;33m'
    BLUE_CLR = '\033[0;34m'
    PURPLE_CLR = '\033[0;35m'
    CYAN_CLR = '\033[0;36m'
    BOLD_CLR = '\033[1m'
    END_CLR = '\033[0m'


def print_msg(msg_type, msg):
    if msg_type == ErrorType.INFO:
		"""for printing info message"""
        print(TermColors.GREEN_CLR + TermColors.BOLD_CLR + msg + TermColors.END_CLR)
    if msg_type == ErrorType.WARN:
		"""for printing warning message"""
        print(TermColors.BROWN_CLR + TermColors.BOLD_CLR + msg + TermColors.END_CLR)
    if msg_type == ErrorType.ERR:
		"""for printing error message"""
        print(TermColors.RED_CLR + TermColors.BOLD_CLR + msg + TermColors.END_CLR)


def parse_arguments():
    """Parsing command line arguments"""
    global args
    parser = argparse.ArgumentParser()
    parser.add_argument('-i', metavar='input-json-file', required=True, help='Input json file to be converted to csv')
    parser.add_argument('-o', metavar='output-csv-file', required=True, help='Output converted csv file')
    args = vars(parser.parse_args())  # This makes args a dictionary


def convert_json2csv(input_json_file, output_csv_file):
    # Open Json file which you need to extract to csv
    with open(input_json_file) as json_file:
        json_data = json.load(json_file)

    # Extract Json data
    comments_data = json_data["comments"]

    # Open csv file to write json into it
    csv_file = open(output_csv_file, "w")

    # create the csv writer object
    csv_data = csv.writer(csv_file)

    # Write the Header row first
    csv_data.writerow(["id", "type", "author_id", "body", "location", "url"])  # You can add other items as well

    # Write each comments to the nex rows
    for json_element in comments_data:
        attachments = " NA "
        # Check whether attachment present in json or not, proceed only if present, else write NA
        if json_element["attachments"]:
            attachments = json_element["attachments"][0]["url"]
        csv_data.writerow([json_element["id"]
                              , json_element["type"]
                              , json_element["author_id"]
                              , json_element["body"]
                              , json_element["metadata"]["system"]["location"]
                              , attachments])  # You can extend this for example 'html_body' or 'plain_body'

    # Close the opened csv_file
    csv_file.close()


if __name__ == '__main__':
    parse_arguments()
    convert_json2csv(args['i'], args['o'])
    print_msg(ErrorType.INFO, "\nCSV file Saved \"" + args['o'] + "\"\n")
