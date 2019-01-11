import sys

if len(sys.argv) != 2:
	print("Usage: python buildcml.py <cml file>")
	exit(1)

infile  = sys.argv[1]

# file names
outfile_md = "docs/" + infile.split(".")[0] + ".md"
outfile_txt = infile.split(".")[0] + ".txt"

# file buffers
md_buffer = ""
txt_buffer = ""

with open(infile, "r") as f:
	cml = eval(f.read())
	f.close()

for controller in cml:
	print(f"Parsing {controller} controller")
	# add data to buffers
	md_buffer += f"# {controller}\nType: {cml[controller]['Type']}\n\nPort: {cml[controller]['Port']}\n|  |  |\n| -- | -- |\n"
	txt_buffer += f"-- {controller} --\nType: {cml[controller]['Type']}\nPort: {cml[controller]['Port']}\n"
	
	# parse through inputs
	for input_type in cml[controller]:
		if type(cml[controller][input_type]) != type({}):
			# Skip non iterable items
			continue
		# add data to buffers
		md_buffer += f"| {input_type} |  |\n"
		txt_buffer += f" {input_type}:\n"
		
		# parse items
		for item in cml[controller][input_type]:
			# deal with extra nesting
			if type(cml[controller][input_type][item]) == type({}):
				md_buffer += f"| {item} |  |\n"
				txt_buffer += f"  {item}:\n"
				for subitem in cml[controller][input_type][item]:
					md_buffer += f"| {subitem} | {cml[controller][input_type][item][subitem]} |\n"
					txt_buffer += f"   {subitem}: {cml[controller][input_type][item][subitem]}\n"
				continue
			# add data to buffers
			md_buffer += f"| {item} | {cml[controller][input_type][item]} |\n"
			txt_buffer += f"  {item}: {cml[controller][input_type][item]}\n"
	print("Done.")

print("Writing to files...")
with open(outfile_txt, "w") as f:
	f.writelines(txt_buffer)
	f.close()

with open(outfile_md, "w") as f:
	f.writelines(md_buffer)
	f.close

print("Done.")