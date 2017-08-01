import json
import argparse
import glob

parser = argparse.ArgumentParser(description='Masscan Parser')
parser.add_argument('-i', '--input', dest='input', required=True, help='Json file to parse')
parser.add_argument('-o', '--output', dest='output', required=True, help='Output CSV')

args = parser.parse_args()

with open(args.output, 'w') as outputFile:
	outputFile.write("IP,Protocol,Status,Reason\n")#Need to investigate Banner Support in Masscan
	for file_path in glob.glob(args.input):#Let glob figure out what the user meant with their fancy input. Could be empty, which would cause the program to exit without issue
		with open(file_path, 'r') as inputFile:
			for record in inputFile:#Json.loads only handles one record at a time
				try:
					data = json.loads(record[:-2]) #Internal Structure is a Dictionary. Removing newline and comma characters
					line = data["ip"] + ","
					line += str(data["ports"][0]["port"]) + ","
					line += data["ports"][0]["proto"] + ","
					line += data["ports"][0]["status"] + ","
					line += data["ports"][0]["reason"] + "\n"
					print(line[:-1])
					outputFile.write(line)
				except:
					print(record[:-1] + " -> Bad Value")#Masscan appends a garbage json value to flag completion
			
